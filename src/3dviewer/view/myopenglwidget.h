#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QtOpenGLWidgets/QtOpenGLWidgets>

class MyOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    MyOpenGLWidget(QWidget *parent = nullptr);
    void setVertices(const QVector<QVector3D>& vertices);
    void setFaces(const QVector<QVector<int>>& faces);
    void updateVertices(const QVector<QVector3D> &vertices);
    void setModelTranslation(const QVector3D &translation);

    float r_fone = 0.5f; // начальный цвет красного: 0.5 (серый)
    float g_fone = 0.5f; // начальный цвет зеленого: 0.5 (серый)
    float b_fone = 0.5f; // начальный цвет синего: 0.5 (серый)

    float r_line = 0.5f, g_line = 0.5f, b_line = 0.5f;
    float r_dot = 0.5f, g_dot = 0.5f, b_dot = 0.5f;

    float dot_size = 1.0f;
    float line_size = 1.0f;

    bool line_stripe = false;

    bool dot_nothing = false;
    bool dot_circle = false;
    bool dot_square = false;


    void setRedFone(float value) { r_fone = value; }
    void setGreenFone(float value) { g_fone = value; }
    void setBlueFone(float value) { b_fone = value; }

    void setRedline(float value) { r_line = value; }
    void setGreenline(float value) { g_line = value; }
    void setBlueline(float value) { b_line = value; }

    void setRedDot(float value) { r_dot = value; }
    void setGreenDot(float value) { g_dot = value; }
    void setBlueDot(float value) { b_dot = value; }

    void setSizeDot(float value) { dot_size = value; }
    void setSizeLine(float value) { line_size = value; }

    void setStripeLine(bool value) { line_stripe = value; }

    void setNothingDot(bool value) { dot_nothing = value; }
    void setCircleDot(bool value) { dot_circle = value; }
    void setSquareDot(bool value) { dot_square = value; }



private:
    QVector3D modelTranslation; 
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    QVector<QVector3D> m_vertices;
    QVector<QVector<int>> m_faces;

    QOpenGLBuffer m_vertexBuffer;
    QOpenGLBuffer m_indexBuffer;

};

#endif // MYOPENGLWIDGET_H
