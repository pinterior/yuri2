#ifdef HOOK_EXPORTS
#define HOOK_API __declspec(dllexport)
#else
#define HOOK_API __declspec(dllimport)
#endif

namespace hook {

HOOK_API HHOOK SetHook(HWND target);

HOOK_API bool SetCallbackWindow(HWND hooked, HWND callback);
HOOK_API bool SetCallbackMessage(HWND hooked, UINT message, UINT params);
HOOK_API bool SetSkipKey(HWND hooked, int vKey);
HOOK_API bool PostMessageNotHooked(HWND hooked, UINT Msg, WPARAM wParam, LPARAM lParam);

}
