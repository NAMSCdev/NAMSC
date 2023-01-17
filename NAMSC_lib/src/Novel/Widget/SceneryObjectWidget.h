#pragma once
#include <QGraphicsPixmapItem>

#include "Novel/Data/Visual/Scenery/SceneryObject.h"

class SceneryObjectWidget final : public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT
public:
	SceneryObjectWidget(const SceneryObject& sceneryObject, bool preview = false);
	SceneryObjectWidget(const SceneryObjectWidget&) = delete;
	SceneryObjectWidget& operator=(const SceneryObjectWidget&) = delete;
	void switchToPreview();
	void switchToDisplay();

private:
	bool preview_;
};
