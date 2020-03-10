#include "imagetopdfdialog.h"

#include <iostream>

ImageToPDF::ImageToPDFForm::ImageToPDFForm(QDialog *parent) : QDialog(parent)
{
  m_UiForm.setupUi(this);

  m_UiForm.comboBox->addItem("PDF");
  m_UiForm.comboBox->addItem("PNG");

  //connect(m_UiForm.plusButton, SIGNAL(clicked()), SLOT(AddElement() ) );
//  connect(m_UiForm.plusButton, &QAbstractButton::clicked, this, &ImageToPDFForm::AddElement);

}

void ImageToPDF::ImageToPDFForm::on_plusButton_clicked()
{
  std::cout << "aaa" << std::endl;
  m_UiForm.InputFiles->addItem("aaa");
}
