#include "pvnLib/Novel/Data/Save/NovelState.h"
#include "pvnLib/Novel/Data/Stat/Stat.h"

template QDataStream& operator>><NovelState>(QDataStream& dataStream, NovelState& t);
template QDataStream& operator<<<NovelState>(QDataStream& dataStream, const NovelState& t);
template QDataStream& operator>><Stat>(QDataStream& dataStream, Stat& t);
template QDataStream& operator<<<Stat>(QDataStream& dataStream, const Stat& t);