#pragma once
#include "Story/Data/Visual/MainMenuTheme.h"

///Global settings for the Story
static struct StorySettings
{
	StorySettings()		= delete;

	///TODO: Serialize here
	static void	load();
	static void	save();

	///Whether Stats button is available
	static bool		bStatsVisible;		/// = true;

	///[optional] Whether every Stat change shows some kind of a notification
	static bool		bStatsNotifications;/// = false;

	///Default language that the translations will try to revert to, if the selected one in [language] is not found
	static QString			language;			/// = "En";

	///Default language that the translations will try to revert to, if the selected one in [language] is not found
	static QString			defaultLanguage;	/// = "En";

	///Last used SaveSlot
	static unsigned			lastSave;			/// = 0;

	///Button that can be pressed to navigate to the next Event
	static Qt::Key			nextButton;			/// = Qt::RightArrow;
	
	///Whether *left mouse button* can be used to navigate to the next Event
	static bool		mouseClick;			/// = true

	///Version of the Story engine that it was written in (matters when loading a newer/older save)
	static unsigned			version;

	///Menu custom graphics
	static MainMenuTheme	theme;

	///All supported ???
	///@todo decide whether its predefined aspect ratio or resolutions.
	///@todo fill the enum
	//enum class AspectRatio
	//{
		
	//};
};
