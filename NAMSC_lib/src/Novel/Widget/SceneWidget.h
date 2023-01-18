#pragma once
#include <QGraphicsView>

#include "Novel/Widget/SceneryObjectWidget.h"
#include "Novel/Widget/ChoiceWidget.h"
#include "Novel/Widget/TextWidget.h"

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
	const SceneryObjectWidget* getSceneryObjectWidget(size_t index)    const;
	      SceneryObjectWidget* getSceneryObjectWidget(size_t index);
	void addSceneryObjectWidget(const SceneryObject& sceneryObject, int zorder);
	bool insertSceneryObjectWidget(size_t index, const SceneryObject& sceneryObject);
	bool removeSceneryObjectWidget(size_t index);
	void clearSceneryObjectWidgets() noexcept;

	void resizeEvent(QResizeEvent* event) override;
	void drawBackground(QPainter* painter, const QRectF& rect) override;
	void wheelEvent(QWheelEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;

public slots:
	void displayBackground(const QImage* img);
	void displayEventChoice(const std::vector<Choice>& choices);
	void displayEventDialogue(const std::vector<Sentence>& sentences, uint sentenceReadIndex = 0u);
	void displaySceneryObjects(const std::vector<SceneryObject>& sceneryObjects);
	void displayCharacters(const std::vector<Character>& characters);

signals:
	void pendNovelEnd();
	void pendChoiceRun(uint choice);
	void LPMClicked();

private:
	std::vector<SceneryObjectWidget*> sceneryObjectWidgets_;

	QTransform transformMatrix_;

	bool bPreview_ = false;
};

