#ifndef MODEL_H
#define MODEL_H

#include <QString>
#include <QQuaternion>
#include <QVector> // Для использования QVector
#include <QCoreApplication>
#include <QDebug>
#include <exception>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QVector3D>
#include <QRegularExpression>
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <memory>

namespace s21 {

class Model {
public:
    Model() {}

    ~Model() {}

    void loadOBJ(const QString &filename);
    void setVertices(const QVector<QVector3D>& vertices) {
        this->vertices = vertices;
    }


    class MoveStrategy {
    public:
    virtual void move(QVector3D& vertex, float distance) = 0;
    virtual ~MoveStrategy() = default;
    };

    class MoveByXStrategy : public MoveStrategy {
    public:
    void move(QVector3D& vertex, float distance) override {
    vertex.setX(vertex.x() + distance);
    }
    };

    class MoveByYStrategy : public MoveStrategy {
    public:
    void move(QVector3D& vertex, float distance) override {
    vertex.setY(vertex.y() + distance);
    }
    };

    class MoveByZStrategy : public MoveStrategy {
    public:
    void move(QVector3D& vertex, float distance) override {
    vertex.setZ(vertex.z() + distance);
    }
    };

    class VertexContext {
    private:
    QVector3D& vertex;
    std::unique_ptr<MoveStrategy> strategy;

    public:
    VertexContext(QVector3D& vertex, std::unique_ptr<MoveStrategy> strategy)
    : vertex(vertex), strategy(std::move(strategy)) {
    }

    void setStrategy(std::unique_ptr<MoveStrategy> newStrategy) {
    strategy = std::move(newStrategy);
    }

    void move(float distance) {
    if (strategy) {
    strategy->move(vertex, distance);
    }
    }
    };

    void moveByX(float dx) {
    for (int i = 0; i < vertices.size(); ++i) {
    QVector3D& vertex = vertices[i];
    VertexContext moverX(vertex, std::make_unique<MoveByXStrategy>());
    moverX.move(dx);
    }
    }

    void moveByY(float dy) {
    for (int i = 0; i < vertices.size(); ++i) {
    QVector3D& vertex = vertices[i];
    VertexContext moverY(vertex, std::make_unique<MoveByYStrategy>());
    moverY.move(dy);
    }
    }


    void moveByZ(float dz) {
    for (int i = 0; i < vertices.size(); ++i) {
    QVector3D& vertex = vertices[i];
    VertexContext moverZ(vertex, std::make_unique<MoveByZStrategy>());
    moverZ.move(dz);
    }
    }

void RotateX(float angle) {
    angle = angle * 3.1496 / 180.;
    double cosA = cos(angle);
    double sinA = sin(angle);
    for (int i = 0; i < vertices.size(); ++i) {
        QVector3D& vertex = vertices[i];
        double y = vertex.y();
        double z = vertex.z();

        vertex.setY(y*cosA - z*sinA);
        vertex.setZ(y*sinA + z*cosA);
    }
}

void RotateY(float angle) {
    angle = angle * 3.1496 / 180.;
    double cosA = cos(angle);
    double sinA = sin(angle);
    for (int i = 0; i < vertices.size(); ++i) {
        QVector3D& vertex = vertices[i];
        double x = vertex.x();
        double z = vertex.z();

        vertex.setX(x*cosA + z*sinA);
        vertex.setZ((-1)*x*sinA + z*cosA);
    }
}

void RotateZ(float angle) {
    angle = angle * 3.1496 / 180.;
    double cosA = cos(angle);
    double sinA = sin(angle);
    for (int i = 0; i < vertices.size(); ++i) {
        QVector3D& vertex = vertices[i];
        double x = vertex.x();
        double y = vertex.y();

        vertex.setX(x*cosA + y*sinA);
        vertex.setY((-1)*x*sinA + y*cosA);
    }
}

void SCALE(float position) {
    float val = max_Gode();
    for (int i = 0; i < vertices.size(); ++i) {
        QVector3D& vertex = vertices[i];
        vertex.setX((vertex.x()/val)*position);
        vertex.setY((vertex.y()/val)*position);
        vertex.setZ((vertex.z()/val)*position);
    }
}


float max_Gode() {
    float max = 0;

     for (int i = 0; i < vertices.size(); ++i) {
         QVector3D& vertex = vertices[i];
         if(vertex.x() > max) {
             max = vertex.x();
         }
         if(vertex.y() > max) {
             max = vertex.y();
         }
         if(vertex.z() > max) {
             max = vertex.z();
         }
     }
     return max;
}


    // Объявления функций с консистентными возвращаемыми типами
    const QVector<QVector3D>& getVertices() const;
    const QVector<QVector<int>>& getFaces() const;

private:
    QVector<QVector3D> vertices;
    QVector<QVector<int>> faces;
};

}  // namespace s21

#endif  // MODEL_H
