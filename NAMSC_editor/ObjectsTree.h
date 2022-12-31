#pragma once

#include <QTreeWidget>

class ObjectsTree : public QTreeWidget
{
	Q_OBJECT

public:
	ObjectsTree(QWidget *parent);
	~ObjectsTree();
};
