#include <QApplication>
#include <QOpenGLWidget>
#include <QDebug>
#include "viewer.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qDebug() << "Qt Application started";
    Viewer widget;
    widget.resize(800, 600);
    widget.show();

    return app.exec();
}