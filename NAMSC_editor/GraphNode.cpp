#include "GraphNode.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

#include "GraphView.h"

GraphNode::GraphNode(QGraphicsObject* parent)
	: QGraphicsObject(parent), nodeBody(GraphNodeBody(this, QRectF(0, 0, 300, 200)))
{
	//setParent(parent);
	setFlags();
	//setZValue(-1); // example zvalue usage
}

GraphNode::GraphNode(const QPoint& pos, QGraphicsObject* parent) : QGraphicsObject(parent), nodeBody(GraphNodeBody(this, QRectF(0, 0, 300, 200)))
{
	moveBy(pos.x(), pos.y());
	setFlags();
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
	Q_UNUSED(painter)
	Q_UNUSED(option)
	Q_UNUSED(widget)
}

void GraphNode::setLabel(QString label)
{
	nodeBody.label = label;

	// Update input names for arrows
	for (auto& elem : inputConnectionPointList)
	{
		elem.get()->setDestinationNodeName(label);
	}

	// Update output labels for arrows
	for (auto& elem : outputConnectionPointList)
	{
		elem.get()->setSourceNodeName(label);
	}
}

std::shared_ptr<GraphConnectionPoint> GraphNode::appendConnectionPoint(GraphConnectionType type)
{
	auto point = std::shared_ptr<GraphConnectionPoint>(new GraphConnectionPoint(this));
	//QPointF pointPos{ pos().x(), pos().y() + boundingRect().height() / 5 };
	QPointF pointPos{ 0, boundingRect().height() / 5 };
	QPointF delta;
	
	switch (type) {
	case GraphConnectionType::In:
		pointPos.setX(pointPos.x() + 5);
		inputConnectionPointList.append(point);
		delta = { 0, boundingRect().height() / inputConnectionPointList.size() * 0.6 };
		for (auto elem : inputConnectionPointList) {
			elem->setPos(pointPos + (delta / 2) - QPointF{ 0, elem->boundingRect().height() / 2 });
			pointPos += delta;
		}
		break;
	case GraphConnectionType::Out:
		pointPos.setX(pointPos.x() + boundingRect().width() - point->boundingRect().width() - 5);
		outputConnectionPointList.append(point);
		delta = { 0, boundingRect().height() / outputConnectionPointList.size() * 0.6 };
		for (auto elem : outputConnectionPointList) {
			elem->setPos(pointPos + (delta / 2) - QPointF{ 0, elem->boundingRect().height() / 2 });
			pointPos += delta;
		}
		break;
	default:
		// TODO error?
		break;
	}

	update();
	return point;
}

// TODO improve as append above
void GraphNode::insertConnectionPoint(GraphConnectionType type, size_t index)
{
	switch (type) {
	case GraphConnectionType::In:
		if (inputConnectionPointList.size() > index) {
			inputConnectionPointList.insert(index, std::make_shared<GraphConnectionPoint>(this));
		}
		break;
	case GraphConnectionType::Out:
		if (outputConnectionPointList.size() > index) {
			outputConnectionPointList.insert(index, std::make_shared<GraphConnectionPoint>(this));
		}
		break;
	default:
		// TODO error?
		break;
	}
}

void GraphNode::removeConnectionPoint(GraphConnectionType type, size_t index)
{
	QPointF pointPos{ 0, boundingRect().height() / 5 };
	QPointF delta;

	switch (type) {
	case GraphConnectionType::In:
		if (inputConnectionPointList.size() > index) {
			inputConnectionPointList.removeAt(index);
			delta = { 0, boundingRect().height() / inputConnectionPointList.size() * 0.6 };
			for (auto elem : inputConnectionPointList) {
				elem->setPos(pointPos + (delta / 2) - QPointF{ 0, elem->boundingRect().height() / 2 });
				pointPos += delta;
			}
		}
		break;
	case GraphConnectionType::Out:
		if (outputConnectionPointList.size() > index) {
			outputConnectionPointList.removeAt(index);
			delta = { 0, boundingRect().height() / outputConnectionPointList.size() * 0.6 };
			for (auto elem : outputConnectionPointList) {
				elem->setPos(pointPos + (delta / 2) - QPointF{ 0, elem->boundingRect().height() / 2 });
				pointPos += delta;
			}
		}
		break;
	default:
		// TODO error?
		break;
	}
}

bool GraphNode::removeConnectionPoint(std::shared_ptr<GraphConnectionPoint> point)
{
	return outputConnectionPointList.removeOne(point) ? true : inputConnectionPointList.removeOne(point);
}

void GraphNode::connectPointTo(std::shared_ptr<GraphConnectionPoint> source, std::shared_ptr<GraphConnectionPoint> destination)
{
	auto arrow = std::make_shared<GraphArrow>(source, destination);
	source->connectArrow(arrow);
	destination->connectArrow(arrow);

	scene()->addItem(arrow.get());
}

std::shared_ptr<GraphConnectionPoint> GraphNode::connectionPointAt(GraphConnectionType type, size_t index)
{
	switch (type) {
	case GraphConnectionType::In:
		if (inputConnectionPointList.size() > index) {
			return inputConnectionPointList.at(index);
		}
		break;
	case GraphConnectionType::Out:
		if (outputConnectionPointList.size() > index) {
			return outputConnectionPointList.at(index);
		}
		break;
	default:
		// TODO error?
		break;
	}

	return nullptr;
}

void GraphNode::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	if (event->button() == Qt::LeftButton) 
	{
		lastLeftMousePressPoint = event->scenePos();
	}
	QGraphicsObject::mousePressEvent(event);
}

void GraphNode::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsObject::mouseReleaseEvent(event);
}

void GraphNode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
	qDebug() << "Double clicked on node:" << nodeBody.label;
	//emit nodeDoubleClicked(this);
	for (auto view : scene()->views())
	{
		//connect(this, &GraphNode::nodeDoubleClicked, dynamic_cast<GraphView*>(view), &GraphView::nodeDoubleClicked);
		dynamic_cast<GraphView*>(view)->passNodeDoubleClick(this);
	}

	QGraphicsObject::mouseDoubleClickEvent(event);
}

void GraphNode::focusOutEvent(QFocusEvent* event)
{
	QGraphicsObject::focusOutEvent(event);
}

QVariant GraphNode::itemChange(GraphicsItemChange change, const QVariant& value)
{
	int step = 100;
	if (change == ItemPositionChange) {
		//return QPoint(value.toPoint().x() - (value.toPoint().x() % step), value.toPoint().y() - (value.toPoint().y() % step));
		//std::function funX = value.toPoint().x() + lastLeftMousePressPoint.toPoint().x() > 0 ? std::ceilf : std::floorf;
		//std::function funY = value.toPoint().y() + lastLeftMousePressPoint.toPoint().y() > 0 ? std::ceilf : std::floorf;
		//auto res = QPoint((value.toPoint().x() + (lastLeftMousePressPoint.toPoint().x() % step)) / step * step, (value.toPoint().y() + (lastLeftMousePressPoint.toPoint().y() % step)) / step * step);

		auto res = QPoint(std::round((value.toPointF().x() + (lastLeftMousePressPoint.toPoint().x() % step)) / step) * step, std::round((value.toPointF().y() + (lastLeftMousePressPoint.toPoint().y() % step)) / step) * step);

		return res;
	}

	if (change == ItemSelectedHasChanged)
	{
		if (value == true)
		{
			nodeBody.setSelectedBorderPen();
		}
		else
		{
			nodeBody.setDefaultBorderPen();
		}
	}

	return QGraphicsItem::itemChange(change, value);
}

QString GraphNode::getLabel() const
{
	return nodeBody.label;
}

bool GraphNode::connectToNode(QString nodeName)
{
	for(auto elem : scene()->items())
	{
		auto otherNode = dynamic_cast<GraphNode*>(elem);
		if (otherNode != nullptr && otherNode->getLabel() == nodeName)
		{
			auto point = appendConnectionPoint(GraphConnectionType::Out);
			auto otherPoint = otherNode->appendConnectionPoint(GraphConnectionType::In);

			connectPointTo(point, otherPoint);
			outputConnectionPointList.last()->setSourceNodeName(getLabel());
			outputConnectionPointList.last()->setDestinationNodeName(nodeName);
			return true;
		}
	}

	return false;
}

bool GraphNode::disconnectFrom(QString nodeName)
{
	std::shared_ptr<GraphConnectionPoint> thisConnectionPoint;
	std::shared_ptr<GraphConnectionPoint> otherConnectionPoint;
	GraphNode* otherNode;

	// Find connection in this node
	for (const auto& connectionPoint : outputConnectionPointList)
	{
		if (connectionPoint->isConnected() && connectionPoint->getDestinationNodeName() == nodeName)
		{
			thisConnectionPoint = connectionPoint;
		}
	}

	if (thisConnectionPoint == nullptr)
	{
		qDebug() << "Node connection to `" << nodeName << "` not found.";
		return false;
	}

	// Find target node
	for (auto node : scene()->items())
	{
		auto castNode = dynamic_cast<GraphNode*>(node);
		if (castNode && castNode->getLabel() == nodeName)
		{
			// Find connection in other node
			for (const auto& connectionPoint : castNode->inputConnectionPointList)
			{
				if (connectionPoint->isConnected() 
					&& connectionPoint->getDestinationNodeName() == nodeName 
					&& thisConnectionPoint->arrow.get() == connectionPoint->arrow.get())
				{
					otherConnectionPoint = connectionPoint;
					otherNode = castNode;
				}
			}
		}
	}

	if (otherConnectionPoint == nullptr)
	{
		qDebug() << "Returning connection from node `" << nodeName << "` not found.";
		return false;
	}

	// Remove item from scene
	scene()->removeItem(thisConnectionPoint->arrow.get());

	qDebug() << "Source connection point removed: " << removeConnectionPoint(thisConnectionPoint);
	qDebug() << "Destination connection point removed: " << otherNode->removeConnectionPoint(otherConnectionPoint);

	return true;
}

void GraphNode::setFlags()
{
	setFlag(ItemHasNoContents);
	setFlag(ItemIsMovable);
	setCacheMode(DeviceCoordinateCache);
	setFlag(ItemSendsScenePositionChanges);
	setFlag(ItemIsFocusable);
	setFlag(ItemIsSelectable);
}

void GraphNode::serializableLoad(QDataStream& dataStream)
{
	QPointF pos;
	QString label;
	dataStream >> label >> pos;
	setLabel(label);
	setPos(pos);
}

void GraphNode::serializableSave(QDataStream& dataStream) const
{
	// Label should identify the scene and pos is the only attribute required to save for now. Connection points and body can be reconstructed with other information. It has to be consistent with scenes anyway.
	dataStream << getLabel() << scenePos();
}
