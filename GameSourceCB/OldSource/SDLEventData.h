#pragma once
#include "stdafx.h"
#include "Components.h"

// structs for custom events, names should start with ""
typedef struct {
	// list the components needed for the hud, drawing 
	//not needed because it should be covered in render list
} EventMainEntity;

// a map for all the user defined events
enum EVENT_DATA {
	// add custom events
	// level view events
	E_CAMERA_PIXEL_INFO = 0,
	E_MAIN_ENTITY = 1,
	E_DRAWABLE_TILE_MAP = 2,
	E_ENTITY_RENDER_LIST = 3
};

