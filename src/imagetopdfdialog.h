#pragma once

#include "ui_imagetopdf.h"

namespace ImageToPDF
{
  class ImageToPDFForm : public QDialog
  {
    Q_OBJECT

    public:
      ImageToPDFForm(QDialog* parent = nullptr);

    private slots:
      //void AddElement();
      void on_plusButton_clicked();
      void on_removeAllButton_clicked();
      void on_buttonBox_clicked(QAbstractButton* btn);
      void on_buttonBox_rejected();
      void itemClicked(QListWidgetItem*item);

    private:
      Ui::ImageToPDFDialog m_UiForm;

      void ImagePreview(QString name);


  };
}

