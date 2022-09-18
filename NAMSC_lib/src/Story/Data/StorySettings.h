#pragma once
#include "Story/Data/Visual/MainMenuTheme.h"

//Global settings for the Story
static struct StorySettings
{
	StorySettings()		= default;

	//TODO: Serialize here
	static void				load				();
	static void				save				();

	//Whether Stats button is available
	static bool				bStatsVisible;		// = true;

	//[optional] Whether every Stat change shows some kind of a notification
	static bool				bStatsNotifications;// = false;

	//Default language that the translations will try to revert to, if the selected one in [language] is not found
	static QString			language;			// = "En";

	//Default language that the translations will try to revert to, if the selected one in [language] is not found
	static QString			defaultLanguage;	// = "En";

	//Last used SaveSlot
	static unsigned			lastSave;			// = 0;

	//Menu custom graphics
	static MainMenuTheme	theme;
}	storySettings;
