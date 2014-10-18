#pragma once
#include "stdafx.h"
#include "Components.h"
#include "EntityGroup.h"


// This is a struct to help manage the free entities
// Each free node has a next and a freed field
typedef EntityListNode;

class EntityManager
{
public:
	// Handles the construction of the EntityGroup
	EntityManager();

	// Handles the cleanup of the EntityGroup
	~EntityManager();

	// This function gets the EntityGroupPtr associated
	// with this EntityManager
	EntityGroupPtr GetEntityGroupPtr();

	// This function gets a free entity from the entity
	// group and returns -1 if there is no more free
	// entities
	EntityID GetFreeEntity();

	// This function releases a entity that is in use, if you
	// pass a already freed entity then nothing happens
	bool ReleaseEntity(EntityID);

private:
	EntityListNode* front_;
	EntityListNode* entity_node_array_;

	EntityGroupPtr entity_group_ptr_;
};


// type for methods that want to create entities
typedef uint64_t(*createEntityFunc)(EntityGroupPtr);

// This method will create a new instance of the game world by
// creating an entity group and returning a pointer to it.
static EntityGroupPtr createEntityGroup();

// This method is used to release an Entity from the structure
// TODO
// As of now, any non null pointer will be freed however the component are
// needed to be freed, ie DestroyTexture, ...
static bool releaseEntity(EntityGroupPtr entityGroup, uint64_t entity);
	
static EntityGroupPtr createEntityGroup() {

	// create the entities struct on the heap with zeroed 
	// out data
	EntityGroupPtr entityGroup = new EntityGroup();

	// This contructor has to properly set up the linked list
	// of free entities
	entityGroup->freeNodes = &entityGroup->maskList[0];
	entityGroup->usedNodes = NULL;

	entityGroup->maskList[0].next = &(entityGroup->maskList[1]);;
	entityGroup->maskList[0].prev = NULL;
	entityGroup->maskList[0].index = 0;
	entityGroup->maskList[0].free = true;

	for (uint64_t i = 1; i < MAX_ENTITIES - 1; i++) {
		entityGroup->maskList[i].next = &(entityGroup->maskList[i + 1]);
		entityGroup->maskList[i].prev = &(entityGroup->maskList[i - 1]);
		entityGroup->maskList[i].index = i;
		entityGroup->maskList[i].free = true;
	}

	entityGroup->maskList[MAX_ENTITIES - 1].next = NULL;
	entityGroup->maskList[MAX_ENTITIES - 1].prev = &(entityGroup->maskList[MAX_ENTITIES - 2]);
	entityGroup->maskList[MAX_ENTITIES - 1].index = MAX_ENTITIES - 1;
	entityGroup->maskList[MAX_ENTITIES - 1].free = true;

	entityGroup->world = new b2World(b2Vec2(0, 0));

	return entityGroup;
}

static bool releaseEntity(EntityGroupPtr entityGroup, uint64_t entity) {
	assert(entity < MAX_ENTITIES);
	if (!entityGroup->maskList[entity].free && entityGroup->usedNodes != NULL) {

		// get the node
		MaskNode* usedNode = &(entityGroup->maskList[entity]);

		// maintaint the used list
		if (usedNode->prev != NULL && usedNode->next != NULL) {
			usedNode->prev->next = usedNode->next;
			usedNode->next->prev = usedNode->prev;
		}
		else if (usedNode->prev == NULL && usedNode->next != NULL) {
			// front of list
			usedNode->next->prev = NULL;
			entityGroup->usedNodes = usedNode->next;
		}
		else if (usedNode->prev == NULL && usedNode->next != NULL) {
			// end of list
			usedNode->prev->next = NULL;
		}
		else if (usedNode->prev == NULL && usedNode->next == NULL) {
			// only node in list
			entityGroup->usedNodes = NULL;
		}

		// add used node to the front of free list
		usedNode->prev = NULL;
		usedNode->next = entityGroup->freeNodes;
		usedNode->free = true;
		entityGroup->freeNodes->prev = usedNode;
		entityGroup->freeNodes = usedNode;
		return true;
	}
	else {
		return false;
	}
}

static uint64_t getEntity(EntityGroupPtr entityGroup) {
	if (entityGroup->freeNodes == NULL) {
		return MAX_ENTITIES;
	}
	else {
		MaskNode* freeNode = entityGroup->freeNodes;

		// change the next of freeNode
		if (freeNode->next != NULL) {
			freeNode->next->prev = NULL;
		}
		// update freeNodes to point at the next of freeNode
		entityGroup->freeNodes = freeNode->next;

		// now put freeNode into the used Nodes list
		freeNode->next = entityGroup->usedNodes;
		freeNode->prev = NULL;

		// change the next used node to point at new used node
		if (freeNode->next != NULL) {
			freeNode->next->prev = freeNode;
		}
		entityGroup->usedNodes = freeNode;

		freeNode->free = false;
		return freeNode->index;
	}
} 


