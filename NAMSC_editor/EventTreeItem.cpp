#include "EventTreeItem.h"
#include "QVariant"
#include "Novel/Data/Scene.h"

EventTreeItem::EventTreeItem(SceneComponent* component, EventTreeItem* parent)
    : m_parentItem(parent), component(component), flags(Qt::ItemIsSelectable | Qt::ItemIsEnabled)
{}

EventTreeItem::~EventTreeItem()
{
    qDeleteAll(m_childItems);
}

void EventTreeItem::appendChild(EventTreeItem* item)
{
    if (
        (component->getComponentType() == NOT_COMPONENT) ||
        (item->component->getComponentType() == EVENT && component->getComponentType() == SCENE) ||
        (item->component->getComponentType() == CHARACTERS_ROOT && component->getComponentType() == EVENT) ||
        (item->component->getComponentType() == OBJECTS_ROOT && component->getComponentType() == EVENT) ||
        (item->component->getComponentType() == CHARACTER && component->getComponentType() == CHARACTERS_ROOT) ||
        (item->component->getComponentType() == OBJECT && component->getComponentType() == OBJECTS_ROOT)
        )
    {
        m_childItems.append(item);
    } else
    {
	    qDebug() << "Item of type " << item->component->getComponentType() << " cant be child of " << component->getComponentType(); 
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

Qt::ItemFlags EventTreeItem::getFlags()
{
    return flags;
}

void EventTreeItem::setFlags(Qt::ItemFlags flags)
{
    this->flags = flags;
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
        return component->getComponentName();
	case 1:
        return component->getComponentSubTypeName();
	}
    return QVariant();
}
