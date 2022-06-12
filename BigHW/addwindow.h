#ifndef ADDWINDOW_H
#define ADDWINDOW_H

#include <QDialog>
#include <QStandardItemModel>
#include "movietracker.h"
#include "data.h"
#include "proxymodel.h"

namespace Ui {
class addWindow;
}

class addWindow : public QDialog
{
    Q_OBJECT

public:
    explicit addWindow(QWidget *parent = nullptr);
    ~addWindow();
    void setPointers(QStandardItemModel *model, Data *data);

private slots:
    void on_addButton_clicked();

    void on_back_button_clicked();

    virtual void paintEvent(QPaintEvent *event);

private:
    Ui::addWindow *ui;

    Data *data;

    ProxyModel *proxyModel;

    QStandardItemModel *itemModel;
};

#endif // ADDWINDOW_H
