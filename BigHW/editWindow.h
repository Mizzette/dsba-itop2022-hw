#ifndef EDITWINDOW_H
#define EDITWINDOW_H

#include <QDialog>
#include "data.h"
#include <QStandardItemModel>

namespace Ui {
class editWindow;
}

class editWindow : public QDialog
{
    Q_OBJECT

public:
    explicit editWindow(QWidget *parent = nullptr);
    ~editWindow();

    void setPointers(Data* data, QStandardItemModel *model, int row);

    virtual void paintEvent(QPaintEvent *event);

private slots:
    void on_back_button_clicked();

    void on_edit_button_clicked();

private:
    Ui::editWindow *ui;
    Data *data;
    QStandardItemModel *model;
    int _row;
};

#endif // EDITWINDOW_H
