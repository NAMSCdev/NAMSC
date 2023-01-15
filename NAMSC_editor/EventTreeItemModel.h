#pragma once
#include <qabstractitemmodel.h>

#include "EventTreeItem.h"
#include "GraphNode.h"
#include "PropertyTypes.h"
#include "Novel/Event/Event.h"
#include "QVariant"
#include "QObject"

class EventTreeItemModel :
    public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit EventTreeItemModel(const QString& data, QObject* parent = nullptr);
    ~EventTreeItemModel();

    QVariant data(const QModelIndex& index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
        int role = Qt::DisplayRole) const override;
    void appendEvent(Event* event, EventTreeItem* parentScene);
    void appendObject(SceneryObject* object, EventTreeItem* parentEvent);
    QModelIndex index(int row, int column,
                      const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex& index) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

public Q_SLOTS:
    void selectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
    void nodeSelectionChanged(GraphNode* node);
    void sceneUpdated(Scene* scene);

signals:
    void propertyTabChangeRequested(void* object, PropertyTypes dataType);
private:
    void setupModelData(Scene* scene);
    EventTreeItem* rootItem;
};

