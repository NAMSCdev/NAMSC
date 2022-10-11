#include "TextBox.h"

TextBox::TextBox(QObject *parent)
	: QObject(parent), QGraphicsItem(), boundingBox(QRectF(0, 0, 200, 500))
{
	setFlag(ItemIsFocusable);
	setAcceptHoverEvents(true);
	// Reference usage - will be removed later
	//setBackground(std::make_shared<QImage>(QImage("./exampleTextBoxTexture.png")));
	//textBoundingBox = QRectF(0, 0, 200, 500);
	//text.setHtml("<span style=\"color: red\">Lorem ipsum</span> dolor sit amet");
	//brush = QBrush(averageColor);
}

TextBox::~TextBox() { }

QRectF TextBox::boundingRect() const
{
	return boundingBox;
}

void TextBox::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	// Draw box
	if (image == nullptr) {
		painter->fillRect(boundingBox, brush);
	}
	else {
		painter->drawImage(boundingBox, *image);
	}

	// Draw text
	if (not text.isEmpty()) {
		text.drawContents(painter, textBoundingBox);
	}
	if (not characterName.isEmpty()) {
		characterName.drawContents(painter, characterNameBoundingBox);
	}

	// Draw dashed line around bounding box
	if (hasFocus()) {
		QPen customPen(Qt::DashLine);
		customPen.setColor({ averageColor.red(), averageColor.green(), averageColor.blue(), 255});
		QList<qreal> dashes;
		dashes << 2 << 6;
		customPen.setWidth(2);
		customPen.setDashPattern(dashes);

		painter->setPen(customPen);
		painter->fillRect(boundingBox, brush);
		painter->drawRect(boundingBox);
	}
}

void TextBox::setBoundingBoxSize(QSizeF size)
{
	boundingBox.setSize(size);
}

void TextBox::setBackground(QImage image)
{
	this->image = std::make_shared<QImage>(image);
	this->boundingBox.setSize(image.size());
	setAverageColor();
}

void TextBox::setBackground(std::shared_ptr<QImage> imageptr)
{
	this->image = imageptr;
	this->boundingBox.setSize(image->size());
	setAverageColor();
}

void TextBox::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	// Focus is set when pressed
	if (boundingBoxMousePosition == BoundingBoxMousePosition::Inside) {
		QApplication::setOverrideCursor(Qt::ClosedHandCursor);
	}
}

void TextBox::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (QApplication::overrideCursor() != nullptr && QApplication::overrideCursor()->shape() == Qt::ClosedHandCursor) {
		QApplication::setOverrideCursor(Qt::OpenHandCursor);
	}
}

void TextBox::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	auto movedBottom = bottomCheck(mouseEvent, boxBorderResizeActionSensitivity);
	auto movedUpper = upperCheck(mouseEvent, boxBorderResizeActionSensitivity);
	auto movedRight = rightCheck(mouseEvent, boxBorderResizeActionSensitivity);
	auto movedLeft = leftCheck(mouseEvent, boxBorderResizeActionSensitivity);

	auto buttonPressed = mouseEvent->button();
	prepareGeometryChange();

	/// TODO keep aspect ratio for images
	// Resize only the corner/border that is affected in the wanted direction
	switch (boundingBoxMousePosition) {
	case BoundingBoxMousePosition::Inside:
		setPos(mouseEvent->scenePos().x() - mouseEvent->buttonDownPos(Qt::LeftButton).x(), mouseEvent->scenePos().y() - mouseEvent->buttonDownPos(Qt::LeftButton).y());
		break;
	case BoundingBoxMousePosition::RightBorder:
		boundingBox.setRight(mouseEvent->lastPos().x());
		break;
	case BoundingBoxMousePosition::RightUpperCorner:
		boundingBox.setTopRight(mouseEvent->lastPos());
		break;
	case BoundingBoxMousePosition::RightBottomCorner:
		boundingBox.setBottomRight(mouseEvent->lastPos());
		break;
	case BoundingBoxMousePosition::LeftBorder:
		boundingBox.setLeft(mouseEvent->lastPos().x());
		break;
	case BoundingBoxMousePosition::LeftUpperCorner:
		boundingBox.setTopLeft(mouseEvent->lastPos());
		break;
	case BoundingBoxMousePosition::LeftBottomCorner:
		boundingBox.setBottomLeft(mouseEvent->lastPos());
		break;
	case BoundingBoxMousePosition::UpperBorder:
		boundingBox.setTop(mouseEvent->lastPos().y());
		break;
	case BoundingBoxMousePosition::BottomBorder:
		boundingBox.setBottom(mouseEvent->lastPos().y());
		break;
	default:
		// Do nothing for now
		break;
	}

	moveBy(boundingBox.x(), boundingBox.y());
	boundingBox.moveTo(0, 0);
}

void TextBox::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
	auto pressedUpper = upperCheck(event, boxBorderActionSensitivity);
	auto pressedBottom = bottomCheck(event, boxBorderActionSensitivity);
	auto pressedLeft = leftCheck(event, boxBorderActionSensitivity);
	auto pressedRight = rightCheck(event, boxBorderActionSensitivity);

	// Logic to detect mouse position inside `TextBox` item and set appropriate cursor if focused
	if (not (pressedUpper || pressedBottom || pressedLeft || pressedRight)) {
		boundingBoxMousePosition = BoundingBoxMousePosition::Inside;
		if (hasFocus()) {
			QApplication::setOverrideCursor(Qt::OpenHandCursor);
		}
	}
	else if (pressedRight) {
		if (pressedUpper) {
			boundingBoxMousePosition = BoundingBoxMousePosition::RightUpperCorner;
			if (hasFocus()) {
				QApplication::setOverrideCursor(Qt::SizeBDiagCursor);
			}
		}
		else if (pressedBottom) {
			boundingBoxMousePosition = BoundingBoxMousePosition::RightBottomCorner;
			if (hasFocus()) {
				QApplication::setOverrideCursor(Qt::SizeFDiagCursor);
			}
		}
		else {
			boundingBoxMousePosition = BoundingBoxMousePosition::RightBorder;
			if (hasFocus()) {
				QApplication::setOverrideCursor(Qt::SizeHorCursor);
			}
		}
	}
	else if (pressedLeft) {
		if (pressedUpper) {
			boundingBoxMousePosition = BoundingBoxMousePosition::LeftUpperCorner;
			if (hasFocus()) {
				QApplication::setOverrideCursor(Qt::SizeFDiagCursor);
			}
		}
		else if (pressedBottom) {
			boundingBoxMousePosition = BoundingBoxMousePosition::LeftBottomCorner;
			if (hasFocus()) {
				QApplication::setOverrideCursor(Qt::SizeBDiagCursor);
			}
		}
		else {
			boundingBoxMousePosition = BoundingBoxMousePosition::LeftBorder;
			if (hasFocus()) {
				QApplication::setOverrideCursor(Qt::SizeHorCursor);
			}
		}
	}
	else if (pressedUpper) {
		boundingBoxMousePosition = BoundingBoxMousePosition::UpperBorder;
		if (hasFocus()) {
			QApplication::setOverrideCursor(Qt::SizeVerCursor);
		}
	}
	else if (pressedBottom) {
		boundingBoxMousePosition = BoundingBoxMousePosition::BottomBorder;
		if (hasFocus()) {
			QApplication::setOverrideCursor(Qt::SizeVerCursor);
		}
	}
	else {
		boundingBoxMousePosition = BoundingBoxMousePosition::None;
		if (hasFocus()) {
			QApplication::setOverrideCursor(Qt::ArrowCursor);
		}
	}
}

void TextBox::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
	QApplication::setOverrideCursor(Qt::ArrowCursor);
}

void TextBox::focusOutEvent(QFocusEvent* event)
{
	boundingBoxMousePosition = BoundingBoxMousePosition::None;
	update();
}

void TextBox::setAverageColor()
{
	if (image != nullptr) {
		uint64_t r = 0, g = 0, b = 0, a = 0;
		for (int row = 0; row < this->image->size().height(); ++row) {
			for (int column = 0; column < this->image->size().width(); ++column) {
				QColor tempPix = this->image->pixelColor({ column, row });
				double alphaMul = tempPix.alphaF();
				r += tempPix.red() * alphaMul;
				g += tempPix.green() * alphaMul;
				b += tempPix.blue() * alphaMul;
				a += tempPix.alpha();
			}
		}
		a /= 255;
		averageColor = { static_cast<int>(r / a), static_cast<int>(g / a), static_cast<int>(b / a), 127 };
	}
}
