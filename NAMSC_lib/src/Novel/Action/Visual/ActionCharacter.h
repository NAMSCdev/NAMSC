#pragma once
#include "Novel/Action/Action.h"

#include "Novel/Data/Visual/Scenery/Character.h"

/// Action that affects a Character
class ActionCharacter : public Action
{
public:
	ActionCharacter(Event* const parentEvent, Scene* const parentScene) noexcept;
	/// \exception Couldn't find the Character named `characterName_`
	ActionCharacter(Event* const parentEvent, Scene* const parentScene, const QString& characterName);
	ActionCharacter(const ActionCharacter& obj) = delete;
	ActionCharacter& operator=(const ActionCharacter& obj) noexcept;
	bool operator==(const ActionCharacter& obj) const noexcept;
	bool operator!=(const ActionCharacter& obj) const = default; //{ return !(*this == obj); }

	virtual void run() override;

	/// \exception Error 'character_` is invalid / 'character_->assetImage_` is invalid /  'character_->assetImage_` cannot be loaded
	/// \return Whether an Error has occurred
	virtual bool checkForErrors(bool bComprehensive = false) const override;

	const Character* getCharacter() const noexcept;
	Character* getCharacter() noexcept;
	QString getCharacterName() const noexcept;
	void setCharacter(const QString& characterName) noexcept;

protected:
	QString	   characterName_ = "";
	Character* character_     = nullptr;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	virtual void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	virtual void serializableSave(QDataStream& dataStream) const override;
};