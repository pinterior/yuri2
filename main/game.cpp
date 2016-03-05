#include "stdafx.h"

void hook_deleter::operator()(HHOOK hook) {
   ::UnhookWindowsHookEx(hook);
}

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

bool game_window::set_hook(HWND callback, UINT message, UINT params, int skip_key)
{
   hook.reset();

   if (!window) {
      return false;
   }

   unique_hook h{ hook::SetHook(window) };
   if (!h) {
      return false;
   }

   if (!hook::SetCallbackWindow(window, callback)) return false;
   if (!hook::SetCallbackMessage(window, message, params)) return false;
   if (!hook::SetSkipKey(window, skip_key)) return false;

   hook = std::move(h);
   return true;
}

void game_window::unset_hook()
{
   hook.reset();
}
