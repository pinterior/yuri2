#include "stdafx.h"
#include "../common/hook.h"

#define WM_HOOK_SETTARGET  (WM_APP + 0x100)
#define WM_HOOK_SETMESSAGE (WM_APP + 0x101)
#define WM_HOOK_SETSKIPKEY (WM_APP + 0x102)
#define WM_HOOK_THROUGH    (WM_APP + 0x200)

namespace {

HWND callback = nullptr;
UINT wm_message = 0, wm_params = 0;
int skip_key = 0;
bool client_area_click = false;

LRESULT CALLBACK HookProc(int code, WPARAM wp, LPARAM lp) {
   if (code < 0) {
      return ::CallNextHookEx(nullptr, code, wp, lp);
   }

   if (code == HC_ACTION && wp != PM_NOREMOVE) {
      MSG *msg = reinterpret_cast<MSG *>(lp);

      if (WM_HOOK_THROUGH <= msg->message) {
         msg->message -= WM_HOOK_THROUGH;

      } else if (msg->message == WM_HOOK_SETTARGET) {
         msg->message = WM_NULL;
         callback = reinterpret_cast<HWND>(msg->lParam);

      } else if (msg->message == WM_HOOK_SETMESSAGE) {
         msg->message = WM_NULL;
         wm_message = static_cast<UINT>(msg->wParam);
         wm_params = static_cast<UINT>(msg->lParam);

      } else if (msg->message == WM_HOOK_SETSKIPKEY) {
         msg->message = WM_NULL;
         skip_key = static_cast<int>(msg->wParam);

      } else if (callback && wm_message && wm_params) {
         switch (msg->message) {
         case WM_NCLBUTTONDOWN:
            client_area_click = false;
            break;
         case WM_LBUTTONDOWN:
            client_area_click = true;
            // fall through
         case WM_LBUTTONUP:
         case WM_LBUTTONDBLCLK:
         case WM_RBUTTONDOWN:
         case WM_RBUTTONUP:
         case WM_RBUTTONDBLCLK:
         case WM_MBUTTONDOWN:
         case WM_MBUTTONUP:
         case WM_MBUTTONDBLCLK:
         case WM_MOUSEMOVE:
         case WM_MOUSEWHEEL:
            if (skip_key && (::GetKeyState(skip_key) & 0x8000)) {
               break;
            }
            // fall through
         case WM_KEYDOWN:
         case WM_KEYUP:
            DWORD thread = ::GetWindowThreadProcessId(msg->hwnd, nullptr);
            GUITHREADINFO gti;
            gti.cbSize = sizeof(gti);
            ::GetGUIThreadInfo(thread, &gti);

            if (!client_area_click && gti.hwndCapture) {
               // drag from non client area
            } else {
               ::PostMessage(callback, wm_message, static_cast<WPARAM>(msg->message), 0);
               ::PostMessage(callback, wm_params, msg->wParam, msg->lParam);
            }
            break;
         }
      }
   }
   return ::CallNextHookEx(nullptr, code, wp, lp);
}

}

namespace hook {

HOOK_API HHOOK SetHook(HWND target) {
   DWORD thread = ::GetWindowThreadProcessId(target, nullptr);
   if (thread == 0) { // not documented :-(
      return nullptr;
   }

   return ::SetWindowsHookEx(WH_GETMESSAGE, HookProc, dllModule, thread);
}

HOOK_API bool SetCallbackWindow(HWND hooked, HWND callback) {
   return 0 != ::PostMessage(hooked, WM_HOOK_SETTARGET, 0, reinterpret_cast<LPARAM>(callback));
}

HOOK_API bool SetCallbackMessage(HWND hooked, UINT message, UINT params) {
   return 0 != ::PostMessage(hooked, WM_HOOK_SETMESSAGE, static_cast<WPARAM>(message), static_cast<LPARAM>(params));
}

HOOK_API bool SetSkipKey(HWND hooked, int vKey) {
   return 0 != ::PostMessage(hooked, WM_HOOK_SETSKIPKEY, static_cast<WPARAM>(vKey), 0);
}

HOOK_API bool PostMessageNotHooked(HWND hooked, UINT Msg, WPARAM wParam, LPARAM lParam) {
   return 0 != ::PostMessage(hooked, WM_HOOK_THROUGH + Msg, wParam, lParam);
}

}
