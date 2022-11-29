#include "BasicNodeProperties.h"

#include <QGraphicsScene>

BasicNodeProperties::BasicNodeProperties(QGraphicsScene* scene, QWidget *parent)
	: QFrame(parent), scene(scene)
{
	ui.setupUi(this);
	ui.collapseButton->setContent(ui.content);
	ui.collapseButton->setText("Basic node properties");
	connect(scene, &QGraphicsScene::selectionChanged, this, &BasicNodeProperties::selectedNodeChanged);
}

BasicNodeProperties::~BasicNodeProperties()
{}

void BasicNodeProperties::setScene(QGraphicsScene* scene)
{
	this->scene = scene;
}

// TODO potentially disconnect signals from on change or upon node change
void BasicNodeProperties::updateConnections(bool b)
{
	instantTextChangeUpdate = b;

	if (not instantTextChangeUpdate) {
		connect(ui.nodeNameLineEdit, &QLineEdit::editingFinished, this, &BasicNodeProperties::updateLabelInNode);
	}
	else
	{
		connect(ui.nodeNameLineEdit, &QLineEdit::textChanged, qgraphicsitem_cast<GraphNode*>(scene->selectedItems().first()), &GraphNode::setLabel);
	}
}

void BasicNodeProperties::selectedNodeChanged()
{
	updateConnections(instantTextChangeUpdate);
	if (scene->selectedItems().isEmpty())
	{
		ui.nodeNameLineEdit->setText("");
	}
	else {
		ui.nodeNameLineEdit->setText(qgraphicsitem_cast<GraphNode*>(scene->selectedItems().first())->getLabel());
	}
}

void BasicNodeProperties::updateLabelInNode()
{
	if (not scene->selectedItems().isEmpty())
	{
		qgraphicsitem_cast<GraphNode*>(scene->selectedItems().first())->setLabel(ui.nodeNameLineEdit->text());
	}
}
