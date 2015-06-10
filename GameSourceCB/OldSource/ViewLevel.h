#pragma once
#include "stdafx.h"
#include "View.h"
#include "SDLEventManager.h"
#include "SDLEventData.h"

#include "EntityGroup.h"
#include "DrawableTileMap.h"

typedef std::list<Components::ComponentRender*>* EntityRenderListPtr;

class ViewLevel : public View
{
public:
	ViewLevel() {
		view_ID_ = VIEW_DATA::ID_VIEW_LEVEL;

		// create the delegate for user events
		user_event_delegate_ = createSDLEventListenerDelegate(this, &ViewLevel::eventHandler);

		deactivate();
	};

	~ViewLevel() {
	};

	virtual void eventHandler(SDL_Event* e) {
		// cast the void* to correct data
		// all of these should 
		if (e->type == SDL_USEREVENT) {
			switch (e->user.code) {
			case E_ENTITY_RENDER_LIST:
				entity_render_list_ = static_cast<std::list<Components::ComponentRender*>*>(e->user.data1);
				assert(entity_render_list_ != NULL);
				break;
			case E_MAIN_ENTITY:
				assert(main_entity_ == NULL);
				main_entity_ = static_cast<EventMainEntity*>(e->user.data1);
				assert(main_entity_ != NULL);
				break;
			case E_CAMERA_PIXEL_INFO:
				assert(camera_pixel_info_ == NULL);
				camera_pixel_info_ = static_cast<CameraPixelInfo*>(e->user.data1);
				assert(camera_pixel_info_ != NULL);
				break;
			case E_DRAWABLE_TILE_MAP:
				assert(drawable_tile_map_ == NULL);
				drawable_tile_map_ = static_cast<DrawableTileMap*>(e->user.data1);
				assert(drawable_tile_map_ != NULL);
				break;
			default:
				break;
			}
		}
		// check whether the view is active for drawing
		if (!active_) {
			checkActive();
		}
	}

	virtual void registerDelegates() {
		// listen for events
		SDLEventManager::getInstance()->addListener(SDL_USEREVENT, &user_event_delegate_);
	}

	virtual void unregisterDelegates() {
		// remove listener
		SDLEventManager::getInstance()->removeListener(SDL_USEREVENT, &user_event_delegate_);


	}

	virtual void init(SDL_Window* window, SDL_Renderer* renderer) {
		// create the hud specifc elements
		// get the window size
		SDL_DisplayMode displayMode;
		SDL_GetWindowDisplayMode(window, &displayMode);

		// adjust health bar rects according to size
		health_bar_border_.h = displayMode.h / 20;
		health_bar_border_.w = displayMode.w / 2;
		health_bar_border_.x = displayMode.w / 4;
		health_bar_border_.y = displayMode.h / 20 * 19;
	}

	virtual void draw(SDL_Renderer* renderer) {
		// first render the tile map
		drawable_tile_map_->draw(renderer, camera_pixel_info_);

		// second draw the entities (no order currently)
		SDL_Rect entityRelativeRect;
		SDL_Color color;
		for (auto it = entity_render_list_->begin(); it != entity_render_list_->end(); it++) {


			camera_pixel_info_->getRelativeCameraRect(&((*it)->rectWorld), &entityRelativeRect);
			//SDL_RenderCopy(renderer, (*it)->texture, &(*it)->rectTexture, &entityRelativeRect);
			SDL_RenderCopy(renderer, (*it)->texture, NULL, &entityRelativeRect);

	
			camera_pixel_info_->getRelativeCameraRect(&((*it)->lifeBarBack), &entityRelativeRect);
			color = (*it)->colorLifeBarBack;
			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
			SDL_RenderFillRect(renderer, &entityRelativeRect);

			camera_pixel_info_->getRelativeCameraRect(&((*it)->lifeBar), &entityRelativeRect);
			color = (*it)->colorLifeBar;
			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
			SDL_RenderFillRect(renderer, &entityRelativeRect);

		}

		// third and finally draw the hud ontop of everything (eventually will be the hud stuff)
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
		SDL_RenderFillRect(renderer, &health_bar_border_);

	}

	virtual void activate() {
		// uses checkActive with events
	}

	virtual void deactivate() {
		entity_render_list_ = NULL;
		main_entity_ = NULL;
		camera_pixel_info_ = NULL;
		drawable_tile_map_ = NULL;
		active_ = false;
	}

private:

	void checkActive() {
		// final active_ = camera_pixel_info_ && main_entity_ && drawable_tile_map_ &&  entity_render_list_;
		// temp
		active_ = (camera_pixel_info_ != NULL) && (drawable_tile_map_ != NULL) && (entity_render_list_ != NULL);
		cout << active_ << endl;
	}

	// things needed to draw
	// 1) CameraPixelInfo
	CameraPixelInfo* camera_pixel_info_;

	// 2) main entity struct containing needed componenets for hud
	EventMainEntity* main_entity_;

	// 3) list of entities, containt pointer to the render components
	std::list<Components::ComponentRender*>* entity_render_list_;
	//EntityRenderListPtr entity_render_list_;
		;
	// 4) drawableTIleMap
	DrawableTileMap* drawable_tile_map_;

	SDLEventListenerDelegate user_event_delegate_;

	// stuff to draw the hud (TODO)
	int window_width_;
	int window_height_;

	SDL_Surface* health_bar_surface_;
	SDL_Rect health_bar_border_;
	SDL_Rect health_bar_;
};

