#pragma once
#include <QGraphicsView>
#include "Novel/Widget/SceneryObjectWidget.h"

class SceneWidget : public QGraphicsView
{
	Q_OBJECT
public:
	SceneWidget(QWidget* parent = nullptr);
	SceneWidget(const SceneWidget&)            = delete;
	SceneWidget& operator=(const SceneWidget&) = delete;

	void switchToPreview();
	void switchToDisplay();

	const std::vector<SceneryObjectWidget*>* getSceneryObjectWidgets() const noexcept;
	const SceneryObjectWidget* getSceneryObjectWidget(size_t index) const noexcept;
	SceneryObjectWidget* getSceneryObjectWidget(size_t index) noexcept;
	void addSceneryObjectWidget(const SceneryObject& sceneryObject) noexcept;
	bool insertSceneryObjectWidget(size_t index, const SceneryObject& sceneryObject);
	bool removeSceneryObjectWidget(size_t index);
	void clearSceneryObjectWidgets() noexcept;

	void resizeEvent(QResizeEvent* event) override;
	void drawBackground(QPainter* painter, const QRectF& rect) override;

public slots:
	void changeBackground(const QImage* img);

private:
	std::vector<SceneryObjectWidget*> sceneryObjectWidgets_;
	bool preview_ = false;
};

