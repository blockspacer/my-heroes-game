#pragma once

extern "C"
{
#include <lua.h>
}

#include <luabind\luabind.hpp>

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

				lua_State* GetGerneralEntityLuaState();
				lua_State* GetRendererEntityLuaState();
				void CloseLuaState(lua_State* luaState);

			private:

				lua_State* CreateAndBindLuaState();
				void LoadGeneralEntityAccess(lua_State* luaState);
				void LoadRendererEntityAccess(lua_State* luaState);

				int m_entityLuaStates{ 0 };

			};
		} // namespace GamePlay
	} // namespace States
} //namespace Heroes

