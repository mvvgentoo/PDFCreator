#include "imagetopdfdialog.h"
#include "utils.h"
#include "globalEnums.h"
#include <Magick++.h>

#include <iostream>
#include <qstringlist.h>
#include <qfiledialog.h>
#include <qlistwidget.h>


ImageToPDF::ImageToPDFForm::ImageToPDFForm(QDialog *parent) : QDialog(parent)
{
  m_UiForm.setupUi(this);

  m_UiForm.comboBox->addItem("PDF");
  m_UiForm.comboBox->addItem("PNG");

  //connect(m_UiForm.plusButton, SIGNAL(clicked()), SLOT(AddElement() ) );
//  connect(m_UiForm.plusButton, &QAbstractButton::clicked, this, &ImageToPDFForm::AddElement);


  connect(m_UiForm.InputFiles, SIGNAL(itemClicked(QListWidgetItem*)), SLOT(itemClicked(QListWidgetItem *)));
}

void ImageToPDF::ImageToPDFForm::ImagePreview(QString name)
{
  QPixmap pixmap(name);
  pixmap = pixmap.scaled(pixmap.size() * 0.1);
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

  for(const QString& i : filenames)
  {
    QListWidgetItem* item = new QListWidgetItem(QFileInfo(i).fileName(), m_UiForm.InputFiles);
    item->setToolTip(i);
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

    const QListWidget* listWidget = m_UiForm.InputFiles;
    std::vector<Magick::Image> ims(listWidget->count());

    for(int row = 0; row < listWidget->count(); row++)
    {
        QListWidgetItem *item = listWidget->item(row);
        ims[row].read(item->toolTip().toStdString());
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

void ImageToPDF::ImageToPDFForm::itemClicked(QListWidgetItem *item)
{
  DebugOutput("aaa1");
  auto it = item->toolTip();
  ImagePreview(it);
  auto t = item->text();

}
