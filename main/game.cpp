#include "stdafx.h"

game_window::game_window(const TCHAR *title) : title(title)
{
}

HWND game_window::get_window() const
{
   return window;
}

bool game_window::find()
{
   window = ::FindWindow(nullptr, title);
   if (!window) return false;

   return true;
}
