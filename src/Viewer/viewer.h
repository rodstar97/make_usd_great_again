#pragma once 

#define QT_NO_KEYWORDS
#include <QOpenGLWidget>
#include <QOpenGLFunctions>


class Scene;

class Viewer : public QOpenGLWidget
{
public:
    Viewer(QWidget* parent=nullptr);
    ~Viewer();
protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    Scene *usd_scene = nullptr;
};