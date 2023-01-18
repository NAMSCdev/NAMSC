#pragma once
#include <QGraphicsWidget>

#include <QElapsedTimer>
#include <QTimer>
#include <QString>
#include <QGraphicsLinearLayout>
#include <QPen>

#include "Novel/Data/Text/Sentence.h"
#include "Novel/Widget/DisplayNameWidget.h"
#include "Novel/Widget/DisplayTextWidget.h"

class TextWidget : public QGraphicsWidget
{
	Q_OBJECT
public:
	TextWidget(QGraphicsScene* scene, const std::vector<Sentence>& sentences, uint sentenceReadIndex = 0u, uint cps = 40u, bool bPreview = false);
	TextWidget(const TextWidget&)            = delete;
	TextWidget& operator=(const TextWidget&) = delete;
	
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

	//todo: not supported yet
	//void switchToPreview();
	//void switchToDisplay();
signals:
	void pendNovelEnd();

public slots:
	void updateText();
	void mouseClicked();

private:
	std::vector<std::pair<QString, QString>> text_;
	QGraphicsLinearLayout* layout      = nullptr;
	DisplayNameWidget*     nameWidget_ = nullptr;
	DisplayTextWidget*     textWidget_ = nullptr;

	uint sentenceReadIndex_ = 0u,
		 cps_               = 40u;

	QStringView   cpsView_;
	QElapsedTimer cpsTimer_;
	QTimer        cpsCallTimer_;

	QPen drawPen_;

	bool bNarrate_          = false,
		 bPreview_          = false;

};
