#pragma once
#include "Novel/Event/Event.h"
#include "Novel/Widget/SceneWidget.h"

class SceneEditorWidget : public SceneWidget
{
	Q_OBJECT

public:
	SceneEditorWidget(QWidget* parent = nullptr);

	//void addSceneryObjectWidget(const SceneryObject& sceneryObject);

public slots:
	void setEvent(Event* event, EventSubType type);
	void eventRemoved(Event* ptr);

private:
	Q_DISABLE_COPY(SceneEditorWidget)

	Event* currentEvent;
	EventSubType eventType;
};

