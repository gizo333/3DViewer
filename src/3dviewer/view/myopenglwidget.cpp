#include "myopenglwidget.h"
#include <QSettings>
#include <iostream>

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent), m_vertexBuffer(QOpenGLBuffer::VertexBuffer), m_indexBuffer(QOpenGLBuffer::IndexBuffer) {}

void MyOpenGLWidget::initializeGL() {
    initializeOpenGLFunctions(); // Инициализация функций OpenGL

    glEnable(GL_DEPTH_TEST);
    glClearColor(50.0f/255, 50.0f/255, 50.0f/255, 1);

    // Инициализация VBO
    m_vertexBuffer.create();
    m_indexBuffer.create();
}

void MyOpenGLWidget::setVertices(const QVector<QVector3D>& vertices) {
    m_vertices = vertices;

    m_vertexBuffer.bind();
    m_vertexBuffer.allocate(m_vertices.constData(), m_vertices.size() * sizeof(QVector3D));
    m_vertexBuffer.release();

    this->update();
}

void MyOpenGLWidget::setFaces(const QVector<QVector<int>>& faces) {
    m_faces = faces;

    QVector<unsigned int> indices;
    for (const auto &face : m_faces) {
        for (const auto &index : face) {
            indices.push_back(index);
        }
    }

    m_indexBuffer.bind();
    m_indexBuffer.allocate(indices.constData(), indices.size() * sizeof(unsigned int));
    m_indexBuffer.release();
}

void MyOpenGLWidget::paintGL() {
    glClearColor(r_fone, g_fone, b_fone, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Добавляем очистку буфера глубины

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Отрисовка вершин с использованием VBO
    m_vertexBuffer.bind();

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(QVector3D), nullptr);

    if(!dot_nothing) {
        glColor3f(r_dot, g_dot, b_dot);
        glColor3f(r_dot, g_dot, b_dot);
        if (!dot_square && dot_circle) {
            glEnable(GL_POINT_SMOOTH);
        } else {
            glDisable(GL_POINT_SMOOTH);
        }
        glDrawArrays(GL_POINTS, 0, m_vertices.size());
        glPointSize(dot_size);
    }

    // Отрисовка граней с использованием VBO
    m_indexBuffer.bind();

    glColor3d(r_line, g_line, b_line);
    if (line_stripe) {
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, 0x00F0);
    } else {
        glDisable(GL_LINE_STIPPLE);
    }
    glDrawElements(GL_LINES, m_indexBuffer.size() / sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);
    glLineWidth(line_size);

    glDisableClientState(GL_VERTEX_ARRAY);
    m_vertexBuffer.release();
    m_indexBuffer.release();
}

void MyOpenGLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}
