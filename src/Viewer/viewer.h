#pragma once 

#define QT_NO_KEYWORDS
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QElapsedTimer>
#include "scene.h"
#include <QVector2D>
#include <QVector3D>
#include <QMatrix4x4>


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
    void mouseReleaseEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

    QMatrix4x4 currentMatrix() const;
    Scene *usd_scene = nullptr;
    std::optional<QVector2D> mousePressPosition;
    QElapsedTimer m_elapsed;
};



struct {
    QVector3D focusPoint = {0, 0, 0};
    QVector3D cameraLocation = {0, 0, -2};
    QVector3D up = QVector3D::crossProduct({-1, 0, 0}, cameraLocation - focusPoint).normalized();
} lookat_camera;

