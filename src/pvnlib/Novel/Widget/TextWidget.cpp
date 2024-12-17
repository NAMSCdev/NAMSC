#include "pvnLib/Novel/Widget/TextWidget.h"

#include <QGraphicsScene>
#include <QPainter>

#define RESOLUTION_X 1600.0
#define RESOLUTION_Y 900.0

TextWidget::TextWidget(QGraphicsScene* scene, const std::vector<Sentence>& sentences, uint sentenceReadIndex, uint cps, bool bPreview)
	: QGraphicsWidget(),
	sentenceReadIndex_(sentenceReadIndex),
	bPreview_(bPreview)
{
	if (sentences.size() <= 0)
	{
		qCritical() << NovelLib::ErrorType::SentenceInvalid << "Cannot construct a TextWidget without Sentences";
		return;
	}

	//todo: not supported yet
	/*if (preview_)
	{
		setFlag(ItemIsMovable);
		setFlag(ItemIsFocusable);
		setFlag(ItemSendsGeometryChanges);
	}*/

	NovelSettings& novelSettings = NovelSettings::getInstance();

	for (const Sentence& sentence : sentences)
	{
		names_.emplace_back(sentence.displayedName);
		text_.emplace_back(sentence.translation.text());
		lengths_.push_back(static_cast<int>(text_.back().length()));
		cpsList_.push_back((sentence.cpsOverwrite == 0) ? qRound(sentence.cpsMultiplier * novelSettings.cps) : sentence.cpsOverwrite);
		requiredTimes_.push_back(lengths_.back() * 1000.0 / cpsList_.back());
	}

	layout_ = new QGraphicsLinearLayout(Qt::Vertical);
	layout_->setContentsMargins(8,8,8,8);
	layout_->setSpacing(16);

	nameWidget_ = new DisplayNameWidget(names_[sentenceReadIndex_]);
	if (!(bNarrate_ = names_[sentenceReadIndex_].isEmpty()))
		layout_->addItem(nameWidget_);
	layout_->addItem(textWidget_ = new DisplayTextWidget(""));
	setLayout(layout_);
	setPos((RESOLUTION_X - minimumWidth()) / 2.0, RESOLUTION_Y * 0.95 - minimumHeight());

	drawPen_.setColor(QColor(60, 68, 107, 255));
	drawPen_.setWidth(2);		
	connect(&cpsCallTimer_, &QTimer::timeout, this, &TextWidget::updateText);
	cpsCallTimer_.start();
	cpsTimer_.start();
}

void TextWidget::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->setRenderHint(QPainter::Antialiasing);
	painter->setPen(drawPen_);
	painter->setBrush(QColor(50, 48, 47, 185));
	painter->drawRoundedRect(0, 0, rect().width(), rect().height(), 6, 6);
	if (!bNarrate_)
		painter->drawLine(QPointF(0, 48 + 16), QPointF(rect().width(), 48 + 8 + 16));
}

void TextWidget::mouseClicked()
{
	if (cpsTimer_.elapsed() < requiredTimes_[sentenceReadIndex_])
	{
		if (!bSkip_)
		{
			bSkip_ = true;
			clickTimePoint_ = cpsTimer_.elapsed();
			cpsCallTimer_.stop();
			textWidget_->text = QString::fromRawData(text_[sentenceReadIndex_].data(), lengths_[sentenceReadIndex_]);
			update();
			return;
		}
	}
	// Accidental second click protection (150ms window)
	if (cpsTimer_.elapsed() - clickTimePoint_ < 150)
		return;

	if ((sentenceReadIndex_ + 1) == text_.size())
	{
		emit pendNovelEnd();
	}
	else
	{
		++sentenceReadIndex_;
		bSkip_    = false;

		if (!bNarrate_)
			layout_->removeItem(nameWidget_);
		layout_->removeItem(textWidget_);

		nameWidget_->text = names_[sentenceReadIndex_];
		textWidget_->text = "";

		if (!(bNarrate_ = names_[sentenceReadIndex_].isEmpty()))
			layout_->addItem(nameWidget_);
		layout_->addItem(textWidget_);

		setPos((RESOLUTION_X - minimumWidth()) / 2.0, RESOLUTION_Y * 0.95 - minimumHeight());		
		update();

		cpsCallTimer_.start();
		cpsTimer_.restart();
	}
}

void TextWidget::updateText()
{
	static unsigned int lastCharacterDisplay = 0;

	double elapsedTime    = cpsTimer_.elapsed();
	int charactersDisplay = qMin(lengths_[sentenceReadIndex_], static_cast<const uint>(qRound(elapsedTime / 1000.0 * cpsList_[sentenceReadIndex_])));

	if (lastCharacterDisplay == charactersDisplay)
		return;

	lastCharacterDisplay = charactersDisplay;
	textWidget_->text = text_[sentenceReadIndex_].left(charactersDisplay);
	update();
	if (elapsedTime >= requiredTimes_[sentenceReadIndex_])
		cpsCallTimer_.stop();
}