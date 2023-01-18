#include "Novel/Data/Visual/Scenery/SceneryObject.h"

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(SceneryObject& first, SceneryObject& second) noexcept
{
	using std::swap;
	swap(first.name,            second.name);
	swap(first.assetImageName_, second.assetImageName_);
	swap(first.bMirrored,       second.bMirrored);
	swap(first.pos,             second.pos);
	swap(first.scale,           second.scale);
	swap(first.rotationDegree,  second.rotationDegree);
	swap(first.colorMultiplier, second.colorMultiplier);
	swap(first.alphaMultiplier, second.alphaMultiplier);
	swap(first.bVisible,        second.bVisible);
	swap(first.assetImage_,     second.assetImage_);
}

SceneryObject::SceneryObject(const QString& name, const QString& assetImageName, bool bMirrored, const QPointF pos, const QSizeF scale, double rotationDegree, const QVarLengthArray<double, 4>& colorMultiplier, double alphaMultiplier, bool bVisible, AssetImage* assetImage)
	: name(name), 
	assetImageName_(assetImageName),
	bMirrored(bMirrored),
	pos(pos),
	scale(scale),
	rotationDegree(rotationDegree), 
	colorMultiplier(colorMultiplier), 
	alphaMultiplier(alphaMultiplier), 
	bVisible(bVisible),
	assetImage_(assetImage)
{
	if (!assetImage_)
		assetImage_ = AssetManager::getInstance().getAssetImageSceneryObject(assetImageName_);
	SceneryObject::errorCheck(true);
}

//defaulted
//SceneryObject::SceneryObject(const SceneryObject& obj) noexcept
//	: name(obj.name), 
//	assetImageName_(obj.assetImageName_), 
//	bMirrored(obj.bMirrored),
//	pos(obj.pos), 
//	scale(obj.scale),
//	rotationDegree(obj.rotationDegree),
//	colorMultiplier(obj.colorMultiplier), 
//	alphaMultiplier(obj.alphaMultiplier),
//	bVisible(obj.bVisible),
//	assetImage_(obj.assetImage_)
//{
//}

bool SceneryObject::operator==(const SceneryObject& obj) const noexcept
{
	if (this == &obj)
		return true;

	return name            == obj.name            &&
		   assetImageName_ == obj.assetImageName_ &&
		   bMirrored       == obj.bMirrored       &&
		   pos             == obj.pos             &&
		   scale           == obj.scale           &&
		   rotationDegree  == obj.rotationDegree  &&
		   colorMultiplier == obj.colorMultiplier &&
		   alphaMultiplier == obj.alphaMultiplier && 
		   bVisible        == obj.bVisible;
}

void SceneryObject::serializableLoad(QDataStream& dataStream)
{
	dataStream >> name >> assetImageName_ >> bMirrored >> pos >> scale >> rotationDegree >> colorMultiplier[0] >> colorMultiplier[1] >> colorMultiplier[2] >> colorMultiplier[3] >> alphaMultiplier >> bVisible;

	if (!assetImageName_.isEmpty())
		assetImage_ = AssetManager::getInstance().getAssetImageSceneryObject(assetImageName_);
	SceneryObject::errorCheck();
}

void SceneryObject::serializableSave(QDataStream& dataStream) const
{
	dataStream << name << assetImageName_ << bMirrored << pos << scale << rotationDegree << colorMultiplier[0] << colorMultiplier[1] << colorMultiplier[2] << colorMultiplier[3] << alphaMultiplier << bVisible;
}

//  MEMBER_FIELD_SECTION_CHANGE END

bool SceneryObject::operator==(const QString& name) const noexcept
{
	return this->name == name;
}

bool SceneryObject::operator!=(const QString& name) const noexcept
{
	return this->name != name;
}

//defaulted
//SceneryObject::SceneryObject(SceneryObject&& obj) noexcept
//	: SceneryObject()
//{
//	swap(*this, obj);
//}

//defaulted
//SceneryObject& SceneryObject::operator=(SceneryObject obj) noexcept
//{
//	if (this == &obj) return *this;
//
//	swap(*this, obj);
//
//	return *this;
//}

QString SceneryObject::getAssetImageName() const noexcept
{
	return assetImageName_;
}

const AssetImage* SceneryObject::getAssetImage() const noexcept
{
	return assetImage_;
}

AssetImage* SceneryObject::getAssetImage() noexcept
{
	return assetImage_;
}

void SceneryObject::setAssetImage(const QString& assetImageName, AssetImage* assetImage) noexcept
{
	if (assetImage)
	{
		if (assetImage->name != assetImageName)
		{
			qCritical() << NovelLib::ErrorType::AssetImageInvalid << "AssetImage's name missmatch (assetImageName=\"" + assetImageName + "\", assetImage->name=\"" + assetImage->name + "\")";
			return;
		}
	}
	else assetImage = AssetManager::getInstance().getAssetImageSceneryObject(assetImageName);

	if (!assetImage)
	{
		qCritical() << NovelLib::ErrorType::AssetImageMissing << "Sprite AssetImage \"" + assetImageName + "\" does not exist";
		return;
	}
	assetImageName_ = assetImageName;
	assetImage_     = assetImage;
	errorCheck(true);
}

void SceneryObject::addAnimator(AnimatorSceneryObjectColor&& animatorColor)
{
	animatorsColor_.push_back(std::move(animatorColor));
	//std::sort(animatorsColor_.begin(), animatorsColor_.end());
	playedAnimatorColorIndex_ = 0;
}

void SceneryObject::addAnimator(AnimatorSceneryObjectFade&& animatorFade)
{
	animatorsFade_.push_back(std::move(animatorFade));
	//std::sort(animatorsFade_.begin(), animatorsFade_.end());
	playedAnimatorFadeIndex_ = 0;
}

void SceneryObject::addAnimator(AnimatorSceneryObjectMove&& animatorMove)
{
	animatorsMove_.push_back(std::move(animatorMove));
	//std::sort(animatorsMove_.begin(), animatorsMove_.end());
	playedAnimatorMoveIndex_ = 0;
}

void SceneryObject::addAnimator(AnimatorSceneryObjectRotate&& animatorRotate)
{
	animatorsRotate_.push_back(std::move(animatorRotate));
	//std::sort(animatorsRotate_.begin(), animatorsRotate_.end());
	playedAnimatorRotateIndex_ = 0;
}

void SceneryObject::addAnimator(AnimatorSceneryObjectScale&& animatorScale)
{
	animatorsScale_.push_back(std::move(animatorScale));
	//std::sort(animatorsScale_.begin(), animatorsScale_.end());
	playedAnimatorScaleIndex_ = 0;
}

void SceneryObject::resetAnimators()
{
	animatorsColor_ .clear();
	animatorsFade_  .clear();
	animatorsMove_  .clear();
	animatorsRotate_.clear();
	animatorsScale_ .clear();
}

QString SceneryObject::getComponentTypeName() const noexcept 
{ 
	return QString("Scenery Object"); 
}

QString SceneryObject::getComponentSubTypeName() const noexcept
{ 
	return QString("Scenery Object");
}

SceneComponentType SceneryObject::getComponentType() const noexcept 
{ 
	return OBJECT; 
}

QString SceneryObject::getComponentName() const noexcept 
{ 
	return name; 
}