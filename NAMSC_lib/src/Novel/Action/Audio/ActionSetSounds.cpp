#include "Novel/Action/Audio/ActionAudioSetSounds.h"

#include "Novel/Data/Scene.h"

ActionAudioSetSounds::ActionAudioSetSounds(Event* const parentEvent, Scene* const parentScene) noexcept
	: ActionAudio(parentEvent, parentScene)
{
}

ActionAudioSetSounds::ActionAudioSetSounds(Event* const parentEvent, Scene* const parentScene, const AudioSettings& audioSettings, const QHash<QString, Sound>& sounds)
	: ActionAudio(parentEvent, parentScene, audioSettings), sounds(sounds)
{
	checkForErrors(true);
}

ActionAudioSetSounds& ActionAudioSetSounds::operator=(const ActionAudioSetSounds& obj) noexcept
{
	if (this == &obj) return *this;

	ActionAudio::operator=(obj);
	//onRun_ = obj.onRun_;
	sounds = obj.sounds;

	return *this;
}

bool ActionAudioSetSounds::operator==(const ActionAudioSetSounds& obj) const noexcept
{
	if (this == &obj) return true;

	return	ActionAudio::operator==(obj) &&
			sounds == obj.sounds;
}

bool ActionAudioSetSounds::checkForErrors(bool bComprehensive) const
{
	bool bError = ActionAudio::checkForErrors(bComprehensive);

	for (const Sound& sound : sounds)
		bError |= sound.checkForErrors(bComprehensive);

	//static auto errorChecker = [&](bool bComprehensive)
	//{
	//};

	if (bError)
		qDebug() << "An Error occurred in ActionAudioSetSounds::checkForErrors of Scene \"" << parentScene_->name << "\" Event " << parentEvent_->getIndex();

	return bError;
}

void ActionAudioSetSounds::ensureResourcesAreLoaded()
{
	for (Sound& sound : sounds)
		sound.load();
}

void ActionAudioSetSounds::setOnRunListener(std::function<void(Event* const parentEvent, Scene* const parentScene, QHash<QString, Sound>* sound)> onRun) noexcept
{
	onRun_ = onRun;
}

void ActionAudioSetSounds::acceptVisitor(ActionVisitor* visitor)
{
	visitor->visitActionAudioSetSounds(this);
}

NovelLib::SerializationID ActionAudioSetSounds::getType() const noexcept
{
	return NovelLib::SerializationID::ActionAudioSetSounds;
}

void ActionAudioSetSounds::serializableLoad(QDataStream& dataStream)
{
	ActionAudio::serializableLoad(dataStream);
	uint soundsSize;
	dataStream >> soundsSize;
	for (uint i = 0; i != soundsSize; ++i)
	{
		Sound sound;
		dataStream >> sound;
		sounds[sound.name] = std::move(sound);
	}
	checkForErrors();
}

void ActionAudioSetSounds::serializableSave(QDataStream& dataStream) const
{
	ActionAudio::serializableSave(dataStream);
	dataStream << sounds.size();
	for (const Sound& sound : sounds)
		dataStream << sound;
}