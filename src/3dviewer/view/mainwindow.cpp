#include "mainwindow.h"
#include "myopenglwidget.h"
#include "ui_mainwindow.h"

#include <QSettings>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , controller(s21::Controller::getInstance())
{
    ui->setupUi(this);
    setWindowTitle("3dViewer 2.0");

    connect(ui->color_back_red, &QSlider::valueChanged, this, &MainWindow::on_color_back_red_valueChanged);

    controller.addObserver(this); // Добавляем текущее окно в список наблюдателей
    s21::Controller& controller = s21::Controller::getInstance();
}

void MainWindow::on_doubleSpinBox_translations_x_valueChanged(double value) {
    float scaleFactor = 0.1f;
    float dx = (static_cast<float>(value) - previousXValue) * scaleFactor;
    controller.moveModelBy(dx, 0.0f, 0.0f);
    previousXValue = static_cast<float>(value);
}

void MainWindow::on_doubleSpinBox_translations_y_valueChanged(double value) {
    float scaleFactor = 0.1f;
    float dy = (static_cast<float>(value) - previousYValue) * scaleFactor;
    controller.moveModelBy(0.0f, dy, 0.0f);
    previousYValue = static_cast<float>(value);
}

void MainWindow::on_doubleSpinBox_translations_z_valueChanged(double value) {
    float scaleFactor = 0.1f;
    float dz = (static_cast<float>(value) - previousZValue) * scaleFactor;
    controller.moveModelBy(0.0f, 0.0f, dz);
    previousZValue = static_cast<float>(value);
}

void MainWindow::on_doubleSpinBox_rotation_x_valueChanged(double angle)
{
    float dx = (static_cast<float>(angle) - static_cast<float>(rotateX));
    rotateX = static_cast<float>(angle);
    controller.rotateModelBy(dx, 0.0f, 0.0f);
}

void MainWindow::on_doubleSpinBox_rotation_y_valueChanged(double angle)
{
    float dy = (static_cast<float>(angle) - static_cast<float>(rotateY));
    rotateY = static_cast<float>(angle);
    controller.rotateModelBy(0.0f, dy, 0.0f);
}

void MainWindow::on_doubleSpinBox_rotation_z_valueChanged(double angle)
{
    float dz = (static_cast<float>(angle) - static_cast<float>(rotateZ));
    rotateZ = static_cast<float>(angle);
    controller.rotateModelBy(0.0f, 0.0f, dz);
}


void MainWindow::on_scale_valueChanged(double position)
{
    controller.Scale_Model(position);
}

// Реализация метода update для паттерна Observer
void MainWindow::update() {
    // Выводите в консоль, что было обновление
    qDebug() << "MainWindow received update notification from the controller!";

    // Теперь можно выводить конкретные измененные данные в консоль
    qDebug() << "Vertices countdsfdsf:" << controller.getVertices().size();
    qDebug() << "Faces countsdfdsfsd:" << controller.getFaces().size();

    // Обновите свой интерфейс на основе измененных данных
    ui->textEdit_edges_count->setText(QString::number(controller.getVertices().size()));
    ui->textEdit_verticles_count->setText(QString::number(controller.getFaces().size()));
    
    // Передача вершин и граней в виджет OpenGL
    auto openGLWidget = ui->widget;
    if (openGLWidget) {
        openGLWidget->setVertices(controller.getVertices());
        openGLWidget->setFaces(controller.getFaces());
        openGLWidget->update();
    }
}


MainWindow::~MainWindow() {
    controller.removeObserver(this); // Удаляем текущее окно из списка наблюдателей
    delete ui;
}

void MainWindow::on_pushButton_choose_file_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open a file", "/Users", "*.obj");
    
    if (!fileName.isEmpty()) {
        controller.loadModel(fileName);
        ui->textEdit_filename->setText(QFileInfo(fileName).fileName());
    }
}


void MainWindow::on_color_back_red_valueChanged(int value) {
    float redValue = static_cast<float>(value) / 255.0f; // Так как максимальное значение вашего ползунка равно 255
    ui->widget->setRedFone(redValue);
    ui->widget->update();  // Обновить виджет OpenGL.
}


void MainWindow::on_color_back_green_valueChanged(int value) {
    float greenValue = static_cast<float>(value) / 255.0f;
    ui->widget->setGreenFone(greenValue);
    ui->widget->update();
}


void MainWindow::on_color_back_blue_valueChanged(int value)
{
    float blueValue = static_cast<float>(value) / 255.0f;
    ui->widget->setBlueFone(blueValue);
    ui->widget->update();
}


void MainWindow::on_color_line_red_valueChanged(int value)
{
    float redValue = static_cast<float>(value) / 255.0f; // Так как максимальное значение вашего ползунка равно 255
    ui->widget->setRedline(redValue);
    ui->widget->update();  // Обновить виджет OpenGL.
}


void MainWindow::on_color_line_green_valueChanged(int value)
{
    float greenValue  = static_cast<float>(value) / 255.0f; // Так как максимальное значение вашего ползунка равно 255
    ui->widget->setGreenline(greenValue);
    ui->widget->update();  // Обновить виджет OpenGL.
}


void MainWindow::on_color_line_blue_valueChanged(int value)
{
    float blueValue  = static_cast<float>(value) / 255.0f; // Так как максимальное значение вашего ползунка равно 255
    ui->widget->setBlueline(blueValue);
    ui->widget->update();  // Обновить виджет OpenGL.
}


void MainWindow::on_color_dot_red_valueChanged(int value)
{
    float redValue = static_cast<float>(value) / 255.0f; // Так как максимальное значение вашего ползунка равно 255
    ui->widget->setRedDot(redValue);
    ui->widget->update();  // Обновить виджет OpenGL.
}



void MainWindow::on_color_dot_green_valueChanged(int value)
{
    float greenValue = static_cast<float>(value) / 255.0f; // Так как максимальное значение вашего ползунка равно 255
    ui->widget->setGreenDot(greenValue);
    ui->widget->update();  // Обновить виджет OpenGL.
}


void MainWindow::on_color_dot_blue_valueChanged(int value)
{
    float blueValue = static_cast<float>(value) / 255.0f; // Так как максимальное значение вашего ползунка равно 255
    ui->widget->setBlueDot(blueValue);
    ui->widget->update();  // Обновить виджет OpenGL.
}


void MainWindow::on_size_dot_valueChanged(int value)
{
    float size_Dot = static_cast<float>(value); // Так как максимальное значение вашего ползунка равно 255
    ui->widget->setSizeDot(size_Dot);
    ui->widget->update();  // Обновить виджет OpenGL.
}


void MainWindow::on_size_lin_valueChanged(int value)
{
    float size_Line = static_cast<float>(value); // Так как максимальное значение вашего ползунка равно 255
    ui->widget->setSizeLine(size_Line);
    ui->widget->update();  // Обновить виджет OpenGL.
}


void MainWindow::on_stripe_line_clicked(bool checked)
{
    ui->widget->setStripeLine(checked);
    ui->widget->update();  // Обновить виджет OpenGL.
}


void MainWindow::on_nothingdot_clicked(bool checked)
{
    ui->widget->setNothingDot(checked);
    ui->widget->update();  // Обновить виджет OpenGL.
}


void MainWindow::on_dot_circle_clicked(bool checked)
{
    ui->widget->setCircleDot(checked);
    ui->widget->update();  // Обновить виджет OpenGL.
}


void MainWindow::on_dot_square_clicked(bool checked)
{
    ui->widget->setSquareDot(checked);
    ui->widget->update();  // Обновить виджет OpenGL.
}


void MainWindow::on_jpeg_clicked()
{
    QString file = QFileDialog::getSaveFileName(this, "Save as...", "name", "JPEG (*.jpg *.jpeg)");
        ui->widget->grab().save(file);

}


void MainWindow::on_bmp_clicked()
{
    QString file = QFileDialog::getSaveFileName(this, "Save as...", "name", "BMP (*.bmp)");
        ui->widget->grab().save(file);
}

void MainWindow::bla() {
  if (time < 75) {
    QImage image;
  image = ui->widget->grab().toImage();
    gif->addFrame(image, 10);
    time++;
  } else {
    QString gif_save_path_ = QFileDialog::getSaveFileName(this, NULL, NULL, "GIF (*.gif)");
    gif->save(gif_save_path_);
    timer->stop();
    delete timer;
    delete gif;
  }
}



void MainWindow::on_gif_clicked()
{
    time = 0;
    gif = new QGifImage();
    timer = new QTimer(this);
    gif->setDefaultDelay(100);
    connect(timer, &QTimer::timeout, this, &MainWindow::bla);
    timer->start(100);
}

