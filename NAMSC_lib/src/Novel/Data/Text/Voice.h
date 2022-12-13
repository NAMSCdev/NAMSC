#pragma once

#include <QColor>
#include <QFont>

#include "Novel/Data/Audio/Sound.h"
#include "Novel/Data/Asset/AssetManager.h"

/// Tells how the text should be displayed
/// [optional] And if there should be any lip syncing done (if the Character is Live2D compatible)
class Voice
{
	//Friends for serialization
	friend QDataStream& operator>>(QDataStream&, Voice&);
	//friend QDataStream& operator<<(QDataStream&, const Voice&);
public:
	/// [optional] If a Character is compatible with Live2D, we can animate its lips while they are talking
	enum class LipSyncType
	{
		None,		/// No animation
		Full,		/// Animation even if the sound is not produced (synthe
		Static		/// Open mouth while talking regardless of the sound volume, but no animation
	};

	Voice()                                 = default;
	Voice(const QString& name, const QString& fontName, uint fontSize, bool bold, bool italic, bool underscore, const QColor color, double cpsMultiplier = 1.0, uint cpsOverwrite = 0, const Qt::AlignmentFlag alignment = Qt::AlignHCenter, const LipSyncType lipSync = LipSyncType::None) noexcept;
	Voice(const Voice& obj)                 = default;
	Voice& operator=(Voice obj) noexcept;
	bool operator==(const Voice& obj) const noexcept;
	bool operator!=(const Voice& obj) const = default; //{ return !(*this == obj); }

	/// \exception Error `font_` is invalid
	/// \return Whether an Error has occurred
	bool checkForErrors(bool bComprehensive = false) const;

	const QFont* getFont() const noexcept;
	QString getFontName() const noexcept;
	void setFont(const QString& fontName) noexcept;

	QString name                = "";

	/// [optional] A short Sound played after a single character insertion
	/// It is cut short if a new character appears before the Sound finished playing
	/// Once this is set, the cps should also be set to a customized for best experience
	Sound insertionSound;

	/// Wraps the rich text with a tag
	bool bold                   = false,
		 italic                 = false,
		 underscore             = false;

	/// Multiplies `NovelSettings::cps` setting
	double cpsMultiplier        = 1.0;

	/// Overwrites `NovelSettings::cps` setting
	/// 0 stands for unchanged (changed only by `cpsMultiplier`)
	/// When `cpsOverwrite` is set, `cpsMultiplier`no longer has any effect on Characters Per Second
	uint cpsOverwrite           = 0;

	/// Default color in RGBA format used to display the text spoken by this Voice
	QColor color                = { 0, 0, 0, 255 };

	/// [optional]
	Qt::AlignmentFlag alignment = Qt::AlignHCenter;

	/// [optional] If a Character is compatible with Live2D, we can animate its lips while they are talking
	/// Possible values:
	/// - None
	/// - Full
	/// - Static
	LipSyncType lipSync         = LipSyncType::Full;

private:
	QString fontName_           = "";
	QFont   font_;
	uint    fontSize_           = 12;

public://---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream);
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const;
};