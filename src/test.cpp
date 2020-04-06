#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <Magick++.h>

#include "utils.h"
#include "globalEnums.h"

#include <QApplication>
#include <QWidget>
#include <ui_imagetopdf.h>
#include "imagetopdfdialog.h"

using Image = Magick::Image;
using Blob = Magick::Blob;


int main(int argc, char ** argv )
{
	Magick::InitializeMagick(*argv);

#define TESTING_MAGICK 0

#if TESTING_MAGICK

    std::vector<Image> ims(2);
    ims[0].read(argv[1]);
    ims[1].read(argv[1]);

    Magick::Image output;
    Magick::appendImages(&output, ims.begin(), ims.end());
    output.write("/tmp/all.png");

    //output.magick("PDF");
    //output.write(argv[2]);

    Magick::writeImages(ims.begin(), ims.end(), std::string("/tmp/") + argv[2]);
    Magick::writeImages(ims.begin(), ims.end(), std::string("/tmp/aaa.png"));

#endif

#if TESTING_QT
	char dst[30];
    char *a =  ImageToPDF::_GetNameNoExtension(argv[2], dst);
	std::cout << a << std::endl;

    std::string s =  ImageToPDF::GetNameNoExtension(argv[2]);
	std::cout << s << " " << s.size()  << std::endl;

    std::cout << ImageToPDF::s_Mapping["pdf"] << std::endl;

    std::cout << ImageToPDF::_BaseName("/aaa/adasd/adasd/bbsdas.pdf") << std::endl;

    ImageToPDF::ID::FileName fl("/sd/das/dasd/aa.pdf");

	//delete[] a;

    QApplication app(argc, argv);

    ImageToPDF::ImageToPDFForm dialog;
    //Ui::ImageToPDFDialog window;
    //window.setupUi(&dialog);

    //QWidget window;

    //window.resize(250, 150);
    //window.setWindowTitle("Simple example");
    //window.setToolTip("QWidget");

    dialog.show();

    return app.exec();

    //return 0;
	//Blob blob;
#endif
}
