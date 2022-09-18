#pragma once
#include "Global.h"

#include "Story/Action/ActionVisitor.h"

#include "Story/Action/Sound/ActionChangeMusic.h"
#include "Story/Action/Sound/ActionPlaySound.h"

#include "Story/Action/Stat/ActionStatVisibility.h"
#include "Story/Action/Stat/ActionStatChange.h"

#include "Story/Action/Visual/Effect/Type/ActionEffectBlur.h"
#include "Story/Action/Visual/Effect/Type/ActionEffectDistort.h"
#include "Story/Action/Visual/Effect/Type/ActionEffectGlow.h"

#include "Story/Action/Visual/Filter/Type/ActionFilterBlur.h"
#include "Story/Action/Visual/Filter/Type/ActionFilterBrightness.h"
#include "Story/Action/Visual/Filter/Type/ActionFilterDilation.h"
#include "Story/Action/Visual/Filter/Type/ActionFilterErosion.h"
#include "Story/Action/Visual/Filter/Type/ActionFilterHue.h"
#include "Story/Action/Visual/Filter/Type/ActionFilterNegative.h"
#include "Story/Action/Visual/Filter/Type/ActionFilterSaturation.h"

#include "Story/Action/Visual/Scenery/Animation/ActionCharLive2DAnim.h"
#include "Story/Action/Visual/Scenery/Animation/ActionSceneryObjectAppearance.h"
#include "Story/Action/Visual/Scenery/ActionSceneryChange.h"
#include "Story/Action/Visual/Scenery/ActionSceneryObjectChange.h"

//Decrements or increments IDs between [minID] and [pivotID] or after it based
class ActionVisitorChangeID final : public ActionVisitor
{
public:
	ActionVisitorChangeID(unsigned pivotID, bool bIncrement = false, int minID = -1)
		: pivotID(pivotID), bIncrement(bIncrement), minID(minID) {}

	static ActionVisitorChangeID createRemoveVisit	(unsigned removedID)									{ return ActionVisitorChangeID(removedID,	false, -1);		}
	static ActionVisitorChangeID createShuffleVisit	(unsigned oldID, unsigned newID)						{ return ActionVisitorChangeID(newID,		true,	oldID); }

	void		visitActionChangeMusic				(ActionChangeMusic					*action) override	{ changeID(action); }
	void		visitActionPlaySound				(ActionPlaySound					*action) override	{ changeID(action); }
	
	void		visitActionStatChange				(ActionStatChange					*action) override	{ changeID(action); }

	void		visitActionSceneryChange			(ActionSceneryChange				*action) override	{ changeID(action); }
	void		visitActionSceneryObjectChange		(ActionSceneryObjectChange			*action) override	{ changeID(action); }
	void		visitActionSceneryObjectAppearance	(ActionSceneryObjectAppearance		*action) override	{ changeID(action); }
	
	//[optional]		
	void		visitActionStatVisibility			(ActionStatVisibility				*action) override	{ changeID(action); }

	void		visitActionEffectBlur				(ActionEffectBlur					*action) override	{ changeID(action); }
	void		visitActionEffectDistort			(ActionEffectDistort				*action) override	{ changeID(action); }
	void		visitActionEffectGlow				(ActionEffectGlow					*action) override	{ changeID(action); }
	
	void		visitActionFilterBlur				(ActionFilterBlur					*action) override	{ changeID(action); }
	void		visitActionFilterBrightness			(ActionFilterBrightness				*action) override	{ changeID(action); }
	void		visitActionFilterDilation			(ActionFilterDilation				*action) override	{ changeID(action); }
	void		visitActionFilterErosion			(ActionFilterErosion				*action) override	{ changeID(action); }
	void		visitActionFilterHue				(ActionFilterHue					*action) override	{ changeID(action); }
	void		visitActionFilterNegative			(ActionFilterNegative				*action) override	{ changeID(action); }
	void		visitActionFilterSaturation			(ActionFilterSaturation				*action) override	{ changeID(action); }

	void		visitActionCharLive2DAnim			(ActionCharLive2DAnim				*action) override	{ changeID(action); }

protected:
	//Changes IDs
	void		changeID							(Action								*action)			
	{ 
		if (minID != -1)
		{
			if (minID >= action->actionID & &action->actionID < pivotID)
				bIncrement ? ++action->actionID : --action->actionID;
		}
		else if (pivotID > action->actionID) 
			bIncrement ? ++action->actionID : --action->actionID; 
	}

	//Minimal ID that will be affected, if -1 it means we edit IDs after [pivotID], not before it
	int			minID																						= -1;

	//ID after which the change will happen
	unsigned	pivotID;

	//Whether we will increment or decrement IDs
	bool		bIncrement																					= false;
};