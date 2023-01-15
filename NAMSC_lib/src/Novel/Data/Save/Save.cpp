#include <QDir>

#include "Novel/Data/Novel.h"

#include <QFile>
#include <QStandardPaths>

bool NovelState::errorCheck(bool bComprehensive) const
{
    bool bError = false;

    //static auto errorChecker = [this](bool bComprehensive)
    //{
    //};

    bError |= scenery.errorCheck(bComprehensive);

    for (const std::pair<const QString, std::shared_ptr<Stat>>& stat : stats_)
        bError |= stat.second->errorCheck(bComprehensive);
    //bError |= NovelLib::catchExceptions(errorChecker, bComprehensive); 
    if (bError)
        qDebug() << "Error occurred in NovelState::errorCheck in the slot" << saveSlot;

    return bError;
}


NovelState NovelState::load(uint saveSlot)
{
    QFile save(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/NAMSC/" + QString::number(saveSlot) + ".sav");
    save.open(QIODeviceBase::ReadOnly);
    QDataStream dataStream(&save);
    NovelState novelState;
    dataStream >> novelState;
    return novelState;
}

NovelState NovelState::reset(uint saveSlot)
{
    QFile save(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/NAMSC/" + QString::number(saveSlot) + ".sav");
    QDataStream dataStream(&save);
    NovelState novelState;
    novelState.saveSlot = saveSlot;
    novelState.sceneName = Novel::getInstance().defaultScene;
    return novelState;
}

void NovelState::save()
{
    NovelState& novelState = Novel::getInstance().state_;
    QDir(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)).mkpath("NAMSC");
    QFile save(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/NAMSC/" + QString::number(saveSlot) + ".sav");
    save.open(QIODeviceBase::WriteOnly);
    QDataStream dataStream(&save);
    dataStream << novelState;
}

void NovelState::update(uint elapsedTime)
{
    scenery.update(elapsedTime);
}

void NovelState::loadStats()
{
}