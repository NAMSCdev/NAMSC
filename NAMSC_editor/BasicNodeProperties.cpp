#include "BasicNodeProperties.h"

#include <QGraphicsScene>
#include <qmessagebox.h>

#include "Novel/Data/Novel.h"
#include "Novel/Event/EventChoice.h"

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
	if (currentlySelectedNode->getLabel() != lineEditText) {
		// Scene rename below
		if (Novel::getInstance().renameScene(currentlySelectedNode->getLabel(), lineEditText) == nullptr)
		{
			QMessageBox(QMessageBox::Critical, tr("Invalid scene name"), tr("Scene with this name already exists, please provide another name."), QMessageBox::Ok).exec();
			ui.nodeNameLineEdit->setText(currentlySelectedNode->getLabel()); // Revert change
			return;
		}
		else
		{
			// todo move this or similar to lib -> void renameSceneJumpsFor(QString scene, QString oldJumpToSceneName, QString newJumpToSceneName);
			// Update self jumps
			for (auto& ev : *Novel::getInstance().getScene(lineEditText)->getEvents())
			{
				switch (ev->getComponentEventType())
				{
				case EventSubType::EVENT_CHOICE:
					for (auto& choice : dynamic_cast<EventChoice*>(ev.get())->choices) {
						if (choice.jumpToSceneName == currentlySelectedNode->getLabel()) choice.jumpToSceneName = lineEditText;
					}
					break;
				case EventSubType::EVENT_JUMP:
					auto evj = dynamic_cast<EventJump*>(ev.get());
					if (evj->jumpToSceneName == currentlySelectedNode->getLabel()) evj->jumpToSceneName = lineEditText;
					break;
				}
			}

			// Update jumps from other scenes to this
			for (auto& conn : currentlySelectedNode->getConnectionPoints(GraphConnectionType::In))
			{
				for (auto& ev : *Novel::getInstance().getScene(conn->getSourceNodeName())->getEvents())
				{
					switch (ev->getComponentEventType())
					{
					case EventSubType::EVENT_CHOICE:
						for (auto& choice : dynamic_cast<EventChoice*>(ev.get())->choices) {
							if (choice.jumpToSceneName == currentlySelectedNode->getLabel()) choice.jumpToSceneName = lineEditText;
						}
						break;
					case EventSubType::EVENT_JUMP:
						auto evj = dynamic_cast<EventJump*>(ev.get());
						if (evj->jumpToSceneName == currentlySelectedNode->getLabel()) evj->jumpToSceneName = lineEditText;
						break;
					}
				}
				
			}



			currentlySelectedNode->setLabel(lineEditText);
			currentlySelectedNode->update();
			emit sceneUpdated(Novel::getInstance().getScene(lineEditText));

		}
	}
}
