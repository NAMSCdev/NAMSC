#include "Novel/Widget/SceneryObjectWidget.h"

SceneryObjectWidget::SceneryObjectWidget(const SceneryObject& sceneryObject, int zorder, bool bPreview)
	: QGraphicsPixmapItem(),
	bPreview_(bPreview)
{
	if (bPreview_)
	{
		setFlag(ItemIsMovable);
		setFlag(ItemIsFocusable);
		setFlag(ItemIsSelectable);
		setFlag(ItemSendsGeometryChanges);
	}
	QImage img = *sceneryObject.getAssetImage()->getImage();
	if (sceneryObject.bMirrored)
		img.mirror(true, false);
	
	transformMatrix_.scale(sceneryObject.scale.width(), sceneryObject.scale.height());

	setPixmap(QPixmap::fromImage(std::move(img)));
	//setZValue(zorder);
	setTransformOriginPoint(boundingRect().center());
	setRotation(sceneryObject.rotationDegree);
	setPos(sceneryObject.pos.x(), sceneryObject.pos.y());
	setTransformationMode(Qt::SmoothTransformation);
	setTransform(transformMatrix_);
	name = sceneryObject.name;
}

void SceneryObjectWidget::switchToPreview()
{
	bPreview_ = true;
	setFlag(ItemIsMovable);
	setFlag(ItemIsFocusable);
	setFlag(ItemIsSelectable);
	setFlag(ItemSendsGeometryChanges);
}

void SceneryObjectWidget::switchToDisplay()
{
	bPreview_ = false;
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
