#pragma once

#include <QVarLengthArray>

#include "Novel/SceneComponent.h"
#include "Novel/Data/Asset/AssetManager.h"

#include "Novel/Data/Visual/Animation/AnimatorAll.h"

/// Holds data for a drawable object
class SceneryObject : public SceneComponent
{
	/// Swap trick
	friend void swap(SceneryObject& first, SceneryObject& second) noexcept;
public:
	SceneryObject()                                    noexcept = default;
	/// \param assetImage Copies the AssetImage pointer. It's okay to leave it as nullptr, as it will be loaded later. This is a very minor optimization
	/// \exception Error Couldn't find/read the AssetImage named `assetImageName`
	SceneryObject(const QString& name, const QString& assetImageName, bool bMirrored = false, const QPoint pos = { 0, 0 }, const QSizeF scale = { 1.0, 1.0 }, double rotationDegree = 0.0, const QVarLengthArray<double, 4>& colorMultiplier = { 1.0, 1.0, 1.0, 1.0 }, double alphaMultiplier = 1.0, bool bVisible = true, AssetImage* assetImage = nullptr);
	SceneryObject(const SceneryObject& obj)            noexcept = default;
	SceneryObject(SceneryObject&& obj)                 noexcept = default;
	SceneryObject& operator=(const SceneryObject& obj) noexcept = default;
	//SceneryObject& operator=(SceneryObject obj)        noexcept;
	bool operator==(const SceneryObject& obj) const    noexcept;
	bool operator!=(const SceneryObject& obj) const    noexcept = default;
	bool operator==(const QString& name)      const    noexcept;
	bool operator!=(const QString& name)      const    noexcept;
	// The destructor needs to be virtual, so the proper destructor will always be called when destroying an Action pointer
	virtual ~SceneryObject() = default;

	/// \exception Error `assetImage_` is invalid 
	virtual bool errorCheck(bool bComprehensive = false) const;

	void run();
	void update(uint elapsedTime);

	QString getAssetImageName()       const noexcept;
	const AssetImage* getAssetImage() const noexcept;
	AssetImage*       getAssetImage()       noexcept;
	void setAssetImage(const QString& assetImageName, AssetImage* assetImage = nullptr) noexcept;

	void addAnimator(AnimatorSceneryObjectColor&&  animatorColor);
	void addAnimator(AnimatorSceneryObjectFade&&   animatorFade);
	void addAnimator(AnimatorSceneryObjectMove&&   animatorMove);
	void addAnimator(AnimatorSceneryObjectRotate&& animatorRotate);
	void addAnimator(AnimatorSceneryObjectScale&&  animatorScale);

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

	bool bMirrored              = false;

	bool bVisible               = false;

	//todo: do not botch
	QString getComponentTypeName()        const noexcept override;
	QString getComponentSubTypeName()     const noexcept override;
	SceneComponentType getComponentType() const noexcept override;
	QString getComponentName()            const noexcept override;

protected:
	QString     assetImageName_ = "";
	AssetImage* assetImage_     = nullptr;

	std::vector<AnimatorSceneryObjectColor>  animatorsColor_;
	int playedAnimatorColorIndex_  = -1;
	std::vector<AnimatorSceneryObjectFade>   animatorsFade_;
	int playedAnimatorFadeIndex_   = -1;
	std::vector<AnimatorSceneryObjectMove>   animatorsMove_;
	int playedAnimatorMoveIndex_   = -1;
	std::vector<AnimatorSceneryObjectRotate> animatorsRotate_;
	int playedAnimatorRotateIndex_ = -1;
	std::vector<AnimatorSceneryObjectScale>  animatorsScale_;
	int playedAnimatorScaleIndex_  = -1;

	//[optional] create this class and it will store AssetImages with custom names for image filtering (useful in Editor)
	//std::vector<SceneryObjectPart> parts;
private:
	bool errorChecked = false;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	virtual void serializableLoad(QDataStream& dataStream);
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	virtual void serializableSave(QDataStream& dataStream) const;
};