#include "MainTextBox.h"
#include "qbrush.h"
#include "qpainter"

MainTextBox::MainTextBox(QWidget *parent) : QGraphicsItem(), boundingBox(QRectF()) {
	setParent(parent);
	setFlag(ItemIsMovable);
	setAcceptHoverEvents(true);
	testBrush = QBrush(Qt::blue);
	currentText = new QString("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.");
}

MainTextBox::~MainTextBox() {

}

QRectF MainTextBox::boundingRect() const
{
	// QGraphicsView* view = scene()->views().first();
	return boundingBox;
}

void MainTextBox::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->fillRect(boundingBox, testBrush);
	painter->drawRect(boundingBox);
	painter->drawText(boundingBox, Qt::TextWordWrap, *currentText);
}

void MainTextBox::setBoundingBoxSize(qreal x, qreal y)
{
	boundingBox.setRect(0, 0, x, y);
}

void MainTextBox::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{	
	auto pressedUpper = upperCheck(mouseEvent, boxBorderClickSensitivity);
	auto pressedBottom = bottomCheck(mouseEvent, boxBorderClickSensitivity);
	auto pressedLeft = leftCheck(mouseEvent, boxBorderClickSensitivity);
	auto pressedRight = rightCheck(mouseEvent, boxBorderClickSensitivity);

	if (not (pressedUpper || pressedBottom || pressedLeft || pressedRight)) {
		boundingBoxPressedType = BoundingBoxPressedType::Inside;				// Inside covered
	}
	else if (pressedRight) {
		if (pressedUpper) {
			boundingBoxPressedType = BoundingBoxPressedType::RightUpperCorner;	// RightUpper covered
		}
		else if (pressedBottom) {
			boundingBoxPressedType = BoundingBoxPressedType::RightBottomCorner;	// RightBottom covered
		}
		else {
			boundingBoxPressedType = BoundingBoxPressedType::RightBorder;		// Right covered
		}
	}
	else if (pressedLeft) {
		if (pressedUpper) {
			boundingBoxPressedType = BoundingBoxPressedType::LeftUpperCorner;	// LeftUpper covered
		}
		else if (pressedBottom) {
			boundingBoxPressedType = BoundingBoxPressedType::LeftBottomCorner;	// LeftBottom covered
		}
		else {
			boundingBoxPressedType = BoundingBoxPressedType::LeftBorder;		// Left covered
		}
	}
	else if (pressedUpper) {
		boundingBoxPressedType = BoundingBoxPressedType::UpperBorder;			// Upper covered
	}
	else if (pressedBottom) {
		boundingBoxPressedType = BoundingBoxPressedType::BottomBorder;			// Bottom covered
	}
	else {
		boundingBoxPressedType = BoundingBoxPressedType::None;
	}

	//if (mouseEvent->pos().x() < boxBorderClickSensitivity || mouseEvent->pos().x() > boundingBox.size().width() - boxBorderClickSensitivity ||
	//	mouseEvent->pos().y() < boxBorderClickSensitivity || mouseEvent->pos().y() > boundingBox.size().height() - boxBorderClickSensitivity) {
	//	testBrush.setColor(Qt::red);
	//	borderPressed = true;
	//}
	//else {
	//	testBrush.setColor(Qt::green);
	//}
	//this->update();
}

void MainTextBox::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	boundingBoxPressedType = BoundingBoxPressedType::None;
	qDebug() << "Bounding box x: " << boundingBox.x() << " y: " << boundingBox.y() 
		<< "\tw: " << boundingBox.width() << " h: " << boundingBox.height()
		<< "\tMouse event: " << mouseEvent->pos().y();
}

void MainTextBox::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	// Not needed??
	auto movedBottom = bottomCheck(mouseEvent, boxBorderResizeSensitivity);
	auto movedUpper	 =  upperCheck(mouseEvent, boxBorderResizeSensitivity);
	auto movedRight	 =  rightCheck(mouseEvent, boxBorderResizeSensitivity);
	auto movedLeft	 =   leftCheck(mouseEvent, boxBorderResizeSensitivity);

	auto buttonPressed = mouseEvent->button();
	prepareGeometryChange();

	// Resize only the corner/border that is affected in the wanted direction
	switch (boundingBoxPressedType) {
	case BoundingBoxPressedType::Inside:
		setPos(mouseEvent->scenePos().x() - mouseEvent->lastPos().x(), mouseEvent->scenePos().y() - mouseEvent->lastPos().y());
		break;
	case BoundingBoxPressedType::RightBorder:		
		boundingBox.setRight(mouseEvent->lastPos().x());
		break;
	case BoundingBoxPressedType::RightUpperCorner:
		// TODO
		break;
	case BoundingBoxPressedType::RightBottomCorner:
		// TODO
		break;
	case BoundingBoxPressedType::LeftBorder:
		boundingBox.setLeft(mouseEvent->lastPos().x());
		break;
	case BoundingBoxPressedType::LeftUpperCorner:
		// TODO
		break;
	case BoundingBoxPressedType::LeftBottomCorner:
		// TODO
		break;
	case BoundingBoxPressedType::UpperBorder:
		boundingBox.setTop(mouseEvent->lastPos().y());
		break;
	case BoundingBoxPressedType::BottomBorder:
		boundingBox.setBottom(mouseEvent->lastPos().y());
		break;
	default:
		// TODO
		break;
	}

	this->update();
	
	//if (borderPressed) {
	//	if (mouseEvent->pos().x() >= boundingBox.width()) {
	//		setBoundingBoxSize(mouseEvent->pos().x(), boundingBox.height());
	//		this->update();
	//	} 
	//}
	

	//if (mouseEvent->pos().x() >= boundingBox.width() && mouseEvent->scenePos().x() > this->scenePos().x()) {
	//	setBoundingBoxSize(boundingBox.width() + this->scenePos().x() - mouseEvent->scenePos().x(), boundingBox.height());
	//	this->update();
	//}

	//auto color = mouseEvent->scenePos().x();
	//testBrush.setColor(QColor(color, mouseEvent->scenePos().y(), color, color));
	//this->update();
}

void MainTextBox::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
	// TODO
}
