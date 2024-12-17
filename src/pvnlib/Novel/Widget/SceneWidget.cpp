#include "pvnLib/Novel/Widget/SceneWidget.h"

#include <QResizeEvent>
#include <QOpenGLWidget>
#include <QSurfaceFormat>

#include "pvnLib/Novel/Data/Novel.h"
#include "pvnLib/Novel/Widget/ChoiceWidget.h"
#include "pvnLib/Novel/Widget/TextWidget.h"

#define RESOLUTION_X 1600.0
#define RESOLUTION_Y 900.0

SceneWidget::SceneWidget(QWidget* parent)
	: QGraphicsView(parent)
{
	setCacheMode(QGraphicsView::CacheBackground);
	setScene(new QGraphicsScene());
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scene()->setSceneRect(rect());
	setViewport(new QOpenGLWidget());
	//todo: support other resolutions I guess
	transformMatrix_.reset();
	transformMatrix_.scale(width() / RESOLUTION_X, height() / RESOLUTION_Y);
	setTransform(transformMatrix_);
}

void SceneWidget::switchToPreview()
{
	bPreview_ = true;
	for (SceneryObjectWidget* sceneryObjectWidget : sceneryObjectWidgets_)
		sceneryObjectWidget->switchToPreview();
}

void SceneWidget::switchToDisplay()
{
	bPreview_ = false;
	for (SceneryObjectWidget* sceneryObjectWidget : sceneryObjectWidgets_)
		sceneryObjectWidget->switchToDisplay();
}

const std::vector<SceneryObjectWidget*>* SceneWidget::getSceneryObjectWidgets() const noexcept
{
	return &sceneryObjectWidgets_;
}

const SceneryObjectWidget* SceneWidget::getSceneryObjectWidget(size_t index) const
{
	return sceneryObjectWidgets_[index];
}

SceneryObjectWidget* SceneWidget::getSceneryObjectWidget(size_t index)
{
	return sceneryObjectWidgets_[index];
}

void SceneWidget::addSceneryObjectWidget(const SceneryObject& sceneryObject, int zorder)
{
	if (!sceneryObject.getAssetImage())
		return;
	SceneryObjectWidget* sceneryObjectWidget = new SceneryObjectWidget(sceneryObject, zorder, bPreview_);

	sceneryObjectWidgets_.push_back(sceneryObjectWidget);
	scene()->addItem(sceneryObjectWidget);
	//sceneryObjectWidget->setZValue(scene()->items().size() - 1);
}

bool SceneWidget::insertSceneryObjectWidget(size_t index, const SceneryObject& sceneryObject)
{
	if (index > sceneryObjectWidgets_.size())
	{
		qCritical() << NovelLib::ErrorType::General << "Tried to insert past \"sceneryObjectWidgets_\" size";
		return false;
	}
	SceneryObjectWidget* sceneryObjectWidget = new SceneryObjectWidget(sceneryObject, index, bPreview_);

	scene()->addItem(sceneryObjectWidget);
	sceneryObjectWidgets_.insert(sceneryObjectWidgets_.begin() + index, std::move(sceneryObjectWidget));
	//Correct Z-Values after inserting a new element
	//for (int i = 0; i != sceneryObjectWidgets_.size(); ++i)
	//	(*(sceneryObjectWidgets_.begin() + i))->setZValue(i);
	return true;
}

bool SceneWidget::removeSceneryObjectWidget(size_t index)
{
	if (index >= sceneryObjectWidgets_.size())
	{
		qCritical() << NovelLib::ErrorType::General << "Tried to remove past \"sceneryObjectWidgets_\" size";
		return false;
	}
	sceneryObjectWidgets_.erase(sceneryObjectWidgets_.begin() + index);
	//Removing an item doesn't need to correct Z-Values
	return true;
}

void SceneWidget::clearSceneryObjectWidgets() noexcept
{
	sceneryObjectWidgets_.clear();
}

void SceneWidget::resizeEvent(QResizeEvent* event)
{
	QGraphicsView::resizeEvent(event);	
	const QSizeF& size = event->size();
	setSceneRect(QRectF(0.0, 0.0, RESOLUTION_X, RESOLUTION_Y));
	transformMatrix_.reset();
	transformMatrix_.scale(width() / RESOLUTION_X, height() / RESOLUTION_Y);
	setTransform(transformMatrix_);	//No Image resize needed, since it will be drawn (where it will be resized) and then cached
	//QImage img = scene()->backgroundBrush().textureImage();
	//if (!img.isNull())
	//	changeBackground(&img);
}	

void SceneWidget::drawBackground(QPainter* painter, const QRectF& rect)
{
	QRectF scaledRect = transformMatrix_.mapRect(rect);

	QImage img = scene()->backgroundBrush().textureImage();
	if (!img.isNull())
	{
		painter->setWindow(0, 0, scaledRect.width(), scaledRect.height());
		QSize size = rect.size().grownBy(QMarginsF(0.0, 0.0, 0.49999, 0.49999)).toSize();
		painter->drawImage(QPoint(0,0), img.scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
	}
}

void SceneWidget::wheelEvent(QWheelEvent* event)
{
	event->ignore();
	return;
	//QGraphicsView::wheelEvent(event);
}

void SceneWidget::mousePressEvent(QMouseEvent* event)
{
	QGraphicsView::mousePressEvent(event);
	if (event->button() == Qt::MouseButton::LeftButton)
		emit LPMClicked();
}

void SceneWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
	QGraphicsView::mouseDoubleClickEvent(event);
	if (event->button() == Qt::MouseButton::LeftButton)
		emit LPMClicked();
}

void SceneWidget::displayEventChoice(const QString& menuText, const std::vector<Choice>& choices)
{
	ChoiceWidget* choiceWidget = new ChoiceWidget(scene(), menuText, choices, bPreview_);
	connect(choiceWidget, &ChoiceWidget::chosen, this, &SceneWidget::pendChoiceRun);
	//Takes ownership and will delete it later
	scene()->addItem(choiceWidget);
}

void SceneWidget::displayEventDialogue(const std::vector<Sentence>& sentences, uint sentenceReadIndex)
{
	TextWidget* textWidget = new TextWidget(scene(), sentences, sentenceReadIndex, bPreview_);
	connect(textWidget, &TextWidget::pendNovelEnd,this,       &SceneWidget::pendNovelEnd);
	connect(this,       &SceneWidget::LPMClicked, textWidget, &TextWidget::mouseClicked);
	//Takes ownership and will delete it later
	scene()->addItem(textWidget);
}

void SceneWidget::displaySceneryObjects(const std::vector<SceneryObject>& sceneryObjects)
{
	for (uint i = 0u; i != sceneryObjects.size(); ++i)
	{
		const SceneryObject& sceneryObject = sceneryObjects[i];
		const AssetImage* sprite = sceneryObject.getAssetImage();
		if (sprite && sprite->isLoaded())
			addSceneryObjectWidget(sceneryObject, i);
	}
	update();
}

void SceneWidget::displayCharacters(const std::vector<Character>& characters)
{
	for (uint i = 0u; i != characters.size(); ++i)
	{
		const Character& character = characters[i];
		const AssetImage* sprite = character.getAssetImage();
		if (sprite && sprite->isLoaded())
			addSceneryObjectWidget(character, i);
	}
	update();
}

void SceneWidget::clearScene()
{
	scene()->clear();
	clearSceneryObjectWidgets();
}

void SceneWidget::displayBackground(const QImage* img)
{
	//No resize needed, since it is cached
	QBrush brush(*img/*->scaled(size())*/);
	scene()->setBackgroundBrush(brush);
}