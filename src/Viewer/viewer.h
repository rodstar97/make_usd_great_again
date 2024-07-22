#pragma once 

#define QT_NO_KEYWORDS
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QElapsedTimer>
#include "scene.h"



class Viewer : public QOpenGLWidget
{
public:
    Viewer(QWidget* parent=nullptr);
    ~Viewer();
protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

    Scene *usd_scene = nullptr;
    QElapsedTimer m_elapsed;
};


