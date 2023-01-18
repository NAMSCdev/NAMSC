#include "Novel/Widget/ChoiceWidget.h"

ChoiceWidget::ChoiceWidget(QGraphicsScene* scene, const std::vector<Choice>& choices, bool bPreview)
	: QGraphicsWidget(),
	bPreview_(bPreview)
{
	//todo: not supported yet
	/*if (preview_)
	{
		setFlag(ItemIsMovable);
		setFlag(ItemIsFocusable);
		setFlag(ItemSendsGeometryChanges);
	}*/
}

void ChoiceWidget::update()
{

}