#pragma once
#include "Novel/Action/Visual/ActionCharacter.h"

#include "Novel/Data/Text/Voice.h"

/// Changes the `defaultVoice_` of a Character
class ActionCharacterSetVoice final : public ActionCharacter
{
public:
	ActionCharacterSetVoice(Event* const parentEvent) noexcept;
	/// \exception Error Couldn't find the Character named `characterName` or couldn't find the Voice named `voiceName`
	ActionCharacterSetVoice(Event* const parentEvent, const QString& characterName, const QString& voiceName);
	ActionCharacterSetVoice(const ActionCharacterSetVoice& obj) noexcept;
	ActionCharacterSetVoice& operator=(const ActionCharacterSetVoice& obj) noexcept;
	bool operator==(const ActionCharacterSetVoice& obj) const noexcept;
	bool operator!=(const ActionCharacterSetVoice& obj) const = default; //{ return !(*this == obj); }

	/// \exception Error 'character_`/`voice_` is invalid
	/// \return Whether an Error has occurred
	bool checkForErrors(bool bComprehensive = false) const override;

	Action* clone() const override;

	void run() override;

	/// Sets a function pointer that is called (if not nullptr) after the ActionCharacterSetVoice's `void run()` allowing for data read
	void setOnRunListener(std::function<void(Event* const parentEvent, Character* character, Voice* voice)> onRun) noexcept;

	void acceptVisitor(ActionVisitor* visitor) override;

	const Voice* getVoice() const noexcept;
	Voice* getVoice() noexcept;
	QString getVoiceName() const noexcept;
	void setVoice(const QString& voiceName) noexcept;

private:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	/// \return NovelLib::SerializationID corresponding to the class of a serialized object
	NovelLib::SerializationID getType() const noexcept override;

	/// A function pointer that is called (if not nullptr) after the ActionCharacterSetVoice's `void run()` allowing for data read
	std::function<void(Event* const parentEvent, Character* character, Voice* voice)> onRun_ = nullptr;

	QString voiceName_ = "";
	Voice*  voice_     = nullptr;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};