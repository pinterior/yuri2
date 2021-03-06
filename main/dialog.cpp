#include "stdafx.h"

CMainDialog::CMainDialog() : game_en{ game_params::en },
                             game_ja{ game_params::ja },
                             en_to_ja{ game_en, game_ja },
                             ja_to_en{ game_ja, game_en }
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
   game_en.unset_hook();
   game_ja.unset_hook();

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

   if (!en_found || !ja_found) {
      return;
   }

   bool en_hooked = game_en.set_hook(*this, WM_MESSAGE_EN, WM_PARAMS_EN, SKIP_KEY);
   bool ja_hooked = game_ja.set_hook(*this, WM_MESSAGE_JA, WM_PARAMS_JA, SKIP_KEY);

   if (!en_hooked || !ja_hooked) {
      game_en.unset_hook();
      game_ja.unset_hook();
   }
}

LRESULT CMainDialog::OnMessageEn(UINT uMsg, WPARAM wParam, LPARAM lParam) {
   en_to_ja.clear();
   en_to_ja.message(static_cast<UINT>(wParam));
   return 0;
}

LRESULT CMainDialog::OnParamsEn(UINT uMsg, WPARAM wParam, LPARAM lParam) {
   en_to_ja.params(wParam, lParam);
   en_to_ja.post();
   return 0;
}

LRESULT CMainDialog::OnMessageJa(UINT uMsg, WPARAM wParam, LPARAM lParam) {
   ja_to_en.clear();
   ja_to_en.message(static_cast<UINT>(wParam));
   return 0;
}

LRESULT CMainDialog::OnParamsJa(UINT uMsg, WPARAM wParam, LPARAM lParam) {
   ja_to_en.params(wParam, lParam);
   ja_to_en.post();
   return 0;
}
