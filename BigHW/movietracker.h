#ifndef MOVIETRACKER_H
#define MOVIETRACKER_H

#include <QDialog>
#include <vector>
#include <QStandardItemModel>
#include "data.h"
#include "proxymodel.h"

namespace Ui {
class MovieTracker;
}

class MovieTracker : public QDialog
{
    Q_OBJECT

public:
    explicit MovieTracker(QWidget *parent = nullptr);
    ~MovieTracker();
    void createList();

private slots:
    void on_search_button_clicked();

    void on_edit_button_clicked();

    void on_add_button_clicked();

    void on_info_button_clicked();

    void on_back_button_clicked();

    void on_delete_button_clicked();

    void on_save_button_clicked();

    void on_load_button_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    virtual void paintEvent(QPaintEvent *event);

private:
    Ui::MovieTracker *ui;

    std::vector<Data> dataVector;

    ProxyModel *proxyModel;

    QStandardItemModel* itemModel;
};

#endif // MOVIETRACKER_H
