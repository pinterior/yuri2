#include "stdafx.h"

void hook_deleter::operator()(HHOOK hook) {
   ::UnhookWindowsHookEx(hook);
}

const game_params game_params::en = {
   _T("Kindred Spirits on the Roof"),
   { 712, 466, 747, 573 }
};
const game_params game_params::ja = {
   _T("屋上の百合霊さん"),
   { 672, 466, 707, 573 }
};

game_window::game_window(game_params params) : params{ params }
{
}

HWND game_window::get_window() const
{
   return window;
}

bool game_window::find()
{
   window = ::FindWindow(nullptr, params.title);
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

void game_window::translate(const game_window &other, UINT &message, WPARAM &wparam, LPARAM &lparam) const {
   if (WM_MOUSEFIRST <= message && message <= WM_MOUSELAST) {
      CPoint p{ static_cast<DWORD>(lparam) };
      const CRect &s = params.control;
      const CRect &d = other.params.control;
      if (!s.IsRectNull() && !d.IsRectNull() && s.PtInRect(p)) {
         p = p - s.TopLeft() + d.TopLeft();
         lparam = MAKELPARAM(p.x, p.y);
      }
   }
}

BOOL game_window::post_message(UINT message, WPARAM wparam, LPARAM lparam)
{
   return hook::PostMessageNotHooked(window, message, wparam, lparam);
}
