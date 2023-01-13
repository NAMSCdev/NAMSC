 #pragma once
#include "Novel/Action/Action.h"

#include "Novel/Data/Visual/Scenery/SceneryObject.h"

/// Action that affects a SceneryObject
class ActionSceneryObject : public Action
{
	/// Swap trick
	friend void swap(ActionSceneryObject& first, ActionSceneryObject& second) noexcept;
public:
	/// \param sceneryObject Copies the SceneryObject pointer. It's okay to leave it as nullptr, as it will be loaded later. This is a very minor optimization
	/// \exception Error Couldn't find the SceneryObject named `sceneryObjectName_`
	explicit ActionSceneryObject(Event* const parentEvent, const QString& sceneryObjectName = "", SceneryObject* sceneryObject = nullptr);
	ActionSceneryObject(const ActionSceneryObject& obj)            noexcept = delete;
	ActionSceneryObject(ActionSceneryObject&& obj)                 noexcept = delete;
	ActionSceneryObject& operator=(const ActionSceneryObject& obj) noexcept = delete;
	bool operator==(const ActionSceneryObject& obj) const          noexcept = delete;
	bool operator!=(const ActionSceneryObject& obj) const          noexcept = delete;
	//Makes it abstract
	virtual ~ActionSceneryObject() = 0;

	virtual void run() override;

	/// \exception Error `sceneryObject_` is invalid
	/// \return Whether an Error has occurred
	virtual bool errorCheck(bool bComprehensive = false) const override;

	QString getSceneryObjectName()          const noexcept;
	const SceneryObject* getSceneryObject() const noexcept;
	SceneryObject*       getSceneryObject()       noexcept;
	void setSceneryObject(const QString& sceneryObjectName, SceneryObject* sceneryObject = nullptr) noexcept;

protected:
	QString		   sceneryObjectName_ = "";
	SceneryObject* sceneryObject_     = nullptr;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	virtual void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	virtual void serializableSave(QDataStream& dataStream) const override;
};