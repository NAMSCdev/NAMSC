#include "Novel/Action/Audio/ActionAudioSetMusic.h"

#include "Novel/Data/Scene.h"

ActionAudioSetMusic::ActionAudioSetMusic(Event* const parentEvent) noexcept
	: ActionAudio(parentEvent)
{
}

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(ActionAudioSetMusic& first, ActionAudioSetMusic& second) noexcept
{
	using std::swap;
	//Static cast, because no check is needed and it's faster
	swap(static_cast<ActionAudio&>(first), static_cast<ActionAudio&>(second));
	swap(first.musicPlaylist_, second.musicPlaylist_);
	swap(first.onRun_,         second.onRun_);
}

ActionAudioSetMusic::ActionAudioSetMusic(Event* const parentEvent, const AudioSettings& audioSettings, const MusicPlaylist& musicPlaylist)
	: ActionAudio(parentEvent, audioSettings),
	 musicPlaylist_(musicPlaylist)
{
	errorCheck(true);
}

ActionAudioSetMusic::ActionAudioSetMusic(const ActionAudioSetMusic& obj) noexcept
	: ActionAudio(obj.parentEvent), 
	musicPlaylist_(obj.musicPlaylist_), 
	onRun_(obj.onRun_)
{
}

//defaulted
bool ActionAudioSetMusic::operator==(const ActionAudioSetMusic& obj) const noexcept
{
	if (this == &obj) return true;

	return ActionAudio::operator==(obj)         &&
		   musicPlaylist_ == obj.musicPlaylist_;
}

void ActionAudioSetMusic::setOnRunListener(std::function<void(const Event* const parentEvent, const MusicPlaylist* const musicPlaylist)> onRun) noexcept
{
	onRun_ = onRun;
}

void ActionAudioSetMusic::serializableLoad(QDataStream& dataStream)
{
	ActionAudio::serializableLoad(dataStream);
	dataStream >> musicPlaylist_;

	errorCheck();
}

void ActionAudioSetMusic::serializableSave(QDataStream& dataStream) const
{
	ActionAudio::serializableSave(dataStream);
	dataStream << musicPlaylist_;
}

//  MEMBER_FIELD_SECTION_CHANGE END

ActionAudioSetMusic::ActionAudioSetMusic(ActionAudioSetMusic&& obj) noexcept
	: ActionAudioSetMusic(obj.parentEvent)
{
	swap(*this, obj);
}

ActionAudioSetMusic& ActionAudioSetMusic::operator=(ActionAudioSetMusic obj) noexcept
{
	if (this == &obj) return *this;

	swap(*this, obj);

	return *this;
}

const MusicPlaylist* ActionAudioSetMusic::getMusicPlaylist() const noexcept
{
	return &musicPlaylist_;
}

MusicPlaylist* ActionAudioSetMusic::getMusicPlaylist() noexcept
{
	return &musicPlaylist_;
}

void ActionAudioSetMusic::setMusicPlaylist(const MusicPlaylist& musicPlaylist) noexcept
{
	musicPlaylist_ = musicPlaylist;
}

void ActionAudioSetMusic::acceptVisitor(ActionVisitor* visitor)
{
	visitor->visitActionAudioSetMusic(this);
}

NovelLib::SerializationID ActionAudioSetMusic::getType() const noexcept
{
	return NovelLib::SerializationID::ActionAudioSetMusic;
}