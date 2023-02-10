#ifndef OPENGL_WIDGET_H
#define OPENGL_WIDGET_H

#include <QtCore/QVector>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QMatrix4x4>
#include <QtGui/QVector3D>
#include <QtOpenGL/QOpenGLBuffer>
#include <QtOpenGL/QOpenGLShader>
#include <QtOpenGL/QOpenGLShaderProgram>
#include <QtOpenGLWidgets/QOpenGLWidget>

#include "renderable.h"

class OpenGLWidget : public QOpenGLWidget, QOpenGLFunctions
{
    Q_OBJECT;

public:
    OpenGLWidget();

public slots:
    void setParamsSlot(int x, int y);

private:
    void initializeGL() override;
    void paintGL() override;

    int m_housePosX;
    int m_housePosY;
    QOpenGLShaderProgram m_program;
    QOpenGLBuffer m_vertPosBuffer;
    QMatrix4x4 m_modelMatrix;
    QMatrix4x4 m_mvpMatrix;
    QMatrix4x4 m_projViewMatrix;
    int m_uMvpMatrixLocation;
    int m_uColorLocation;
    QVector<Renderable> m_objects;
};

#endif // OPENGL_WIDGET_H
