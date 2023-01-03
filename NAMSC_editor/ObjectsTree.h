#pragma once

#include <QTreeWidget>

#include "TreeWidgetItemTypes.h"

class ObjectsTree : public QTreeWidget
{
	Q_OBJECT

public:
	ObjectsTree(QWidget *parent = nullptr);

	// TODO serialization / deserialization 
	// void serialize();
	// void deserialize();

	signals:
		void addObjectToScene(QTreeWidgetItem* object, TreeWidgetItemTypes type); // JAKUBIE TUTAJ SIE PODLACZ

protected:
	void selectionChanged(const QItemSelection& selected, const QItemSelection& deselected) override;
	void contextMenuEvent(QContextMenuEvent*) override;

private:
	Q_DISABLE_COPY(ObjectsTree);

	QPointF contextMenuInvokePosition;

	QAction* addObjectToSceneAction;
	QAction* removeObjectFromTreeAction; // TODO

	void createContextMenu();
};
