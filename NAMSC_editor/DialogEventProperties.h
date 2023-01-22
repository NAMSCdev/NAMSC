#pragma once

#include <QFrame>

#include "LineEditDelegate.h"
#include "ui_DialogEventProperties.h"
#include "Novel/Event/EventDialogue.h"

class DialogEventProperties : public QFrame
{
	Q_OBJECT

public:
	DialogEventProperties(EventDialogue* dialogue, QWidget *parent = nullptr);

	~DialogEventProperties();

protected:
	void contextMenuEvent(QContextMenuEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;

private:
	EventDialogue* dialogue;

	QAction* addSentenceAction;
	QAction* removeSentenceAction;

	LineEditDelegate lineEditDelegate;
	QModelIndex lastClickedModelIndex;

	Ui::DialogEventPropertiesClass ui;

	inline static bool expanded = false;

	void prepareConnections();
	void prepareDataInUi();
	void createContextMenu();

private slots:
	void changeTextEdit(const QModelIndex& index);
	void changeModelItem();
};
