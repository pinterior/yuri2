#pragma once

#define GAME_TITLE_EN _T("Kindred Spirits on the Roof")
#define GAME_TITLE_JA _T("屋上の百合霊さん")

class game_window {
private:
   const TCHAR *title;
   HWND window;

public:
   game_window(const TCHAR *title);

   HWND get_window() const;
   bool find();
};
