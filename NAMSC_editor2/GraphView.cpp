#include "GraphView.h"
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
