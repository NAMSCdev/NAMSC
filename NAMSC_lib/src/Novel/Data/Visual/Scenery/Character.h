#pragma once
#include "Novel/Data/Visual/Scenery/SceneryObject.h"

#include "Novel/Data/Asset/AssetImage.h"
#include "Novel/Data/Asset/AssetAnim.h"
#include "Novel/Data/Text/Voice.h"

/// Represents a Character in the Novel
class Character final : public SceneryObject
{
	/// Swap trick
	friend void swap(Character& first, Character& second) noexcept;
public:
	Character()                                 noexcept = default;
	/// \param assetImage Copies the AssetImage pointer. It's okay to leave it as nullptr, as it will be loaded later. This is a very minor optimization
	/// \param defaultVoice Copies the Voice pointer. It's okay to leave it as nullptr, as it will be loaded later. This is a very minor optimization
	/// \exception Error Couldn't find the Voice named `voiceName` or couldn't find/read the AssetImage named `assetImageName`
	Character(const QString& name, const QString& assetImageName, bool bMirrored = false, const QPoint pos = { 0, 0 }, const QSizeF scale = { 1.0, 1.0 }, double rotationDegree = 0.0, const QVarLengthArray<double, 4>& colorMultiplier = { 1.0, 1.0, 1.0, 1.0 }, double alphaMultiplier = 1.0, bool bVisible = true, const QString& defaultVoiceName = "", AssetImage* assetImage = nullptr, Voice* defaultVoice = nullptr);
	Character(const Character& obj)             noexcept = default;
	Character(Character&& obj)                  noexcept = default;
	Character& operator=(const Character& obj)  noexcept = default;
	//Character& operator=(Character obj)         noexcept;
	bool operator==(const Character& obj) const noexcept; 
	bool operator!=(const Character& obj) const noexcept = default;

	/// \exception Error `defaultVoice_`/`assetImage_` is invalid
	/// \return Whether an Error has occurred
	bool errorCheck(bool bComprehensive = false) const override;

	QString getDefaultVoiceName()  const noexcept;
	const Voice* getDefaultVoice() const noexcept;
	Voice*       getDefaultVoice()       noexcept;
	void setDefaultVoice(const QString& defaultVoiceName, Voice* defaultVoice = nullptr) noexcept;

	//todo: do not botch
	QString getComponentTypeName()          const noexcept override;
	QString getComponentSubTypeName()       const noexcept override;
	SceneComponentType getComponentType()   const noexcept override;

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