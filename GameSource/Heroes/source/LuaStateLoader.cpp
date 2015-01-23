// Heroes Game
// Author: Samuel Hall
// Last Commented ?

// Heavy Development

#include "Engine/Log.h"
#include <SDL_gamecontroller.h>
#include <Box2D/Common/b2Math.h>

#include "States/GamePlayState/Entities/EntityComponentConstants.h"
#include "States/GamePlayState/Entities/ComponentsContainer.h"
#include "States/GamePlayState/Entities/StatusComponents.h"
#include "States/GamePlayState/Entities/HealthComponents.h"
#include "States/GamePlayState/Entities/AIComponents.h"
#include "States/GamePlayState/Entities/ActionComponents.h"
#include "States/GamePlayState/Entities/MovementComponents.h"
#include "States/GamePlayState/LuaStateLoader.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{

			LuaStateLoader::LuaStateLoader() {}
			LuaStateLoader::~LuaStateLoader() {}

			lua_State* LuaStateLoader::GetRendererEntityLuaState()
			{
				lua_State* luaState = CreateAndBindLuaState();
				//LoadGeneralEntityAccess(luaState);
				//LoadRendererEntityAccess(luaState);
				return luaState;
			}

			lua_State* LuaStateLoader::GetGerneralEntityLuaState(EntityMemory& entityMemory)
			{
				lua_State* luaState = CreateAndBindLuaState();
				LoadGeneralEntityAccess(luaState, entityMemory);
				return luaState;
			}

			void LuaStateLoader::CloseLuaState(lua_State* luaState)
			{
				g_assert(luaState != nullptr);
				lua_close(luaState);
			}

			lua_State* LuaStateLoader::CreateAndBindLuaState()
			{
				lua_State *luaState = luaL_newstate();
				g_assert(luaState != nullptr);
				luabind::open(luaState);
				return luaState;
			}

			void LuaStateLoader::LoadGeneralEntityAccess(lua_State* luaState, EntityMemory& entityMemory)
			{

				try {

				luabind::module(luaState)[
					luabind::def("SDL_GameControllerGetButton", &SDL_GameControllerGetAxis),
						//luabind::def("SDL_GameControllerGetButton", &print_hello)
						//luabind::def("SDL_GameControllerGetButton", &print_hello)

					// b2Vec2 class
					luabind::class_<b2Vec2>("B2Vec2")
						.def("Length", &b2Vec2::Length)
						.def("Normalize", &b2Vec2::Normalize)
						.def_readwrite("x", &b2Vec2::x)
						.def_readwrite("x", &b2Vec2::y),

					// EntityComponents

					//enum EntityCollisionMasks
					//{
					//	ALLY_BODY = 0x0010,
					//	ALLY_SENSOR = 0x0020,
					//	ENEMY_BODY = 0x0004,
					//	ENEMY_SENSOR = 0x0008,
					//	ENVIRONMENT_BODY = 0x0001,
					//	ENVIRONMENT_SENSOR = 0x0002
					//};
					luabind::class_<EntityCollisionMasks>("EntityCollisionMasks")
					.enum_("Constants")
					[
						luabind::value("ALLY_BODY", EntityCollisionMasks::ALLY_BODY),
						luabind::value("ALLY_SENSOR", EntityCollisionMasks::ALLY_SENSOR),
						luabind::value("ENEMY_BODY", EntityCollisionMasks::ENEMY_BODY),
						luabind::value("ENEMY_SENSOR", EntityCollisionMasks::ENEMY_SENSOR),
						luabind::value("ENVIRONMENT_BODY", EntityCollisionMasks::ENVIRONMENT_BODY),
						luabind::value("ENVIRONMENT_SENSOR", EntityCollisionMasks::ENVIRONMENT_SENSOR)
					],

					//enum EntityCollisionCategories
					//{
					//	ALLY_BODY_COL = ALLY_BODY | ENEMY_BODY | ENEMY_SENSOR | ENVIRONMENT_BODY | ENVIRONMENT_SENSOR,
					//	ALLY_SENSOR_COL = ENEMY_BODY,
					//	ENEMY_BODY_COL = ALLY_BODY | ALLY_SENSOR | ENEMY_BODY | ENVIRONMENT_BODY | ENVIRONMENT_SENSOR,
					//	ENEMY_SENSOR_COL = ALLY_BODY,
					//	ENVIRONMENT_BODY_COL = ALLY_BODY | ENEMY_BODY | ENVIRONMENT_BODY,
					//	ENVIRONMENT_SENSOR_COL = ALLY_BODY | ENEMY_BODY
					//};
					luabind::class_<EntityCollisionCategories>("EntityCollisionCategories")
					.enum_("Constants")
					[
						luabind::value("ALLY_BODY_COL", EntityCollisionCategories::ALLY_BODY_COL),
						luabind::value("ALLY_SENSOR_COL", EntityCollisionCategories::ALLY_SENSOR_COL),
						luabind::value("ENEMY_BODY_COL", EntityCollisionCategories::ENEMY_BODY_COL),
						luabind::value("ENEMY_SENSOR_COL", EntityCollisionCategories::ENEMY_SENSOR_COL),
						luabind::value("ENVIRONMENT_BODY_COL", EntityCollisionCategories::ENVIRONMENT_BODY_COL),
						luabind::value("ENVIRONMENT_SENSOR_COL", EntityCollisionCategories::ENVIRONMENT_SENSOR_COL)
					],

					//enum ActionType
					//{
					//	NO_ACTION,
					//	CLOSE_COMBAT
					//};
					luabind::class_<BusyStatusType>("BusyStatusType")
					.enum_("Constants")
					[
						luabind::value("NONE", BusyStatusType::NONE),
						luabind::value("STUNNED", BusyStatusType::STUNNED),
						luabind::value("BASIC_ATTACK", BusyStatusType::BASIC_ATTACK),
						luabind::value("SPECIAL_ATTACK", BusyStatusType::SPECIAL_ATTACK)
					],

					//enum MovementType
					//{
					//	NO_MOVEMENT,
					//	MOVING
					//};
					luabind::class_<IdleStatusType>("IdleStatusType")
					.enum_("Constants")
					[
						luabind::value("STANDING", IdleStatusType::STANDING),
						luabind::value("MOVING", IdleStatusType::MOVING)
					],

					//enum StatusType
					//{
					//	ALIVE,
					//	DEAD
					//};
					/*luabind::class_<ActiveStatusType>("ActiveStatusType")
					.enum_("Constants")
					[
						luabind::value("ALIVE", ActiveStatusType::ACTIVE),
						luabind::value("DEAD", ActiveStatusType::INACTIVE),
						luabind::value("NA", ActiveStatusType::TOMBSTONE)
					],*/

					//struct DynamicStatusComponent
					//{
					//	ActionType m_action{ ActionType::NO_ACTION }; // whether entity is actively doing something (busy)
					//	MovementType m_movement{ MovementType::NO_MOVEMENT };
					//	StatusType m_status{ StatusType::DEAD }; // whether entity is dead
					//	int m_deathTimer{ -1 }; // amount until this entity should be cleaned up
					//	StaticEntityIDType m_staticEntityID{ -1 };
					//};
					/*luabind::class_<StatusComponents>("StatusComponentsType")
					.def("GetAction_D", &StatusComponents::GetAction_D)
					.def("SetAction_S", &StatusComponents::SetAction_D)
					.def("GetMovement_D", &StatusComponents::GetMovement_D)
					.def("SetMovement_D", &StatusComponents::SetMovement_D)
					.def("GetStatus_D", &StatusComponents::GetStatus_D)
					.def("SetStatus_D", &StatusComponents::SetStatus_D)
					.def("GetDeathTimer_D", &StatusComponents::GetDeathTimer_D)
					.def("SetDeathTimer_D", &StatusComponents::SetDeathTimer_D)
					.def("GetStaticEntityID_D", &StatusComponents::GetStaticEntityID_D)
					.def("SetStaticEntityID_D", &StatusComponents::SetStaticEntityID_D)
					.def("GetDeathTimer_S", &StatusComponents::GetDeathTimer_S),*/

					luabind::class_<HealthComponents>("HealthComponentsType")
					.def("GetDirectDamageSource_D", &HealthComponents::GetDirectDamageSource_D)
					.def("SetDirectDamageSource_D", &HealthComponents::SetDirectDamageSource_D)
					.def("GetDirectDamage_D", &HealthComponents::GetDirectDamage_D)
					.def("SetDirectDamage_D", &HealthComponents::SetDirectDamage_D)
					.def("GetNormalHealth_D", &HealthComponents::GetNormalHealth_D)
					.def("SetNormalHealth_D", &HealthComponents::SetNormalHealth_D)
					.def("GetNormalHealth_S", &HealthComponents::GetNormalHealth_S),

					luabind::class_<AIComponents>("AIComponentsType")
					.def("GetTarget_D", &AIComponents::GetTarget_D),

					luabind::class_<ActionComponents>("ActionComponentsType")
					.def("GetNormalAttackDamage_S", &ActionComponents::GetNormalAttackDamage_S)

				];

				// bind all the components to global space in luaState
				//luabind::globals(luaState)["StatusComponents"] = &entityMemory.m_statusComponents;
				luabind::globals(luaState)["HealthComponents"] = &entityMemory.m_healthComponents;
				luabind::globals(luaState)["AIComponents"] = &entityMemory.m_AIComponents;
				luabind::globals(luaState)["ActionComponents"] = &entityMemory.m_actionComponents;
				/*luabind::globals(luaState)["StaticStatusComponents"] = entityMemory.m_staticStatusComponents;

				luabind::globals(luaState)["DynamicHealthComponents"] = entityMemory.m_dynamicHealthComponents;
				luabind::globals(luaState)["StaticHealthComponents"] = entityMemory.m_staticHealthComponents;

				luabind::globals(luaState)["DynamicAIComponents"] = entityMemory.m_dynamicAIComponents;
				luabind::globals(luaState)["StaticAIComponents"] = entityMemory.m_staticAIComponents;

				luabind::globals(luaState)["DynamicActionComponents"] = entityMemory.m_dynamicActionComponents;
				luabind::globals(luaState)["StaticActionComponents"] = entityMemory.m_staticActionComponents;

				luabind::globals(luaState)["DynamicDirectionComponents"] = entityMemory.m_dynamicDirectionComponents;
				luabind::globals(luaState)["StaticDirectionComponents"] = entityMemory.m_staticDirectionComponents;

				luabind::globals(luaState)["DynamicMovementComponents"] = entityMemory.m_dynamicMovementComponents;
				luabind::globals(luaState)["StaticMovementComponents"] = entityMemory.m_staticMovementComponents;*/
				
				}
				catch (const std::exception &TheError) {
					g_assert(false);
				}
			}

			void LuaStateLoader::LoadRendererEntityAccess(lua_State* luaState)
			{
				// the specifc sdl rendering componenets for lua scripts
			}

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes

