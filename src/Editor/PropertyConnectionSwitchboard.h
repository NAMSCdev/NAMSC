#pragma once

#include <QObject>

#include "GraphNode.h"
#include "PropertyTypes.h"

class PropertyConnectionSwitchboard : public QObject
{
	Q_OBJECT

public:
	PropertyConnectionSwitchboard();
	~PropertyConnectionSwitchboard();

public slots:
	void nodeSelectionChanged(GraphNode* node);
	void objectSelectionChanged(QString sceneryObjectName);
	void characterSelectionChanged(QString characterName);

	signals:
		void nodeSelectionChangedSignal(void* node, PropertyTypes dataType = PropertyTypes::Node);
		void sceneryObjectSelectionChangedSignal(void* object, PropertyTypes dataType = PropertyTypes::ObjectTreeItem);
		void characterSelectionChangedSignal(void* object, PropertyTypes dataType = PropertyTypes::ObjectTreeItem);
};
