#include "EventTreeItemModel.h"

#include "EventTreeItem.h"
#include "QVariant"
#include "Novel/Data/Novel.h"
#include "Novel/Data/Scene.h"
#include "Novel/Event/EventDialogue.h"
#include "Novel/Event/EventChoice.h"
#include "Novel/Event/EventJump.h"

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

void EventTreeItemModel::sceneUpdated(Scene* scene)
{
    qDebug() << "Scene updated";
    if (scene == nullptr) setupModelData(nullptr);
    else setupModelData(Novel::getInstance().getScene(scene->getComponentName()));
}

void EventTreeItemModel::sceneDeleted()
{
    sceneUpdated(nullptr);
}

void EventTreeItemModel::selectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
    if(selected.size() > 0 && selected.indexes().size() > 0)
    {
        QModelIndex index = selected.indexes().at(0);
        qDebug() << data(index, Qt::DisplayRole);
        EventTreeItem* item = static_cast<EventTreeItem*>(index.internalPointer());
        switch(item->component->getComponentType())
        {
        case SCENE:
            qDebug() << item->component->getComponentName();
            emit propertyTabChangeRequested(static_cast<Scene*>(item->component), PropertyTypes::Scene);
            break;
        case EVENT:
            switch(item->component->getComponentEventType())
            {
            case EventSubType::EVENT_DIALOG:
                emit propertyTabChangeRequested(static_cast<EventDialogue*>(item->component), PropertyTypes::DialogEventItem);
                break;
            case EventSubType::EVENT_JUMP:
                emit propertyTabChangeRequested(static_cast<EventJump*>(item->component), PropertyTypes::JumpEventItem);
                break;
            case EventSubType::EVENT_CHOICE:
                emit propertyTabChangeRequested(static_cast<EventChoice*>(item->component), PropertyTypes::ChoiceEventItem);
                break;
            }
            break;
        case OBJECT:
            emit propertyTabChangeRequested(item->component, PropertyTypes::ObjectOnScene);
        	break;
        case CHARACTER:
            emit propertyTabChangeRequested(item->component, PropertyTypes::ObjectOnScene);
            break;
        }
    }
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
    
    return item->data(index.column());
}

Qt::ItemFlags EventTreeItemModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
    {
        return Qt::NoItemFlags;
    }

    return static_cast<EventTreeItem*>(index.internalPointer())->getFlags();
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
    

    if (event->getComponentEventType() != EventSubType::EVENT_JUMP)
    {
	    EventTreeItem* objectsRoot = new EventTreeItem(new SceneryObjectsRootSceneComponent(), eventItem);
        objectsRoot->setFlags( Qt::ItemIsEnabled);
	    eventItem->appendChild(objectsRoot);

	    for ( int i = 0 ; i < event->scenery.getDisplayedSceneryObjects()->size(); i++)
	    {
			EventTreeItem* objectItem = new EventTreeItem( event->scenery.getDisplayedSceneryObject(i), objectsRoot);
			objectsRoot->appendChild(objectItem);
	    }

	    EventTreeItem* charactersRoot = new EventTreeItem(new CharactersRootSceneComponent(), eventItem);
        charactersRoot->setFlags( Qt::ItemIsEnabled);
	    eventItem->appendChild(charactersRoot);

	    for ( int i = 0 ; i < event->scenery.getDisplayedCharacters()->size(); i++)
	    {
			EventTreeItem* characterItem = new EventTreeItem( event->scenery.getDisplayedCharacter(i), charactersRoot);
			charactersRoot->appendChild(characterItem);
	    }
    }

    parentScene->appendChild(eventItem);
}

void EventTreeItemModel::refresh()
{
    if(rootItem->childCount() > 0)
    {
		setupModelData(static_cast<Scene*>(rootItem->child(0)->component));   
    }
}

void EventTreeItemModel::setupModelData(Scene* scene)
{
    beginResetModel();
    if(rootItem->childCount()!=0) rootItem->removeChild(0);
    SceneComponent* rootComponent = dynamic_cast<SceneComponent*>(scene);
    if (rootComponent != nullptr) {
        qDebug() << "Setting EventsTree with root: " << rootComponent->getComponentName() << " " << rootComponent->getComponentTypeName();
        EventTreeItem* sceneItem = new EventTreeItem(scene, rootItem);
        rootItem->appendChild(sceneItem);
        rootItem->child(0)->data(0);
        for (int i = 0; i < scene->getEvents()->size(); i++)
        {
            appendEvent(scene->getEvents()->at(i).get(), sceneItem);
        }
    }
    endResetModel();
}