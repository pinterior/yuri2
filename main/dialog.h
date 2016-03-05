#pragma once

#include "game.h"

class CMainDialog : public CDialogImpl<CMainDialog>,
                    public CMessageFilter
{
private:
   game_window game_en;
   game_window game_ja;

public:
   enum { IDD = IDD_MAINDIALOG };

   CMainDialog();

   virtual BOOL PreTranslateMessage(MSG *msg);

   BEGIN_MSG_MAP(CMainDIalog)
      MSG_WM_INITDIALOG(OnInitDialog)
      MSG_WM_CLOSE(OnClose)
      MSG_WM_DESTROY(OnDestroy)

      COMMAND_ID_HANDLER_EX(IDC_HOOK, OnHook)
   END_MSG_MAP()

private:
   BOOL OnInitDialog(CWindow wndFocus, LPARAM lInitParam);
   void OnClose();
   void OnDestroy();

   void OnHook(UINT uNotifyCode, int nID, CWindow wndCtl);
};
