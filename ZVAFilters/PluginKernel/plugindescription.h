// --- CMAKE generated variables for your plugin

#include "pluginstructures.h"

#ifndef _plugindescription_h
#define _plugindescription_h

#define QUOTE(name) #name
#define STR(macro) QUOTE(macro)
#define AU_COCOA_VIEWFACTORY_STRING STR(AU_COCOA_VIEWFACTORY_NAME)
#define AU_COCOA_VIEW_STRING STR(AU_COCOA_VIEW_NAME)

// --- AU Plugin Cocoa View Names (flat namespace)
#define AU_COCOA_VIEWFACTORY_NAME AUCocoaViewFactory_37D967367DFA4531A1F9B98D06B20503
#define AU_COCOA_VIEW_NAME AUCocoaView_37D967367DFA4531A1F9B98D06B20503

// --- BUNDLE IDs (MacOS Only)
const char* kAAXBundleID = "doomsvillesoundscapes.aax.ZVAFilters.bundleID";
const char* kAUBundleID = "doomsvillesoundscapes.au.ZVAFilters.bundleID";
const char* kVST3BundleID = "doomsvillesoundscapes.vst3.ZVAFilters.bundleID";

// --- Plugin Names
const char* kPluginName = "ZVAFilters";
const char* kShortPluginName = "ZVAFilters";
const char* kAUBundleName = "ZVAFilters";
const char* kAAXBundleName = "ZVAFilters";
const char* kVSTBundleName = "ZVAFilters";

// --- bundle name helper
inline static const char* getPluginDescBundleName()
{
#ifdef AUPLUGIN
	return kAUBundleName;
#endif

#ifdef AAXPLUGIN
	return kAAXBundleName;
#endif

#ifdef VSTPLUGIN
	return kVSTBundleName;
#endif

	// --- should never get here
	return kPluginName;
}

// --- Plugin Type
const pluginType kPluginType = pluginType::kFXPlugin;

// --- VST3 UUID
const char* kVSTFUID = "{37D96736-7DFA-4531-A1F9-B98D06B20503}";

// --- 4-char codes
const int32_t kFourCharCode = 'ZVAF';
const int32_t kAAXProductID = 'ZVAF';
const int32_t kManufacturerID = 'DOOM';

// --- Vendor information
const char* kVendorName = "Doomsville Soundscapes";
const char* kVendorURL = "github.com/DoomyDwyer";
const char* kVendorEmail = "doomy@puscii.nl";

// --- Plugin Options
const bool kProcessFrames = true;
const uint32_t kBlockSize = DEFAULT_AUDIO_BLOCK_SIZE;
const bool kWantSidechain = true;
const uint32_t kLatencyInSamples = 0;
const double kTailTimeMsec = 0.000;
const bool kVSTInfiniteTail = false;
const bool kVSTSAA = false;
const uint32_t kVST3SAAGranularity = 1;
const uint32_t kAAXCategory = 0;

#endif


