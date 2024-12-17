#pragma once
#include "pvnLib/Novel/Action/Action.h"

#include "pvnLib/Novel/Data/Visual/Scenery/Character.h"

/// Action that affects a Character
class ActionCharacter : public Action
{
	/// Swap trick
	friend void swap(ActionCharacter& first, ActionCharacter& second) noexcept;
public:
	/// \param character Copies the Character pointer. It's okay to leave it as nullptr, as it will be loaded later. This is a very minor optimization
	/// \exception Couldn't find the Character named `characterName_`
	explicit ActionCharacter(Event* const parentEvent, const QString& characterName = "", Character* character = nullptr);
	bool operator==(const ActionCharacter& obj) const noexcept;
	bool operator!=(const ActionCharacter& obj) const noexcept = default;
	//Makes it abstract
	virtual ~ActionCharacter() = 0;

	virtual void run() override;

	/// \exception Error 'character_` is invalid / 'character_->assetImage_` is invalid /  'character_->assetImage_` cannot be loaded
	/// \return Whether an Error has occurred
	virtual bool errorCheck(bool bComprehensive = false) const override;

	QString getCharacterName()      const noexcept;
	const Character* getCharacter() const noexcept;
	Character*       getCharacter()       noexcept;
	void setCharacter(const QString& characterName, Character* character = nullptr) noexcept;

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