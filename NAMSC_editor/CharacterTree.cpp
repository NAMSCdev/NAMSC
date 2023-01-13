#include "CharacterTree.h"

#include <QContextMenuEvent>
#include <QMenu>

#include "ProjectConfiguration.h"
#include "Novel/Data/Novel.h"

CharacterTree::CharacterTree(QWidget *parent) : QTreeWidget(parent)
{
	createContextMenu();
}

void CharacterTree::addAssetToCharacters(QString path, QString name, TreeWidgetItemTypes type)
{
	CharacterTreeWidgetItem* tempTreeItem;

	if (type == TreeWidgetItemTypes::ImageObject)
	{
		Character tempCharacter;
		tempCharacter.name = name;
		tempCharacter.setAssetImage(path);
		Novel::getInstance().setDefaultCharacter(name, tempCharacter);

		tempTreeItem = new CharacterTreeWidgetItem(this, static_cast<int>(type));
		tempTreeItem->character = Novel::getInstance().getDefaultCharacter(name);
		tempTreeItem->setIcon(0, QIcon(":/NAMSC_editor/imageIcon")); // todo change to character icon or make it iconless
	}
	else
	{
		// todo error?
	}

	tempTreeItem->relativeAssetPath = ProjectConfiguration::getInstance()->getProjectPath().relativeFilePath(path);

	tempTreeItem->setText(0, name);

	addTopLevelItem(tempTreeItem);
}

void CharacterTree::selectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
	if (selectedItems().size() > 0) {
		emit selectedCharacterChanged(selectedItems().first()->text(0));
	}
	QTreeWidget::selectionChanged(selected, deselected);
}

void CharacterTree::contextMenuEvent(QContextMenuEvent* event)
{
	if (selectedItems().size() > 0)
	{
		contextMenuInvokePosition = event->globalPos();

		QMenu menu(this);
		menu.addAction(addCharacterToSceneAction);
		menu.exec(event->globalPos());
	}
}

void CharacterTree::mousePressEvent(QMouseEvent* event)
{
	// clearSelection(); // todo deselection in preview
	QTreeWidget::mousePressEvent(event);
}

void CharacterTree::createContextMenu()
{
	addCharacterToSceneAction = new QAction(tr("Add character to scene"), this);
	addCharacterToSceneAction->setStatusTip(tr("Character will be added to the currently edited scene"));

	connect(addCharacterToSceneAction, &QAction::triggered, this, [&]
		{
			emit addCharacterToScene(dynamic_cast<CharacterTreeWidgetItem*>(this->currentItem()));
		});
}
