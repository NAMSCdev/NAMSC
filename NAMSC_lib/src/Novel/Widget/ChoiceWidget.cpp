#include "Novel/Widget/ChoiceWidget.h"

#include <QPainter>

#define RESOLUTION_X 1600.0
#define RESOLUTION_Y 900.0
#define WIDTH RESOLUTION_X * 0.44

ChoiceWidget::ChoiceWidget(QGraphicsScene* scene, const QString& menuText, const std::vector<Choice>& choices, bool bPreview)
	: QGraphicsWidget(),
	menuText_(menuText),
	bPreview_(bPreview)
{
	if (choices.size() <= 0)
	{
		qCritical() << NovelLib::ErrorType::ChoiceInvalid << "Cannot construct a ChoiceWidget without Choices";
		return;
	}

	font_.setStyleHint(QFont::Helvetica, QFont::PreferAntialias);
	QFontMetrics metrics(font_);
	QRectF textRect = metrics.boundingRect(QRect(0, 0, static_cast<uint>(WIDTH - 16.0), RESOLUTION_Y), Qt::TextWordWrap, menuText_);
	height_         = textRect.height();

	setMinimumSize(textRect.width() + 16.0, height_);

	//todo: not supported yet
	/*if (preview_)
	{
		setFlag(ItemIsMovable);
		setFlag(ItemIsFocusable);
		setFlag(ItemSendsGeometryChanges);
	}*/

	NovelSettings& novelSettings = NovelSettings::getInstance();

	layout_ = new QGraphicsLinearLayout(Qt::Vertical);
	layout_->setContentsMargins(8, height_ + 40, 8, 8);
	layout_->setSpacing(32);

	uint index = 0;
	for (const Choice& choice : choices)
	{
		ChoiceTextWidget* choiceTextWidget = new ChoiceTextWidget(index++, choice.translation.text(), textRect.width());
		choices_.push_back(choiceTextWidget);
		layout_->addItem(choiceTextWidget);
		connect(choiceTextWidget, &ChoiceTextWidget::chosen, this, &ChoiceWidget::chosen);
	}
	setLayout(layout_);

	drawPen_.setColor(QColor(80, 88, 167, 255));
	drawPen_.setWidth(2);
}

void ChoiceWidget::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->setRenderHint(QPainter::Antialiasing);
	painter->setPen(drawPen_);
	painter->setBrush(QColor(50, 48, 97, 210));
	painter->drawRoundedRect(0, 0, rect().width(), rect().height(), 8.0, 8.0);
	painter->setPen(QColor(255, 249, 208, 255));
	painter->setFont(font_);
	QTextOption options;
	options.setAlignment(Qt::AlignCenter);
	painter->drawText(QRectF(8.0, 8.0, rect().width() - 16.0, height_), menuText_, options);
}

void ChoiceWidget::showEvent(QShowEvent* event)
{
	QGraphicsWidget::showEvent(event);
	setPos((RESOLUTION_X - rect().width()) / 2.0, (RESOLUTION_Y - rect().height()) / 2.0);
}

void ChoiceWidget::resizeEvent(QGraphicsSceneResizeEvent* event)
{
	QGraphicsWidget::resizeEvent(event);
	setPos((RESOLUTION_X - rect().width()) / 2.0, (RESOLUTION_Y - rect().height()) / 2.0);
}