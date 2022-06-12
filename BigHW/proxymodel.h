#ifndef PROXYMODEL_H
#define PROXYMODEL_H
#include <QSortFilterProxyModel>

class ProxyModel : public QSortFilterProxyModel
{
    public:
        ProxyModel(QObject *parent = 0);

        //Setters
        void setTitle(QString title);

        void setStatus(QString status);

        //Getters
        QString getTitle() const;

        QString getStatus() const;

    protected:
       bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;

       bool lessThan(const QModelIndex& left, const QModelIndex& right) const override;

    private:
        QString title;

        QString status;
};

#endif // PROXYMODEL_H
