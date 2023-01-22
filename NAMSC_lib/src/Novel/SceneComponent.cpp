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


QString CharactersRootSceneComponent::getComponentTypeName() const noexcept
{ 
	return QString("");
}

QString CharactersRootSceneComponent::getComponentSubTypeName() const noexcept 
{
	return QString("");
}

QString CharactersRootSceneComponent::getComponentName() const noexcept 
{
	return QString("Characters");
}

SceneComponentType CharactersRootSceneComponent::getComponentType() const noexcept 
{ 
	return CHARACTERS_ROOT;
}


QString SceneryObjectsRootSceneComponent::getComponentTypeName() const noexcept
{ 
	return QString("");
}

QString SceneryObjectsRootSceneComponent::getComponentSubTypeName() const noexcept 
{
	return QString("");
}

QString SceneryObjectsRootSceneComponent::getComponentName() const noexcept 
{
	return QString("Objects");
}

SceneComponentType SceneryObjectsRootSceneComponent::getComponentType() const noexcept 
{ 
	return OBJECTS_ROOT;
}