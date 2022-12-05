#include "Novel/Action/Audio/ActionAudio.h"

#include "Novel/Data/Scene.h"

ActionAudio::ActionAudio(Event* const parentEvent, Scene* const parentScene) noexcept
	: Action(parentEvent, parentScene)
{
}

ActionAudio::ActionAudio(Event* const parentEvent, Scene* const parentScene, const AudioSettings& audioSettings)
	: Action(parentEvent, parentScene), audioSettings_(audioSettings)
{
	//checkForErrors(true);
}

ActionAudio& ActionAudio::operator=(const ActionAudio& obj) noexcept
{
	if (this == &obj) return *this;

	Action::operator=(obj);
	audioSettings_ = obj.audioSettings_;

	return *this;
}

bool ActionAudio::operator==(const ActionAudio& obj) const noexcept
{
	if (this == &obj) return true;

	return	Action::operator==(obj)             &&
			audioSettings_ == obj.audioSettings_;
}

bool ActionAudio::checkForErrors(bool bComprehensive) const
{
	bool bError = Action::checkForErrors(bComprehensive);

	//static auto errorChecker = [&](bool bComprehensive)
	//{
	//};

	//Only leafs should report, but if needed for further debug, uncomment it
	//bError |= NovelLib::catchExceptions(errorChecker, bComprehensive))
	//if (bError)
	//	qDebug() << "Error occurred in ActionAudio::checkForErrors of Scene \"" << parentScene_->name << "\" Event " << parentEvent_->getIndex();
	return bError;
}

const AudioSettings& ActionAudio::getAudioSettings() const noexcept
{
	return audioSettings_;
}

AudioSettings& ActionAudio::getAudioSettings() noexcept
{
	return audioSettings_; 
}

void ActionAudio::setAudioSettings(const AudioSettings& audioSettings) noexcept
{
	audioSettings_ = audioSettings;
	checkForErrors(true);
}

void ActionAudio::serializableLoad(QDataStream& dataStream)
{
	Action::serializableLoad(dataStream);
	dataStream >> audioSettings_;

	//checkForErrors();
}

void ActionAudio::serializableSave(QDataStream& dataStream) const
{
	Action::serializableSave(dataStream);
	dataStream << audioSettings_;
}
