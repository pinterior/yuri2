#pragma once

struct hook_deleter {
   void operator()(HHOOK hook);
};

typedef std::unique_ptr<std::remove_pointer<HHOOK>::type, hook_deleter> unique_hook;

#define GAME_TITLE_EN _T("Kindred Spirits on the Roof")
#define GAME_TITLE_JA _T("屋上の百合霊さん")

class game_window {
private:
   const TCHAR *title;
   HWND window;
   unique_hook hook;

public:
   game_window(const TCHAR *title);

   HWND get_window() const;
   bool find();
   bool set_hook(HWND callback, UINT message, UINT params, int skip_key);
   void unset_hook();
};
