#pragma once

#include "pvnLib/Novel/Data/Text/Voice.h"
#include "pvnLib/Novel/Data/Text/Choice.h"

/// Represents one portion of the Dialogue that ends with user click if `bEndWithInput` is enabled or after `waitBeforeContinueTime` milliseconds
/// This could be not only one sentence but also a longer text, but this name is kind of intuitional
class Sentence final
{
	/// Swap trick
	friend void swap(Sentence& first, Sentence& second) noexcept;
public:
	/// Determines how the text should appear
	enum class SentenceAppearType
	{
		CharByChar,		/// It gives a feeling of actual talking and it is possible to change character insertion sound (if Character is mute) and speed
		WordByWord		/// [optional] Karaoke-like style, where words appear one after another
	};

	/// [optional] Flags (they can be joined) that specify effect that appearing words have, if `wordAppearType_ == WordAppearType::WordByWord`
	/// NOTE: RenPy doesn't support this by default (other than manual usage of Python), so integration with it would be hard
	/// It is probably better to contribute to RenPy by adding this feature and then adding support for RenPy for it there
	enum class SentenceStyle
	{
		Bold		= 0b1,			
		Italic		= 0b10,	
		Underscore	= 0b100,
		Color		= 0b1000		/// Custom color
	};

	explicit Sentence(Event* const parentEvent);

	/// \param displayedName If not empty, this name will be displayed as the Character's name during this Sentence's display
	/// \param assetImageName A temporary AssetImage for the Character to show some facial expresions or anything else
	/// \param cpsMultiplier Multiplies `NovelSettings::cps_` setting, unless `cpsOverwrite` is set
	/// \param cpsOverwrite Overwrites `NovelSettings::cps` setting if not zero
	/// \param bEndWithInput Whether the user `Qt::MouseButton::LeftButton` (if `NovelSettings::mouseButton_` is `true`) / `NovelSettings::nextButton_` is needed to end the Sentence
	/// \param waitBeforeContinueTime If the `bEndWithInput_` is set to false, this is the time in milliseconds that the Engine will wait after the text is rendered before moving to a new Sentence
	/// \param character Copies the Character pointer. It's okay to leave it as nullptr, as it will be loaded later. This is a very minor optimization
	/// \param voice Copies the Voice pointer. It's okay to leave it as nullptr, as it will be loaded later. This is a very minor optimization
	/// \param assetImage Copies the AssetImage pointer. It's okay to leave it as nullptr, as it will be loaded later. This is a very minor optimization
	/// \exception Error An Error occurred in `text` or the 'character_'/`voice_`/`assetImage_` couldn't be found/read
	Sentence(Event* const parentEvent, const Translation& translation, const QString& displayedName = "", const QString& characterName = "", const QString& voiceName = "", const QString& assetImageName = "", double cpsMultiplier = 1.0, uint cpsOverwrite = 0, bool bEndWithInput = true, uint waitBeforeContinueTime = 1000, Character* character = nullptr, Voice* voice = nullptr, AssetImage* assetImage = nullptr);
	Sentence(const Sentence& obj)              noexcept;
	Sentence(Sentence&& obj)                   noexcept;
	Sentence& operator=(Sentence obj)          noexcept;
	bool operator==(const Sentence& obj) const noexcept;
	bool operator!=(const Sentence& obj) const noexcept = default;

	/// \exception Error `text`/'character_'/`voice_`/`assetImage_` is invalid
	/// \return Whether an Error has occurred
	bool errorCheck(bool bComprehensive = false) const;

	QString getAssetImageName()       const noexcept;
	const AssetImage* getAssetImage() const noexcept;
	AssetImage*       getAssetImage()       noexcept;
	void setAssetImage(const QString& assetImageName, AssetImage* assetImage = nullptr) noexcept;

	QString getVoiceName()  const noexcept;
	const Voice* getVoice() const noexcept;
	Voice*       getVoice()       noexcept;
	void setVoice(const QString& voiceName, Voice* voice = nullptr) noexcept;

	QString getCharacterName()      const noexcept;
	const Character* getCharacter() const noexcept;
	Character*       getCharacter()       noexcept;
	void setCharacter(const QString& characterName, Character* character = nullptr) noexcept;

	void render(SceneWidget* sceneWidget, uint characterCount);

	Event* const parentEvent;

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// If not empty, this name will be displayed as the Character's name during this Sentence's display
	QString     displayedName   = "";

	Translation translation;

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// Multiplies `NovelSettings::cps_` setting, unless `cpsOverwrite` is set
	/// If the Sentence is spoken by a Voice with its own `cpsMultiplier`, they multiply
	double cpsMultiplier         = 1.0;

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// Overwrites `NovelSettings::cps` setting if not zero
	/// 0 stands for unchanged (changed only by `cpsMultiplier`)
	/// When `cpsOverwrite` is set, `cpsMultiplier_` no longer has any effect on Characters Per Second
	uint cpsOverwrite            = 0;

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// Whether the user `Qt::MouseButton::LeftButton` (if `NovelSettings::mouseButton_` is `true`) / `NovelSettings::nextButton_` is needed to end the Sentence
	bool bEndWithInput           = true;

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// If the `bEndWithInput_` is set to false, this is the time in milliseconds that the Engine will wait after the text is rendered before moving to a new Sentence
	uint waitBeforeContinueTime  = 1000;

private:
	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// A temporary AssetImage for the Character to show some facial expresions or anything else
	/// Empty means no change
	QString     assetImageName_ = "";
	AssetImage* assetImage_     = nullptr;

	QString	    voiceName_      = "";
	Voice*      voice_          = nullptr;

	QString     characterName_  = "";
	Character*  character_      = nullptr;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream);
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const;
};