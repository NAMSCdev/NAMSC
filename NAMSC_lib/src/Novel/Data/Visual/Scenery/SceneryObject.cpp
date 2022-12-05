#include "Novel/Data/Visual/Scenery/SceneryObject.h"

SceneryObject::SceneryObject(const QString& name, const QString& assetImageName, const QPoint pos, const QSize scale, double rotationDegree, const QVarLengthArray<double, 4>& colorMultiplier, double alphaMultiplier, bool bVisible)
	: name(name), assetImageName_(assetImageName), pos(pos), scale(scale), rotationDegree(rotationDegree), colorMultiplier(colorMultiplier), alphaMultiplier(alphaMultiplier), bVisible(bVisible)
{
	assetImage_ = AssetManager::getInstance().getAssetImageSceneryObject(assetImageName_);
	SceneryObject::checkForErrors(true);
}

SceneryObject::SceneryObject(const SceneryObject& obj) noexcept
	: name(obj.name), 
	  assetImageName_(obj.assetImageName_), 
	  pos(obj.pos), 
	  scale(obj.scale),
	  rotationDegree(obj.rotationDegree),
	  colorMultiplier(obj.colorMultiplier), 
	  alphaMultiplier(obj.alphaMultiplier),
	  bVisible(obj.bVisible)
{
}


SceneryObject& SceneryObject::operator=(SceneryObject obj) noexcept
{ 
	if (this == &obj) return *this;

	std::swap(*this, obj); 
	
	return *this; 
}

bool SceneryObject::operator==(const SceneryObject& obj) const noexcept
{
	if (this == &obj)
		return true;

	return  name            == obj.name            &&
			assetImageName_ == obj.assetImageName_ &&
			pos             == obj.pos             &&
			scale           == obj.scale           &&
			rotationDegree  == obj.rotationDegree  &&
			colorMultiplier == obj.colorMultiplier &&
			alphaMultiplier == obj.alphaMultiplier && 
			bVisible        == obj.bVisible;
}

bool SceneryObject::checkForErrors(bool bComprehensive) const
{
	bool bError = false;

	static auto errorChecker = [&](bool bComprehensive)
	{
		if (assetImage_ == nullptr)
		{
			bError = true;
			qCritical() << this << NovelLib::ErrorType::AssetImageInvalid << "No valid Sprite AssetImage assigned. Was it deleted and not replaced?";
			if (assetImageName_ == "")
				qCritical() << this << NovelLib::ErrorType::AssetImageMissing << "Sprite AssetImage \"" << assetImageName_ << "\" does not exist. Definition file might be corrupted";
		}
		else
			bError |= assetImage_->checkForErrors(bComprehensive);
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	if (bError)
		qDebug() << "Error occurred in SceneryObject::checkForErrors (object's name: \"" << name << ")\"";

	return bError;
}

void SceneryObject::run()
{
	for (AnimatorSceneryObjectColor& animator : animatorsColor_)
		animator.run();

	for (AnimatorSceneryObjectFade& animator : animatorsFade_)
		animator.run();

	for (AnimatorSceneryObjectRotate& animator : animatorsRotate_)
		animator.run();

	for (AnimatorSceneryObjectMove& animator : animatorsMove_)
		animator.run();

	for (AnimatorSceneryObjectScale& animator : animatorsScale_)
		animator.run();
}

void SceneryObject::update(uint elapsedTime)
{
	if (playedAnimatorColorIndex_ != -1)
		if (animatorsColor_[playedAnimatorColorIndex_].update(elapsedTime))
			if (++playedAnimatorColorIndex_ > animatorsColor_.size())
				playedAnimatorColorIndex_ = -1;

	if (playedAnimatorFadeIndex_ != -1)
		if (animatorsFade_[playedAnimatorFadeIndex_].update(elapsedTime))
			if (++playedAnimatorFadeIndex_ > animatorsFade_.size())
				playedAnimatorFadeIndex_ = -1;

	if (playedAnimatorMoveIndex_ != -1)
		if (animatorsMove_[playedAnimatorMoveIndex_].update(elapsedTime))
			if (++playedAnimatorMoveIndex_ > animatorsMove_.size())
				playedAnimatorMoveIndex_ = -1;

	if (playedAnimatorRotateIndex_ != -1)
		if (animatorsRotate_[playedAnimatorRotateIndex_].update(elapsedTime))
			if (++playedAnimatorRotateIndex_ > animatorsRotate_.size())
				playedAnimatorRotateIndex_ = -1;

	if (playedAnimatorScaleIndex_ != -1)
		if (animatorsScale_[playedAnimatorScaleIndex_].update(elapsedTime))
			if (++playedAnimatorScaleIndex_ > animatorsScale_.size())
				playedAnimatorScaleIndex_ = -1;
}

void SceneryObject::setAssetImage(const QString& assetImageName, AssetImage* assetImage) noexcept
{
	if (assetImage != nullptr)
	{
		assetImageName_ = assetImageName;
		assetImage_     = assetImage;
		checkForErrors(true);
		return;
	}

	AssetImage* newAssetImage = nullptr;
	newAssetImage = AssetManager::getInstance().getAssetImageSceneryObject(assetImageName);
	if (newAssetImage == nullptr)
		qCritical() << this << NovelLib::ErrorType::AssetImageMissing << "AssetImage \"" << assetImageName << "\" does not exist";
	else
	{
		assetImageName_ = assetImageName;
		assetImage_     = newAssetImage;
		checkForErrors(true);
	}
}

const AssetImage* SceneryObject::getAssetImage() const noexcept
{
	return assetImage_;
}

AssetImage* SceneryObject::getAssetImage() noexcept
{
	return assetImage_;
}

QString SceneryObject::getAssetImageName() noexcept
{
	return assetImageName_;
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
	animatorsColor_.clear();
	animatorsFade_.clear();
	animatorsMove_.clear();
	animatorsRotate_.clear();
	animatorsScale_.clear();
}

/// \exception Error Couldn't load the `assetImage_`
void SceneryObject::ensureResourcesAreLoaded()
{
	if (assetImage_ && !assetImage_->isLoaded())
		assetImage_->load();
}

void SceneryObject::serializableLoad(QDataStream& dataStream)
{
	dataStream >> name >> assetImageName_ >> pos >> scale >> rotationDegree >> colorMultiplier[0] >> colorMultiplier[1] >> colorMultiplier[2] >> colorMultiplier[3] >> alphaMultiplier >> bVisible;

	assetImage_ = AssetManager::getInstance().getAssetImageSceneryObject(assetImageName_);
	SceneryObject::checkForErrors();
}

void SceneryObject::serializableSave(QDataStream& dataStream) const
{
	dataStream << name << assetImageName_ << pos << scale << rotationDegree << colorMultiplier[0] << colorMultiplier[1] << colorMultiplier[2] << colorMultiplier[3] << alphaMultiplier << bVisible;
}