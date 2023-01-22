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

	const QString& getName() const noexcept;

	signals:
		void sceneryObjectPositionChanged(const QString& name, const QPointF& pos);
		void sceneryObjectSelectionChanged(const QString& name, bool selected);

protected:
	QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

private:
	QString name;
	QTransform transformMatrix_;
	bool bPreview_ = false;
};
