#include "Novel/Widget/SceneWidget.h"

#include <QResizeEvent>

SceneWidget::SceneWidget(QWidget* parent)
	: QGraphicsView(parent)
{
	setCacheMode(QGraphicsView::CacheBackground);
	setScene(new QGraphicsScene());
}

void SceneWidget::switchToPreview()
{
	preview_ = true;
	for (SceneryObjectWidget* sceneryObjectWidget : sceneryObjectWidgets_)
		sceneryObjectWidget->switchToPreview();
}

void SceneWidget::switchToDisplay()
{
	preview_ = false;
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

const SceneryObjectWidget* SceneWidget::getSceneryObjectWidget(const QString& name) const
{
	return *std::ranges::find_if(sceneryObjectWidgets_, [&](const SceneryObjectWidget* elem) { return elem->getName() == name; });
}

SceneryObjectWidget* SceneWidget::getSceneryObjectWidget(size_t index)
{
	return sceneryObjectWidgets_[index];
}

void SceneWidget::addSceneryObjectWidget(const SceneryObject& sceneryObject)
{
	if (!sceneryObject.getAssetImage())
		return;
	SceneryObjectWidget* sceneryObjectWidget = new SceneryObjectWidget(sceneryObject, preview_);

	sceneryObjectWidgets_.push_back(sceneryObjectWidget);
	scene()->addItem(sceneryObjectWidget);
	sceneryObjectWidget->setZValue(scene()->items().size() - 1);

	connect(sceneryObjectWidget, &SceneryObjectWidget::sceneryObjectPositionChanged, this, &SceneWidget::sceneryObjectPositionChangedPass);
	connect(sceneryObjectWidget, &SceneryObjectWidget::sceneryObjectSelectionChanged, this, &SceneWidget::sceneryObjectSelectionChangedPass);
}

bool SceneWidget::insertSceneryObjectWidget(size_t index, const SceneryObject& sceneryObject)
{
	if (index > sceneryObjectWidgets_.size())
	{
		qCritical() << NovelLib::ErrorType::General << "Tried to insert past \"sceneryObjectWidgets_\" size";
		return false;
	}
	SceneryObjectWidget* sceneryObjectWidget = new SceneryObjectWidget(sceneryObject, preview_);

	scene()->addItem(sceneryObjectWidget);
	sceneryObjectWidgets_.insert(sceneryObjectWidgets_.begin() + index, std::move(sceneryObjectWidget));
	//Correct Z-Values after inserting a new element
	for (int i = 0; i != sceneryObjectWidgets_.size(); ++i)
		(*(sceneryObjectWidgets_.begin() + i))->setZValue(i);
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
	//No Image resize needed, since it will be drawn (where it will be resized) and then cached
	//QImage img = scene()->backgroundBrush().textureImage();
	//if (!img.isNull())
	//	changeBackground(&img);
}

void SceneWidget::drawBackground(QPainter* painter, const QRectF& rect)
{
	QImage img = scene()->backgroundBrush().textureImage();
	if (!img.isNull())
	{
		QSize size = rect.size().grownBy(QMarginsF(0.0, 0.0, 0.49999, 0.49999)).toSize();
		painter->drawImage(QPoint(-size.width()/2, -size.height()/2), img.scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
	}
}

void SceneWidget::changeBackground(const QImage* img)
{
	//No resize needed, since it is cached
	QBrush brush(*img/*->scaled(size())*/);
	scene()->setBackgroundBrush(brush);
}

void SceneWidget::sceneryObjectPositionChangedPass(const QString& name, const QPointF& pos)
{
	emit sceneryObjectPositionChanged(name, pos);
}

void SceneWidget::sceneryObjectSelectionChangedPass(const QString& name, bool selected)
{
	emit sceneryObjectSelectionChanged(name, selected);
}
