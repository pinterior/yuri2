#include "stdafx.h"

BOOL CMainDialog::PreTranslateMessage(MSG *msg)
{
   return IsDialogMessage(msg);
}

BOOL CMainDialog::OnInitDialog(CWindow wndFocus, LPARAM lInitParam)
{
   CenterWindow();

   auto loop = appModule.GetMessageLoop();
   loop->AddMessageFilter(this);

   return TRUE;
}

void CMainDialog::OnClose()
{
   DestroyWindow();
   ::PostQuitMessage(0);
}

void CMainDialog::OnDestroy()
{
   auto loop = appModule.GetMessageLoop();
   loop->RemoveMessageFilter(this);
}
