#include "Novel/Widget/SceneryObjectWidget.h"

SceneryObjectWidget::SceneryObjectWidget(const SceneryObject& sceneryObject, bool preview)
	: QGraphicsPixmapItem(),
	preview_(preview)
{
	if (preview_)
	{
		setFlag(ItemIsMovable);
		setFlag(ItemIsFocusable);
		setFlag(ItemSendsGeometryChanges);
	}
	setPixmap(QPixmap::fromImage(*(sceneryObject.getAssetImage()->getImage())));
	//TODO: setScale resizes the QPixmap
	setPos(sceneryObject.pos);
	setRotation(sceneryObject.rotationDegree);

	//setPixmap(QPixmap::fromImage(*sceneryObject.getAssetImage()->getImage()));
}

void SceneryObjectWidget::switchToPreview()
{
	preview_ = true;
	setFlag(ItemIsMovable);
	setFlag(ItemIsFocusable);
	setFlag(ItemSendsGeometryChanges);
}

void SceneryObjectWidget::switchToDisplay()
{
	preview_ = false;
	setFlag(ItemIsMovable,            false);
	setFlag(ItemIsFocusable,          false);
	setFlag(ItemSendsGeometryChanges, false);
}