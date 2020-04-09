#include "imagetopdfdialog.h"
#include "utils.h"
#include "globalEnums.h"
#include <Magick++.h>

#include <iostream>
#include <qstringlist.h>
#include <qfiledialog.h>
#include <qlistwidget.h>

QTableWidgetItem* CreateNameItem(const QString& str)
{
  auto* item = new QTableWidgetItem(QFileInfo(str).fileName());
  item->setToolTip(str);
  return item;
}

QComboBox* CreateRotateComboBox()
{
  auto* box = new QComboBox();
  box->addItem("0");
  box->addItem("90");
  box->addItem("180");
  box->addItem("270");
  return box;
}

QSlider* CreateScaleSlider()
{
  auto slider = new QSlider(Qt::Orientation::Horizontal);
  slider->setMaximum(100);
  slider->setMinimum(1);
  slider->setValue(100);
  return slider;
}

ImageToPDF::ImageToPDFForm::ImageToPDFForm(QDialog *parent) : QDialog(parent)
{
  m_UiForm.setupUi(this);

  m_UiForm.comboBox->addItem("PDF");
  m_UiForm.comboBox->addItem("PNG");

  //connect(m_UiForm.plusButton, SIGNAL(clicked()), SLOT(AddElement() ) );
//  connect(m_UiForm.plusButton, &QAbstractButton::clicked, this, &ImageToPDFForm::AddElement);


  //connect(m_UiForm.InputFiles, SIGNAL(itemClicked(QTableWidgetItem*)), SLOT(itemClicked(QTableWidgetItem *)));
  connect(m_UiForm.InputFiles, SIGNAL(cellClicked(int, int)), SLOT(itemClicked(int, int)));
}

void ImageToPDF::ImageToPDFForm::ImagePreview(QString name, int rotate)
{
  QPixmap pixmap(name);
  pixmap = pixmap.scaled(pixmap.size() * 0.1);

  QTransform transform;
  QTransform trans = transform.rotate(rotate);
  pixmap = pixmap.transformed(trans);
  m_UiForm.ImagePreview->setPixmap(pixmap);
  m_UiForm.ImagePreview->resize(pixmap.size());
}

void ImageToPDF::ImageToPDFForm::on_plusButton_clicked()
{
  DebugOutput("aaa");

  QFileDialog dialog(this);
  dialog.setFileMode(QFileDialog::ExistingFiles);
  dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg *.bmp *.gif *.tiff)"));

  QStringList filenames;
  if (dialog.exec())
      filenames = dialog.selectedFiles();

  int ind = m_UiForm.InputFiles->rowCount();
  for(const QString& str : filenames)
  {    
    m_UiForm.InputFiles->insertRow(m_UiForm.InputFiles->rowCount() );
    m_UiForm.InputFiles->setItem(ind, 0, CreateNameItem(str));
    m_UiForm.InputFiles->setCellWidget(ind, 1, CreateRotateComboBox());
    m_UiForm.InputFiles->setCellWidget(ind, 2, CreateScaleSlider());
    ++ind;
  }

  if(!filenames.empty())
  {
    if(m_UiForm.comboBox->currentIndex() == static_cast<int>(ListOfConverters::PDF) )
    {
      m_UiForm.OutputFiles->clear();
      QString file = "/tmp/output.pdf";
      QListWidgetItem* item = new QListWidgetItem(QFileInfo(file).fileName(), m_UiForm.OutputFiles);
      item->setToolTip(file);
    }
  }

}

void ImageToPDF::ImageToPDFForm::on_removeAllButton_clicked()
{
    m_UiForm.InputFiles->clear();
    m_UiForm.OutputFiles->clear();
}

void ImageToPDF::ImageToPDFForm::on_buttonBox_clicked(QAbstractButton* btn)
{
    DebugOutput("aaa12");

    const auto* listWidget = m_UiForm.InputFiles;
    std::vector<Magick::Image> ims(listWidget->rowCount());

    for(int row = 0; row < listWidget->rowCount(); row++)
    {
        auto *item = listWidget->item(row,0);
        ims[row].read(item->toolTip().toStdString());

        int rotate = 0;
        QWidget* wdg = listWidget->cellWidget(row,1);
        if( QComboBox* item2 = dynamic_cast<QComboBox*>(wdg) )
        {
           rotate = item2->currentText().toInt();
        }

        ims[row].rotate(rotate);

        //ims[row].resize("30%");
    }


    //output.magick("PDF");
    //output.write(argv[2]);

    Magick::writeImages(ims.begin(), ims.end(), m_UiForm.OutputFiles->item(0)->toolTip().toStdString());

    std::system("okular /tmp/output.pdf");
}

void ImageToPDF::ImageToPDFForm::on_buttonBox_rejected()
{
  //QPushButton *ab = dynamic_cast<QPushButton*>(button);
  DebugOutput("aaa1");
}

void ImageToPDF::ImageToPDFForm::itemClicked(QTableWidgetItem *item)
{
  DebugOutput("aaa1");
  auto it = item->toolTip();
  //ImagePreview(it, 0);
  auto t = item->text();

}

void ImageToPDF::ImageToPDFForm::itemClicked(int r, int c)
{
   if(c != 0)
   {
     return;
   }

   DebugOutput("aaa12");
   auto item = m_UiForm.InputFiles->item(r,c);

   int rotate = 0;
   auto wdg = m_UiForm.InputFiles->cellWidget(r,1);
   if( QComboBox* item2 = dynamic_cast<QComboBox*>(wdg) )
   {
      rotate = item2->currentText().toInt();
   }

   auto it = item->toolTip();
   ImagePreview(it, rotate);
   auto t = item->text();
}
