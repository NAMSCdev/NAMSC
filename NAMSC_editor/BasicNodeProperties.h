#pragma once

#include <QFrame>

#include "GraphNode.h"
#include "ui_BasicNodeProperties.h"
#include "CollapseButton.h"

class BasicNodeProperties : public QFrame
{
	Q_OBJECT

public:
	BasicNodeProperties(GraphNode* node, QWidget *parent = nullptr);
	~BasicNodeProperties();

	//void setScene(QGraphicsScene* scene);

	void updateConnections(bool b);

public slots:
	void selectedNodeChanged();

private:
	bool instantTextChangeUpdate = false;
	GraphNode* currentlySelectedNode;

	Ui::BasicNodePropertiesClass ui;


private slots:
	void updateLabelInNode();
};
