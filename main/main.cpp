#include "stdafx.h"

#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

CAppModule appModule;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR lpCmdLine,
                       int nCmdShow)
{
   appModule.Init(nullptr, hInstance);

   CMessageLoop loop;
   appModule.AddMessageLoop(&loop);

   CMainDialog dialog;
   dialog.Create(NULL);
   dialog.ShowWindow(nCmdShow);

   int ret = loop.Run();

   appModule.RemoveMessageLoop();
   appModule.Term();

   return ret;
}
