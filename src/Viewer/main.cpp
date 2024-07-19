#include <QApplication>
#include <QOpenGLWidget>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QOpenGLWidget widget;
    //widget.resize(800, 600);
    widget.show();

    return app.exec();
}