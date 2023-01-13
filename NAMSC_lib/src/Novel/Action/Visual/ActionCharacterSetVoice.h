#pragma once
#include "Novel/Action/Visual/ActionCharacter.h"

#include "Novel/Data/Text/Voice.h"

/// Changes the `defaultVoice_` of a Character
class ActionCharacterSetVoice final : public ActionCharacter
{
	/// Swap trick
	friend void swap(ActionCharacterSetVoice& first, ActionCharacterSetVoice& second) noexcept;
public:
	explicit ActionCharacterSetVoice(Event* const parentEvent)             noexcept;
	/// \param character Copies the Character pointer. It's okay to leave it as nullptr, as it will be loaded later. This is a very minor optimization 
	/// \param voice Copies the Voice pointer. It's okay to leave it as nullptr, as it will be loaded later. This is a very minor optimization 
	/// \exception Error Couldn't find the Character named `characterName` or couldn't find the Voice named `voiceName`
	ActionCharacterSetVoice(Event* const parentEvent, const QString& characterName, const QString& voiceName = "", Character* character = nullptr, Voice* voice = nullptr);
	ActionCharacterSetVoice(const ActionCharacterSetVoice& obj)            noexcept = delete;
	ActionCharacterSetVoice(ActionCharacterSetVoice&& obj)                 noexcept;
	ActionCharacterSetVoice& operator=(const ActionCharacterSetVoice& obj) noexcept = delete;
	//ActionCharacterSetVoice& operator=(ActionCharacterSetVoice obj)        noexcept;
	bool operator==(const ActionCharacterSetVoice& obj) const              noexcept = delete;
	bool operator!=(const ActionCharacterSetVoice& obj) const              noexcept = delete;

	/// \exception Error 'character_`/`voice_` is invalid
	/// \return Whether an Error has occurred
	bool errorCheck(bool bComprehensive = false) const override;

	void run() override;

	/// Sets a function pointer that is called (if not nullptr) after the ActionCharacterSetVoice's `void run()` allowing for data read. Consts are safe to be casted to non-consts, they are there to indicate you should not do that, unless you have a very reason for it
	void setOnRunListener(std::function<void(const Event* const parentEvent, const Character* const character, const Voice* const voice)> onRun) noexcept;

	void acceptVisitor(ActionVisitor* visitor) override;

	QString getVoiceName()  const noexcept;
	const Voice* getVoice() const noexcept;
	Voice*       getVoice()       noexcept;
	void setVoice(const QString& voiceName, Voice* voice = nullptr) noexcept;

private:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	/// \return NovelLib::SerializationID corresponding to the class of a serialized object
	NovelLib::SerializationID getType() const noexcept override;

	/// A function pointer that is called (if not nullptr) after the ActionCharacterSetVoice's `void run()` allowing for data read. Consts are safe to be casted to non-consts, they are there to indicate you should not do that, unless you have a very reason for it
	std::function<void(const Event* const parentEvent, const Character* const character, const Voice* const voice)> onRun_ = nullptr;

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