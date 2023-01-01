#pragma once
#include <qsortfilterproxymodel.h>
class CustomSortFilterProxyModel :
    public QSortFilterProxyModel
{
    std::function < bool(int, const QModelIndex&) > _filter = [](int source_row, const QModelIndex& source_parent)
    {
    	return true;
    };
protected:
    bool filterAcceptsRow(int source_row, const QModelIndex& source_parent) const override {
        return _filter(source_row, source_parent);
    }
public:
    CustomSortFilterProxyModel(QObject* parent = nullptr) : QSortFilterProxyModel(parent) {}
    void setFilter(std::function < bool(int, const QModelIndex&) >  filter) { _filter = filter; }
};

