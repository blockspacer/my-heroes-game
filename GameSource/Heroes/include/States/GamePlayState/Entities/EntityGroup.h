using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using FarseerPhysics;
using FarseerPhysics.Dynamics;
using FarseerPhysics.Collision;
using FarseerPhysics.Factories;

// for vector2 ?
using Microsoft.Xna.Framework;

namespace Heroes
{
    // Space for class constants dealing with entities
    enum ENTITY_CONSTANTS {
        MAX_ENTITIES = 500
    }

    // EntityGroups will consist of..
    // mask array (which is used to multiplex systems to entites)
    // arrays of all possible componets that any entity can have,
    // each entity can potential be any game object
    public class EntityGroup
    {
        // constructor
        public EntityGroup()
        {
            // create world with no gravity
            world = new World(new Vector2(0,0));
            
            // create the entity list
            used_entites_ = new bool[(int)ENTITY_CONSTANTS.MAX_ENTITIES];
            free_entities_ = new LinkedList<int>();
            // put the ids of all the entites into the free list
            for (int i = 0; i < (int)ENTITY_CONSTANTS.MAX_ENTITIES; i++)
            {
                free_entities_.AddFirst(i);
                used_entites_[i] = false;
            }

            // The entity data object which make up the game
            entity_systems = new ComponentSystems[(int)ENTITY_CONSTANTS.MAX_ENTITIES];
            entity_health  = new ComponentHealth[(int)ENTITY_CONSTANTS.MAX_ENTITIES];
            entity_damage = new ComponentDamage[(int)ENTITY_CONSTANTS.MAX_ENTITIES];
            entity_resist = new ComponenetResistance[(int)ENTITY_CONSTANTS.MAX_ENTITIES];
            entity_dead = new ComponentDead[(int)ENTITY_CONSTANTS.MAX_ENTITIES];
            entity_physics = new ComponentPhysics[(int)ENTITY_CONSTANTS.MAX_ENTITIES];
            entity_render = new ComponentRender[(int)ENTITY_CONSTANTS.MAX_ENTITIES];


            // TODO ......
        }

        ~EntityGroup()
        {
            // you have to go through entities that the user did not give
            // and make sure everything is removed correctly
            for (int i = 0; i < (int)ENTITY_CONSTANTS.MAX_ENTITIES; i++)
            {
                if (used_entites_[i])
                {
                    CleanAndReleaseEntity(i);
                }
            }
        }

        /*
         * This method attempts to get an id of a free entity
         * returns: the id of the entity or negative one if there
         * are no free entities.
         */
        public int GetEntity()
        {
            // check for entry in free list and return it
            if (free_entities_.Count() > 0)
            {
                // move id from free to used
                int free_entity = free_entities_.First();
                free_entities_.RemoveFirst();
                used_entites_[free_entity] = true;
                return free_entity;
            }

            // negative one means there are no more free entities
            return -1;
        }

        // This methods goes through an entity at an index and
        // removes the information of any non null reference values
        public void CleanAndReleaseEntity(int entity)
        {
            // remove systems by setting them to null
            entity_systems[entity].health = null;
            entity_systems[entity].target = null;
            entity_systems[entity].action = null;
            entity_systems[entity].direction = null;
            entity_systems[entity].movement = null;
            entity_systems[entity].render_update = null;
            entity_systems[entity].renderer = null;

            // health is all values
            // damage is all values
            // resistance is all values

            // last thing to do is put entity id back into the free list
            used_entites_[entity] = false;
            free_entities_.AddFirst(entity);
        }

        public LinkedList<int> QueryWorld(Vector2 min, Vector2 max)
        {
            // query based on the passed vectors
            AABB a;
            a.LowerBound = min;
            a.UpperBound = max;
            List<Fixture> l = world.QueryAABB(ref a);

            // create an empty list on entity references
            LinkedList<int> entities = new LinkedList<int>();

            // go through the list of returned fixtures and add this index into the
            // array into the entities list
            foreach (Fixture f in l) {
                entities.AddFirst((int)f.Body.UserData);
            }

            return entities;
        }

        public void UpdateWorld()
        {
            // ??? Going th assume 30 FPS
            world.Step(0.033333f);
        }

        public World world;

        private bool[] used_entites_;
        private LinkedList<int> free_entities_;

        // The entity data object which make up the game
        public ComponentSystems[] entity_systems;
        public ComponentHealth[] entity_health;
        public ComponentDamage[] entity_damage;
        public ComponenetResistance[] entity_resist;
        public ComponentDead[] entity_dead;
        public ComponentPhysics[] entity_physics;

        public ComponentRender[] entity_render;
        //....
    }
}
