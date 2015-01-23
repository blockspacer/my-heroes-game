// Heroes Game
// Author: Samuel Hall
// Last Commented ? A lot of work

#pragma once

extern "C"
{
#include <lua.h>
}

#include <luabind/luabind.hpp>
#include <luabind/return_reference_to_policy.hpp>

#include "States/GamePlayState/Entities/StatusComponents.h"
#include <States/GamePlayState/Entities/EntityMemory.h>

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{

			class LuaStateLoader final
			{
			public:

				LuaStateLoader();
				~LuaStateLoader();

				lua_State* GetGerneralEntityLuaState(EntityMemory& entityMemory);
				lua_State* GetRendererEntityLuaState();
				void CloseLuaState(lua_State* luaState);

			private:

				lua_State* CreateAndBindLuaState();
				void LoadGeneralEntityAccess(lua_State* luaState, EntityMemory& entityMemory);
				void LoadRendererEntityAccess(lua_State* luaState);

				int m_entityLuaStates{ 0 };

				luabind::object m_luaObject;

			};
		} // namespace GamePlay
	} // namespace States
} //namespace Heroes

