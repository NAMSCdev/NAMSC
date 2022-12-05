#include "Novel/Data/Novel.h"

#include <QFile>
#include <QStandardPaths>

#include "Helpers.h"
#include "Novel/Data/Stat/StatDouble.h"
#include "Novel/Data/Stat/StatLongLong.h"
#include "Novel/Data/Stat/StatString.h"

NovelState::NovelState(const QDate& saveDate, const QImage& screenshot, const Scenery& scenery, uint saveSlot, const QString& sceneName, uint eventID)
    : saveDate(saveDate), screenshot(screenshot), scenery(scenery), saveSlot(saveSlot), sceneName(sceneName), eventID(eventID)
{
    checkForErrors(true);
}

NovelState::NovelState(const NovelState& obj) noexcept
    : saveDate(obj.saveDate),
      screenshot(obj.screenshot),
      scenery(obj.scenery),
      saveSlot(obj.saveSlot),
      sceneName(obj.sceneName),
      eventID(obj.eventID)
    //jsEngine_(obj.jsEngine_)
{
}

NovelState& NovelState::operator=(NovelState obj) noexcept
{
    if (this == &obj) return *this;

    std::swap(*this, obj);

    //todo: reset and copy jsEngine properties

    return *this;
}

bool NovelState::operator==(const NovelState& obj) const noexcept
{
    if (this == &obj) return true;

    return  saveDate   == obj.saveDate   &&
            screenshot == obj.screenshot &&
            scenery    == obj.scenery    &&
            saveSlot   == obj.saveSlot   &&
            sceneName  == obj.sceneName  &&
            eventID    == obj.eventID    &&
            stats_     == obj.stats_;

    //todo: Should we check for jsEngine properties match as well? I doesn't quite make sense, since we check the stats for equality, from which properties are created
    //todo: but maybe I have overlooked something, so this todo remains as a reminder to write tests for it
}

bool NovelState::checkForErrors(bool bComprehensive) const
{
    bool bError = false;

    //static auto errorChecker = [&](bool bComprehensive)
    //{
    //};

    bError |= scenery.checkForErrors(bComprehensive);
    
    for (const std::pair<const QString, std::unique_ptr<Stat>>& stat : stats_)
        bError |= stat.second->checkForErrors(bComprehensive);
    //bError |= NovelLib::catchExceptions(errorChecker, bComprehensive); 
    if (bError)
    	qDebug() << "Error occurred in NovelState::checkForErrors in the slot " << saveSlot;

    return bError;
}

void NovelState::update(uint elapsedTime)
{
    scenery.update(elapsedTime);
}

const std::unordered_map<QString, std::unique_ptr<Stat>>* NovelState::getStats() const noexcept
{
    return &stats_;
}

const Stat* NovelState::getStat(const QString& statName) const noexcept
{
    return NovelLib::getFromNamedMap(stats_, statName, "Stat")->get();
}

NovelState* NovelState::getCurrentlyLoadedState()
{
    return &(Novel::getInstance().state_);
}

NovelState NovelState::load(uint saveSlot)
{
    QFile save(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/NAMSC/" + QString::number(saveSlot) + ".sav");
    QDataStream dataStream(&save);
    return NovelState();
}

NovelState NovelState::reset(uint saveSlot)
{
    QFile save(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/NAMSC/" + QString::number(saveSlot) + ".sav");
    QDataStream dataStream(&save);
    return NovelState();
}

void NovelState::save()
{
}

Stat* NovelState::getStat(const QString& statName) noexcept
{
    if (stats_.contains(statName))
        return stats_.at(statName).get();
    return nullptr;
}

void NovelState::setStat(const QString& statName, Stat* stat) noexcept
{
}

bool NovelState::removeStat(const QString& statName) noexcept
{
    return false;
}

void NovelState::loadStats()
{
}

void NovelState::serializableLoad(QDataStream& dataStream)
{
    dataStream >> saveDate >> screenshot >> scenery >> saveSlot >> sceneName >> eventID;

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
            qCritical() << this << "Could not find a Stat's type " << static_cast<int>(type) << '!';
            break;
        }
        dataStream >> *stat;
        stats_.emplace(stat->name, std::move(std::unique_ptr<Stat>(stat)));
    }
    checkForErrors();
}

void NovelState::serializableSave(QDataStream& dataStream) const
{
    dataStream << saveDate << screenshot << scenery << saveSlot << sceneName << eventID << stats_.size();

    for (const std::pair<const QString, std::unique_ptr<Stat>>& stat : stats_)
        dataStream << *(stat.second);
}
