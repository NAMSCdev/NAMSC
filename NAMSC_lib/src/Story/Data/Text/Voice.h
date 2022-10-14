#pragma once
#include "Global.h"

#include "Story/Data/Asset/Type/FontAsset.h"
#include "Story/Data/Asset/AssetManager.h"

///Tells how the text should be displayed
///[optional] And if there should be any lip syncing done (if the Character is Live2D compatible)
class Voice
{
	///Friends for serialization
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
	Voice(QString &&fontAssetName, QString &&insertionSoundAssetName, unsigned fontSize, bool bold, bool italic, 
		  bool underscore, unsigned short color[4], Qt::AlignmentFlag alignment = Qt::AlignHCenter, LipSyncType lipSync = LipSyncType::None) : 
		fontAssetName(move(fontAssetName)), insertionSoundAssetName(move(insertionSoundAssetName)), fontSize(fontSize), bold(bold), italic(italic),
		underscore(underscore), alignment(alignment), lipSync(lipSync)
	{
		this->color[0] = color[0];
		this->color[1] = color[1];
		this->color[2] = color[2];
		this->color[3] = color[3];
		fontAsset = AssetManager::getInstance().findFontAsset(this->fontAssetName);
		insertionSoundAsset = AssetManager::getInstance().findSoundAsset(this->insertionSoundAssetName);
	}
	Voice(const Voice& asset)						{ *this = asset; }
	Voice& operator=(const Voice& asset)			= default;

private:
	///Name to the Font used to display the text spoken by this Voice
	QString		fontAssetName;
	///Font used to display the text spoken by this Voice
	FontAsset	*fontAsset;

	///Name to the Font used to display the text spoken by this Voice
	QString		insertionSoundAssetName;
	///Font used to display the text spoken by this Voice
	SoundAsset *insertionSoundAsset;

	///Font size used to display the text spoken by this Voice
	unsigned	fontSize;

	///Wraps rich text with a <b> tag, bolding it
	bool	 bold			= false;

	///Wraps rich text with a <i> tag, italizing it
	bool	italic			= false;	

	///Wraps rich text with a <u> tag, underscoring it
	bool	underscore		= false;

	///Multiplies cps value and rounds it
	///Possible values:
	///0.0-1.0
	double  cpsMultiplier	= 1.0;

	///Default color in RGBA format used to display the text spoken by this Voice
	unsigned short color[4]	= { 0, 0, 0, 255 };

	///[optional]Alignment of the text
	Qt::AlignmentFlag alignment	= Qt::AlignHCenter;

	///[optional]If a Character is compatible with Live2D, we can animate its lips while they are talking
	///Possible values:
	///- None
	///- Full
	///- Static
	LipSyncType	lipSync	= LipSyncType::Full;

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream &dataStream)
	{
		dataStream >> fontAssetName >> fontSize >> bold >> italic >> underscore >> color[0] >> color[1] >> color[2] >> color[3] >> alignment >> lipSync;
	}
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const
	{
		dataStream << SerializationID::Voice << fontAssetName << fontSize << bold << italic << underscore << color[0] << color[1] << color[2] << color[3] << alignment << lipSync;
	}
};