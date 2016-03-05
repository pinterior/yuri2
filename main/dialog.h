#pragma once

#include "game.h"
#include "message.h"

class CMainDialog : public CDialogImpl<CMainDialog>,
                    public CMessageFilter
{
private:
   enum : UINT {
      WM_MESSAGE_EN = WM_APP,
      WM_PARAMS_EN,
      WM_MESSAGE_JA,
      WM_PARAMS_JA,
   };
   enum : int { SKIP_KEY = 'S' };

   game_window game_en;
   game_window game_ja;
   message_flow en_to_ja;
   message_flow ja_to_en;

public:
   enum { IDD = IDD_MAINDIALOG };

   CMainDialog();

   virtual BOOL PreTranslateMessage(MSG *msg);

   BEGIN_MSG_MAP(CMainDIalog)
      MSG_WM_INITDIALOG(OnInitDialog)
      MSG_WM_CLOSE(OnClose)
      MSG_WM_DESTROY(OnDestroy)

      COMMAND_ID_HANDLER_EX(IDC_HOOK, OnHook)
      MESSAGE_HANDLER_EX(WM_MESSAGE_EN, OnMessageEn)
      MESSAGE_HANDLER_EX(WM_PARAMS_EN, OnParamsEn)
      MESSAGE_HANDLER_EX(WM_MESSAGE_JA, OnMessageJa)
      MESSAGE_HANDLER_EX(WM_PARAMS_JA, OnParamsJa)
   END_MSG_MAP()

private:
   BOOL OnInitDialog(CWindow wndFocus, LPARAM lInitParam);
   void OnClose();
   void OnDestroy();

   void OnHook(UINT uNotifyCode, int nID, CWindow wndCtl);
   LRESULT OnMessageEn(UINT uMsg, WPARAM wParam, LPARAM lParam);
   LRESULT OnParamsEn(UINT uMsg, WPARAM wParam, LPARAM lParam);
   LRESULT OnMessageJa(UINT uMsg, WPARAM wParam, LPARAM lParam);
   LRESULT OnParamsJa(UINT uMsg, WPARAM wParam, LPARAM lParam);
};
