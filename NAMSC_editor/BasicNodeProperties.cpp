#include "BasicNodeProperties.h"

#include <QGraphicsScene>
#include <qmessagebox.h>

#include "Novel/Data/Novel.h"

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
	ui.nodeNameLineEdit->setText(currentlySelectedNode->getLabel());
}

void BasicNodeProperties::updateLabelInNode()
{
	QString lineEditText = ui.nodeNameLineEdit->text();

	if (Novel::getInstance().renameScene(currentlySelectedNode->getLabel(), lineEditText) == nullptr)
	{
		QMessageBox(QMessageBox::Critical, tr("Invalid scene name"), tr("Scene with this name already exists, please provide another name."), QMessageBox::Ok).exec();
		ui.nodeNameLineEdit->setText(currentlySelectedNode->getLabel()); // Revert change
		return;
	}
	else
	{
		currentlySelectedNode->setLabel(lineEditText);
		currentlySelectedNode->update();
    emit sceneUpdated(Novel::getInstance().getScene(lineEditText));
	}
}
