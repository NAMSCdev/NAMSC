#pragma once

#include <QColor>
#include <QFont>

#include "pvnLib/Novel/Data/Audio/Sound.h"
#include "pvnLib/Novel/Data/Asset/AssetManager.h"

/// Tells how the text should be displayed
/// [optional] And if there should be any lip syncing done (if the Character is Live2D compatible)
class Voice
{
	/// Swap trick
	friend void swap(Voice& first, Voice& second) noexcept;
public:
	/// [optional] If a Character is compatible with Live2D, we can animate its lips while they are talking
	enum class LipSyncType
	{
		None,		/// No animation
		Full,		/// Animation even if the sound is not produced (synthe
		Static		/// Open mouth while talking regardless of the sound volume, but no animation
	};

	Voice() noexcept = default;
	/// \param A short Sound played after a single character insertion
	/// \param cpsMultiplier Multiplies `NovelSettings::cps_` setting, unless `cpsOverwrite` is set
	/// \param cpsOverwrite Overwrites `NovelSettings::cps` setting if not zero
	/// \param Default color in RGBA format used to display the text spoken by this Voice
	/// \param If a Character is compatible with Live2D, we can animate its lips while they are talking
	explicit Voice(const QString& name, const QString& fontName = "", uint fontSize = 12, bool bold = false, bool italic = false, bool underscore = false, const QColor color = QColor(0, 0, 0, 255), double cpsMultiplier = 1.0, uint cpsOverwrite = 0, const Qt::AlignmentFlag alignment = Qt::AlignHCenter, const LipSyncType lipSync = LipSyncType::None) noexcept;
	Voice(const Voice& obj)                 noexcept = default;
	Voice(Voice&& obj)                      noexcept = default;
	Voice& operator=(const Voice& obj)      noexcept = default;
	//Voice& operator=(Voice obj)             noexcept;
	bool operator==(const Voice& obj) const noexcept;
	bool operator!=(const Voice& obj) const noexcept = default;

	/// \exception Error `font_` is invalid
	/// \return Whether an Error has occurred
	bool errorCheck(bool bComprehensive = false) const;

	QString getFontName()  const noexcept;
	const QFont* getFont() const noexcept;
	QFont*       getFont()       noexcept;
	void setFont(const QString& fontName) noexcept;

	QString name                = "";

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// A short Sound played after a single character insertion
	/// It is cut short if a new character appears before the Sound finished playing
	/// Once this is set, the cps should also be set to a customized for best experience
	Sound insertionSound;

	/// Wraps the rich text with a tag
	bool bold                   = false,
		 italic                 = false,
		 underscore             = false;

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// Multiplies `NovelSettings::cps` setting
	double cpsMultiplier        = 1.0;

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// Overwrites `NovelSettings::cps` setting if not zero
	/// 0 stands for unchanged (changed only by `cpsMultiplier`)
	/// When `cpsOverwrite` is set, `cpsMultiplier`no longer has any effect on Characters Per Second
	uint cpsOverwrite           = 0;

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// Default color in RGBA format used to display the text spoken by this Voice
	QColor color                = { 0, 0, 0, 255 };

	Qt::AlignmentFlag alignment = Qt::AlignHCenter;

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// If a Character is compatible with Live2D, we can animate its lips while they are talking
	//TODO: display it in doxy in a normal way
	/// Possible values:
	/// - None
	/// - Full
	/// - Static
	LipSyncType lipSync         = LipSyncType::Full;

private:
	QString fontName_           = "";
	QFont   font_;
	uint    fontSize_           = 12;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream);
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const;
};