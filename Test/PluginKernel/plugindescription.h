// --- CMAKE generated variables for your plugin

#include "pluginstructures.h"

#ifndef _plugindescription_h
#define _plugindescription_h

#define QUOTE(name) #name
#define STR(macro) QUOTE(macro)
#define AU_COCOA_VIEWFACTORY_STRING STR(AU_COCOA_VIEWFACTORY_NAME)
#define AU_COCOA_VIEW_STRING STR(AU_COCOA_VIEW_NAME)

// --- AU Plugin Cocoa View Names (flat namespace)
#define AU_COCOA_VIEWFACTORY_NAME AUCocoaViewFactory_FA6C6653010E492E90B5E6396AA22E9E
#define AU_COCOA_VIEW_NAME AUCocoaView_FA6C6653010E492E90B5E6396AA22E9E

// --- BUNDLE IDs (MacOS Only)
const char* kAAXBundleID = "doomsvillesoundscapes.aax.Test.bundleID";
const char* kAUBundleID = "doomsvillesoundscapes.au.Test.bundleID";
const char* kVST3BundleID = "doomsvillesoundscapes.vst3.Test.bundleID";

// --- Plugin Names
const char* kPluginName = "Test";
const char* kShortPluginName = "Test";
const char* kAUBundleName = "Test";
const char* kAAXBundleName = "Test";
const char* kVSTBundleName = "Test";

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
const char* kVSTFUID = "{FA6C6653-010E-492E-90B5-E6396AA22E9E}";

// --- 4-char codes
const int32_t kFourCharCode = 'TEST';
const int32_t kAAXProductID = 'TEST';
const int32_t kManufacturerID = 'DOOM';

// --- Vendor information
const char* kVendorName = "Doomsville Soundscapes";
const char* kVendorURL = "github.com/DoomyDwyer";
const char* kVendorEmail = "doomy@puscii.nl";

// --- Plugin Options
const bool kProcessFrames = true;
const uint32_t kBlockSize = DEFAULT_AUDIO_BLOCK_SIZE;
const bool kWantSidechain = false;
const uint32_t kLatencyInSamples = 0;
const double kTailTimeMsec = 0.000;
const bool kVSTInfiniteTail = false;
const bool kVSTSAA = false;
const uint32_t kVST3SAAGranularity = 1;
const uint32_t kAAXCategory = 0;

#endif


