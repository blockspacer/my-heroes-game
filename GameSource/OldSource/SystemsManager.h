#pragma once
#include "EntityManager.h"
#include <unordered_set>
#include <unordered_map>

typedef bool System(EntityGroupPtr entity_group, uint64_t entity);
typedef std::unordered_map<uint64_t, System*> System_Map;

typedef std::unordered_set<uint64_t> SetOfEntities;



// struct for holding the the user ai control systems (always)
// not needed but good for ensuring the systems are correct
typedef struct {
	uint64_t entity_under_control;
	System* ai_action_system;
	System* ai_movement_system;
} User_Control_Systems;

// struct for holding the entity, that is being controlled by the
// users, actual ai systems. You need to hold them somewhere so that
// when you switch you can give the entity its original ai systems
typedef struct {
	uint64_t entity_under_control;
	System* ai_action_system;
	System* ai_movement_system;
} User_Standby_Systems;

class SystemsManager
{
public:

	// Contructor and Destructor
	SystemsManager();
	~SystemsManager();



	// These functions go through the set of entities and call their
	// respective functions from the system maps
	// param: a pointer to an SetOfEntities, this function is not
	// responsible for the pointer it is passed, and should not alter it
	// or the contents
	bool RunHealthSystems(SetOfEntities* set_of_entities);
	bool RunDeathSystems(SetOfEntities* set_of_entities);
	bool RunAIActionSystems(SetOfEntities* set_of_entities);
	bool RunActionSystems(SetOfEntities* set_of_entities);
	bool RunAIMovementSystems(SetOfEntities* set_of_entities);
	bool RunMovementSystems(SetOfEntities* set_of_entities);
	bool RunRenderSystems(SetOfEntities* set_of_entities);

private:

	// This is the group of entities that this SystemsManager should
	// operate on
	// SHOULD NOT CHANGE
	EntityGroupPtr entity_group_;

	// These are the system maps and their respective masks that
	// enable them to operate on entities
	// The masks should be defined when the SystemsManager is created and
	// should not change throughout it's life time
	// ----------------- System Maps Begin --------------------//

	Components::ComponentMask health_mask_;
	System_Map health_systems_;

	Components::ComponentMask death_mask_;
	System_Map death_systems_;

	Components::ComponentMask ai_action_mask_;
	System_Map ai_action_systems_;

	Components::ComponentMask action_mask_;
	System_Map action_systems_;

	Components::ComponentMask ai_movement_mask_;
	System_Map ai_movement_systems_;

	Components::ComponentMask movement_mask_;
	System_Map movement_systems_;

	Components::ComponentMask render_mask_;
	System_Map render_systems_;

	// ----------------- System Maps End ----------------------//

    // Used to control one of the squad entities
	User_Control_Systems user_control_systems_;
	User_Standby_Systems user_standby_systems_;

	// List of squad members
	std::vector<uint64_t> squad_;

};

