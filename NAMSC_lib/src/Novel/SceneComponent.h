#pragma once
#include <QString>

enum SceneComponentType
{
	INVALID,
	NOT_COMPONENT,
	SCENE,
	EVENT,
	OBJECT,
	CHARACTER,
	OBJECTS_ROOT,
	CHARACTERS_ROOT
};

enum class EventSubType
{
	INVALID,
	NOT_EVENT,
	EVENT_DIALOG,
	EVENT_CHOICE,
	EVENT_JUMP,
    EVENT_IF,
    EVENT_END_IF,
    EVENT_INPUT,
    EVENT_WAIT
};

//todo: do not botch
class SceneComponent
{
public:
	SceneComponent() = default;
	virtual ~SceneComponent() = 0;

	virtual QString getComponentTypeName()        const noexcept = 0;
	virtual QString getComponentSubTypeName()     const noexcept = 0;
	virtual SceneComponentType getComponentType() const noexcept = 0;
	virtual EventSubType getComponentEventType()  const noexcept;
	virtual QString getComponentName()            const noexcept = 0;
};

class DummySceneComponent final : public SceneComponent
{
public:
	DummySceneComponent() = default;

	QString getComponentTypeName()         const noexcept override;
	QString getComponentSubTypeName()      const noexcept override;
	SceneComponentType getComponentType()  const noexcept override;
	QString getComponentName()             const noexcept override;
};

class CharactersRootSceneComponent final : public SceneComponent
{
public:
	CharactersRootSceneComponent() = default;

	QString getComponentTypeName()         const noexcept override;
	QString getComponentSubTypeName()      const noexcept override;
	SceneComponentType getComponentType()  const noexcept override;
	QString getComponentName()             const noexcept override;
};

class SceneryObjectsRootSceneComponent final : public SceneComponent
{
public:
	SceneryObjectsRootSceneComponent() = default;

	QString getComponentTypeName()         const noexcept override;
	QString getComponentSubTypeName()      const noexcept override;
	SceneComponentType getComponentType()  const noexcept override;
	QString getComponentName()             const noexcept override;
};

