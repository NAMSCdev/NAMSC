#include "GraphView.h"
#include <nodes/Node>
#include <nodes/FlowScene>
#include <QMouseEvent>

GraphView::GraphView(FlowScene* scene)
	: QtNodes::FlowView(scene), _scene(scene)
{}

GraphView::~GraphView()
{}

void GraphView::addNode(const QString& modelName, const QPoint& pos)
{
	qDebug() << "Add node";

	auto type = _scene->registry().create(modelName);
	if (type) {
		auto& node = _scene->createNode(std::move(type));
		node.nodeGraphicsObject().setPos(mapToScene(pos));
	}
	else {
		// Exception?
	}
}

void GraphView::mousePressEvent(QMouseEvent* event)
{
	FlowView::mousePressEvent(event);

	if (event->button() == Qt::RightButton) {
		qDebug() << "right button pressed on graph view!";
		if (itemAt(event->pos())) {
			qDebug() << "Pressed item: " << "pos: " << itemAt(event->pos());
		}
	}
}
