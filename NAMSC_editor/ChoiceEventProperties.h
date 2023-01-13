#pragma once

#include <QFrame>

#include "LineEditDelegate.h"
#include "ui_ChoiceEventProperties.h"
#include "Novel/Event/EventChoice.h"

class ChoiceEventProperties : public QFrame
{
	Q_OBJECT

public:
	ChoiceEventProperties(EventChoice* choices, QWidget *parent = nullptr);
	~ChoiceEventProperties();

protected:
	void contextMenuEvent(QContextMenuEvent* event) override;

private:
	EventChoice* choices;

	QAction* addChoiceAction;
	QAction* removeChoiceAction;

	LineEditDelegate lineEditDelegate;

	Ui::ChoiceEventPropertiesClass ui;

	void prepareConnections();
	void prepareDataInUi();
	void createContextMenu();

private slots:
	void updateName(Choice* c, QString name);
	void updateJumpToSceneName(Choice* c, QString name);
	void updateCondition(Choice* c, QString cond);
	void updateText(Choice* c, QString text);
};
