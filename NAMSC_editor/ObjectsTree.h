#pragma once

#include <QTreeWidget>

#include "ObjectTreeWidgetItem.h"
#include "TreeWidgetItemTypes.h"
#include "Novel/Data/Visual/Scenery/SceneryObject.h"

class ObjectsTree : public QTreeWidget
{
	Q_OBJECT

public:
	ObjectsTree(QWidget *parent = nullptr);

	// TODO serialization / deserialization 
	// void serialize();
	// void deserialize();

public slots:
	void addAssetToObjects(QString path, QString name, TreeWidgetItemTypes type);

	signals:
	void addObjectToScene(ObjectTreeWidgetItem* object);
	// to czy item zawiera wskaznik na dzwiek lub grafike mozna sprawdzic object->type() == "TreeWidgetItemTypes.h" lub po nullptr
	// chwilowo nie ma pola dla dzwieku wiec sugeruje sprawdzanie po typie
	void selectedObjectChanged(QString sceneryObjectName);

protected:
	void selectionChanged(const QItemSelection& selected, const QItemSelection& deselected) override;
	void contextMenuEvent(QContextMenuEvent*) override;
	void mousePressEvent(QMouseEvent* event) override;

private:
	Q_DISABLE_COPY(ObjectsTree)

	QPointF contextMenuInvokePosition;

	QAction* addObjectToSceneAction;
	QAction* removeObjectFromTreeAction; // TODO add remove object from ObjectTree

	void createContextMenu();
};
