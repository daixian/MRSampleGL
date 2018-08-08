
#define WIN32_LEAN_AND_MEAN             // 从Windows标头中排除很少使用的东西

#include "stdafx.h"
#include "oglMRDemo.h"
#include "./Common/Log.h"
#include <windows.h>
#include <commctrl.h>                   // common controls
#include "./Base/Window.h"
#include "./Base/DialogWindow.h"
#include "./Controller/ControllerMain.h"
#include "./Controller/ControllerGL.h"
#include "./Controller/ControllerFormGL.h"
#include "./Model/ModelGL.h"
#include "./View/ViewGL.h"
#include "./View/ViewFormGL.h"
#include "resource.h"


// 函数声明: 
int mainMessageLoop(HACCEL hAccelTable = 0);



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    // register Trackbar control from comctl32.dll before creating windows
    INITCOMMONCONTROLSEX commonCtrls;
    commonCtrls.dwSize = sizeof(commonCtrls);
    commonCtrls.dwICC = ICC_STANDARD_CLASSES | ICC_BAR_CLASSES | ICC_LINK_CLASS | ICC_UPDOWN_CLASS;
    ::InitCommonControlsEx(&commonCtrls);

    RECT rect;
    DWORD style;
    DWORD styleEx;

    Win::Log::getInstance().setMode(Win::LOG_MODE_BOTH);
    Win::log("Start!");

    // create model and view components for controller
    ModelGL modelGL;
    Win::ViewGL viewGL;
    Win::ViewFormGL viewFormGL(&modelGL);

    //创建主窗口
    Win::ControllerMain mainCtrl(&modelGL);
    Win::Window mainWin(hInstance, L"OpenGL MR Demo", 0, &mainCtrl);
    mainWin.setWindowStyleEx(WS_EX_WINDOWEDGE);
    if (mainWin.create())
        Win::log("Main window is created.");
    else
        Win::log("[ERROR] Failed to create main window.");

    //@@ MS ArticleID: 272222
    //当窗口调整得更大时，会出现剪裁错误。
    //最初创建一个最大大小的窗口，以避免此剪切错误。
    //后续的SetWindowPos()调用来调整窗口尺寸的大小造成的剪辑问题。
    int fullWidth = ::GetSystemMetrics(SM_CXSCREEN);    // primary display only
    int fullHeight = ::GetSystemMetrics(SM_CYSCREEN);
    Win::log("Display Resolution: %dx%d", fullWidth, fullHeight);

    //创建OpenGL渲染窗口glWin，把它作为mainWin窗口的子窗口
    Win::ControllerGL glCtrl(&modelGL, &viewGL);
    Win::Window glWin(hInstance, L"WindowGL", mainWin.getHandle(), &glCtrl);
    glWin.setClassStyle(CS_OWNDC);
    glWin.setWindowStyle(WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
    // remove client edge of glWin
    styleEx = (DWORD)::GetWindowLongPtr(glWin.getHandle(), GWL_EXSTYLE);
    glWin.setWindowStyleEx(styleEx & ~WS_EX_CLIENTEDGE);
    glWin.setWidth(fullWidth);
    glWin.setHeight(fullHeight);
    if (glWin.create())
        Win::log("OpenGL child window is created.");
    else
        Win::log("[ERROR] Failed to create OpenGL window.");

     //create a child dialog box, glDialog contains all controls
    Win::ControllerFormGL formCtrl(&modelGL, &viewFormGL);
    Win::DialogWindow glDialog(hInstance, IDD_FORMVIEW, mainWin.getHandle(), &formCtrl);
    glDialog.setWidth(1000);    // temporary width and height
    glDialog.setHeight(300);
    if (glDialog.create())
        Win::log("OpenGL form dialog is created.");
    else
        Win::log("[ERROR] Failed to create OpenGL form dialog.");

    // send window handles to mainCtrl, so we can resize the child windows when main window resized
    mainCtrl.setGLHandle(glWin.getHandle());
    mainCtrl.setFormHandle(glDialog.getHandle());

    formCtrl.setMianWinHandle(mainWin.getHandle());

    // place windows in the right position ================
    // get the dim of glDialog
    ::GetWindowRect(glDialog.getHandle(), &rect);
    int dialogWidth = rect.right - rect.left;
    int dialogHeight = rect.bottom - rect.top;
    Win::log(L"Form dialog dimension: %d x %d", dialogWidth, dialogHeight);
    if (dialogWidth % 2 != 0)
        dialogWidth++;     // make it even

    // compute dim of glWin
    int glWidth = dialogWidth;
    int glHeight = glWidth / 2; // half of width
    ::SetWindowPos(glWin.getHandle(), 0, 0, 0, glWidth, glHeight, SWP_NOZORDER);
    Win::log(L"GL window dimension: %d x %d", glWidth, glHeight);

    // place the glDialog at the bottom of the opengl rendering window
    ::SetWindowPos(glDialog.getHandle(), 0, 0, glHeight, dialogWidth, dialogHeight, SWP_NOZORDER);

    // set dim of mainWin
    rect.left = 0;
    rect.right = glWidth;
    rect.top = 0;
    rect.bottom = glHeight + dialogHeight;
    style = (DWORD)::GetWindowLongPtr(mainWin.getHandle(), GWL_STYLE);
    styleEx = (DWORD)::GetWindowLongPtr(mainWin.getHandle(), GWL_EXSTYLE);
    ::AdjustWindowRectEx(&rect, style, FALSE, styleEx);
    ::SetWindowPos(mainWin.getHandle(), 0, 0, 0, (rect.right - rect.left), (rect.bottom - rect.top), SWP_NOZORDER);

    // show all windows
    glWin.show();
    glDialog.show();
    mainWin.show();

    // 主消息循环
    int exitCode;
    HACCEL hAccelTable = 0;
    //hAccelTable = ::LoadAccelerators(hInst, MAKEINTRESOURCE(ID_ACCEL));
    exitCode = mainMessageLoop(hAccelTable);

    Win::log("Application is terminated.");
    return exitCode;
}


///////////////////////////////////////////////////////////////////////////////
// main message loop
///////////////////////////////////////////////////////////////////////////////
int mainMessageLoop(HACCEL hAccelTable)
{
    HWND activeHandle;
    MSG msg;

    while (::GetMessage(&msg, 0, 0, 0) > 0)  // loop until WM_QUIT(0) received
    {
        // determine the activated window is dialog box
        // skip if messages are for the dialog windows
        activeHandle = GetActiveWindow();
        if (::GetWindowLongPtr(activeHandle, GWL_EXSTYLE) & WS_EX_CONTROLPARENT) // WS_EX_CONTROLPARENT is automatically added by CreateDialogBox()
        {
            if (::IsDialogMessage(activeHandle, &msg))
                continue;   // message handled, back to while-loop
        }

        // now, handle window messages
        if (!::TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;                 // return nExitCode of PostQuitMessage()
}
