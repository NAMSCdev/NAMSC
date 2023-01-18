#include "Novel/Widget/TextWidget.h"

#include <QGraphicsScene>
#include <QPainter>

#define RESOLUTION_X 1600.0
#define RESOLUTION_Y 900.0

TextWidget::TextWidget(QGraphicsScene* scene, const std::vector<Sentence>& sentences, uint sentenceReadIndex, uint cps, bool bPreview)
	: QGraphicsWidget(),
	sentenceReadIndex_(sentenceReadIndex),
	bPreview_(bPreview)
{
	//todo: not supported yet
	/*if (preview_)
	{
		setFlag(ItemIsMovable);
		setFlag(ItemIsFocusable);
		setFlag(ItemSendsGeometryChanges);
	}*/
	for (const Sentence& sentence : sentences)
		text_.emplace_back(sentence.displayedName, std::move(sentence.translation.text()));

	layout = new QGraphicsLinearLayout(Qt::Vertical);
	layout->setContentsMargins(8,8,8,8);
	layout->setSpacing(16);

	nameWidget_ = new DisplayNameWidget(text_[sentenceReadIndex_].first);
	if (!(bNarrate_ = text_[sentenceReadIndex_].first.isEmpty()))
		layout->addItem(nameWidget_);
	layout->addItem(textWidget_ = new DisplayTextWidget(text_[sentenceReadIndex_].second));

	cpsView_ = QStringView(text_[sentenceReadIndex_].second);

	setLayout(layout);

	setPos((RESOLUTION_X - minimumWidth()) / 2.0, RESOLUTION_Y * 0.95 - minimumHeight());

	drawPen_.setColor(QColor(60, 68, 107, 255));
	drawPen_.setWidth(2);
	cpsTimer_.start();
	connect(&cpsCallTimer_, &QTimer::timeout, this, &TextWidget::updateText);
	cpsCallTimer_.start(1000.0 / cps_);

}

void TextWidget::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->setRenderHint(QPainter::Antialiasing);
	painter->setPen(drawPen_);
	painter->setBrush(QColor(50, 48, 47, 185));
	painter->drawRoundedRect(rect(), 6, 6);
	if (!bNarrate_)
		painter->drawLine(QPointF(0, 48 + 16), QPointF(rect().width(), 48 + 8 + 16));
}

void TextWidget::mouseClicked()
{
	if (++sentenceReadIndex_ >= text_.size())
	{
		//So it's done only once
		if (sentenceReadIndex_ == text_.size())
			emit pendNovelEnd();
	}
	else
	{
		if (!bNarrate_)
			layout->removeItem(nameWidget_);
		layout->removeItem(textWidget_);

		nameWidget_->text = text_[sentenceReadIndex_].first;
		textWidget_->text = text_[sentenceReadIndex_].second;

		if (!(bNarrate_ = text_[sentenceReadIndex_].first.isEmpty()))
			layout->addItem(nameWidget_);
		layout->addItem(textWidget_);

		setPos((RESOLUTION_X - minimumWidth()) / 2.0, RESOLUTION_Y * 0.95 - minimumHeight());
		cpsTimer_.restart();

		cpsView_ = QStringView(text_[sentenceReadIndex_].second);
		update();
	}
}

void TextWidget::updateText()
{
	int charactersDisplay = qRound(cpsTimer_.elapsed() / 1000.0 * cps_);
}