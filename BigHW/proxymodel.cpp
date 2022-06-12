#include "proxymodel.h"

ProxyModel::ProxyModel(QObject* parent) : QSortFilterProxyModel(parent)
{
    title = QString();
    status = QString();
}

//Setters
void ProxyModel::setTitle(QString title)
{
    this -> title = title.trimmed().isEmpty() ? QString() : title;
    invalidateFilter();
}

void ProxyModel::setStatus(QString status)
{
    this -> status = status;
    invalidateFilter();
}
//Getters
QString ProxyModel::getTitle() const
{
    return title;
}
QString ProxyModel::getStatus() const
{
    return status;
}
//Less than (checks if the left element is first)
bool ProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{

    QString lenA = sourceModel()->data(left).toString();
    QString lenB = sourceModel()->data(right).toString();

    return lenA < lenB;
}
bool ProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex title_index = sourceModel()->index(sourceRow, 0, sourceParent);
    QString title = sourceModel()->data(title_index).toString();

    QModelIndex status_index = sourceModel() -> index(sourceRow, 1, sourceParent);
    QString status = sourceModel() -> data(status_index).toString();

    return status == this -> status || title == this -> title;
}

