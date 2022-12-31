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

	signals:
		void nodeSelectionChangedSignal(void* node, PropertyTypes dataType = PropertyTypes::Node);
};
