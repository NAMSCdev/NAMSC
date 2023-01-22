#include "SceneEditorWidget.h"

SceneEditorWidget::SceneEditorWidget(QWidget* parent) : SceneWidget(parent)
{
}

//void SceneEditorWidget::addSceneryObjectWidget(const SceneryObject& sceneryObject)
//{
//	SceneWidget::addSceneryObjectWidget(sceneryObject);
//
//}

void SceneEditorWidget::setEvent(Event* event, EventSubType type)
{
	// save
	// change to new
	currentEvent = event;
	eventType = type;
	event->run();
}

void SceneEditorWidget::eventRemoved(Event* ptr)
{
	if (currentEvent == ptr)
	{
		currentEvent = nullptr;
		clearSceneryObjectWidgets();
	}
}
