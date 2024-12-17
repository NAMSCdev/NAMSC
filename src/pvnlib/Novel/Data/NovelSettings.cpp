#include "pvnLib/Novel/Data/NovelSettings.h"

#include "pvnLib/Novel/Data/Novel.h"
#include "pvnLib/Novel/Event/EventDialogue.h"
#include "pvnLib/Serialization.h"

NovelSettings& NovelSettings::getInstance()
{
    static NovelSettings instance;
    return instance;
}

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

NovelSettings::NovelSettings(const QString& language, const QString& defaultLanguage, uint lastSaveSlot, uint cps, double volumeMusicMultiplier, double volumeSoundMultiplier, double volumeVoiceMultiplier, const Qt::Key nextButton, bool mouseClick, bool bStatsVisible, bool bStatsNotification, bool bLazyFileLoad, const AvailableResolutions resoultion)
{
}

void NovelSettings::serializableLoad(QDataStream& dataStream)
{
    dataStream >> language >> defaultLanguage >> lastSaveSlot >> cps >> volumeMusicMultiplier >> volumeSoundMultiplier >> volumeVoiceMultiplier >> nextButton >> mouseClick >> bStatsVisible >> bStatsNotification >> bLazyFileLoad >> resolution;
}

void NovelSettings::serializableSave(QDataStream& dataStream) const
{
    dataStream << language << defaultLanguage << lastSaveSlot << cps << volumeMusicMultiplier << volumeSoundMultiplier << volumeVoiceMultiplier << nextButton << mouseClick << bStatsVisible << bStatsNotification << bLazyFileLoad << resolution;
}

//  MEMBER_FIELD_SECTION_CHANGE END

void NovelSettings::defaultLanguageChange(const QString& newDefaultLanguage)
{
    const QString oldDefaultLanguage = defaultLanguage;
    defaultLanguage = newDefaultLanguage;
    for (std::pair<const QString, Scene>& scene : Novel::getInstance().scenes_)
        for (std::shared_ptr<Event>& event : scene.second.events_)
        {
            EventDialogue* eventDialog = dynamic_cast<EventDialogue*>(event.get());
            if (eventDialog)
                for (Sentence& sentence : eventDialog->sentences_)
                    sentence.translation.defaultLanguageChangeFix(oldDefaultLanguage);
        }
}