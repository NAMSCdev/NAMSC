#include "Novel/Action/Audio/ActionAudioSetSounds.h"

#include "Novel/Data/Scene.h"

ActionAudioSetSounds::ActionAudioSetSounds(Event* const parentEvent) noexcept
	: ActionAudio(parentEvent)
{
}

ActionAudioSetSounds::ActionAudioSetSounds(Event* const parentEvent, const AudioSettings& audioSettings, const std::unordered_map<QString, Sound>& sounds)
	: ActionAudio(parentEvent, audioSettings), sounds(sounds)
{
	checkForErrors(true);
}

ActionAudioSetSounds::ActionAudioSetSounds(const ActionAudioSetSounds& obj) noexcept
	: ActionAudio(obj.parentEvent)
{
	//TODO: change to swap trick for more efficency
	*this = obj;
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

	for (const std::pair<const QString, Sound>& sound : sounds)
		bError |= sound.second.checkForErrors(bComprehensive);

	//static auto errorChecker = [&](bool bComprehensive)
	//{
	//};

	if (bError)
		qDebug() << "An Error occurred in ActionAudioSetSounds::checkForErrors of Scene \"" + parentEvent->parentScene->name + "\" Event" << parentEvent->getIndex();

	return bError;
}

Action* ActionAudioSetSounds::clone() const
{
	ActionAudioSetSounds* clone = new ActionAudioSetSounds(*this);
	return clone;
}

void ActionAudioSetSounds::ensureResourcesAreLoaded()
{
	for (std::pair<const QString, Sound>& sound : sounds)
		sound.second.load();
}

void ActionAudioSetSounds::setOnRunListener(std::function<void(Event* const parentEvent, std::unordered_map<QString, Sound>* sound)> onRun) noexcept
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
	for (const std::pair<const QString, Sound>& sound : sounds)
		dataStream << sound.second;
}