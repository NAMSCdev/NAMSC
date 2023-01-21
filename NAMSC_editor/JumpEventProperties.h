#pragma once

#include <QFrame>

#include "GraphView.h"
#include "ui_JumpEventProperties.h"
#include "Novel/Event/EventJump.h"

class JumpEventProperties : public QFrame
{
	Q_OBJECT

public:
	JumpEventProperties(EventJump* jump, GraphView* graph, QWidget *parent = nullptr);
	~JumpEventProperties();

private:
	EventJump* jump;
	GraphView* graph;

	Ui::JumpEventPropertiesClass ui;

	inline static bool expanded = false;

	void prepareConnections();
	void prepareDataInUi();

private slots:
	void updateJumpToScene();
	void updateCondition();
};