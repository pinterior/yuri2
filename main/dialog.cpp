#include "stdafx.h"

CMainDialog::CMainDialog() : game_en(GAME_TITLE_EN),
                             game_ja(GAME_TITLE_JA)
{
}

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

namespace {

void ShowWindowInfo(CEdit edit, HWND hwnd) {
   TCHAR buf[96], title[64];

   if (0 == GetWindowText(hwnd, title, _countof(title))) {
      _stprintf_s(buf, _T("%p"), hwnd);
   } else {
      _stprintf_s(buf, _T("%p: %s"), hwnd, title);
   }
   edit.SetWindowText(buf);
}

}

void CMainDialog::OnHook(UINT uNotifyCode, int nID, CWindow wndCtl) {
   CEdit edit_en = GetDlgItem(IDC_GAME_EN);
   CEdit edit_ja = GetDlgItem(IDC_GAME_JA);
   edit_en.SetWindowText(_T(""));
   edit_ja.SetWindowText(_T(""));

   bool en_found = game_en.find();
   bool ja_found = game_ja.find();

   if (en_found) {
      ShowWindowInfo(edit_en, game_en.get_window());
   }
   if (ja_found) {
      ShowWindowInfo(edit_ja, game_ja.get_window());
   }
}
