#include "pvnLib/Novel/Action/Audio/ActionAudioSetSounds.h"

#include "pvnLib/Novel/Data/Scene.h"
#include "pvnLib/Helpers.h"

ActionAudioSetSounds::ActionAudioSetSounds(Event* const parentEvent) noexcept
	: ActionAudio(parentEvent)
{
}

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(ActionAudioSetSounds& first, ActionAudioSetSounds& second) noexcept
{
	using std::swap;
	//Static cast, because no check is needed and it's faster
	swap(dynamic_cast<ActionAudio&>(first), dynamic_cast<ActionAudio&>(second));
	swap(first.sounds_, second.sounds_);
	swap(first.onRun_,  second.onRun_);
}

ActionAudioSetSounds::ActionAudioSetSounds(Event* const parentEvent, const AudioSettings& audioSettings, const std::vector<Sound>& sounds)
	: ActionAudio(parentEvent, audioSettings),
	sounds_(sounds)
{
	errorCheck(true);
}

ActionAudioSetSounds::ActionAudioSetSounds(const ActionAudioSetSounds& obj) noexcept
	: ActionAudio(obj.parentEvent, obj.audioSettings_), 
	sounds_(obj.sounds_), 
	onRun_(obj.onRun_)
{
}

bool ActionAudioSetSounds::operator==(const ActionAudioSetSounds& obj) const noexcept
{
	if (this == &obj) return true;

	return ActionAudio::operator==(obj) &&
		   sounds_ == obj.sounds_;
}

void ActionAudioSetSounds::setOnRunListener(std::function<void(const Event* const parentEvent, const std::vector<Sound>* const sounds)> onRun) noexcept
{
	onRun_ = onRun;
}

void ActionAudioSetSounds::serializableLoad(QDataStream& dataStream)
{
	ActionAudio::serializableLoad(dataStream);

	uint soundsSize;
	dataStream >> soundsSize;
	for (uint i = 0u; i != soundsSize; ++i)
	{
		Sound sound;
		dataStream >> sound;
		addSound(std::move(sound));
	}
	errorCheck();
}

void ActionAudioSetSounds::serializableSave(QDataStream& dataStream) const
{
	ActionAudio::serializableSave(dataStream);

	dataStream << static_cast<uint>(sounds_.size());
	for (const Sound& sound : sounds_)
		dataStream << sound;
}

//  MEMBER_FIELD_SECTION_CHANGE END

ActionAudioSetSounds::ActionAudioSetSounds(ActionAudioSetSounds&& obj) noexcept
	: ActionAudio(obj.parentEvent)
{
	swap(*this, obj);
}

ActionAudioSetSounds& ActionAudioSetSounds::operator=(ActionAudioSetSounds obj) noexcept
{
	if (this == &obj) return *this;

	swap(*this, obj);

	return *this;
}

const std::vector<Sound>* ActionAudioSetSounds::getSounds() const noexcept
{
	return &sounds_;
}

const Sound* ActionAudioSetSounds::getSound(uint index) const
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listGet(sounds_, index, "Sound", NovelLib::ErrorType::SoundMissing, "Event (ActionAudioSetSounds)", QString::number(parentEvent->getIndex()), "Scene", parentEvent->parentScene->name));
}

Sound* ActionAudioSetSounds::getSound(uint index)
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listGet(sounds_, index, "Sound", NovelLib::ErrorType::SoundMissing, "Event (ActionAudioSetSounds)", QString::number(parentEvent->getIndex()), "Scene", parentEvent->parentScene->name));
}

const Sound* ActionAudioSetSounds::getSound(const QString& soundName) const
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listGet(sounds_, soundName, "Sound", NovelLib::ErrorType::SoundMissing, "Event (ActionAudioSetSounds)", QString::number(parentEvent->getIndex()), "Scene", parentEvent->parentScene->name));
}

Sound* ActionAudioSetSounds::getSound(const QString& soundName)
{
	return NovelLib::Helpers::itToPtr((std::vector<Sound>::iterator)NovelLib::Helpers::listGet(sounds_, soundName, "Sound", NovelLib::ErrorType::SoundMissing, "Event (ActionAudioSetSounds)", QString::number(parentEvent->getIndex()), "Scene", parentEvent->parentScene->name));
}

const std::vector<Sound>* ActionAudioSetSounds::setSounds(const std::vector<Sound>& sounds) noexcept
{
	return &(sounds_ = sounds);
}

const std::vector<Sound>* ActionAudioSetSounds::setSounds(std::vector<Sound>&& sounds) noexcept
{
	return &(sounds = std::move(sounds));
}

Sound* ActionAudioSetSounds::addSound(const Sound& sound)
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listAdd(sounds_, sound, "Sound", NovelLib::ErrorType::SoundInvalid, "Event (ActionAudioSetSounds)", QString::number(parentEvent->getIndex()), "Scene", parentEvent->parentScene->name));
}

Sound* ActionAudioSetSounds::addSound(Sound&& sound)
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listAdd(sounds_, std::move(sound), "Sound", NovelLib::ErrorType::SoundInvalid, "Event (ActionAudioSetSounds)", QString::number(parentEvent->getIndex()), "Scene", parentEvent->parentScene->name));
}

bool ActionAudioSetSounds::removeSound(const QString& soundName)
{
	return NovelLib::Helpers::listRemove(sounds_, soundName, "Sound", NovelLib::ErrorType::SoundMissing, "Event (ActionAudioSetSounds)", QString::number(parentEvent->getIndex()), "Scene", parentEvent->parentScene->name);
}

bool ActionAudioSetSounds::removeSound(uint index)
{
	return NovelLib::Helpers::listRemove(sounds_, index, "Sound", NovelLib::ErrorType::SoundMissing, "Event (ActionAudioSetSounds)", QString::number(parentEvent->getIndex()), "Scene", parentEvent->parentScene->name);
}

void ActionAudioSetSounds::clearSounds() noexcept
{
	sounds_.clear();
}

void ActionAudioSetSounds::acceptVisitor(ActionVisitor* visitor)
{
	visitor->visitActionAudioSetSounds(this);
}

NovelLib::SerializationID ActionAudioSetSounds::getType() const noexcept
{
	return NovelLib::SerializationID::ActionAudioSetSounds;
}