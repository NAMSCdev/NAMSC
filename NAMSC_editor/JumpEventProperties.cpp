#include "JumpEventProperties.h"

JumpEventProperties::JumpEventProperties(EventJump* jump, GraphView* graph, QWidget *parent)
	: QFrame(parent), jump(jump), graph(graph)
{
	ui.setupUi(this);

	ui.jumpEventCollapseButton->setContent(ui.jumpEventContent);
	ui.jumpEventCollapseButton->setText(tr("Jump event properties"));
	if (expanded) ui.jumpEventCollapseButton->toggle();

	prepareDataInUi();
	prepareConnections();
}

JumpEventProperties::~JumpEventProperties()
{}

void JumpEventProperties::prepareConnections()
{
	connect(ui.jumpEventCollapseButton, &CollapseButton::clicked, this, [] { expanded = !expanded; });

	// If we want to check there, then instead of textChanged -> editingFinished
	connect(ui.jumpToSceneLineEdit, &QLineEdit::textChanged, this, &JumpEventProperties::updateJumpToScene);
	connect(ui.conditionLineEdit, &QLineEdit::textChanged, this, &JumpEventProperties::updateCondition);
}

void JumpEventProperties::prepareDataInUi()
{
	ui.jumpToSceneLineEdit->setText(jump->jumpToSceneName);
	ui.conditionLineEdit->setText(jump->condition);

	if (graph->getNodeByName(jump->jumpToSceneName) == nullptr)
	{
		QPalette palette;
		palette.setColor(QPalette::Base, QColor(255, 70, 70));
		ui.jumpToSceneLineEdit->setPalette(palette);
	}
}

void JumpEventProperties::updateJumpToScene()
{
	QPalette palette;
	const QString nodeToJump = ui.jumpToSceneLineEdit->text();
	const auto node = graph->getNodeByName(jump->parentScene->name);

	node->disconnectFrom(jump->jumpToSceneName);

	if (graph->getNodeByName(nodeToJump) != nullptr) {
		node->connectToNode(nodeToJump);
		palette.setColor(QPalette::Base, Qt::white);
	}
	else
	{
		palette.setColor(QPalette::Base, QColor(255, 70, 70));
	}

	ui.jumpToSceneLineEdit->setPalette(palette);
	jump->jumpToSceneName = nodeToJump;
}

void JumpEventProperties::updateCondition()
{
	jump->condition = ui.conditionLineEdit->text();
}
