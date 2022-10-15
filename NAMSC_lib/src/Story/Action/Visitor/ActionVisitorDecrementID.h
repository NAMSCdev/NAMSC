#pragma onceS
#include "Global.h"

#include "Story/Action/ActionVisitor.h"

#include "Story/Action/ActionsAll.h"

///Decrements or increments IDs between [minID] and [pivotID] or after it based
class ActionVisitorChangeID final : public ActionVisitor
{
public:
	ActionVisitorChangeID(unsigned minID, bool bIncrement, int maxID)
		: minID(minID), bIncrement(bIncrement), maxID(maxID) {}

	static ActionVisitorChangeID createRemoveVisit(unsigned removedID)						{ return ActionVisitorChangeID(removedID - 1, false, -1); }
	static ActionVisitorChangeID createShuffleVisit(unsigned oldID, unsigned newID)			{ return ActionVisitorChangeID(std::min(newID, oldID), true, std::max(newID, oldID)); }

	void visitActionChangeMusic(ActionChangeMusic* action) override							{ changeID(action); }
	void visitActionPlaySound(ActionPlaySound* action) override								{ changeID(action); }

	void visitActionStatChange(ActionStatChange	*action) override							{ changeID(action); }
		
	void visitActionSetBackground(ActionSetBackground* action) override						{ changeID(action); }
	void visitActionSceneryObjectChange(ActionSceneryObjectChange* action) override			{ changeID(action); }
	void visitActionSceneryObjectAnimMove(ActionSceneryObjectAnimMove* action) override		{ changeID(action); }
	void visitActionSceneryObjectAnimScale(ActionSceneryObjectAnimScale* action) override	{ changeID(action); }
	void visitActionSceneryObjectAnimRotate(ActionSceneryObjectAnimRotate* action) override	{ changeID(action); }
	void visitActionSceneryObjectAnimColor(ActionSceneryObjectAnimColor* action) override	{ changeID(action); }
	void visitActionSceneryObjectShow(ActionSceneryObjectShow* action) override				{ changeID(action); }

	///[optional]
	void visitActionStatShow(ActionStatShow* action) override								{ changeID(action); }

	void visitActionEffectBlur(ActionEffectBlur* action) override							{ changeID(action); }
	void visitActionEffectDistort(ActionEffectDistort* action) override						{ changeID(action); }
	void visitActionEffectGlow(ActionEffectGlow* action) override							{ changeID(action); }
		 
	void visitActionFilterBlur(ActionFilterBlur* action) override							{ changeID(action); }
	void visitActionFilterBrightness(ActionFilterBrightness* action) override				{ changeID(action); }
	void visitActionFilterDilation(ActionFilterDilation* action) override					{ changeID(action); }
	void visitActionFilterErosion(ActionFilterErosion* action) override						{ changeID(action); }
	void visitActionFilterHue(ActionFilterHue* action) override								{ changeID(action); }
	void visitActionFilterNegative(ActionFilterNegative* action) override					{ changeID(action); }
	void visitActionFilterSaturation(ActionFilterSaturation	*action) override				{ changeID(action); }
		 
	void visitActionCharLive2DAnim(ActionCharLive2DAnim* action) override					{ changeID(action); }

private:
	///Changes IDs
	void changeID (Action* action)			
	{
		if (maxID == -1)
		{
			if ((action->actionID > minID))
				bIncrement ? ++action->actionID : --action->actionID;
		}
		else
		{
			if ((action->actionID > minID) && (action->actionID < maxID))
				bIncrement ? ++action->actionID : --action->actionID;
		}
	}

	///Minimal ID that will be affected, if -1 it means we edit IDs after [pivotID], not before it
	int	 minID		= -1;

	///ID after which the change will happen
	int  maxID;

	///Whether we will increment or decrement IDs
	bool bIncrement	= false;
};