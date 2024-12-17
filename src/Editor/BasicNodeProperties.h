#pragma once
#include <QFrame>

#include "CollapseButton.h"
#include "EventTreeItemModel.h"
#include "GraphNode.h"

#include "ui_BasicNodeProperties.h"

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

    signals:
    void sceneUpdated(Scene* scene);

private:
	bool instantTextChangeUpdate = false;
	GraphNode* currentlySelectedNode;

	Ui::BasicNodePropertiesClass ui;

	inline static bool expanded = false;

private slots:
	void updateLabelInNode();
};
