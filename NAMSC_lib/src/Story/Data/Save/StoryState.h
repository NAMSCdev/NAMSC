#pragma once
#include "Global.h"

#include "Story/Data/Stat/Stat.h"

//Contains data about Story progression and choices made, which affect Stats
struct StoryState
{
public:
    Stat* getStat(const QString &name)      { return std::find(stats.begin(), stats.end(), name)->get(); }

    //At which saveslot this state will be saved/loaded
    unsigned                saveSlot        = 0;

   	//Event execution order position with sceneID identifies the Event
    //precisely and all Actions are contained within Events
    unsigned                sceneID         = 0,
                            executionOrder  = 0;

    //All the Stats retrievable by getStat
    std::vector<uPtr<Stat>> stats;
};
