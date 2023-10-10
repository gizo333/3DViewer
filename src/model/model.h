#ifndef MODEL_H
#define MODEL_H

#include <QString>
#include <QQuaternion>
#include <QVector> // Для использования QVector

namespace s21 {

class Model {
public:

    void loadOBJ(const QString &filename);
    void move(const QVector3D &offset);
    void rotate(const QQuaternion &rotation);
    void scale(float factor);

    // Объявления функций с консистентными возвращаемыми типами
    const QVector<QVector3D>& getVertices() const;
    const QVector<QVector<int>>& getFaces() const;

private:
    QVector<QVector3D> vertices;
    QVector<QVector<int>> faces;
};

}  // namespace s21

#endif  // MODEL_H
