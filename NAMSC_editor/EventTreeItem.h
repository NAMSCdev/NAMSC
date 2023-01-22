#pragma once
#include <QList>

#include "ObjectTreeWidgetItem.h"
#include "QVariant"
#include "Novel/Event/Event.h"
#include "Novel/SceneComponent.h"
#include "EventTreeItem.h"

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
    QVariant getComponentName() const;
    QVariant getSubname() const;
    int row() const;
    EventTreeItem* parentItem();
    Qt::ItemFlags getFlags();
    void setFlags(Qt::ItemFlags flags);
    SceneComponent* component;

private:
    QList<EventTreeItem*> m_childItems;
    EventTreeItem* m_parentItem;
    Qt::ItemFlags flags;
};

