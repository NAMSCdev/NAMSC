#pragma once
#include <QGraphicsWidget>

#include "Novel/Data/Text/Choice.h"

class ChoiceWidget : public QGraphicsWidget
{
	Q_OBJECT
public:
	ChoiceWidget(QGraphicsScene* scene, const std::vector<Choice>& choices, bool bPreview = false);
	ChoiceWidget(const ChoiceWidget&)            = delete;
	ChoiceWidget& operator=(const ChoiceWidget&) = delete;

	//todo: not supported yet
	//void switchToPreview();
	//void switchToDisplay();

signals:
	//void choice();

public slots:
	void update();

private:
	bool bPreview_ = false;
};
