#pragma once

#include <QFrame>

#include "LineEditDelegate.h"
#include "ui_ChoiceEventProperties.h"
#include "Novel/Event/EventChoice.h"
#include "GraphView.h"

class ChoiceEventProperties : public QFrame
{
	Q_OBJECT

public:
	ChoiceEventProperties(EventChoice* choices, GraphView* graph, QWidget *parent = nullptr);
	~ChoiceEventProperties();

protected:
	void contextMenuEvent(QContextMenuEvent* event) override;

private:
	EventChoice* choices;
	GraphView* graph;

	QAction* addChoiceAction;
	QAction* removeChoiceAction;

	LineEditDelegate lineEditDelegate;

	Ui::ChoiceEventPropertiesClass ui;

	inline static bool expanded = false;

	void prepareConnections();
	void prepareDataInUi();
	void createContextMenu();

private slots:
	void updateName(Choice* c, QString name);
	void updateJumpToSceneName(Choice* c, QString name);
	void updateCondition(Choice* c, QString cond);
	void updateText(Choice* c, QString text);
	void updateChoiceLabel();
};
