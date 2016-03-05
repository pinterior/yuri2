#pragma once

class CMainDialog : public CDialogImpl<CMainDialog>,
                    public CMessageFilter
{
public:
   enum { IDD = IDD_MAINDIALOG };

   virtual BOOL PreTranslateMessage(MSG *msg);

   BEGIN_MSG_MAP(CMainDIalog)
      MSG_WM_INITDIALOG(OnInitDialog)
      MSG_WM_CLOSE(OnClose)
      MSG_WM_DESTROY(OnDestroy)
   END_MSG_MAP()

private:
   BOOL OnInitDialog(CWindow wndFocus, LPARAM lInitParam);
   void OnClose();
   void OnDestroy();
};
