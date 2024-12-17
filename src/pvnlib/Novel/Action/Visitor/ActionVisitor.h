#pragma once

/// Forward declaration of all Actions for the ActionVisitor
class ActionStatSetValue;
class ActionAudioSetMusic;
class ActionAudioSetSounds;
class ActionSetBackground;
class ActionSceneryObjectSetImage;
class ActionSceneryObjectAnimMove;
class ActionSceneryObjectAnimScale;
class ActionSceneryObjectAnimRotate;
class ActionSceneryObjectAnimColor;
class ActionSceneryObjectAnimFade;
class ActionCharacterSetVoice;
// [optional]
//class ActionStatHide;
//class ActionStatVisibility;
//class ActionLive2DAnim;
//class ActionEffectBlur;
//class ActionEffectDistort;
//class ActionEffectGlow;
//class ActionFilterBlur;
//class ActionFilterBrightness;
//class ActionFilterDilation;
//class ActionFilterErosion;
//class ActionFilterHue;
//class ActionFilterNegative;
//class ActionFilterSaturation;

/// Base class of a Visitor for Actions
/// It is not the abstract class, like it should be, but default to doing nothing and allow for the overload
class ActionVisitor
{
public:
    // The destructor needs to be virtual, so the proper destructor will always be called when destroying an ActionVisitor pointer
    virtual ~ActionVisitor() = 0;
    
    virtual void visitActionAudioSetMusic(ActionAudioSetMusic* action)                    {}
    virtual void visitActionAudioSetSounds(ActionAudioSetSounds* action)                  {}
                                                                                          
    virtual void visitActionStatSetValue(ActionStatSetValue* action)                      {}
                                                                                          
    virtual void visitActionSceneryObjectAnimColor(ActionSceneryObjectAnimColor* action)  {}
    virtual void visitActionSceneryObjectAnimMove(ActionSceneryObjectAnimMove* action)    {}
    virtual void visitActionSceneryObjectAnimRotate(ActionSceneryObjectAnimRotate* action){}
    virtual void visitActionSceneryObjectAnimScale(ActionSceneryObjectAnimScale* action)  {}
    virtual void visitActionSceneryObjectAnimFade(ActionSceneryObjectAnimFade* action)    {}
                                                                                        
    virtual void visitActionSceneryObjectSetImage(ActionSceneryObjectSetImage* action)    {}
    virtual void visitActionCharacterSetVoice(ActionCharacterSetVoice* action)            {}
    virtual void visitActionSetBackground(ActionSetBackground* action)                    {}
    // [optional]																		  
    //virtual void visitActionLive2DAnim(ActionLive2DAnim* action)						  {}
                                                                                          
    //virtual void visitActionStatVisibility(ActionStatVisibility* action)				  {}
    //virtual void visitActionEffectBlur(ActionEffectBlur* action)						  {}
    //virtual void visitActionEffectDistort(ActionEffectDistort* action)				  {}
    //virtual void visitActionEffectGlow(ActionEffectGlow* action)						  {}
                                                                                          
    //virtual void visitActionFilterBlur(ActionFilterBlur* action)						  {}
    //virtual void visitActionFilterBrightness(ActionFilterBrightness* action)			  {}
    //virtual void visitActionFilterDilation(ActionFilterDilation* action)				  {}
    //virtual void visitActionFilterErosion(ActionFilterErosion* action)				  {}
    //virtual void visitActionFilterHue(ActionFilterHue* action)						  {}
    //virtual void visitActionFilterNegative(ActionFilterNegative* action)				  {}
    //virtual void visitActionFilterSaturation(ActionFilterSaturation* action)			  {}
};