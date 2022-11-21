#pragma once
#include <QObject>

#include "GraphNode.h"

class NodeManager : public QObject
{
public:
	void addNode(GraphNode* node);
	GraphNode* at(size_t index);
	bool removeNode(size_t index);
	bool removeNode(GraphNode* node);

private:
	QVector<GraphNode*> nodeVector; // Replace with QMultiMap?
};

