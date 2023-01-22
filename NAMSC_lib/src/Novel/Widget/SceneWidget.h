#pragma once
#include <QGraphicsView>

#include "Novel/Widget/SceneryObjectWidget.h"

class SceneWidget : public QGraphicsView
{
	Q_OBJECT
public:
	SceneWidget(QWidget* parent = nullptr);
	SceneWidget(const SceneWidget&) = delete;
	SceneWidget& operator=(const SceneWidget&) = delete;

	void switchToPreview();
	void switchToDisplay();

	const std::vector<SceneryObjectWidget*>* getSceneryObjectWidgets() const noexcept;
	const SceneryObjectWidget* getSceneryObjectWidget(size_t index) const;
	const SceneryObjectWidget* getSceneryObjectWidget(const QString& name) const;
	SceneryObjectWidget* getSceneryObjectWidget(size_t index);
	void addSceneryObjectWidget(const SceneryObject& sceneryObject);
	bool insertSceneryObjectWidget(size_t index, const SceneryObject& sceneryObject);
	bool removeSceneryObjectWidget(size_t index);
	void clearSceneryObjectWidgets() noexcept;

	void resizeEvent(QResizeEvent* event) override;
	void drawBackground(QPainter* painter, const QRectF& rect) override;

public slots:
	void changeBackground(const QImage* img);

	signals:
		void sceneryObjectPositionChanged(const QString& name, const QPointF& pos);
		void sceneryObjectSelectionChanged(const QString& name, bool selected);

private:
	std::vector<SceneryObjectWidget*> sceneryObjectWidgets_;
	double scale_[2] = { 1.0, 1.0 };
	bool preview_ = false;

private slots:
	void sceneryObjectPositionChangedPass(const QString& name, const QPointF& pos);
	void sceneryObjectSelectionChangedPass(const QString& name, bool selected);
};

