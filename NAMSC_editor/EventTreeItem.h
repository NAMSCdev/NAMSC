#pragma once
#include <QList>

#include "ObjectTreeWidgetItem.h"
#include "QVariant"
#include "Novel/Event/Event.h"
#include "Novel/SceneComponent.h"

class EventTreeItem
{
public:
    explicit EventTreeItem(SceneComponent* component, EventTreeItem* parentItem = nullptr);
    ~EventTreeItem();

    void appendChild(EventTreeItem* child);
    void removeChild(int row);
    EventTreeItem* child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    QVariant getName() const;
    QVariant getSubname() const;
    int row() const;
    EventTreeItem* parentItem();
    SceneComponent* component;

private:
    QList<EventTreeItem*> m_childItems;
    EventTreeItem* m_parentItem;
};

