#pragma once
#include "Global.h"

#include "Story/Action/Action.h"
#include "Story/Data/Audio/AudioSettings.h"

///Contains common properties of Actions that manage Audio
class ActionAudio : public Action
{
public:
	ActionAudio() = default;
	ActionAudio(unsigned actionID, double volume, double stereo, int timesPlayed, QString &&label) :
		Action(actionID, move(label)), settings(timesPlayed, stereo, volume) {}
	ActionAudio(const ActionAudio& obj) { *this = obj; }
	ActionAudio& operator=(const ActionAudio& obj)
	{
		if (this == &obj) return *this;

		Action::operator=(obj);
		settings = obj.settings;

		return *this;
	}

protected:
	///Common properties of Actions that manage Audio
	AudioSettings settings;

	//---SERIALIZATION---
	///Loading an object from a binary file
	virtual void serializableLoad(QDataStream &dataStream) override;
	///Saving an object to a binary file
	virtual void serializableSave(QDataStream &dataStream) const override;
};