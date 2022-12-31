#include "BasicNodeProperties.h"

#include <QGraphicsScene>

BasicNodeProperties::BasicNodeProperties(GraphNode* node, QWidget *parent)
	: QFrame(parent), currentlySelectedNode(node)
{
	ui.setupUi(this);
	ui.collapseButton->setContent(ui.content);
	ui.collapseButton->setText("Basic node properties");
	//connect(scene, &QGraphicsScene::selectionChanged, this, &BasicNodeProperties::selectedNodeChanged);
	selectedNodeChanged();
}

BasicNodeProperties::~BasicNodeProperties()
{}

//void BasicNodeProperties::setScene(QGraphicsScene* scene)
//{
//	this->scene = scene;
//}

// TODO potentially disconnect signals from on change or upon node change
void BasicNodeProperties::updateConnections(bool b)
{
	instantTextChangeUpdate = b;

	if (not instantTextChangeUpdate) {
		connect(ui.nodeNameLineEdit, &QLineEdit::editingFinished, this, &BasicNodeProperties::updateLabelInNode);
	}
	else
	{
		connect(ui.nodeNameLineEdit, &QLineEdit::textChanged, currentlySelectedNode, &GraphNode::setLabel);
	}
}

void BasicNodeProperties::selectedNodeChanged()
{
	updateConnections(instantTextChangeUpdate);
	//if (scene->selectedItems().isEmpty())
	//{
	//	ui.nodeNameLineEdit->setText("");
	//	ui.nodeNameLineEdit->setEnabled(false);
	//}
	//else {
		ui.nodeNameLineEdit->setText(currentlySelectedNode->getLabel());
	//}
}

void BasicNodeProperties::updateLabelInNode()
{
	//if (not scene->selectedItems().isEmpty())
	//{
	//	qgraphicsitem_cast<GraphNode*>(scene->selectedItems().first())->setLabel(ui.nodeNameLineEdit->text());
	//}
	currentlySelectedNode->setLabel(ui.nodeNameLineEdit->text());
}
