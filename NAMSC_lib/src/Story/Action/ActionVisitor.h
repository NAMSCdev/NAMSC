#pragma once
#include "Global.h"

///Forward declaration of all Actions for the ActionVisitor
class ActionStatChange;
class ActionChangeMusic;
class ActionPlaySound;
class ActionSetBackground;
class ActionSceneryObjectChange;
class ActionSceneryObjectAnimMove;
class ActionSceneryObjectAnimScale;
class ActionSceneryObjectAnimRotation;
class ActionSceneryObjectAnimColor;
class ActionSceneryObjectHide;
class ActionSceneryObjectShow;

///[optional]
class ActionStatHide;
class ActionStatShow;
class ActionCharLive2DAnim;
class ActionEffectBlur;
class ActionEffectDistort;
class ActionEffectGlow;
class ActionFilterBlur;
class ActionFilterBrightness;
class ActionFilterDilation;
class ActionFilterErosion;
class ActionFilterHue;
class ActionFilterNegative;
class ActionFilterSaturation;

///Base class of a visitor for Events
///We will not write the abstract class here, like it should be, but default to doing nothing and allow for the overload
class ActionVisitor
{
public:
	virtual ~ActionVisitor() = 0;

	virtual void visitActionChangeMusic(ActionChangeMusic* action)							{}
	virtual void visitActionPlaySound(ActionPlaySound* action)								{}
				 
	virtual void visitActionStatChange(ActionStatChange* action)							{}
				 
	virtual void visitActionSetBackground(ActionSetBackground* action)						{}
	virtual void visitActionSceneryObjectChange(ActionSceneryObjectChange* action)			{}
	virtual void visitActionSceneryObjectAnimMove(ActionSceneryObjectAnimMove* action)		{}
	virtual void visitActionSceneryObjectAnimScale(ActionSceneryObjectAnimScale* action)	{}
	virtual void visitActionSceneryObjectAnimRotate(ActionSceneryObjectAnimRotate* action)	{}
	virtual void visitActionSceneryObjectAnimColor(ActionSceneryObjectAnimColor* action)	{}
	virtual void visitActionSceneryObjectHide(ActionSceneryObjectHide* action)				{}
	virtual void visitActionSceneryObjectShow(ActionSceneryObjectShow* action)				{}

	///[optional]
	virtual void visitActionStatShow(ActionStatShow* action)								{}
	virtual void visitActionEffectBlur(ActionEffectBlur* action)							{}
	virtual void visitActionEffectDistort(ActionEffectDistort* action)						{}
	virtual void visitActionEffectGlow(ActionEffectGlow* action)							{}

	virtual void visitActionFilterBlur(ActionFilterBlur* action)							{}
	virtual void visitActionFilterBrightness(ActionFilterBrightness* action)				{}
	virtual void visitActionFilterDilation(ActionFilterDilation* action)					{}
	virtual void visitActionFilterErosion(ActionFilterErosion* action)						{}
	virtual void visitActionFilterHue(ActionFilterHue* action)								{}
	virtual void visitActionFilterNegative(ActionFilterNegative* action)					{}
	virtual void visitActionFilterSaturation(ActionFilterSaturation* action)				{}

	virtual void visitActionCharLive2DAnim(ActionCharLive2DAnim* action)					{}
};