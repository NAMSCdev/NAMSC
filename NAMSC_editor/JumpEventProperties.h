#pragma once

#include <QFrame>
#include "ui_JumpEventProperties.h"
#include "Novel/Event/EventJump.h"

class JumpEventProperties : public QFrame
{
	Q_OBJECT

public:
	JumpEventProperties(EventJump* jump, QWidget *parent = nullptr);
	~JumpEventProperties();

private:
	EventJump* jump;

	Ui::JumpEventPropertiesClass ui;

	void prepareConnections();
	void prepareDataInUi();

private slots:
	void updateJumpToScene();
	void updateCondition();
};
