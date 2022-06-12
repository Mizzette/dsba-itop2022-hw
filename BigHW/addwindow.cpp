#include "addwindow.h"
#include "ui_addwindow.h"
#include <QStandardItem>
#include <QPainter>

addWindow::addWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addWindow)
{
    ui->setupUi(this);
}

addWindow::~addWindow()
{
    delete ui;
}

//Setting pointers
void addWindow::setPointers(QStandardItemModel *model, Data *data)
{
    this -> data = data;
    this -> itemModel = model;
}

//Back button
void addWindow::on_back_button_clicked()
{
    this -> close();
}

//Add button
void addWindow::on_addButton_clicked()
{
    //Setting up attributes to the Data class
    data -> title = ui -> titleText -> toPlainText().toStdString();
    data -> type = ui -> typeText -> toPlainText().toStdString();
    data -> director = ui -> directorText -> toPlainText().toStdString();
    data -> country = ui -> countryText -> toPlainText().toStdString();
    data -> year = ui -> yearText -> toPlainText().toStdString();
    data -> tv_rating = ui -> ratingText -> toPlainText().toStdString();
    data -> status = ui -> statusText -> toPlainText().toStdString();

    int row = itemModel -> rowCount();

    //Inserting row
    itemModel -> insertRows(row, 1);
    //Column 0
    QModelIndex index = itemModel -> index(row, 0, QModelIndex());
    itemModel -> setData(index, ui -> titleText -> toPlainText());
    //Column 1
    index = itemModel -> index(row, 1, QModelIndex());
    itemModel -> setData(index, ui -> statusText -> toPlainText());

    this -> close();
}
//Setting up a logo
 void addWindow::paintEvent(QPaintEvent *event)
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

