#pragma once

struct hook_deleter {
   void operator()(HHOOK hook);
};

typedef std::unique_ptr<std::remove_pointer<HHOOK>::type, hook_deleter> unique_hook;

struct game_params {
   const TCHAR *title;
   CRect control;

   static const game_params en;
   static const game_params ja;
};


class game_window {
private:
   const game_params params;
   HWND window;
   unique_hook hook;

public:
   game_window(game_params params);

   HWND get_window() const;
   bool find();
   bool set_hook(HWND callback, UINT message, UINT params, int skip_key);
   void unset_hook();
   void translate(const game_window &other, UINT &message, WPARAM &wparam, LPARAM &lparam) const;
   BOOL post_message(UINT message, WPARAM wparam, LPARAM lparam);
};
