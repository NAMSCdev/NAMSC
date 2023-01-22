#pragma once
#include <QGraphicsWidget>

#include <QGraphicsLinearLayout>
#include <QPen>

#include "Novel/Data/Text/Choice.h"
#include "Novel/Widget/ChoiceTextWidget.h"

class ChoiceWidget : public QGraphicsWidget
{
	Q_OBJECT
public:
	ChoiceWidget(QGraphicsScene* scene, const QString& menuText, const std::vector<Choice>& choices, bool bPreview = false);
	ChoiceWidget(const ChoiceWidget&)            = delete;
	ChoiceWidget& operator=(const ChoiceWidget&) = delete;

	//todo: not supported yet
	//void switchToPreview();
	//void switchToDisplay();

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

signals:
	void chosen(uint choiceID);

private:
	void showEvent(QShowEvent* event) override;
	void resizeEvent(QGraphicsSceneResizeEvent* event) override;

	QString menuText_;
	QFont   font_ = QFont("Fantasque Sans Mono", 40);

	uint height_ = 0;

	std::vector<ChoiceTextWidget *> choices_;

	QGraphicsLinearLayout* layout_ = nullptr;
	QPen drawPen_;

	bool bPreview_ = false;
};
