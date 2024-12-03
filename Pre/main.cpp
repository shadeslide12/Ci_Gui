#include "PreMainWindow.h"
#ifndef NO_VTK_WINDOW
#include "QVTKOpenGLWidget.h"
#endif

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
     a.setStyleSheet("QPushButton:pressed { "
                    "background-color: red; "  // 按下时的背景色
                    "}");
#ifndef NO_VTK_WINDOW
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLWidget::defaultFormat());
#endif
    PreMainWindow w;

    w.show();
    return a.exec();

}
