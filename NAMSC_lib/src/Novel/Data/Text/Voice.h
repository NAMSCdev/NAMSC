#pragma once
#include "Global.h"

#include "Novel/Data/Asset/Type/AssetFont.h"
#include "Novel/Data/Asset/AssetManager.h"

///Tells how the text should be displayed
///[optional] And if there should be any lip syncing done (if the Character is Live2D compatible)
class Voice
{
	//Friends for serialization
	friend QDataStream& operator>>(QDataStream&, Voice&);
	friend QDataStream& operator<<(QDataStream&, const Voice&);
public:
	///[optional]If a Character is compatible with Live2D, we can animate its lips while they are talking
	enum class LipSyncType
	{
		None,		///No animation
		Full,		///Animation even if the sound is not produced (synthe
		Static		///Open mouth while talking regardless of the sound volume, but no animation
	};

	Voice() = default;
	Voice(QString&& fontAssetName, QString&& insertionAssetSoundName, uint fontSize, bool bold, bool italic,
		bool underscore, QColor color, Qt::AlignmentFlag alignment = Qt::AlignHCenter, LipSyncType lipSync = LipSyncType::None);
	Voice(const Voice& obj) { *this = obj; }
	Voice& operator=(const Voice& obj);

private:
	///Name to the Font used to display the text spoken by this Voice
	QString	fontAssetName;
	///Font used to display the text spoken by this Voice
	AssetFont *fontAsset;

	///Name to the Font used to display the text spoken by this Voice
	QString	insertionAssetSoundName;
	///Font used to display the text spoken by this Voice
	AssetSound *insertionAssetSound;

	///Font size used to display the text spoken by this Voice
	uint fontSize;

	///Wraps rich text with a <b> tag, bolding it
	bool bold = false;

	///Wraps rich text with a <i> tag, italizing it
	bool italic	= false;	

	///Wraps rich text with a <u> tag, underscoring it
	bool underscore	= false;

	///Multiplies cps value and rounds it
	///Possible values:
	///0.0-1.0
	double cpsMultiplier = 1.0;

	///Default color in RGBA format used to display the text spoken by this Voice
	QColor color = { 0, 0, 0, 255 };

	///[optional]Alignment of the text
	Qt::AlignmentFlag alignment	= Qt::AlignHCenter;

	///[optional]If a Character is compatible with Live2D, we can animate its lips while they are talking
	///Possible values:
	///- None
	///- Full
	///- Static
	LipSyncType lipSync = LipSyncType::Full;

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream& dataStream);
	///Saving an object to a binary file
	void serializableSave(QDataStream& dataStream) const;
};

inline Voice::Voice(QString&& fontAssetName, QString&& insertionAssetSoundName, uint fontSize, bool bold, bool italic,
	bool underscore, QColor color, Qt::AlignmentFlag alignment = Qt::AlignHCenter, LipSyncType lipSync = LipSyncType::None) :
	fontAssetName(move(fontAssetName)), insertionAssetSoundName(move(insertionAssetSoundName)), fontSize(fontSize), bold(bold), italic(italic),
	underscore(underscore), alignment(alignment), lipSync(lipSync)
{
	this->color = color;
	fontAsset = AssetManager::getInstance().findAssetFont(this->fontAssetName);
	insertionAssetSound = AssetManager::getInstance().findAssetSound(this->insertionAssetSoundName);
}

inline Voice& Voice::operator=(const Voice& obj)
{
	if (this == &obj) return *this;

	fontAssetName = obj.fontAssetName;
	fontAsset = obj.fontAsset;
	insertionAssetSoundName = obj.insertionAssetSoundName;
	insertionAssetSound = obj.insertionAssetSound;
	fontSize = obj.fontSize;
	bold = obj.bold;
	italic = obj.italic;
	underscore = obj.underscore;
	cpsMultiplier = obj.cpsMultiplier;
	color = obj.color;
	alignment = obj.alignment;
	lipSync = obj.lipSync;

	return *this;
}