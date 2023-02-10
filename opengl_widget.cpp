#include "opengl_widget.h"

#include <QtGui/QSurfaceFormat>

#include <iostream>

OpenGLWidget::OpenGLWidget()
{
    // Set format
    QSurfaceFormat format;
    format.setSamples(8);
    setFormat(format);
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.77f, 0.93f, 0.95f, 1.f);

    m_program.addShaderFromSourceFile(QOpenGLShader::ShaderTypeBit::Vertex,
        "assets/shaders/default.vert");
    m_program.addShaderFromSourceFile(QOpenGLShader::ShaderTypeBit::Fragment,
        "assets/shaders/default.frag");
    m_program.bindAttributeLocation("aPosition", 0);
    m_program.link();
    m_program.bind();

    float vertPositions[] = {
        0, 0, // Quad
        1, 0,
        0, 1,
        1, 1,
        0, 0, // Triangle
        1.2, -1,
        2.4, 0
    };
    m_vertPosBuffer.create();
    m_vertPosBuffer.bind();
    m_vertPosBuffer.allocate(vertPositions, sizeof(vertPositions));
    m_program.setAttributeBuffer(0, GL_FLOAT, 0, 2);
    m_program.enableAttributeArray(0);

    QMatrix4x4 projMatrix;
    projMatrix.ortho(0, 200, 200, 0, 1, -1);
    QMatrix4x4 viewMatrix;
    viewMatrix.lookAt(
        QVector3D(0, 0, 1),
        QVector3D(0, 0, 0),
        QVector3D(0, 1, 0));
    m_projViewMatrix = projMatrix * viewMatrix;

    m_uMvpMatrixLocation = m_program.uniformLocation("uMvpMatrix");
    m_uColorLocation = m_program.uniformLocation("uColor");

    Renderable houseBody(0, 0, 100, 100, QVector3D(0, 0.7, 0), 0, 4);
    Renderable roof(-10, 0, 50, 50, QVector3D(0.35, 0.25, 0.2), 4, 4);
    Renderable window(20, 20, 30, 50, QVector3D(0, 0, 0), 0, 4);
    Renderable windowLine0(20, 38, 30, 4, QVector3D(1, 1, 1), 0, 4);
    Renderable windowLine1(33, 40, 4, 30, QVector3D(1, 1, 1), 0, 4);

    m_objects.append(houseBody);
    m_objects.append(roof);
    m_objects.append(window);
    m_objects.append(windowLine0);
    m_objects.append(windowLine1);
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < m_objects.size(); ++i)
    {
        m_modelMatrix.setToIdentity();
        m_modelMatrix.translate(m_housePosX + m_objects[i].x,
            m_housePosY + m_objects[i].y);
        m_modelMatrix.rotate(m_objects[i].angle, QVector3D(0, 0, 1));
        m_modelMatrix.scale(m_objects[i].w, m_objects[i].h);
        m_mvpMatrix = m_projViewMatrix * m_modelMatrix;
        m_program.bind();
        m_program.setUniformValue(m_uMvpMatrixLocation, m_mvpMatrix);
        m_program.setUniformValue(m_uColorLocation, m_objects[i].color);
        glDrawArrays(GL_TRIANGLE_STRIP, m_objects[i].startIndex,
            m_objects[i].amountOfVertices);
    }
}

void OpenGLWidget::setParamsSlot(int x, int y)
{
    m_housePosX = x;
    m_housePosY = y;
    update();
}
