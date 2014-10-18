using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

// for drawing
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;

namespace Heroes
{
    /*
     * This class represents a active level in the game, it can be
     * updated, drawn, loaded.
     */
    class LevelManager
    {
        public LevelManager()
        {
            // just set everything to null
            camera_ = null;
            entities_ = null;
            tile_map_ = null;
            entity_system_manager_ = null;

        }

        /* TODO figure out level loading files */
        public void LoadLevel(Camera camera, TileMap tile_map, EntitySystemManager entity_system_manager)
        {
            if (camera == null || tile_map == null || entity_system_manager == null)
            {
                // TODO errors
            }
            camera_ = camera;
            entities_ = new LinkedList<int>();
            tile_map_ = tile_map;
            entity_system_manager_ = entity_system_manager; 
        }


        public void UpdateLevel()
        {
            if (camera_ != null)
            {
                // use the camera to get the entities that should be updated
                entities_ = entity_system_manager_.QueryEntityWorld(camera_);

                // update camera based on location of main entity
                Vector2 camera_dummy_location = new Vector2(0,0);
                //camera_.Update(entity_system_manager_.GetMainEntityLocation());
                camera_.Update(camera_dummy_location);

                // update the entities
                entity_system_manager_.UpdateEntities(entities_, camera_);

                // TODO update the hud
            }
        }

        /*
         * This method draws what state this level currently represents
         */
        public void DrawLevel(SpriteBatch sprite_batch)
        {
            if (camera_ != null)
            {
                tile_map_.DrawTileMap(sprite_batch, camera_.GetDisplayCoordinate());
                entity_system_manager_.DrawEntities(sprite_batch, entities_);
                // draw hud
            }
        }

        private Camera camera_;
        private LinkedList<int> entities_;
        private TileMap tile_map_;
        private EntitySystemManager entity_system_manager_;
    }
}
