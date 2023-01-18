#pragma once
#include <QGraphicsPixmapItem>

#include "Novel/Data/Visual/Scenery/SceneryObject.h"

class SceneryObjectWidget final : public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT
public:
	SceneryObjectWidget(const SceneryObject& sceneryObject, int zorder = 0, bool bPreview = false);
	SceneryObjectWidget(const SceneryObjectWidget&)            = delete;
	SceneryObjectWidget& operator=(const SceneryObjectWidget&) = delete;
	void switchToPreview();
	void switchToDisplay();

private:
	QTransform matrixTransform_;
	bool bPreview_ = false;
};
