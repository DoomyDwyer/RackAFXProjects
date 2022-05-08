// -----------------------------------------------------------------------------
//    ASPiK Plugin Kernel File:  plugincore.h
//
/**
    \file   plugincore.h
    \author Will Pirkle
    \date   17-September-2018
    \brief  base class interface file for ASPiK plugincore object
    		- http://www.aspikplugins.com
    		- http://www.willpirkle.com
*/
// -----------------------------------------------------------------------------
#ifndef __pluginCore_h__
#define __pluginCore_h__

#include "../../../../ASPiKCommon/dsp/customfxobjects.h"
#include "../../../../ASPiKCommon/utils/observer.h"
#include "fxobjects.h"
#include "pluginbase.h"

// **--0x7F1F--**

// --- Plugin Variables controlID Enumeration 

enum controlID {
	fx_On = 0,
	filterFc_Hz = 1,
	filterQ = 2,
	attackTime_mSec = 3,
	releaseTime_mSec = 4,
	threshold_dB = 5,
	sensitivity = 6,
	filterOutputGain_dB = 10,
	matchAnalogNyquistLPF = 12,
	selfOscillate = 13,
	enableNLP = 14,
	filterType = 15,
	vuMeter = 16,
	enableGainComp = 11,
	fx_OnOff_Toggle = 7,
	thresholdExceeded = 17
};

	// **--0x0F1F--**

/**
\class PluginCore
\ingroup ASPiK-Core
\brief
The PluginCore object is the default PluginBase derived object for ASPiK projects.
Note that you are fre to change the name of this object (as long as you change it in the compiler settings, etc...)


PluginCore Operations:
- overrides the main processing functions from the base class
- performs reset operation on sub-modules
- processes audio
- processes messages for custom views
- performs pre and post processing functions on parameters and audio (if needed)

\author Will Pirkle http://www.willpirkle.com
\remark This object is included in Designing Audio Effects Plugins in C++ 2nd Ed. by Will Pirkle
\version Revision : 1.0
\date Date : 2018 / 09 / 7
*/
class PluginCore : public PluginBase, Observer
{
public:
    PluginCore();

	/** Destructor: empty in default version */
    virtual ~PluginCore(){}

	// --- PluginBase Overrides ---
	//
	/** this is the creation function for all plugin parameters */
	bool initPluginParameters();

	/** called when plugin is loaded, a new audio file is playing or sample rate changes */
	virtual bool reset(ResetInfo& resetInfo);

	/** one-time post creation init function; pluginInfo contains path to this plugin */
	virtual bool initialize(PluginInfo& _pluginInfo);

	/** preProcess: sync GUI parameters here; override if you don't want to use automatic variable-binding */
	virtual bool preProcessAudioBuffers(ProcessBufferInfo& processInfo);

	/** process frames of data (DEFAULT MODE) */
	virtual bool processAudioFrame(ProcessFrameInfo& processFrameInfo);

	/** Pre-process the block with: MIDI events for the block and parametet smoothing */
	virtual bool preProcessAudioBlock(IMidiEventQueue* midiEventQueue = nullptr);

	/** process sub-blocks of data (OPTIONAL MODE) */
	virtual bool processAudioBlock(ProcessBlockInfo& processBlockInfo);

	/** This is the native buffer processing function; you may override and implement
	     it if you want to roll your own buffer or block procssing code */
	// virtual bool processAudioBuffers(ProcessBufferInfo& processBufferInfo);

	/** preProcess: do any post-buffer processing required; default operation is to send metering data to GUI  */
	virtual bool postProcessAudioBuffers(ProcessBufferInfo& processInfo);

	/** called by host plugin at top of buffer proccess; this alters parameters prior to variable binding operation  */
	virtual bool updatePluginParameter(int32_t controlID, double controlValue, ParameterUpdateInfo& paramInfo);

	/** called by host plugin at top of buffer proccess; this alters parameters prior to variable binding operation  */
	virtual bool updatePluginParameterNormalized(int32_t controlID, double normalizedValue, ParameterUpdateInfo& paramInfo);

	/** this can be called: 1) after bound variable has been updated or 2) after smoothing occurs  */
	virtual bool postUpdatePluginParameter(int32_t controlID, double controlValue, ParameterUpdateInfo& paramInfo);

	/** this is ony called when the user makes a GUI control change */
	virtual bool guiParameterChanged(int32_t controlID, double actualValue);

	/** processMessage: messaging system; currently used for custom/special GUI operations */
	virtual bool processMessage(MessageInfo& messageInfo);

	/** processMIDIEvent: MIDI event processing */
	virtual bool processMIDIEvent(midiEvent& event);

	/** specialized joystick servicing (currently not used) */
	virtual bool setVectorJoystickParameters(const VectorJoystickData& vectorJoysickData);

	/** create the presets */
	bool initPluginPresets();

	// --- example block processing template functions (OPTIONAL)
	//
	/** FX EXAMPLE: process audio by passing through */
	bool renderFXPassThrough(ProcessBlockInfo& blockInfo);

	/** SYNTH EXAMPLE: render a block of silence */
	bool renderSynthSilence(ProcessBlockInfo& blockInfo);

	// --- BEGIN USER VARIABLES AND FUNCTIONS -------------------------------------- //
	//	   Add your variables and methods here



	// --- END USER VARIABLES AND FUNCTIONS -------------------------------------- //

protected:
	AutoQEnvelopeFollower envFollowers[NUM_CHANNELS];
    int const FILTER_ENUM_OFFSET = 3;
    void updateParameters();
    void update(Observable* observable) override;
    void registerEnvelopeFollowerObservers();

private:
	//  **--0x07FD--**

	// --- Continuous Plugin Variables 
	double filterFc_Hz = 0.0;
	double filterQ = 0.0;
	double attackTime_mSec = 0.0;
	double releaseTime_mSec = 0.0;
	double threshold_dB = 0.0;
	double sensitivity = 0.0;
	double filterOutputGain_dB = 0.0;

	// --- Discrete Plugin Variables 
	int fx_On = 0;
	enum class fx_OnEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(fx_OnEnum::SWITCH_OFF, fx_On)) etc... 

	int matchAnalogNyquistLPF = 0;
	enum class matchAnalogNyquistLPFEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(matchAnalogNyquistLPFEnum::SWITCH_OFF, matchAnalogNyquistLPF)) etc... 

	int selfOscillate = 0;
	enum class selfOscillateEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(selfOscillateEnum::SWITCH_OFF, selfOscillate)) etc... 

	int enableNLP = 0;
	enum class enableNLPEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(enableNLPEnum::SWITCH_OFF, enableNLP)) etc... 

	int filterType = 0;
	enum class filterTypeEnum { kSVF_LP,kSVF_HP,kSVF_BP };	// to compare: if(compareEnumToInt(filterTypeEnum::kSVF_LP, filterType)) etc... 

	int enableGainComp = 0;
	enum class enableGainCompEnum { BOOST_Q_OFF,BOOST_Q_ON };	// to compare: if(compareEnumToInt(enableGainCompEnum::BOOST_Q_OFF, enableGainComp)) etc... 

	int fx_OnOff_Toggle = 0;
	enum class fx_OnOff_ToggleEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(fx_OnOff_ToggleEnum::SWITCH_OFF, fx_OnOff_Toggle)) etc... 

	// --- Meter Plugin Variables
	float vuMeter = 0.f;
	float thresholdExceeded = 0.f;

	// **--0x1A7F--**
    // --- end member variables

public:
    /** static description: bundle folder name

	\return bundle folder name as a const char*
	*/
    static const char* getPluginBundleName();

    /** static description: name

	\return name as a const char*
	*/
    static const char* getPluginName();

	/** static description: short name

	\return short name as a const char*
	*/
	static const char* getShortPluginName();

	/** static description: vendor name

	\return vendor name as a const char*
	*/
	static const char* getVendorName();

	/** static description: URL

	\return URL as a const char*
	*/
	static const char* getVendorURL();

	/** static description: email

	\return email address as a const char*
	*/
	static const char* getVendorEmail();

	/** static description: Cocoa View Factory Name

	\return Cocoa View Factory Name as a const char*
	*/
	static const char* getAUCocoaViewFactoryName();

	/** static description: plugin type

	\return type (FX or Synth)
	*/
	static pluginType getPluginType();

	/** static description: VST3 GUID

	\return VST3 GUID as a const char*
	*/
	static const char* getVSTFUID();

	/** static description: 4-char code

	\return 4-char code as int
	*/
	static int32_t getFourCharCode();

	/** initalizer */
	bool initPluginDescriptors();

    /** Status Window Messages for hosts that can show it */
    void sendHostTextMessage(std::string messageString)
    {
        HostMessageInfo hostMessageInfo;
        hostMessageInfo.hostMessage = sendRAFXStatusWndText;
        hostMessageInfo.rafxStatusWndText.assign(messageString);
        if(pluginHostConnector)
            pluginHostConnector->sendHostMessage(hostMessageInfo);
    }

};




#endif /* defined(__pluginCore_h__) */
