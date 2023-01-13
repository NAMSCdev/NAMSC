#include "EventTreeItemModel.h"

#include "EventTreeItem.h"
#include "QVariant"
#include "Novel/Data/Novel.h"
#include "Novel/Data/Scene.h"
#include "Novel/Event/EventDialogue.h"

EventTreeItemModel::EventTreeItemModel(const QString& data, QObject* parent)
    : QAbstractItemModel(parent)
{
    rootItem = new EventTreeItem( new DummySceneComponent);
}

EventTreeItemModel::~EventTreeItemModel()
{
    delete rootItem;
}

QModelIndex EventTreeItemModel::parent(const QModelIndex& index) const
{
    if (!index.isValid())
        return QModelIndex();

    EventTreeItem* childItem = static_cast<EventTreeItem*>(index.internalPointer());
    EventTreeItem* parentItem = childItem->parentItem();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

QModelIndex EventTreeItemModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    EventTreeItem* parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<EventTreeItem*>(parent.internalPointer());

    EventTreeItem* childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    return QModelIndex();
}

int EventTreeItemModel::rowCount(const QModelIndex& parent) const
{
    EventTreeItem* parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<EventTreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

int EventTreeItemModel::columnCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return static_cast<EventTreeItem*>(parent.internalPointer())->columnCount();
    return rootItem->columnCount();
}

void EventTreeItemModel::nodeSelectionChanged(GraphNode* node)
{
    setupModelData(Novel::getInstance().getScene(node->getLabel()));
}

QVariant EventTreeItemModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
    {
        qDebug() << "EventTreeItemModel::data - Invalid index: " << index;
        return QVariant();
    }
		
    if (role != Qt::DisplayRole)
        return QVariant();

    EventTreeItem* item = static_cast<EventTreeItem*>(index.internalPointer());

    qDebug() << "EventTreeItemModel::data " << item->data(0);
    return item->data(index.column());
}

Qt::ItemFlags EventTreeItemModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
    {
        return Qt::NoItemFlags;
    }

    return QAbstractItemModel::flags(index);
}

QVariant EventTreeItemModel::headerData(int section, Qt::Orientation orientation,
    int role) const
{
    QList<QVariant> list = { QString("Name"),QString("Type")};
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole && section < list.count())
        return list.at(section);

    return QVariant();
}

void EventTreeItemModel::appendEvent(Event* event, EventTreeItem* parentScene)
{
    EventTreeItem* eventItem = new EventTreeItem(event, parentScene);
    parentScene->appendChild(eventItem);

    /* where are objects held?
    for (int i = 0; i < event->getObjects()->size(); i++)
    {
        appendObject(event->getObjects()->at(i).get(), eventItem);
    }
    */
}

void EventTreeItemModel::setupModelData(Scene* scene)
{
    beginResetModel();
    if(rootItem->childCount()!=0) rootItem->removeChild(0);
    SceneComponent* rootComponent = dynamic_cast<SceneComponent*>(scene);
    qDebug() << rootComponent->getName() << " " << rootComponent->getTypeName();
    EventTreeItem* sceneItem = new EventTreeItem(scene, rootItem);
    rootItem->appendChild(sceneItem);
    qDebug() << rowCount();
    rootItem->child(0)->data(0);
    for (int i = 0 ; i < scene->getEvents()->size() ; i++)
    {
        appendEvent(scene->getEvents()->at(i).get(), sceneItem);
    }
    endResetModel();
    
    /*
    auto dialogue1 = new EventDialogue(dynamic_cast<Scene*>(sceneItem->component));
    dialogue1->label = "Test Event";
    dialogue1->sentences.emplace_back(dialogue1, dialogue1->parentScene_);
    auto eventItem1 = new EventTreeItem(dialogue1, sceneItem);
    sceneItem->appendChild(eventItem1);


    auto dialogue2 = new EventDialogue(dynamic_cast<Scene*>(sceneItem->component));
    dialogue2->label = "Test Event 2";
    dialogue2->sentences.emplace_back(dialogue2, dialogue2->parentScene_);
    auto eventItem2 = new EventTreeItem(dialogue1, sceneItem);
    sceneItem->appendChild(eventItem2);
    */
    
    /*
    auto event2 = new EventTreeItem({ tr("Event2"), tr("Summary") }, sceneItem);
    sceneItem->appendChild(event2);

    auto event3 = new EventTreeItem({ tr("Event3"), tr("Summary") }, sceneItem);
    sceneItem->appendChild(event3);

    event2->appendChild(new EventTreeItem({ tr("Character1"), tr("Summary") }, event2));
    event2->appendChild(new EventTreeItem({ tr("Object1"), tr("Summary") }, event2));
    event2->appendChild(new EventTreeItem({ tr("Object1"), tr("Summary") }, event2));

    eventItem1->appendChild(new EventTreeItem({ tr("Character1"), tr("Summary") }, eventItem1));
    eventItem1->appendChild(new EventTreeItem({ tr("Object1"), tr("Summary") }, eventItem1));
    */
}