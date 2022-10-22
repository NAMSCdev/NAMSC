#include "GraphNode.h"

GraphNode::GraphNode(QGraphicsObject* parent)
	: QGraphicsObject(parent), nodeBody(GraphNodeBody(this, QRectF(0, 0, 300, 200)))
{
	//setParent(parent);
	setFlag(ItemHasNoContents);
	setFlag(ItemIsMovable);
}

GraphNode::~GraphNode()
{ }

QRectF GraphNode::boundingRect() const
{
	QRectF retVal = nodeBody.boundingRect();

	return retVal;
}

void GraphNode::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	Q_UNUSED(painter);
	Q_UNUSED(option);
	Q_UNUSED(widget);
}

void GraphNode::setLabel(QString label)
{
	nodeBody.label = label;
}
