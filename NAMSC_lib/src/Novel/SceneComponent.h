#pragma once
#include <QString>

enum SceneComponentType
{
	NOT_COMPONENT,
	SCENE,
	EVENT,
	OBJECT,
	CHARACTER
};

enum class EventSubType
{
	NOT_EVENT,
	EVENT_DIALOG,
	EVENT_CHOICE,
	EVENT_JUMP
};
class SceneComponent
{
public:
	SceneComponent() {}

	virtual QString getTypeName() = 0;
	virtual QString getSubTypeName() = 0;
	virtual SceneComponentType getType() = 0;
	virtual EventSubType getEventType() = 0;
	virtual QString getName() = 0;
	SceneComponent* component() { return (SceneComponent*)this; }
};

class DummySceneComponent : public SceneComponent
{
public:
	DummySceneComponent() : SceneComponent() {}
	virtual QString getTypeName() { return QString("Dummy"); }
	virtual QString getSubTypeName() { return QString("Dummy"); }
	virtual QString getName() { return QString("Dummy"); }
	virtual SceneComponentType getType() { return NOT_COMPONENT; }
	virtual EventSubType getEventType() { return EventSubType::NOT_EVENT; }
};

