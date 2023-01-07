#pragma once

#include <QVarLengthArray>

#include "Novel/Data/Asset/AssetManager.h"

#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectColor.h"
#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectFade.h"
#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectMove.h"
#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectRotate.h"
#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectScale.h"

/// Holds data for a drawable object
class SceneryObject
{
public:
	SceneryObject()                                 = default;
	/// \exception Error Couldn't find/read the AssetImage named `assetImageName`
	SceneryObject(const QString& name, const QString& assetImageName, const QPoint pos = { 0, 0 }, const QSizeF scale = { 1.0, 1.0 }, double rotationDegree = 0.0, const QVarLengthArray<double, 4>& colorMultiplier = { 1.0, 1.0, 1.0, 1.0 }, double alphaMultiplier = 1.0, bool bVisible = true);
	SceneryObject(const SceneryObject &obj) noexcept;
	SceneryObject& operator=(SceneryObject obj) noexcept;
	bool operator==(const SceneryObject& obj) const noexcept;
	bool operator!=(const SceneryObject& obj) const = default; //{ return !(*this == obj); }
	// The destructor needs to be virtual, so the proper destructor will always be called when destroying an Action pointer
	virtual ~SceneryObject() = default;

	/// \exception Error `assetImage_` is invalid 
	virtual bool checkForErrors(bool bComprehensive = false) const;

	void run();
	void update(uint elapsedTime);

	void setAssetImage(const QString& assetImageName, AssetImage* assetImage = nullptr) noexcept;
	const AssetImage* getAssetImage() const noexcept;
	AssetImage* getAssetImage() noexcept;
	QString getAssetImageName() noexcept;
	
	void addAnimator(AnimatorSceneryObjectColor&& animatorColor);
	void addAnimator(AnimatorSceneryObjectFade&& animatorFade);
	void addAnimator(AnimatorSceneryObjectMove&& animatorMove);
	void addAnimator(AnimatorSceneryObjectRotate&& animatorRotate);
	void addAnimator(AnimatorSceneryObjectScale&& animatorScale);

	void resetAnimators();
	/// \exception Error Couldn't load the `assetImage_`
	void ensureResourcesAreLoaded();

	QString name                = "";

	/// \todo [optional] allow for setting position in Z-dimension and do proper maths about it
	QPoint pos                  = { 0.0, 0.0/*, 0.0*/ };

	QSizeF scale                = { 1.0, 1.0 };
	
	double rotationDegree       = 0.0;
	
	QVarLengthArray<double, 4> colorMultiplier = { 1.0, 1.0, 1.0, 1.0 };

	double alphaMultiplier      = 1.0;

	bool bVisible               = false;

protected:
	QString     assetImageName_ = "";
	AssetImage* assetImage_     = nullptr;

	std::vector<AnimatorSceneryObjectColor> animatorsColor_;
	int playedAnimatorColorIndex_  = -1;
	std::vector<AnimatorSceneryObjectFade> animatorsFade_;
	int playedAnimatorFadeIndex_   = -1;
	std::vector<AnimatorSceneryObjectMove> animatorsMove_;
	int playedAnimatorMoveIndex_   = -1;
	std::vector<AnimatorSceneryObjectRotate> animatorsRotate_;
	int playedAnimatorRotateIndex_ = -1;
	std::vector<AnimatorSceneryObjectScale> animatorsScale_;
	int playedAnimatorScaleIndex_  = -1;

	//[optional] create this class and it will store AssetImages with custom names for image filtering (useful in Editor)
	//std::vector<SceneryObjectPart> parts;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	virtual void serializableLoad(QDataStream& dataStream);
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	virtual void serializableSave(QDataStream& dataStream) const;
};