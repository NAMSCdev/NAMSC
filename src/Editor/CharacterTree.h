#pragma once
#include <QTreeWidget>

#include "CharacterTreeWidgetItem.h"
#include "TreeWidgetItemTypes.h"

class CharacterTree  : public QTreeWidget
{
	Q_OBJECT

public:
	CharacterTree(QWidget *parent = nullptr);


public slots:
	void addAssetToCharacters(QString path, QString name, TreeWidgetItemTypes type);

	signals:
	 void addCharacterToScene(CharacterTreeWidgetItem* character);
	 void selectedCharacterChanged(QString characterName);

protected:
	void selectionChanged(const QItemSelection& selected, const QItemSelection& deselected) override;
	void contextMenuEvent(QContextMenuEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;

private:
	Q_DISABLE_COPY(CharacterTree);

	QPointF contextMenuInvokePosition;

	QAction* addCharacterToSceneAction;
	QAction* removeCharacterFromTreeAction; // TODO remove character from characterTree

	void createContextMenu();
};
