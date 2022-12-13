#pragma once
#include "Novel/Data/Visual/Scenery/SceneryObject.h"

#include "Novel/Data/Asset/AssetImage.h"
#include "Novel/Data/Asset/AssetAnim.h"
#include "Novel/Data/Text/Voice.h"

/// Represents a Character in the Novel
class Character final : public SceneryObject
{
public:
	Character()                                 = default;
	/// \exception Error Couldn't find the Voice named `voiceName` or couldn't find/read the AssetImage named `assetImageName`
	Character(const QString& name, const QString& assetImageName, const QPoint pos, const QSize scale, double rotationDegree, const QVarLengthArray<double, 4>& colorMultiplier, double alphaMultiplier, bool bVisible, const QString& defaultVoiceName);
	Character(const Character& obj)             = default;
	Character& operator=(Character obj) noexcept;
	bool operator==(const Character& obj) const noexcept; 
	bool operator!=(const Character& obj) const = default; //{ return !(*this == obj); }

	/// \exception Error `defaultVoice_`/`assetImage_` is invalid
	/// \return Whether an Error has occurred
	bool checkForErrors(bool bComprehensive = false) const override;

	const Voice* getDefaultVoice() const noexcept;
	Voice* getDefaultVoice() noexcept;
	QString getDefaultVoiceName() const noexcept;
	void setDefaultVoice(const QString& defaultVoiceName, Voice* voice = nullptr) noexcept;

private:
	QString defaultVoiceName_ = "";
	Voice*  defaultVoice_     = nullptr;

	//QString			idleLive2DAnimName;
	//AssetLive2DAnim *idleLive2DAnim;
	//QString			currentLive2DAnimName;
	//AssetLive2DAnim *currentLive2DAnim;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	virtual void serializableLoad(QDataStream& dataStream);
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	virtual void serializableSave(QDataStream& dataStream) const;
};