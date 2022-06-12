#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "movietracker.h"
#include <QFileDialog>
#include <QPainter>
#include <QPolygon>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Button to open Movie tracker window
void MainWindow::on_open_button_clicked()
{
    MovieTracker mt;

    mt.setModal(true);
    this->hide();
    mt.exec();
    if (mt.close())
    {
        this -> show();
    }
}

//Settings button
void MainWindow::on_settings_button_clicked()
{

}

//Setting up a logo
 void MainWindow::paintEvent(QPaintEvent *event)
 {
    QPainter painter(this);
     painter.setPen(QPen(Qt::black, 8));
    painter.drawRect(0, 0, 138, 61);
    painter.setPen(QPen(Qt::black, 8));
    painter.background();
    QPolygon pol;
    pol << QPoint(30, 61) << QPoint(45, 0) << QPoint(70, 40) << QPoint(95, 0) << QPoint(110, 61);
    painter.drawPolygon(pol);
 }
