#include "infowindow.h"
#include "ui_infowindow.h"
#include "movietracker.h"
#include <QPainter>

infoWindow::infoWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::infoWindow)
{
    ui->setupUi(this);
}

infoWindow::~infoWindow()
{
    delete ui;
}


//Back button
void infoWindow::on_back_button_clicked()
{
    this -> close();
}

//Function to get the data from row of tableView
void infoWindow::getData(Data data)
{
    ui -> titleText -> setText(QString::fromStdString(data.title));
    ui -> typeText -> setText(QString::fromStdString(data.type));
    ui -> directorText -> setText(QString::fromStdString(data.director));
    ui -> countryText -> setText(QString::fromStdString(data.country));
    ui -> yearText -> setText(QString::fromStdString(data.year));
    ui -> ratingText -> setText(QString::fromStdString(data.tv_rating));
    ui -> statusText -> setText(QString::fromStdString(data.status));
}

//Setting up a logo
 void infoWindow::paintEvent(QPaintEvent *event)
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


