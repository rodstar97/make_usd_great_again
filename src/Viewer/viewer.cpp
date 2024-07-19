#include "viewer.h"
#include "scene.h"
#include <QDebug>
#include <QTimer>
#include <QMouseEvent>

Viewer::Viewer(QWidget* parent) : QOpenGLWidget(parent) 
{ 
    
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

    

    // m_elapsed.restart();
    // update();
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
    //m_elapsed.restart();
    //update(); 
}


void Viewer::resizeGL(int w, int h)
{
    // Set the viewport to cover the entire widget
    glViewport(0, 0, w, h);
}
// void View::mouseMoveEvent(QMouseEvent* event)
// {
//     m_scene->cursor(event->x()/(float)width(), event->y()/(float)height());

// }

// void View::mousePressEvent(QMouseEvent* event)
// {
//     m_scene->click();
// }