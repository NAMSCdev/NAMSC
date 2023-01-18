#include "Novel/Widget/SceneryObjectWidget.h"

SceneryObjectWidget::SceneryObjectWidget(const SceneryObject& sceneryObject, int zorder, bool bPreview)
	: QGraphicsPixmapItem(),
	bPreview_(bPreview)
{
	if (bPreview_)
	{
		setFlag(ItemIsMovable);
		setFlag(ItemIsFocusable);
		setFlag(ItemSendsGeometryChanges);
	}
	QImage img = *sceneryObject.getAssetImage()->getImage();
	if (sceneryObject.bMirrored)
		img.mirror(true, false);
	
	matrixTransform_.translate(sceneryObject.pos.x(), sceneryObject.pos.y());
	matrixTransform_.scale(sceneryObject.scale.width(), sceneryObject.scale.height());
	matrixTransform_.rotate(sceneryObject.rotationDegree);
	setPixmap(QPixmap::fromImage(std::move(img)));
	//setZValue(zorder);
	setTransform(matrixTransform_);
}

void SceneryObjectWidget::switchToPreview()
{
	bPreview_ = true;
	setFlag(ItemIsMovable);
	setFlag(ItemIsFocusable);
	setFlag(ItemSendsGeometryChanges);
}

void SceneryObjectWidget::switchToDisplay()
{
	bPreview_ = false;
	setFlag(ItemIsMovable,            false);
	setFlag(ItemIsFocusable,          false);
	setFlag(ItemSendsGeometryChanges, false);
}