#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "../controller/controller.h"
#include "../3dviewer/model/observe/observe.h"
#include "qgifimage.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public s21::Observer
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void update() override; // Реализация метода update для паттерна Observer
    float scale = 0.0f;

private slots:
    void on_pushButton_choose_file_clicked();
    void on_doubleSpinBox_translations_x_valueChanged(double value);
    void on_doubleSpinBox_translations_y_valueChanged(double value);
    void on_doubleSpinBox_translations_z_valueChanged(double value);
    

    void on_doubleSpinBox_rotation_x_valueChanged(double arg1);

    void on_doubleSpinBox_rotation_y_valueChanged(double arg1);

    void on_doubleSpinBox_rotation_z_valueChanged(double arg1);

    void on_scale_valueChanged(double arg1);

    void on_color_back_red_valueChanged(int value);

    void on_color_back_green_valueChanged(int value);

    void on_color_back_blue_valueChanged(int value);

    void on_color_line_red_valueChanged(int value);

    void on_color_line_green_valueChanged(int value);

    void on_color_line_blue_valueChanged(int value);

    void on_color_dot_red_valueChanged(int value);

    void on_color_dot_green_valueChanged(int value);

    void on_color_dot_blue_valueChanged(int value);

    void on_size_dot_valueChanged(int value);

    void on_size_lin_valueChanged(int value);

    void on_stripe_line_clicked(bool checked);

    void on_nothingdot_clicked(bool checked);

    void on_dot_circle_clicked(bool checked);

    void on_dot_square_clicked(bool checked);

    void on_jpeg_clicked();

    void on_bmp_clicked();

    void on_gif_clicked();

    void bla();

private:
    float previousXValue = 0.0f;
    float previousYValue = 0.0f;
    float previousZValue = 0.0f;

    float rotateX = 0.0f;
    float rotateY = 0.0f;
    float rotateZ = 0.0f;
    Ui::MainWindow *ui;
    s21::Controller& controller;

    QImage grabFramebuffer();
    QGifImage *gif;
    QTimer *timer;
    int time;

};
#endif // MAINWINDOW_H
