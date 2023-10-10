
    #include <QCoreApplication>
    #include <QDebug>
    #include <exception>

   #include "/Users/gizo/projects/3Dviwer/src/controller/controller.h"

int main() {
    s21::Controller controller;

    // Загрузка модели из файла
    controller.loadModel("/Users/gizo/projects/3Dviwer/src/obj/cube.obj");

    // Получение вершин и граней
    const QVector<QVector3D>& vertices = controller.getVertices();
    const QVector<QVector<int>>& faces = controller.getFaces();

    // Вывод вершин в консоль
    qDebug() << "Vertices:";
    for (const QVector3D &vertex : vertices) {
        qDebug() << vertex;
    }

    // Вывод граней в консоль
    qDebug() << "\nFaces:";
    for (const QVector<int> &face : faces) {
        qDebug() << face;
    }

    return 0;
}
