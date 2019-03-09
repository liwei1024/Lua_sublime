#include <stdio.h>
#include <windows.h>
#include "../src/lua.h"
lua_State *g_L;

int findWindow(lua_State *m_L)
{
	LPCSTR lpClassName = lua_tostring(m_L, 1) ? lua_tostring(m_L, 1) : "";
	LPCSTR lpWindowName = lua_tostring(m_L, 2) ? lua_tostring(m_L, 2) : "";
	HWND hWnd = FindWindowA(lpClassName, lpWindowName);
	printf("%s %s %p\n", lpClassName, lpWindowName, hWnd);

	if (hWnd == NULL)
	{
		lua_pushnil(m_L);
	}
	else {
		lua_pushinteger(m_L, (lua_Integer)hWnd);
	}
	return 1;
}
int getForegroundWindow(lua_State* m_L)
{
	lua_pushinteger(m_L, (lua_Integer)GetForegroundWindow());
	return 1;
}
int setForegroundWindow(lua_State* m_L)
{
	lua_pushboolean(m_L, SetForegroundWindow((HWND)lua_tointeger(m_L, 1)));
	return 1;
}
int setWindowLong(lua_State* m_L)
{
	HWND hWnd = (HWND)lua_tointeger(m_L, 1);
	int index = (int)lua_tointeger(m_L, 2);
	LONG newLong = (LONG)lua_tointeger(m_L, 3);
	lua_pushinteger(m_L, SetWindowLongW(hWnd, index, newLong));
	return 1;
}
int outputDebugString(lua_State* m_L)
{
	OutputDebugStringA(lua_tostring(m_L, 1));
	return 0;
}
int messageBox(lua_State* m_L)
{
	MessageBoxA(NULL, lua_tostring(m_L, 1), "CA", MB_OK);
	return 0;
}
int sendMessage(lua_State* m_L)
{
	HWND hWnd = (HWND)lua_tointeger(m_L, 1);
	UINT uMsg = (UINT)lua_tointeger(m_L, 2);
	WPARAM wParam = (WPARAM)lua_tointeger(m_L, 3);
	LPARAM lParam = (LPARAM)lua_tointeger(m_L, 4);
	lua_pushinteger(m_L, (lua_Integer)SendMessageW(hWnd, uMsg, wParam, lParam));
	return 1;
}
int sleep(lua_State* m_L)
{
	Sleep((DWORD)lua_tointeger(m_L, 1));
	return 0;
}
int getWindowRect(lua_State* m_L)
{
	RECT rect;
	HWND hWnd = (HWND)lua_tointeger(m_L, 1);
	GetWindowRect(hWnd, &rect);
	lua_newtable(m_L);
	lua_pushstring(m_L, "bottom");
	lua_pushinteger(m_L, rect.bottom);
	lua_settable(m_L, -3);//弹出key,value，并设置到table里面去
	lua_pushstring(m_L, "left");
	lua_pushinteger(m_L, rect.left);
	lua_settable(m_L, -3);//弹出key,value，并设置到table里面去
	lua_pushstring(m_L, "top");
	lua_pushinteger(m_L, rect.top);
	lua_settable(m_L, -3);//弹出key,value，并设置到table里面去
	lua_pushstring(m_L, "right");
	lua_pushinteger(m_L, rect.right);
	lua_settable(m_L, -3);//弹出key,value，并设置到table里面去
	return 1;
}


void lua_extend()
{
	lua_register(g_L, "findWindow", findWindow);
	lua_register(g_L, "getForegroundWindow", getForegroundWindow);
	lua_register(g_L, "setForegroundWindow", setForegroundWindow);
	lua_register(g_L, "setWindowLong", setWindowLong);
	lua_register(g_L, "outputDebugString", outputDebugString);
	lua_register(g_L, "messageBox", messageBox);
	lua_register(g_L, "sleep", sleep);
	lua_register(g_L, "getWindowRect", getWindowRect);
}