#pragma once

#include <QGraphicsView>
#include <qitemselectionmodel.h>

class Preview  : public QGraphicsView
{
	Q_OBJECT

public:
	Preview(QWidget *parent);
	~Preview();

	void dragEnterEvent(QDragEnterEvent* event) override;
	void dropEvent(QDropEvent* event) override;

public slots:
	void selectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
};
