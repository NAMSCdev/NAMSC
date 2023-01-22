#pragma once
#include <QGraphicsView>

#include "Novel/Widget/SceneryObjectWidget.h"
#include "Novel/Widget/ChoiceWidget.h"
#include "Novel/Widget/TextWidget.h"

class SceneWidget : public QGraphicsView
{
	Q_OBJECT
public:
	explicit SceneWidget(QWidget* parent = nullptr);
	SceneWidget(const SceneWidget&)            = delete;
	SceneWidget& operator=(const SceneWidget&) = delete;

	void switchToPreview();
	void switchToDisplay();

	const std::vector<SceneryObjectWidget*>* getSceneryObjectWidgets() const noexcept;
	const SceneryObjectWidget* getSceneryObjectWidget(size_t index)    const;
	      SceneryObjectWidget* getSceneryObjectWidget(size_t index);
	const SceneryObjectWidget* getSceneryObjectWidget(const QString& name) const;
	void addSceneryObjectWidget(const SceneryObject& sceneryObject, int zorder);
	bool insertSceneryObjectWidget(size_t index, const SceneryObject& sceneryObject);
	bool removeSceneryObjectWidget(size_t index);
	void clearSceneryObjectWidgets() noexcept;

	void drawBackground(QPainter* painter, const QRectF& rect) override;

public slots:
	void displayBackground(const QImage* img);
	void displayEventChoice(const QString& menuText, const std::vector<Choice>& choices);
	void displayEventDialogue(const std::vector<Sentence>& sentences, uint sentenceReadIndex = 0u);
	void displaySceneryObjects(const std::vector<SceneryObject>& sceneryObjects);
	void displayCharacters(const std::vector<Character>& characters);
	void clearScene();

signals:
	void pendNovelEnd();
	void pendChoiceRun(uint choiceID);
	void LPMClicked();
	void sceneryObjectPositionChanged(const QString& name, const QPointF& pos);
	void sceneryObjectSelectionChanged(const QString& name, bool selected);

private:
	void resizeEvent(QResizeEvent* event)          override;
	void wheelEvent(QWheelEvent* event)            override;
	void mousePressEvent(QMouseEvent* event)       override;
	void mouseDoubleClickEvent(QMouseEvent* event) override;

	std::vector<SceneryObjectWidget*> sceneryObjectWidgets_;

	QTransform transformMatrix_;

	bool bPreview_ = false;

private slots:
	void sceneryObjectPositionChangedPass(const QString& name, const QPointF& pos);
	void sceneryObjectSelectionChangedPass(const QString& name, bool selected);
};

