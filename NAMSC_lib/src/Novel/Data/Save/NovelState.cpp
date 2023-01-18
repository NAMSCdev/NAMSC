#include "Novel/Data/Novel.h"

#include "Helpers.h"
#include "Novel/Data/Stat/StatDouble.h"
#include "Novel/Data/Stat/StatLongLong.h"
#include "Novel/Data/Stat/StatString.h"
#include "Serialization.h"

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(NovelState& first, NovelState& second) noexcept
{
    using std::swap;
    swap(first.saveDate,   second.saveDate);
    swap(first.screenshot, second.screenshot);
    swap(first.scenery,    second.scenery);
    swap(first.saveSlot,   second.saveSlot);
    swap(first.sceneName,  second.sceneName);
    swap(first.eventID,    second.eventID);
    swap(first.sentenceID, second.sentenceID);
    swap(first.stats_,     second.stats_);
}

NovelState::NovelState(const QDate& saveDate, const QImage& screenshot, uint saveSlot, const QString& sceneName, uint eventID, uint sentenceID)
    : saveDate(saveDate), 
    screenshot(screenshot), 
    scenery(scenery), 
    saveSlot(saveSlot), 
    sceneName(sceneName), 
    eventID(eventID),
    sentenceID(sentenceID)
{
    errorCheck(true);
}

//defaulted
//NovelState::NovelState(const NovelState& obj) noexcept
//        : saveDate(obj.saveDate
//      screenshot(obj.screenshot),
//      scenery(obj.scenery),
//      saveSlot(obj.saveSlot),
//      sceneName(obj.sceneName),
//      eventID(obj.eventID),
//      sentenceID(obj.sentenceID),
//      stats_(obj.stats_)
//{
//}

//defaulted
//bool NovelState::operator==(const NovelState& obj) const noexcept
//{
//    if (this == &obj) return true;
//
//    return saveDate   == obj.saveDate   &&
//           screenshot == obj.screenshot &&
//           scenery    == obj.scenery    &&
//           saveSlot   == obj.saveSlot   &&
//           sceneName  == obj.sceneName  &&
//           eventID    == obj.eventID    &&
//           sentenceID == obj.sentenceID &&
//           stats_     == obj.stats_;
//}

void NovelState::serializableLoad(QDataStream& dataStream)
{
    dataStream >> saveDate >> screenshot >> scenery >> saveSlot >> sceneName >> eventID >> sentenceID;

    uint statsSize = 0;
    dataStream >> statsSize;
    for (uint i = 0; i != statsSize; ++i)
    {
        NovelLib::SerializationID type;
        dataStream >> type;

        Stat* stat = nullptr;
        switch (type)
        {
        case NovelLib::SerializationID::StatDouble:
            stat = new StatDouble();
            break;
        case NovelLib::SerializationID::StatLongLong:
            stat = new StatLongLong();
            break;
        case NovelLib::SerializationID::StatString:
            stat = new StatString();
            break;
        default:
            qCritical() << "Could not find a Stat's type" << static_cast<int>(type) << '!';
            break;
        }
        if (stat)
        {
            dataStream >> *stat;
            stats_.emplace(stat->name, std::move(std::shared_ptr<Stat>(stat)));
        }
    }
    errorCheck();
}

void NovelState::serializableSave(QDataStream& dataStream) const
{
    dataStream << saveDate << screenshot << scenery << saveSlot << sceneName << eventID << sentenceID << static_cast<uint>(stats_.size());

    for (const std::pair<const QString, std::shared_ptr<Stat>>& stat : stats_)
        dataStream << *(stat.second.get());
}

//  MEMBER_FIELD_SECTION_CHANGE END

//defaulted
//NovelState::NovelState(NovelState&& obj) noexcept
//    : NovelState()
//{
//    swap(*this, obj);
//}

//defaulted
//NovelState& NovelState::operator=(NovelState obj) noexcept
//{
//    if (this == &obj) return *this;
//
//    swap(*this, obj);
//
//    return *this;
//}

NovelState* NovelState::getCurrentlyLoadedState()
{
    return &(Novel::getInstance().state_);
}

const std::unordered_map<QString, std::shared_ptr<Stat>>* NovelState::getStats() const noexcept
{
    return &stats_;
}

const Stat* NovelState::getStat(const QString& statName) const
{
    return NovelLib::mapGet(stats_, statName, "Stat", NovelLib::ErrorType::StatMissing)->get();
}

Stat* NovelState::getStat(const QString& statName)
{
    return NovelLib::mapGet(stats_, statName, "Stat", NovelLib::ErrorType::StatMissing)->get();
}

Stat* NovelState::addStat(Stat*&& stat)
{
    return NovelLib::mapSet(stats_, std::move(std::shared_ptr<Stat>(stat)), "Stat", NovelLib::ErrorType::StatInvalid)->get();
}

Stat* NovelState::renameStat(const QString& oldName, const QString& newName)
{
    return NovelLib::mapRename(stats_, oldName, newName, "Stat", NovelLib::ErrorType::StatMissing, NovelLib::ErrorType::StatInvalid)->get();
}

bool NovelState::removeStat(const QString& statName)
{
    return NovelLib::mapRemove(stats_, statName, "Stat", NovelLib::ErrorType::StatMissing);
}

void NovelState::clearStats() noexcept
{
    stats_.clear();
}
