#include "editwindow.h"
#include "ui_editwindow.h"
#include <QPainter>

editWindow::editWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editWindow)
{
    ui->setupUi(this);
}

editWindow::~editWindow()
{
    delete ui;
}

//Setting up pointers
void editWindow::setPointers(Data *data, QStandardItemModel* model, int row)
{
    this -> data = data;
    this -> model = model;
    this -> _row = row;

    ui -> statusText -> setText(QString::fromStdString(data -> status));
}

//Back button
void editWindow::on_back_button_clicked()
{
    this -> close();
}




void editWindow::on_edit_button_clicked()
{
    this -> data -> status = ui -> statusText->toPlainText().toStdString();

    QModelIndex index = model->index(_row, 1, QModelIndex());
    model -> setData(index, ui -> statusText -> toPlainText());

    this->close();
}

//Setting up a logo
 void editWindow::paintEvent(QPaintEvent *event)
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


