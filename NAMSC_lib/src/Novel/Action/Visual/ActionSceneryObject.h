 #pragma once
#include "Novel/Action/Action.h"

#include "Novel/Data/Visual/Scenery/SceneryObject.h"

/// Action that affects a SceneryObject
class ActionSceneryObject : public Action
{
public:
	ActionSceneryObject(Event* const parentEvent, Scene* const parentScene) noexcept;
	/// \exception Error Couldn't find the SceneryObject named `sceneryObjectName_`
	ActionSceneryObject(Event* const parentEvent, Scene* const parentScene, const QString& sceneryObjectName);
	ActionSceneryObject(const ActionSceneryObject& obj) = delete;
	ActionSceneryObject& operator=(const ActionSceneryObject& obj) noexcept;
	bool operator==(const ActionSceneryObject& obj) const noexcept;
	bool operator!=(const ActionSceneryObject& obj) const = default; //{ return !(*this == obj); }

	/// \exception Error `sceneryObject_` is invalid
	/// \return Whether an Error has occurred
	virtual bool checkForErrors(bool bComprehensive = false) const override;

	const SceneryObject* getSceneryObject() const noexcept;
	SceneryObject* getSceneryObject() noexcept;
	QString getSceneryObjectName() const noexcept;
	void setSceneryObject(const QString& sceneryObjectName) noexcept;

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