#include "PostMainWindow.h"
#include <QApplication>
#include <QSurface>
//#include "QVTKOpenGLWidget.h"
#include "QVTKOpenGLNativeWidget.h"

int main(int argc, char *argv[])
{
//    QSurfaceFormat::setDefaultFormat(QVTKOpenGLWidget::defaultFormat());
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());

    QApplication a(argc, argv);
    PostMainWindow w;
    w.show();
    return a.exec();
}