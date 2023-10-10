// controller.h
#pragma once
#include "/Users/gizo/projects/3Dviwer/src/model/model.h"

namespace s21 {

class Controller {
public:
    Controller() {}

    // Метод для загрузки модели из файла
    void loadModel(const QString &filename) {
        try {
            model.loadOBJ(filename);
        } catch (const std::runtime_error &e) {
            // Обработка ошибки при загрузке модели
            qDebug() << "Error loading model: " << e.what();
        }
    }

    // Методы для получения вершин и граней
    const QVector<QVector3D>& getVertices() const {
        return model.getVertices();
    }

    const QVector<QVector<int>>& getFaces() const {
        return model.getFaces();
    }

private:
    Model model;
};

}  // namespace s21
