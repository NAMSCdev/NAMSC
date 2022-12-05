#include "Novel/Data/NovelSettings.h"

#include "Novel/Data/Novel.h"
#include "Novel/Event/EventDialogue.h"
#include "Serialization.h"

void NovelSettings::load()
{
}

NovelSettings& NovelSettings::getInstance()
{
    static NovelSettings instance;
    return instance;
}

NovelSettings::NovelSettings(const QString& novelTitle, const QString& language, const QString& defaultLanguage, uint lastSaveSlot, uint cps, double volumeMusicMultiplier, double volumeSoundMultiplier, double volumeVoiceMultiplier, const Qt::Key nextButton, bool mouseClick, uint animationFramerate, bool bLazyFileLoad, uint version, const AvailableResolutions resoultion)
{
}

void NovelSettings::defaultLanguageChange(const QString& newDefaultLanguage)
{
    const QString oldDefaultLanguage = defaultLanguage;
    defaultLanguage = newDefaultLanguage;
    for (std::pair < const QString, Scene>& scene : Novel::getInstance().scenes_)
        for (std::unique_ptr<Event>& event : scene.second.events_)
        {
            EventDialogue* eventDialog = dynamic_cast<EventDialogue*>(event.get());
            if (eventDialog)
                for (Sentence& sentence : eventDialog->sentences)
                    sentence.text.defaultLanguageChangeFix(oldDefaultLanguage);
        }
}

void NovelSettings::serializableLoad(QDataStream& dataStream)
{
    dataStream >> novelTitle >> language >> defaultLanguage >> lastSaveSlot >> cps >> volumeMusicMultiplier >> volumeSoundMultiplier >> volumeVoiceMultiplier >> nextButton >> mouseClick >> animationUpdateInterval >> bStatsVisible >> bStatsNotification >> bLazyFileLoad >> version >> resolution;
}

void NovelSettings::serializableSave(QDataStream& dataStream) const
{
    dataStream << novelTitle << language << defaultLanguage << lastSaveSlot << cps << volumeMusicMultiplier << volumeSoundMultiplier << volumeVoiceMultiplier << nextButton << mouseClick << animationUpdateInterval << bStatsVisible << bStatsNotification << bLazyFileLoad << version << resolution;
}