#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include <QDialog>
#include "data.h"
namespace Ui {
class infoWindow;
}

class infoWindow : public QDialog
{
    Q_OBJECT

public:
    explicit infoWindow(QWidget *parent = nullptr);
    ~infoWindow();
    void getData(Data data);

    virtual void paintEvent(QPaintEvent *event);

private slots:
    void on_back_button_clicked();

private:
    Ui::infoWindow *ui;
};

#endif // INFOWINDOW_H
