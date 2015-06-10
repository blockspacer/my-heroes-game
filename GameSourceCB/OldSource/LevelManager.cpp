#include "stdafx.h"
#include "LevelManager.h"



LevelManager::LevelManager(CameraPtr cameraPtr)
{
	tile_map_ = NULL;

	// create all the default masks (unknown)
	health_mask_ = Components::C_HEALTH | Components::C_HEALTH_DAMAGE | Components::C_RESISTANCE | 
		           Components::C_REGENERATE | Components::C_RECOIL | Components::C_DEATH | 
				   Components::C_ACTIVE;
	
	// death mask needs these: (any b2world pointers or texture pointers
	death_mask_ = Components::C_DEATH | Components::C_PHYSICS | Components::C_RENDER |
		          Components::C_VISION_SENSORS;

	// target/action mask needs these:
	target_action_mask_ = Components::C_ACTIVE | Components::C_DEATH | Components::C_PHYSICS | 
		                  Components::C_VISION_ORIENTATION | Components::C_VISION_SENSORS | 
						  Components::C_VISION_TARGET | Components::C_ATTACK | Components::C_BASICATTACK;

	movement_mask_ = Components::C_ACTIVE | Components::C_DEATH | Components::C_PHYSICS | 
		             Components::C_MOVEMENT_ORIENTATION | Components::C_MOVEMENT_SPEED | 
					 Components::C_VISION_ORIENTATION | Components::C_VISION_TARGET;

	render_mask_ = Components::C_HEALTH | Components::C_PHYSICS | Components::C_RENDER;

	// entity group can be reused so only one is made
	entity_group_ = EntityManager::createEntityGroup();
	camera_ptr_ = cameraPtr;


	// make all the singular systems
	default_target_ = new DecisionSystemDefaultTarget(entity_group_);
	default_movementD_ = new DecisionSystemDefaultMovement(entity_group_);

	SDL_Rect* screen = camera_ptr_->getCameraRect();
	control_target_ = new DecisionSystemControlTarget(entity_group_, screen->w, screen->h);
	control_movementD_ = new DecisionSystemControlMovement(entity_group_);

	default_health_ = new EffectSystemDefaultHealth(entity_group_); // mask not added yet
	default_death_ = new EffectSystemDefaultDeath(entity_group_);
	default_action_ = new EffectSystemDefaultAction(entity_group_);
	default_movementE_ = new EffectSystemDefaultMovement(entity_group_);
	default_render_ = new EffectSystemDefaultRender(entity_group_);

	event_messager_.type = SDL_USEREVENT;
	event_messager_.user.code = NULL;
	event_messager_.user.data1 = NULL;
	event_messager_.user.data2 = NULL;
}


LevelManager::~LevelManager()
{
	// delete systems
}

void LevelManager::loadLevel(SDL_Renderer* renderer) {

	// TEMP create a whole level here

	// load the tile map (80 meter square)
	tile_map_ = new TileMap();
	assert(tile_map_ != NULL);
	tile_map_->init(renderer, "Textures/Grasslands.bmp", 80, 80);

	// for all entities
	b2BodyDef def;
	b2FixtureDef fixDef;

	// create boundaries
	// create the variables
	uint64_t bottomWall = EntityManager::getEntity(entity_group_);
	uint64_t topWall = EntityManager::getEntity(entity_group_);
	uint64_t leftWall = EntityManager::getEntity(entity_group_);
	uint64_t rightWall = EntityManager::getEntity(entity_group_);

	// bottom wall
	entity_group_->maskList[bottomWall].mask = 0;

	def.type = b2_staticBody;
	def.position = b2Vec2(40, 7.5);
	def.angle = 0;

	// create it
	entity_group_->physics[bottomWall].body = entity_group_->world->CreateBody(&def);
	entity_group_->physics[bottomWall].body->SetUserData((void*) bottomWall); // assign number to body

	// give it a shape
	b2PolygonShape* bottomShape = new b2PolygonShape;
	bottomShape->SetAsBox(40, 7.5);
	entity_group_->physics[bottomWall].shapes.push_back(bottomShape);

	fixDef.shape = bottomShape;
	fixDef.density = 1;
	fixDef.filter.categoryBits = ENTITY_COLLISION_CATEGORIES::ENVIRONMENT_BODY;
	fixDef.filter.maskBits = ENVIRONMENT_BODY_COL;

	// add fixture to shape
	entity_group_->physics[bottomWall].body->CreateFixture(&fixDef);

	entity_group_->render[bottomWall].texture = IMG_LoadTexture(renderer, "Textures/GrasslandsBorderBottom.png");
	assert(entity_group_->render[bottomWall].texture != NULL);

	// sdl rect
	entity_group_->render[bottomWall].rectWorld.w = 5120;
	entity_group_->render[bottomWall].rectWorld.h = 960;
	entity_group_->render[bottomWall].rectWorld.x = 0;
	entity_group_->render[bottomWall].rectWorld.y = 960;

	// top wall
	entity_group_->maskList[topWall].mask = 0;

	def.type = b2_staticBody;
	def.position = b2Vec2(40, 72.5);
	def.angle = 0;

	// create it
	entity_group_->physics[topWall].body = entity_group_->world->CreateBody(&def);
	entity_group_->physics[topWall].body->SetUserData((void*)topWall); // assign number to body

	// give it a shape
	b2PolygonShape* topShape = new b2PolygonShape;
	topShape->SetAsBox(40, 7.5);
	entity_group_->physics[topWall].shapes.push_back(topShape);

	fixDef.shape = topShape;
	fixDef.density = 1;
	fixDef.filter.categoryBits = ENTITY_COLLISION_CATEGORIES::ENVIRONMENT_BODY;
	fixDef.filter.maskBits = ENVIRONMENT_BODY_COL;

	// add fixture to shape
	entity_group_->physics[topWall].body->CreateFixture(&fixDef);

	entity_group_->render[topWall].texture = IMG_LoadTexture(renderer, "Textures/GrasslandsBorderTop.png");
	assert(entity_group_->render[topWall].texture != NULL);

	// sdl rect
	entity_group_->render[topWall].rectWorld.w = 5120;
	entity_group_->render[topWall].rectWorld.h = 960;
	entity_group_->render[topWall].rectWorld.x = 0;
	entity_group_->render[topWall].rectWorld.y = 5120;

	// left wall
	entity_group_->maskList[leftWall].mask = 0;

	def.type = b2_staticBody;
	def.position = b2Vec2(7.5, 40);
	def.angle = 0;

	// create it
	entity_group_->physics[leftWall].body = entity_group_->world->CreateBody(&def);
	entity_group_->physics[leftWall].body->SetUserData((void*)leftWall); // assign number to body

	// give it a shape
	b2PolygonShape* leftShape = new b2PolygonShape;
	leftShape->SetAsBox(7.5, 40);
	entity_group_->physics[leftWall].shapes.push_back(leftShape);

	fixDef.shape = leftShape;
	fixDef.density = 1;
	fixDef.filter.categoryBits = ENTITY_COLLISION_CATEGORIES::ENVIRONMENT_BODY;
	fixDef.filter.maskBits = ENVIRONMENT_BODY_COL;

	// add fixture to shape
	entity_group_->physics[leftWall].body->CreateFixture(&fixDef);

	entity_group_->render[leftWall].texture = IMG_LoadTexture(renderer, "Textures/GrasslandsBorderLeft.png");
	assert(entity_group_->render[leftWall].texture != NULL);

	// sdl rect
	entity_group_->render[leftWall].rectWorld.w = 960;
	entity_group_->render[leftWall].rectWorld.h = 5120;
	entity_group_->render[leftWall].rectWorld.x = 0;
	entity_group_->render[leftWall].rectWorld.y = 5120;

	// right wall
	entity_group_->maskList[rightWall].mask = 0;

	def.type = b2_staticBody;
	def.position = b2Vec2(72.5, 40);
	def.angle = 0;

	// create it
	entity_group_->physics[rightWall].body = entity_group_->world->CreateBody(&def);
	entity_group_->physics[rightWall].body->SetUserData((void*)rightWall); // assign number to body

	// give it a shape
	b2PolygonShape* rightShape = new b2PolygonShape;
	rightShape->SetAsBox(7.5, 40);
	entity_group_->physics[rightWall].shapes.push_back(rightShape);

	fixDef.shape = rightShape;
	fixDef.density = 1;
	fixDef.filter.categoryBits = ENTITY_COLLISION_CATEGORIES::ENVIRONMENT_BODY;
	fixDef.filter.maskBits = ENVIRONMENT_BODY_COL;

	// add fixture to shape
	entity_group_->physics[rightWall].body->CreateFixture(&fixDef);

	entity_group_->render[rightWall].texture = IMG_LoadTexture(renderer, "Textures/GrasslandsBorderRight.png");
	assert(entity_group_->render[rightWall].texture != NULL);

	// sdl rect
	entity_group_->render[rightWall].rectWorld.w = 960;
	entity_group_->render[rightWall].rectWorld.h = 5120;
	entity_group_->render[rightWall].rectWorld.x = 4160;
	entity_group_->render[rightWall].rectWorld.y = 5120;

	//------------------------MAIN ENTITY
	uint64_t mainEntity = EntityManager::getEntity(entity_group_);

	cout << mainEntity << endl;
	// add mask and systems
	main_entity_ = mainEntity;
	entity_group_->maskList[mainEntity].mask = death_mask_ | health_mask_ | target_action_mask_ | movement_mask_ | render_mask_;

	systems_health_[mainEntity] = default_health_;
	systems_death_[mainEntity] = default_death_;

	// system pair
	SystemPair* sysTargetActionPair = new SystemPair[1];
	sysTargetActionPair->decisionSystem = control_target_; // todo
	sysTargetActionPair->effectSystem = default_action_;
	systems_target_action_[mainEntity] = sysTargetActionPair;

	// system pair
	SystemPair* sysMovementPair = new SystemPair[1];
	sysMovementPair->decisionSystem = control_movementD_;
	sysMovementPair->effectSystem = default_movementE_;
	systems_movement_[mainEntity] = sysMovementPair;

	systems_render_[mainEntity] = default_render_;

	entity_group_->movementSpeed[mainEntity].baseMax = 10;
	entity_group_->movementSpeed[mainEntity].currentMax = 10;
	entity_group_->movementSpeed[mainEntity].current = 0;

	entity_group_->visionOrientation[mainEntity].orientation.x = 0;
	entity_group_->visionOrientation[mainEntity].orientation.y = 0;

	entity_group_->visionTarget[mainEntity].target = -1;
	entity_group_->visionTarget[mainEntity].targetDistance = -1;
	entity_group_->visionTarget[mainEntity].trackingRange = 10;

	entity_group_->death[mainEntity].countDown = 60;
	entity_group_->death[mainEntity].death = false;

	entity_group_->active[mainEntity].active = false;

	// health components
	entity_group_->health[mainEntity].base = 100;
	entity_group_->health[mainEntity].current = 100;

	entity_group_->healthDamage[mainEntity].chunkDamage = 0;
	entity_group_->healthDamage[mainEntity].chunckDamageSource = -1;
	entity_group_->healthDamage[mainEntity].incrementalDamage = 0;
	entity_group_->healthDamage[mainEntity].incrementalDamageSource = -1;
	entity_group_->healthDamage[mainEntity].incrementalRate = 0;

	entity_group_->resistance[mainEntity].normal_base = 0;
	entity_group_->resistance[mainEntity].normal_current = 0;
	entity_group_->resistance[mainEntity].fire_base = 5;
	entity_group_->resistance[mainEntity].fire_current = 5;
	entity_group_->resistance[mainEntity].poison_base = 5;
	entity_group_->resistance[mainEntity].poison_current = 5;


	entity_group_->regenerate[mainEntity].base = 180;
	entity_group_->regenerate[mainEntity].countDown = 180;
	entity_group_->regenerate[mainEntity].rate = 1;

	entity_group_->recoil[main_entity_].base = 0;
	entity_group_->recoil[main_entity_].countDown = 0;

	// bottom wall
	def.type = b2_dynamicBody;
	def.position = b2Vec2(40, 40); // center
	def.angle = 0;

	// create it
	entity_group_->physics[mainEntity].body = entity_group_->world->CreateBody(&def);
	entity_group_->physics[mainEntity].body->SetUserData((void*)mainEntity); // assign number to body

	// give it a shape
	b2CircleShape* topHalfShape = new b2CircleShape;
	topHalfShape->m_radius = 0.5;
	topHalfShape->m_p = b2Vec2(0, 0.25);
	b2CircleShape* bottomHalfShape = new b2CircleShape;
	bottomHalfShape->m_radius = 0.5;
	bottomHalfShape->m_p = b2Vec2(0, -0.25);
	entity_group_->physics[mainEntity].shapes.push_back(topHalfShape);
	entity_group_->physics[mainEntity].shapes.push_back(bottomHalfShape);

	// add top half
	fixDef.shape = topHalfShape;
	fixDef.density = 1;
	fixDef.filter.categoryBits = ENTITY_COLLISION_CATEGORIES::ALLY_BODY;
	fixDef.filter.maskBits = ALLY_BODY_COL;

	// add fixture to shape
	entity_group_->physics[mainEntity].body->CreateFixture(&fixDef);

	// add bottom half
	fixDef.shape = bottomHalfShape;
	fixDef.density = 1;
	fixDef.filter.categoryBits = ENTITY_COLLISION_CATEGORIES::ALLY_BODY;
	fixDef.filter.maskBits = ALLY_BODY_COL;

	// add fixture to shape
	entity_group_->physics[mainEntity].body->CreateFixture(&fixDef);
	// physics done

	entity_group_->render[mainEntity].colorLifeBar.a = 0;
	entity_group_->render[mainEntity].colorLifeBar.r = 0;
	entity_group_->render[mainEntity].colorLifeBar.g = 255;
	entity_group_->render[mainEntity].colorLifeBar.b = 0;
	entity_group_->render[mainEntity].lifeBar.w = 64;
	entity_group_->render[mainEntity].lifeBar.h = 96 / 20;
	entity_group_->render[mainEntity].lifeBar.x = 2528;
	entity_group_->render[mainEntity].lifeBar.y = 2560;

	entity_group_->render[mainEntity].colorLifeBarBack.a = 0;
	entity_group_->render[mainEntity].colorLifeBarBack.r = 0;
	entity_group_->render[mainEntity].colorLifeBarBack.g = 0;
	entity_group_->render[mainEntity].colorLifeBarBack.b = 0;
	entity_group_->render[mainEntity].lifeBarBack = entity_group_->render[mainEntity].lifeBar;

	entity_group_->render[mainEntity].texture = IMG_LoadTexture(renderer, "Textures/Hero.png");
	assert(entity_group_->render[mainEntity].texture != NULL);

	// sdl rect
	entity_group_->render[mainEntity].rectWorld.w = 128; //64
	entity_group_->render[mainEntity].rectWorld.h = 184; //96
	entity_group_->render[mainEntity].rectWorld.x = 2528;
	entity_group_->render[mainEntity].rectWorld.y = 2560;

	//____________________ end main enitty

	// The enemy 1__________________________
	makeHellBat(40, 40, renderer);
	makeHellBat(50, 50, renderer);
	makeHellBat(50, 30, renderer);
	makeHellBat(30, 50, renderer);
	makeHellBat(30, 30, renderer);
	makeHellBat(50, 40, renderer);
	makeHellBat(40, 30, renderer);
	makeHellBat(40, 50, renderer);
	makeHellBat(30, 40, renderer);
	makeHellBat(30, 40, renderer);

	makeHellBat(40, 40, renderer);
	makeHellBat(50, 50, renderer);
	makeHellBat(50, 30, renderer);
	makeHellBat(30, 50, renderer);
	makeHellBat(30, 30, renderer);
	makeHellBat(50, 40, renderer);
	makeHellBat(40, 30, renderer);
	makeHellBat(40, 50, renderer);
	makeHellBat(30, 40, renderer);
	makeHellBat(30, 40, renderer);

	makeHellBat(40, 40, renderer);
	makeHellBat(50, 50, renderer);
	makeHellBat(50, 30, renderer);
	makeHellBat(30, 50, renderer);
	makeHellBat(30, 30, renderer);
	makeHellBat(50, 40, renderer);
	makeHellBat(40, 30, renderer);
	makeHellBat(40, 50, renderer);
	makeHellBat(30, 40, renderer);
	makeHellBat(30, 40, renderer);

	makeHellBat(40, 40, renderer);
	makeHellBat(50, 50, renderer);
	makeHellBat(50, 30, renderer);
	makeHellBat(30, 50, renderer);
	makeHellBat(30, 30, renderer);
	makeHellBat(50, 40, renderer);
	makeHellBat(40, 30, renderer);
	makeHellBat(40, 50, renderer);
	makeHellBat(30, 40, renderer);
	makeHellBat(30, 40, renderer);

	makeHellBat(40, 40, renderer);
	makeHellBat(50, 50, renderer);
	makeHellBat(50, 30, renderer);
	makeHellBat(30, 50, renderer);
	makeHellBat(30, 30, renderer);
	makeHellBat(50, 40, renderer);
	makeHellBat(40, 30, renderer);
	makeHellBat(40, 50, renderer);
	makeHellBat(30, 40, renderer);
	makeHellBat(30, 40, renderer);

	makeHellBat(40, 40, renderer);
	makeHellBat(50, 50, renderer);
	makeHellBat(50, 30, renderer);
	makeHellBat(30, 50, renderer);
	makeHellBat(30, 30, renderer);
	makeHellBat(50, 40, renderer);
	makeHellBat(40, 30, renderer);
	makeHellBat(40, 50, renderer);
	makeHellBat(30, 40, renderer);
	makeHellBat(30, 40, renderer);

	makeHellBat(40, 40, renderer);
	makeHellBat(50, 50, renderer);
	makeHellBat(50, 30, renderer);
	makeHellBat(30, 50, renderer);
	makeHellBat(30, 30, renderer);
	makeHellBat(50, 40, renderer);
	makeHellBat(40, 30, renderer);
	makeHellBat(40, 50, renderer);
	makeHellBat(30, 40, renderer);
	makeHellBat(30, 40, renderer);

	makeHellBat(40, 40, renderer);
	makeHellBat(50, 50, renderer);
	makeHellBat(50, 30, renderer);
	makeHellBat(30, 50, renderer);
	makeHellBat(30, 30, renderer);
	makeHellBat(50, 40, renderer);
	makeHellBat(40, 30, renderer);
	makeHellBat(40, 50, renderer);
	makeHellBat(30, 40, renderer);
	makeHellBat(30, 40, renderer);






	// make entites
	// for now just make the main entity

	// after everything is created send the events to viewlevel
	// send tile map
	event_messager_.user.code = E_DRAWABLE_TILE_MAP;
	event_messager_.user.data1 = tile_map_;
	SDL_PushEvent(&event_messager_);

	// send camera
	event_messager_.user.code = E_CAMERA_PIXEL_INFO;
	event_messager_.user.data1 = camera_ptr_.get();
	SDL_PushEvent(&event_messager_);

	// send the main entity event


	// send event
	event_messager_.user.code = E_ENTITY_RENDER_LIST;
	event_messager_.user.data1 = &render_targets_;
	SDL_PushEvent(&event_messager_);

	camera_ptr_->update(b2Vec2(40, 40));
}

void LevelManager::clearLevel() {
	// clean up all the entities
	// delete tile map
	// delete b2world
	// remove systems
}

void LevelManager::updateLevel() {

	render_targets_.clear();
	entity_group_->world->QueryAABB(this, camera_ptr_->getCameraLargeB2AABB());

	// these process use the greate area of the camera
	processEffectSystem(health_mask_, &systems_health_);
	processEffectSystem(death_mask_, &systems_death_);

	// b2 world after bodies have been removed
	//entity_group_->world->ClearForces();
	entity_group_->world->Step(1.0 / 30, 8, 2);

	processPairSystem(target_action_mask_, &systems_target_action_);
	processPairSystem(movement_mask_, &systems_movement_);

	camera_targets_.clear();
	entity_group_->world->QueryAABB(this, camera_ptr_->getCameraSmallB2AABB());

	// render system just needs visible entities
	processEffectSystem(render_mask_, &systems_render_);

	render_targets_.clear();
	for (auto it = camera_targets_.begin(); it != camera_targets_.end(); it++) {
		render_targets_.push_back(&entity_group_->render[*it]);
	}

	// update camera
	camera_ptr_->update(entity_group_->physics[main_entity_].body->GetWorldCenter());
}

// adds the entities to a list a camera targets
bool LevelManager::ReportFixture(b2Fixture* fixture) {
	camera_targets_.insert((uint64_t) fixture->GetBody()->GetUserData());
	return true;//keep going to find all fixtures in the query area
}

void LevelManager::processEffectSystem(Components::ComponentMask mask, EffectSystemMap* effectSystemMap) {

	// If the entity has the correct mask then the system function will
	// be found and called
	for (auto it = camera_targets_.begin(); it != camera_targets_.end(); it++) {
		uint64_t index = (*it);
		// check that if the mask passes that the map contains a function for
		// that entity
		if ((entity_group_->maskList[index].mask & mask) == mask) {
			assert(effectSystemMap->count(index));
			(*effectSystemMap)[index]->updateSystem(index);
		}
	}
}

void LevelManager::processPairSystem(Components::ComponentMask mask, PairSystemMap* pairSystemMap) {

	// If the entity has the correct mask then the system function will
	// be found and called
	for (auto it = camera_targets_.begin(); it != camera_targets_.end(); it++) {
		uint64_t index = (*it);
		// check that if the mask passes that the map contains a function for
		// that entity
		if ((entity_group_->maskList[index].mask & mask) == mask) {
			assert(pairSystemMap->count(index));
			SystemPair* pair = (*pairSystemMap)[index];
			assert(pair != NULL);
			// decision system will return a bool on whether to
			// update the effect
			if (pair->decisionSystem->updateSystem(index)) {

				pair->effectSystem->updateSystem(index);
			}
		}
	}
}


void LevelManager::makeHellBat(float x, float y, SDL_Renderer* renderer) {
	b2BodyDef def;
	b2FixtureDef fixDef;

	uint64_t enemyEntity1 = EntityManager::getEntity(entity_group_);
	entity_group_->maskList[enemyEntity1].mask = death_mask_ | target_action_mask_ | movement_mask_ | render_mask_;

	systems_health_[enemyEntity1] = default_health_;
	systems_death_[enemyEntity1] = default_death_;

	// system pair
	SystemPair* sysTargetActionPair = new SystemPair[1];
	sysTargetActionPair->decisionSystem = default_target_; // todo
	sysTargetActionPair->effectSystem = default_action_;
	systems_target_action_[enemyEntity1] = sysTargetActionPair;

	// system pair
	SystemPair* sysMovementPair = new SystemPair[1];
	sysMovementPair->decisionSystem = default_movementD_;
	sysMovementPair->effectSystem = default_movementE_;
	systems_movement_[enemyEntity1] = sysMovementPair;

	systems_render_[enemyEntity1] = default_render_;

	// physics component
	def.type = b2_dynamicBody;
	def.position = b2Vec2(x, y); // center
	def.angle = 0;

	entity_group_->physics[enemyEntity1].body = entity_group_->world->CreateBody(&def);
	entity_group_->physics[enemyEntity1].body->SetUserData((void*)enemyEntity1);

	// give it a shape
	b2CircleShape* topHalfShapeE1 = new b2CircleShape;
	topHalfShapeE1->m_radius = 0.5;
	topHalfShapeE1->m_p = b2Vec2(0, 0.25);
	b2CircleShape* bottomHalfShapeE1 = new b2CircleShape;
	bottomHalfShapeE1->m_radius = 0.5;
	bottomHalfShapeE1->m_p = b2Vec2(0, -0.25);
	entity_group_->physics[enemyEntity1].shapes.push_back(topHalfShapeE1);
	entity_group_->physics[enemyEntity1].shapes.push_back(bottomHalfShapeE1);

	// add top half
	fixDef.shape = topHalfShapeE1;
	fixDef.density = 1;
	fixDef.isSensor = false;
	fixDef.filter.categoryBits = ENTITY_COLLISION_CATEGORIES::ENEMY_BODY;
	fixDef.filter.maskBits = ENEMY_BODY_COL;

	// add fixture to shape
	entity_group_->physics[enemyEntity1].body->CreateFixture(&fixDef);

	// add bottom half
	fixDef.shape = bottomHalfShapeE1;
	fixDef.density = 1;
	fixDef.isSensor = false;
	fixDef.filter.categoryBits = ENTITY_COLLISION_CATEGORIES::ENEMY_BODY;
	fixDef.filter.maskBits = ENEMY_BODY_COL;

	// add fixture to shape
	entity_group_->physics[enemyEntity1].body->CreateFixture(&fixDef);

	// movement speed component
	entity_group_->movementSpeed[enemyEntity1].baseMax = 5;
	entity_group_->movementSpeed[enemyEntity1].currentMax = 5;
	entity_group_->movementSpeed[enemyEntity1].current = 0;

	// orientation componenet (up)
	entity_group_->visionOrientation[enemyEntity1].orientation.x = 0;
	entity_group_->visionOrientation[enemyEntity1].orientation.y = 0;

	// death componenet
	entity_group_->death[enemyEntity1].countDown = 90;
	entity_group_->death[enemyEntity1].death = false;

	// active component
	entity_group_->active[enemyEntity1].active = false;

	// vision component
	entity_group_->visionTarget[enemyEntity1].trackingRange = 10;
	entity_group_->visionTarget[enemyEntity1].target = -1;
	entity_group_->visionTarget[enemyEntity1].targetDistance = -1;

	def.type = b2_dynamicBody;
	def.position = b2Vec2(x, y); // center
	def.angle = 0;
	entity_group_->visionSensor[enemyEntity1].visionBody = entity_group_->world->CreateBody(&def);
	entity_group_->visionSensor[enemyEntity1].visionBody->SetUserData((void*) enemyEntity1);

	entity_group_->visionSensor[enemyEntity1].smallSightShape = new b2CircleShape();
	entity_group_->visionSensor[enemyEntity1].smallSightShape->m_radius = 2;

	entity_group_->visionSensor[enemyEntity1].smallSightFixDef.isSensor = true;
	entity_group_->visionSensor[enemyEntity1].smallSightFixDef.shape = entity_group_->visionSensor[enemyEntity1].smallSightShape;
	entity_group_->visionSensor[enemyEntity1].smallSightFixDef.density = 0;
	entity_group_->visionSensor[enemyEntity1].smallSightFixDef.filter.categoryBits = ENTITY_COLLISION_CATEGORIES::ENEMY_SENSOR;
	entity_group_->visionSensor[enemyEntity1].smallSightFixDef.filter.maskBits = ENEMY_SENSOR_COL;

	entity_group_->visionSensor[enemyEntity1].largeSightShape = new b2CircleShape();
	entity_group_->visionSensor[enemyEntity1].largeSightShape->m_radius = 5;

	entity_group_->visionSensor[enemyEntity1].largeSightFixDef.isSensor = true;
	entity_group_->visionSensor[enemyEntity1].largeSightFixDef.shape = entity_group_->visionSensor[enemyEntity1].largeSightShape;
	entity_group_->visionSensor[enemyEntity1].largeSightFixDef.density = 0;
	entity_group_->visionSensor[enemyEntity1].largeSightFixDef.filter.categoryBits = ENTITY_COLLISION_CATEGORIES::ENEMY_SENSOR;
	entity_group_->visionSensor[enemyEntity1].largeSightFixDef.filter.maskBits = ENEMY_SENSOR_COL;

	b2DistanceJointDef jointDef;
	jointDef.collideConnected = false;
	jointDef.length = 0;
	jointDef.bodyA = entity_group_->physics[enemyEntity1].body;
	jointDef.localAnchorA = b2Vec2(0, 0);
	jointDef.bodyB = entity_group_->visionSensor[enemyEntity1].visionBody;
	jointDef.localAnchorB = b2Vec2(0, 0);

	// add shape
	entity_group_->visionSensor[enemyEntity1].visionBody->CreateFixture(&entity_group_->visionSensor[enemyEntity1].largeSightFixDef);
	// create joint
	entity_group_->visionSensor[enemyEntity1].connectionJoint = entity_group_->world->CreateJoint(&jointDef);

	// attack component
	entity_group_->attack[enemyEntity1].attacking = false;

	// basic component
	entity_group_->basicAttack[enemyEntity1].heavyDamage = 10;
	entity_group_->basicAttack[enemyEntity1].heavyRange = 2;
	entity_group_->basicAttack[enemyEntity1].heavySpeedBase = 60;
	entity_group_->basicAttack[enemyEntity1].heavySpeedCurrent = 60;
	entity_group_->basicAttack[enemyEntity1].heavySpeedDamagePoint = 30;
	entity_group_->basicAttack[enemyEntity1].heavyType = Components::ATTACK_TYPE_DAMAGE::NORMAL;


	entity_group_->attack[enemyEntity1].attacking = false;
	// entity_group_->attack[enemyEntity1].attackType


	entity_group_->render[enemyEntity1].colorLifeBar.a = 0;
	entity_group_->render[enemyEntity1].colorLifeBar.r = 0;
	entity_group_->render[enemyEntity1].colorLifeBar.g = 255;
	entity_group_->render[enemyEntity1].colorLifeBar.b = 0;
	entity_group_->render[enemyEntity1].lifeBar.w = 64;
	entity_group_->render[enemyEntity1].lifeBar.h = 96 / 20;
	entity_group_->render[enemyEntity1].lifeBar.x = x * 64 - 32;
	entity_group_->render[enemyEntity1].lifeBar.y = y * 64 + 49;

	entity_group_->render[enemyEntity1].colorLifeBarBack.a = 0;
	entity_group_->render[enemyEntity1].colorLifeBarBack.r = 0;
	entity_group_->render[enemyEntity1].colorLifeBarBack.g = 0;
	entity_group_->render[enemyEntity1].colorLifeBarBack.b = 0;
	entity_group_->render[enemyEntity1].lifeBarBack = entity_group_->render[enemyEntity1].lifeBar;

	// render component
	entity_group_->render[enemyEntity1].texture = IMG_LoadTexture(renderer, "Textures/HellBat.png");
	assert(entity_group_->render[enemyEntity1].texture != NULL);

	// sdl rect
	entity_group_->render[enemyEntity1].rectWorld.w = 64;
	entity_group_->render[enemyEntity1].rectWorld.h = 96;
	entity_group_->render[enemyEntity1].rectWorld.x = x * 64 - 32;
	entity_group_->render[enemyEntity1].rectWorld.y = y * 64 + 49;

}