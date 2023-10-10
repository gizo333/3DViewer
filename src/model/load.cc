#include "model.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QVector3D>
#include <QRegularExpression>
#include <stdexcept>
#include <QDebug>

namespace s21 {

void Model::loadOBJ(const QString &filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw std::runtime_error("Cannot open OBJ file.");
    }

    QTextStream in(&file);
    QVector<QVector3D> temp_vertices;
    QVector<QVector<int>> temp_faces; // Добавлен вектор для хранения граней.

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList list = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
        if (list.empty()) continue;

        if (list[0] == "v" && list.size() >= 4) {
            float x = list[1].toFloat();
            float y = list[2].toFloat();
            float z = list[3].toFloat();
            temp_vertices.push_back(QVector3D(x, y, z));
        } 
        else if (list[0] == "f" && list.size() >= 4) {
            QVector<int> face_indices;
            for (int i = 1; i < list.size(); ++i) {
                QStringList vertex_data = list[i].split('/');
                if (vertex_data.empty()) {
                    throw std::runtime_error("Error parsing face data: empty vertex data");
                }

                bool ok;
                int idx = vertex_data[0].toInt(&ok) - 1;
                if (!ok) {
                    qDebug() << "Failed to parse face data:" << line;
                    throw std::runtime_error("Error parsing face data (vertex index)");
                }
                face_indices.push_back(idx);
            }
            temp_faces.push_back(face_indices);
        }
    }

    vertices = temp_vertices;
    faces = temp_faces; // Копирование временных граней в член класса.

    file.close();


    // Выводим вершины и грани в консоль
    qDebug() << "Vertices:";
    for (const QVector3D &vertex : vertices) {
        qDebug() << vertex;
    }

    qDebug() << "\nFaces:";
    for (const QVector<int> &face : faces) {
        qDebug() << face;
    }
}

const QVector<QVector3D>& Model::getVertices() const {
    return vertices;
}

const QVector<QVector<int>>& Model::getFaces() const {
    return faces;
}

} // namespace s21
