#include "JumpEventProperties.h"

JumpEventProperties::JumpEventProperties(EventJump* jump, QWidget *parent)
	: QFrame(parent), jump(jump)
{
	ui.setupUi(this);

	ui.jumpEventCollapseButton->setContent(ui.jumpEventContent);
	ui.jumpEventCollapseButton->setText(tr("Jump event properties"));

	prepareDataInUi();
	prepareConnections();
}

JumpEventProperties::~JumpEventProperties()
{}

void JumpEventProperties::prepareConnections()
{
	// If we want to check there, then instead of textChanged -> editingFinished
	connect(ui.jumpToSceneLineEdit, &QLineEdit::textChanged, this, &JumpEventProperties::updateJumpToScene);
	connect(ui.conditionLineEdit, &QLineEdit::textChanged, this, &JumpEventProperties::updateCondition);
}

void JumpEventProperties::prepareDataInUi()
{
	ui.jumpToSceneLineEdit->setText(jump->jumpToSceneName);
	ui.conditionLineEdit->setText(jump->condition);
}

void JumpEventProperties::updateJumpToScene()
{
	jump->jumpToSceneName = ui.jumpToSceneLineEdit->text();
}

void JumpEventProperties::updateCondition()
{
	jump->condition = ui.conditionLineEdit->text();
}
