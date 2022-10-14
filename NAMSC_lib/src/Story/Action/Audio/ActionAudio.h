#pragma once
#include "Global.h"

#include "Story/Action/Action.h"

///Contains common properties of Actions that manage Audio
class ActionAudio : public Action
{
public:
	///Common properties of Actions that manage Audio
	struct AudioSettings
	{
		AudioSettings() = default;
		AudioSettings(double volume, double stereo, int timesPlayed) : 
			volume(volume), stereo(stereo), timesPlayed(timesPlayed) {}

		///Volume of the played Sound
		double	volume		= 1.0;

		///How the Sound is played in stereo headphones
		///0.0 - left only, 0.5 - both, 1.0 - right only
		///Accepted values: 0.0 - 1.0
		///@todo [optional] Allow more channels
		///[ensure todo] implement this
		double	stereo		= 0.5;

		///How many times it will be played
		///Can be set to -1, so it will be played infinite amount of times
		int		timesPlayed	= 1;
	};

	ActionAudio() = default;
	ActionAudio(Event *parent, unsigned actionID, QString&& label, double volume, double stereo, int timesPlayed) :
		Action(parent, actionID, move(label)), settings(volume, stereo, timesPlayed) {}
	ActionAudio(const ActionAudio& actionAudio)				= default;
	ActionAudio& operator=(const ActionAudio& actionAudio)	= default;
protected:
	///Common properties of Actions that manage Audio
	AudioSettings settings;

	//---SERIALIZATION---
	///Loading an object from a binary file
	virtual void serializableLoad(QDataStream &dataStream) override;
	///Saving an object to a binary file
	virtual void serializableSave(QDataStream &dataStream) const override;
};