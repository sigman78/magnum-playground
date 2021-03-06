//
//

#pragma once

#ifdef _DEBUG 
#define MAGNUM_PLUGINS_DIR "${MAGNUM_PLUGINS_DEBUG_DIR}" 
#define MAGNUM_PLUGINS_FONT_DIR "${MAGNUM_PLUGINS_FONT_DEBUG_DIR}" 
#define MAGNUM_PLUGINS_FONTCONVERTER_DIR "${MAGNUM_PLUGINS_FONTCONVERTER_DEBUG_DIR}" 
#define MAGNUM_PLUGINS_IMAGECONVERTER_DIR "${MAGNUM_PLUGINS_IMAGECONVERTER_DEBUG_DIR}" 
#define MAGNUM_PLUGINS_IMPORTER_DIR "${MAGNUM_PLUGINS_IMPORTER_DEBUG_DIR}" 
#define MAGNUM_PLUGINS_AUDIOIMPORTER_DIR "${MAGNUM_PLUGINS_AUDIOIMPORTER_DEBUG_DIR}" 
#else 
#define MAGNUM_PLUGINS_DIR "${MAGNUM_PLUGINS_RELEASE_DIR}" 
#define MAGNUM_PLUGINS_FONT_DIR "${MAGNUM_PLUGINS_FONT_RELEASE_DIR}" 
#define MAGNUM_PLUGINS_FONTCONVERTER_DIR "${MAGNUM_PLUGINS_FONTCONVERTER_RELEASE_DIR}" 
#define MAGNUM_PLUGINS_IMAGECONVERTER_DIR "${MAGNUM_PLUGINS_IMAGECONVERTER_RELEASE_DIR}" 
#define MAGNUM_PLUGINS_IMPORTER_DIR "${MAGNUM_PLUGINS_IMPORTER_RELEASE_DIR}" 
#define MAGNUM_PLUGINS_AUDIOIMPORTER_DIR "${MAGNUM_PLUGINS_AUDIOIMPORTER_RELEASE_DIR}" 
#endif 