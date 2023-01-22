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

	const QString& getName() const noexcept;

	signals:
		void sceneryObjectPositionChanged(const QString& name, const QPointF& pos);
		void sceneryObjectSelectionChanged(const QString& name, bool selected);

protected:
	QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

private:
	QString name;
	bool preview_;
};
