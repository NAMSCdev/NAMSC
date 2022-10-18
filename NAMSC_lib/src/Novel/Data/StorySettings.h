#pragma once
#include "Novel/Data/Visual/MainMenuTheme.h"

///Global settings for the Novel
class NovelSettings
{    //Friends for serialization
    friend QDataStream& operator>>(QDataStream&, NovelSettings&);
    friend QDataStream& operator<<(QDataStream&, const NovelSettings&);
public:
    static NovelSettings& getInstance()
    {
        static NovelSettings instance;
        return instance;
    };
    NovelSettings() = default;
    NovelSettings(NovelSettings const&)	    = delete;
    void operator=(NovelSettings const&)    = delete;

	///Whether Stats button is available
	bool    bStatsVisible       = true;

	///[optional] Whether every Stat change shows some kind of a notification
	bool    bStatsNotification  = false;

	///Default language that the translations will try to revert to, if the selected one in [language] is not found
	QString	language            = "En";

	///Default language that the translations will try to revert to, if the selected one in [language] is not found
	QString	defaultLanguage     = "En";

	///Last used SaveSlot
	uint lastSave           = 0;

	///Button that can be pressed to navigate to the next Event
	Qt::Key	nextButton          = Qt::Key::Key_Right;
	
	///Whether **left mouse button** can be used to navigate to the next Event
	bool	mouseClick          = true;

	///Version of the Novel engine that it was written in (matters when loading a newer/older save)
	uint version            = 0;

    ///How often the Animator keeps updating its Animation
    ///0 stands for minimal update time (very bad for performance)
    uint animationFramerate = 0;

	//[optional]Menu custom graphics
	//MainMenuTheme theme;

    ///List of available resolutions for the story
    ///@todo [optional] Make it custom defined
    enum class AvailableResolutions
    {
        r_800x600
    } resolution = AvailableResolutions::r_800x600;

    ///Changes the default language and forces severy AssetText to copy the text from previous one, if there is no translation in the new default language
    ///@todo iplement this
    void defaultLanguageChange(const QString &newLanguage)
    {
    }

private:
    //---SERIALIZATION---
    ///Loading an object from a binary file
    void serializableLoad(QDataStream &dataStream)
    {
        dataStream  >> bStatsVisible >> bStatsNotification >> language >> defaultLanguage 
                    >> lastSave >> nextButton >> mouseClick >> version /* >> theme*/ >> resolution;
    }
    ///Saving an object to a binary file
    void serializableSave(QDataStream &dataStream) const
    {
        dataStream  << bStatsVisible << bStatsNotification << language << defaultLanguage 
                    << lastSave << nextButton << mouseClick << version /* << theme*/ << resolution;
    }

};
