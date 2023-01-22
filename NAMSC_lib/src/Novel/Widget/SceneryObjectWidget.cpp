#include "Novel/Widget/SceneryObjectWidget.h"

SceneryObjectWidget::SceneryObjectWidget(const SceneryObject& sceneryObject, bool preview)
	: QGraphicsPixmapItem(),
	preview_(preview)
{
	if (preview_)
	{
		setFlag(ItemIsMovable);
		setFlag(ItemIsFocusable);
		setFlag(ItemIsSelectable);
		setFlag(ItemSendsGeometryChanges);
	}
	setPixmap(QPixmap::fromImage(*(sceneryObject.getAssetImage()->getImage())));
	//TODO: setScale resizes the QPixmap
	setPos(sceneryObject.pos);
	setRotation(sceneryObject.rotationDegree);
	name = sceneryObject.name;
}

void SceneryObjectWidget::switchToPreview()
{
	preview_ = true;
	setFlag(ItemIsMovable);
	setFlag(ItemIsFocusable);
	setFlag(ItemIsSelectable);
	setFlag(ItemSendsGeometryChanges);
}

void SceneryObjectWidget::switchToDisplay()
{
	preview_ = false;
	setFlag(ItemIsMovable,            false);
	setFlag(ItemIsFocusable,          false);
	setFlag(ItemIsSelectable,		  false);
	setFlag(ItemSendsGeometryChanges, false);
}

const QString& SceneryObjectWidget::getName() const noexcept
{
	return name;
}

QVariant SceneryObjectWidget::itemChange(GraphicsItemChange change, const QVariant& value)
{
	if (change == ItemPositionHasChanged) emit sceneryObjectPositionChanged(name, value.toPointF());
	else if (change == ItemSelectedHasChanged) emit sceneryObjectSelectionChanged(name, value.toBool());

	return QGraphicsPixmapItem::itemChange(change, value);
}
