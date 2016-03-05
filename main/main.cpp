#include "stdafx.h"

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
