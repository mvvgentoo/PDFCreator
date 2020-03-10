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

    private:
      Ui::ImageToPDFDialog m_UiForm;


  };
}

