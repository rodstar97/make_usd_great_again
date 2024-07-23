#include "viewer.h"
#include "scene.h"
#include <QDebug>
#include <QTimer>
#include <QMouseEvent>
#include <QVector2D>
#include <QVector3D>
#include <QMatrix4x4>



Viewer::Viewer(QWidget* parent) : QOpenGLWidget(parent) 
{ 
    setMouseTracking(true);
    
}

Viewer::~Viewer()
{

}

 void Viewer::initializeGL()
{
    // Set up the rendering context, load shaders and other resources, etc.:
    QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
    // f->glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    usd_scene = new Scene;
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    qDebug() << "Renderer:" << renderer;
    qDebug() << "OpenGL version supported:" << version;


}

inline void Viewer::paintGL()
{
    // QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
    // glEnable(GL_DEPTH_TEST);
    // glDepthFunc(GL_LESS);

    // glEnable(GL_BLEND);

    


    //glClear(GL_COLOR_BUFFER_BIT);
    QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
    
    glDepthFunc(GL_LESS);



    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glBegin(GL_TRIANGLES);
    // glColor3f(1.0f, 0.0f, 0.0f); // Rot
    // glVertex3f(-0.5f, -0.5f, 0.0f);
    // glColor3f(0.0f, 1.0f, 0.0f); // Grün
    // glVertex3f(0.5f, -0.5f, 0.0f);
    // glColor3f(0.0f, 0.0f, 1.0f); // Blau
    // glVertex3f(0.0f, 0.5f, 0.0f);
    // glEnd();
    //m_scene->prepare(m_elapsed.elapsed()/100.0f);
    usd_scene->draw(width(), height());
    // m_elapsed.restart();
    // update();
    //m_elapsed.restart();
    //update(); 
}


void Viewer::resizeGL(int w, int h)
{
    // Set the viewport to cover the entire widget
    glViewport(0, 0, w, h);
}

void Viewer::mouseMoveEvent(QMouseEvent* event)
{
    if (!mousePressPosition) {
        return;
    }

    auto const pos = QVector2D(event->localPos());
    auto const diff = pos - *mousePressPosition;
    auto const focusVector = lookat_camera.cameraLocation - lookat_camera.focusPoint;
    auto const up = lookat_camera.up.normalized();
    auto const right = QVector3D::crossProduct(lookat_camera.up, focusVector).normalized();

    if (event->buttons() & Qt::LeftButton) {
        // rotate
        QMatrix4x4 mat;
        mat.rotate(-diff.x(), up);
        mat.rotate(-diff.y(), right);
        auto const newFocusVector = mat.map(focusVector);
        auto const newCameraPos = newFocusVector + lookat_camera.focusPoint;
        lookat_camera.cameraLocation = newCameraPos;
        lookat_camera.up = mat.mapVector(up);
        // Ensure the "up" vector is actually orthogonal to the focus vector. This is approximately
        // the case anyways, but might drift over time due to float precision.
        lookat_camera.up -= QVector3D::dotProduct(lookat_camera.up, newFocusVector) * lookat_camera.up;
        lookat_camera.up.normalize();
    }
    if (event->buttons() & Qt::RightButton) {
        // pan
        auto const panDelta = -diff.x() / width() * right + diff.y() / height() * up;
        lookat_camera.cameraLocation += panDelta;
        lookat_camera.focusPoint += panDelta;
    }

    mousePressPosition = QVector2D(event->localPos());
    usd_scene->set_camera(currentMatrix());
    update();
}

void Viewer::wheelEvent(QWheelEvent* event)
{
    auto const delta = event->angleDelta().y();
    auto const focusVector = lookat_camera.cameraLocation - lookat_camera.focusPoint;
    auto const mul = -delta / 1000.;
    lookat_camera.cameraLocation += mul*focusVector;
    update();
}


void Viewer::mousePressEvent(QMouseEvent* event)
{
    mousePressPosition = QVector2D(event->localPos());
}

void Viewer::mouseReleaseEvent(QMouseEvent* event)
{
    mousePressPosition.reset();
    

    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //usd_scene->draw(width(), height());
    //update();
}

QMatrix4x4 Viewer::currentMatrix() const
{
    QMatrix4x4 viewMatrix;
    viewMatrix.lookAt(lookat_camera.cameraLocation, lookat_camera.focusPoint, lookat_camera.up);
    return viewMatrix;
}