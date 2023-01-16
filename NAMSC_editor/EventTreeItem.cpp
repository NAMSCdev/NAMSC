#include "EventTreeItem.h"
#include "QVariant"
#include "Novel/Data/Scene.h"

EventTreeItem::EventTreeItem(SceneComponent* component, EventTreeItem* parent)
    : m_parentItem(parent), component(component)
{}

EventTreeItem::~EventTreeItem()
{
    qDeleteAll(m_childItems);
}

void EventTreeItem::appendChild(EventTreeItem* item)
{
    if (
        (component->getType() == NOT_COMPONENT) ||
        (item->component->getType() == EVENT && component->getType() == SCENE) ||
        (item->component->getType() == OBJECT && component->getType() == EVENT)
        )
    {
        m_childItems.append(item);
    }
}

void EventTreeItem::removeChild(int row)
{
    m_childItems.remove(row);
}

EventTreeItem* EventTreeItem::child(int row)
{
    if (row < 0 || row >= m_childItems.size())
        return nullptr;
    return m_childItems.at(row);
}

int EventTreeItem::childCount() const
{
    return m_childItems.count();
}

int EventTreeItem::row() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<EventTreeItem*>(this));

    return 0;
}

EventTreeItem* EventTreeItem::parentItem()
{
    return m_parentItem;
}

int EventTreeItem::columnCount() const
{
    return 2;
}

QVariant EventTreeItem::data(int column) const
{
	switch (column)
	{
	case 0:
        return component->getName();
	case 1:
        return component->getSubTypeName();
	}
    return QVariant();
}
