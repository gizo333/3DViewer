#pragma once
#include <QObject>
#include <QDebug>
#include "../model/model.h"
#include "../3dviewer/model/observe/observeble.h"

namespace s21 {

    

class Controller : public QObject, public Observable {
    Q_OBJECT 

public:
    static Controller& getInstance() {
        static Controller instance;
        return instance;
    }

    void moveModelBy(float dx, float dy, float dz) {
    model.moveByX(dx);
    model.moveByY(dy);
    model.moveByZ(dz);
    notifyObservers();
}
    void rotateModelBy(float angelX,  float angelY, float angelZ) {
        model.RotateX(angelX);
        model.RotateY(angelY);
        model.RotateZ(angelZ);
        notifyObservers();
    }

    void Scale_Model(float position) {
        model.SCALE(position);
        notifyObservers();
    }


    // Метод для загрузки модели из файла
    void loadModel(const QString &filename) {
        try {
            model.loadOBJ(filename);
            notifyObservers();
        } catch (const std::runtime_error &e) {
            qDebug() << "Error loading model: " << e.what();
        }
    }


public:
    

    // Методы для получения вершин и граней
    const QVector<QVector3D>& getVertices() const {
        return model.getVertices();
    }

    const QVector<QVector<int>>& getFaces() const {
        return model.getFaces();
    }


private:
    Controller() {}
    Controller(const Controller&) = delete;
    Controller& operator=(const Controller&) = delete;
    Model model;
    
};

}  // namespace s21
