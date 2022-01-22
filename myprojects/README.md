# RackAFX custom ported project #

Overwrite the contents of `C:\Program Files (x86)\RackAFX 7.0\BaseClassFiles\PortedProjectsRAFX2\myprojects` with the contents of this directory to:
1. Include the following files from ASPiKCommon into your poerted ASPiK project: 
	-	${OBJECTS_SOURCE_ROOT}/customfxobjects.h
	-	${OBJECTS_SOURCE_ROOT}/customfxobjects.cpp
	-	${OBJECTS_SOURCE_ROOT}/utilities
	-	${VSTGUI_SOURCE_ROOT}/custompedalviews.cpp
1. Ensure that Universal project build targets follow the same naming as non-universal build targets:
	- *Plugin*.vst3 is named precisely that, and **not** *Plugin*_VST.vst3
