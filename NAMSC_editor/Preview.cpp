#include "Preview.h"
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>


Preview::Preview(QWidget *parent)
	: QGraphicsView(parent)
{
	this->setAcceptDrops(true);
}

Preview::~Preview()
{}

void Preview::dragEnterEvent(QDragEnterEvent* event)
{
	if (event->mimeData()->hasUrls())
		event->acceptProposedAction();
}

void Preview::dropEvent(QDropEvent* event)
{
	if (event->mimeData()->hasUrls()) {
		qDebug() << "Dropped file " + event->mimeData()->urls().takeAt(0).fileName();
	}
}

void Preview::selectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
	qDebug() << "Selected " << selected.indexes()[0];
}

