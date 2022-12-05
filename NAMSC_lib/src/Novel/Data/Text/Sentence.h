#pragma once

#include "Novel/Data/Text/Voice.h"
#include "Novel/Data/Text/Choice.h"

/// Represents one portion of the Dialogue that ends with user click if `bEndWithInput` is enabled or after `waitBeforeContinueTime` milliseconds
/// This could be not only one sentence but also a longer text, but this name is kind of intuitional
class Sentence final
{
	//Friends for serialization
	friend QDataStream& operator>>(QDataStream&, Sentence&);
	friend QDataStream& operator<<(QDataStream&, const Sentence&);
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

	Sentence(Event* const parentEvent, Scene* const parentScene) noexcept;
	/// \exception Error An Error occurred in `text` or the 'character_'/`voice_`/`assetImage_` couldn't be found/read
	Sentence(Event* const parentEvent, Scene* const parentScene, const Translation& text, const QString& displayedName, const QString& characterName, const QString& voiceName, const QString& assetImageName, double cpsMultiplier, uint cpsOverwrite, bool bEndWithInput, uint waitBeforeContinueTime);
	Sentence(const Sentence& obj)             = default;
	Sentence& operator=(Sentence obj) noexcept;
	bool operator==(const Sentence& obj) const noexcept;
	bool operator!=(const Sentence& obj) const = default; //{ return !(*this == obj); }

	/// \exception Error `text`/'character_'/`voice_`/`assetImage_` is invalid
	/// \return Whether an Error has occurred
	bool checkForErrors(bool bComprehensive = false) const;

	const AssetImage* getAssetImage() const noexcept;
	AssetImage* getAssetImage() noexcept;
	QString getAssetImageName() const noexcept;
	void setAssetImage(const QString& assetImageName) noexcept;

	const Voice* getVoice() const noexcept;
	Voice* getVoice() noexcept;
	QString getVoiceName() const noexcept;
	void setVoice(const QString& voiceName) noexcept;

	Translation text;

	QString displayedName        = "";
	QString characterName        = "";

	/// Multiplies `NovelSettings::cps_` setting, unless `cpsOverwrite` is set
	/// If the Sentence is spoken by a Voice with its own `cpsMultiplier`, they multiply
	double cpsMultiplier         = 1.0;

	/// Overwrites `NovelSettings::cps` setting
	/// 0 stands for unchanged (changed only by `cpsMultiplier`)
	/// When `cpsOverwrite` is set, `cpsMultiplier_` no longer has any effect on Characters Per Second
	uint cpsOverwrite            = 0;

	/// Whether the user `Qt::MouseButton::LeftButton` (if `NovelSettings::mouseButton_` is `true`) / `NovelSettings::nextButton_` is needed to end the Sentence
	bool bEndWithInput           = true;

	/// If the `bEndWithInput_` is set to false, this is the time in milliseconds that the Engine will wait after the text is rendered before moving to a new Sentence
	uint waitBeforeContinueTime  = 1000;

private:
	Event* const parentEvent_;
	Scene* const parentScene_;

	/// A temporary Image to show some facial expresions or anything else
	/// Empty means no change
	QString      assetImageName_ = "";
	AssetImage*  assetImage_     = nullptr;

	QString	     voiceName_      = "";
	Voice*       voice_          = nullptr;

	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream);
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const;
};