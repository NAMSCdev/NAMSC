#pragma once
#include "Global.h"

#include "Novel/Action/Action.h"

#include "Novel/Data/Audio/AudioSettings.h"

///Contains common properties of Actions that manage Audio
class ActionAudio : public Action
{
public:
	ActionAudio() = default;
	ActionAudio(AudioSettings settings);
	ActionAudio(double volume, double stereo, int timesPlayed, uint delayBetweenReplays);
	ActionAudio(const ActionAudio& obj) { *this = obj; }
	ActionAudio& operator=(const ActionAudio& obj);

protected:
	///Common properties of Actions that manage Audio
	AudioSettings settings;

	//---SERIALIZATION---
	///Loading an object from a binary file
	virtual void serializableLoad(QDataStream &dataStream) override;
	///Saving an object to a binary file
	virtual void serializableSave(QDataStream &dataStream) const override;
};




inline ActionAudio::ActionAudio(AudioSettings settings) :
	Action(), settings(settings)
{
}

inline ActionAudio::ActionAudio(double volume, double stereo, int timesPlayed, uint delayBetweenReplays) :
	Action(), settings(volume, stereo, timesPlayed, delayBetweenReplays)
{
}

inline ActionAudio& ActionAudio::operator=(const ActionAudio& obj)
{
	if (this == &obj) return *this;

	Action::operator=(obj);
	settings = obj.settings;

	return *this;
}