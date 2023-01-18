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
	img = std::move(img.scaledToWidth(qRound(img.width() * sceneryObject.scale.width()), Qt::SmoothTransformation));
	img = std::move(img.scaledToHeight(qRound(img.height() * sceneryObject.scale.height()), Qt::SmoothTransformation));
	setPixmap(QPixmap::fromImage(std::move(img)));
	//setZValue(zorder);
	setPos(sceneryObject.pos);
	setRotation(sceneryObject.rotationDegree);
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