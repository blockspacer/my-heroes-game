#include "stdafx.h"
#include "EntityManager.h"

// actually definition of the list node
typedef struct {
	EntityListNode* next;
	bool free;
} EntityListNode;

EntityManager::EntityManager() {
	// allocate space for the EntityNodeList, enough to store all the entities
	entity_node_array_ = new EntityListNode[MAX_ENTITIES];

	// construct the list starting with entity zero
	for (int i = 0; i < MAX_ENTITIES - 1; i++) {
		entity_node_array_[i].next = i + 1;
		entity_node_array_[i].free = true;
	}

	// the last EntityListNode points to NULL
	entity_node_array_[MAX_ENTITIES - 1].next = NULL;
	entity_node_array_[MAX_ENTITIES - 1].free = true;

	// point front at the first EntityListNode
	front_ = entity_node_array_;
}

EntityManager::~EntityManager() {

}

EntityGroupPtr EntityManager::GetEntityGroupPtr() {
	return entity_group_ptr_;
}

EntityID EntityManager::GetFreeEntity() {

}

bool EntityManager::ReleaseEntity(EntityID) {

}