#include "pvnLib/Novel/Action/Audio/ActionAudio.h"

#include "pvnLib/Novel/Data/Scene.h"

ActionAudio::~ActionAudio() = default;

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(ActionAudio& first, ActionAudio& second) noexcept
{
	using std::swap;
	//Static cast, because no check is needed and it's faster
	swap(static_cast<Action&>(first), static_cast<Action&>(second));
	swap(first.audioSettings_, second.audioSettings_);
}

ActionAudio::ActionAudio(Event* const parentEvent, const AudioSettings& audioSettings)
	: Action(parentEvent), 
	audioSettings_(audioSettings)
{
}

bool ActionAudio::operator==(const ActionAudio& obj) const noexcept
{
	if (this == &obj) return true;

	return audioSettings_ == obj.audioSettings_;
}

void ActionAudio::serializableLoad(QDataStream& dataStream)
{
	Action::serializableLoad(dataStream);
	dataStream >> audioSettings_;
}

void ActionAudio::serializableSave(QDataStream& dataStream) const
{
	Action::serializableSave(dataStream);
	dataStream << audioSettings_;
}

//  MEMBER_FIELD_SECTION_CHANGE END

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
	errorCheck(true);
}