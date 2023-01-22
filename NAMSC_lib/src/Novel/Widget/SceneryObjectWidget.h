#pragma once
#include <QGraphicsPixmapItem>

#include "Novel/Data/Visual/Scenery/SceneryObject.h"
#include <QGraphicsWidget>

class SceneryObjectWidget final : public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT
public:
	explicit SceneryObjectWidget(const SceneryObject& sceneryObject, int zorder = 0, bool bPreview = false);
	SceneryObjectWidget(const SceneryObjectWidget&)            = delete;
	SceneryObjectWidget& operator=(const SceneryObjectWidget&) = delete;
	void switchToPreview();
	void switchToDisplay();

private:
	QTransform transformMatrix_;
	bool bPreview_ = false;
};
