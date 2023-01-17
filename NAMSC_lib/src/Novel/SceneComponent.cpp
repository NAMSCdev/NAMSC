#include "SceneComponent.h"

SceneComponent::~SceneComponent() = default;

EventSubType SceneComponent::getComponentEventType() const noexcept
{
	return EventSubType::NOT_EVENT;
}

QString DummySceneComponent::getComponentTypeName() const noexcept
{ 
	return QString("Dummy");
}

QString DummySceneComponent::getComponentSubTypeName() const noexcept 
{
	return QString("Dummy");
}

QString DummySceneComponent::getComponentName() const noexcept 
{
	return QString("Dummy");
}

SceneComponentType DummySceneComponent::getComponentType() const noexcept 
{ 
	return NOT_COMPONENT;
}