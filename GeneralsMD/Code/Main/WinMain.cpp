/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: WinMain.cpp //////////////////////////////////////////////////////////
//
// Entry point for game application - 游戏应用的入口点
//
// Author: Colin Day, April 2001
//
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES - 系统包括 ////////////////////////////////////////////////////////////
#define WIN32_LEAN_AND_MEAN  // only bare bones windows stuff wanted - 只需要最基本的Windows操作系统
#include <windows.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <eh.h>
#include <ole2.h>
#include <dbt.h>

// USER INCLUDES - 用户包括 //////////////////////////////////////////////////////////////
#include "WinMain.h"
#include "Lib/BaseType.h"
#include "Common/CommandLine.h"
#include "Common/CriticalSection.h"
#include "Common/GlobalData.h"
#include "Common/GameEngine.h"
#include "Common/GameSounds.h"
#include "Common/Debug.h"
#include "Common/GameMemory.h"
#include "Common/StackDump.h"
#include "Common/MessageStream.h"
#include "Common/Registry.h"
#include "Common/Team.h"
#include "GameClient/ClientInstance.h"
#include "GameClient/InGameUI.h"
#include "GameClient/GameClient.h"
#include "GameLogic/GameLogic.h"  ///< @todo for demo, remove
#include "GameClient/Mouse.h"
#include "GameClient/IMEManager.h"
#include "Win32Device/GameClient/Win32Mouse.h"
#include "Win32Device/Common/Win32GameEngine.h"
#include "Common/version.h"
#include "BuildVersion.h"
#include "GeneratedVersion.h"
#include "resource.h"

#include <rts/profile.h>


// GLOBALS - 全局变量 ////////////////////////////////////////////////////////////////////
HINSTANCE ApplicationHInstance = NULL;  ///< our application instance - 应用程序实例
HWND ApplicationHWnd = NULL;  ///< our application window handle - 应用程序窗口句柄
Win32Mouse *TheWin32Mouse= NULL;  ///< for the WndProc() only - 仅适用于WndProc（）
DWORD TheMessageTime = 0;	///< For getting the time that a message was posted from Windows. - 用于获取消息从Windows发布的时间。

const Char *g_strFile = "data\\Generals.str";
const Char *g_csfFile = "data\\%s\\Generals.csf";
const char *gAppPrefix = ""; /// So WB can have a different debug log file name. - 因此，WB可以使用不同的调试日志文件名。

static Bool gInitializing = false;
static Bool gDoPaint = true;
static Bool isWinMainActive = false;

static HBITMAP gLoadScreenBitmap = NULL;

//#define DEBUG_WINDOWS_MESSAGES 通过switch-case结构将数百个Windows消息ID映射为对应的常量名称，极大简化了窗口消息处理的调试工作

#ifdef DEBUG_WINDOWS_MESSAGES
static const char *messageToString(unsigned int message)
{
	static char name[32];

	switch (message)
	{
	case WM_NULL: return "WM_NULL";
	case WM_CREATE: return  "WM_CREATE";
	case WM_DESTROY: return  "WM_DESTROY";
	case WM_MOVE: return  "WM_MOVE";
	case WM_SIZE: return  "WM_SIZE";
	case WM_ACTIVATE: return  "WM_ACTIVATE";
	case WM_SETFOCUS: return  "WM_SETFOCUS";
	case WM_KILLFOCUS: return  "WM_KILLFOCUS";
	case WM_ENABLE: return  "WM_ENABLE";
	case WM_SETREDRAW: return  "WM_SETREDRAW";
	case WM_SETTEXT: return  "WM_SETTEXT";
	case WM_GETTEXT: return  "WM_GETTEXT";
	case WM_GETTEXTLENGTH: return  "WM_GETTEXTLENGTH";
	case WM_PAINT: return  "WM_PAINT";
	case WM_CLOSE: return  "WM_CLOSE";
	case WM_QUERYENDSESSION: return  "WM_QUERYENDSESSION";
	case WM_QUIT: return  "WM_QUIT";
	case WM_QUERYOPEN: return  "WM_QUERYOPEN";
	case WM_ERASEBKGND: return  "WM_ERASEBKGND";
	case WM_SYSCOLORCHANGE: return  "WM_SYSCOLORCHANGE";
	case WM_ENDSESSION: return  "WM_ENDSESSION";
	case WM_SHOWWINDOW: return  "WM_SHOWWINDOW";
	case WM_WININICHANGE: return "WM_WININICHANGE";
	case WM_DEVMODECHANGE: return  "WM_DEVMODECHANGE";
	case WM_ACTIVATEAPP: return  "WM_ACTIVATEAPP";
	case WM_FONTCHANGE: return  "WM_FONTCHANGE";
	case WM_TIMECHANGE: return  "WM_TIMECHANGE";
	case WM_CANCELMODE: return  "WM_CANCELMODE";
	case WM_SETCURSOR: return  "WM_SETCURSOR";
	case WM_MOUSEACTIVATE: return  "WM_MOUSEACTIVATE";
	case WM_CHILDACTIVATE: return  "WM_CHILDACTIVATE";
	case WM_QUEUESYNC: return  "WM_QUEUESYNC";
	case WM_GETMINMAXINFO: return  "WM_GETMINMAXINFO";
	case WM_PAINTICON: return  "WM_PAINTICON";
	case WM_ICONERASEBKGND: return  "WM_ICONERASEBKGND";
	case WM_NEXTDLGCTL: return  "WM_NEXTDLGCTL";
	case WM_SPOOLERSTATUS: return  "WM_SPOOLERSTATUS";
	case WM_DRAWITEM: return  "WM_DRAWITEM";
	case WM_MEASUREITEM: return  "WM_MEASUREITEM";
	case WM_DELETEITEM: return  "WM_DELETEITEM";
	case WM_VKEYTOITEM: return  "WM_VKEYTOITEM";
	case WM_CHARTOITEM: return  "WM_CHARTOITEM";
	case WM_SETFONT: return  "WM_SETFONT";
	case WM_GETFONT: return  "WM_GETFONT";
	case WM_SETHOTKEY: return  "WM_SETHOTKEY";
	case WM_GETHOTKEY: return  "WM_GETHOTKEY";
	case WM_QUERYDRAGICON: return  "WM_QUERYDRAGICON";
	case WM_COMPAREITEM: return  "WM_COMPAREITEM";
	case WM_COMPACTING: return  "WM_COMPACTING";
	case WM_COMMNOTIFY: return  "WM_COMMNOTIFY";
	case WM_WINDOWPOSCHANGING: return  "WM_WINDOWPOSCHANGING";
	case WM_WINDOWPOSCHANGED: return  "WM_WINDOWPOSCHANGED";
	case WM_POWER: return  "WM_POWER";
	case WM_COPYDATA: return  "WM_COPYDATA";
	case WM_CANCELJOURNAL: return  "WM_CANCELJOURNAL";
	case WM_NOTIFY: return  "WM_NOTIFY";
	case WM_INPUTLANGCHANGEREQUEST: return  "WM_INPUTLANGCHANGEREQUES";
	case WM_INPUTLANGCHANGE: return  "WM_INPUTLANGCHANGE";
	case WM_TCARD: return  "WM_TCARD";
	case WM_HELP: return  "WM_HELP";
	case WM_USERCHANGED: return  "WM_USERCHANGED";
	case WM_NOTIFYFORMAT: return  "WM_NOTIFYFORMAT";
	case WM_CONTEXTMENU: return  "WM_CONTEXTMENU";
	case WM_STYLECHANGING: return  "WM_STYLECHANGING";
	case WM_STYLECHANGED: return  "WM_STYLECHANGED";
	case WM_DISPLAYCHANGE: return  "WM_DISPLAYCHANGE";
	case WM_GETICON: return  "WM_GETICON";
	case WM_SETICON: return  "WM_SETICON";
	case WM_NCCREATE: return  "WM_NCCREATE";
	case WM_NCDESTROY: return  "WM_NCDESTROY";
	case WM_NCCALCSIZE: return  "WM_NCCALCSIZE";
	case WM_NCHITTEST: return  "WM_NCHITTEST";
	case WM_NCPAINT: return  "WM_NCPAINT";
	case WM_NCACTIVATE: return  "WM_NCACTIVATE";
	case WM_GETDLGCODE: return  "WM_GETDLGCODE";
	case WM_SYNCPAINT: return  "WM_SYNCPAINT";
	case WM_NCMOUSEMOVE: return  "WM_NCMOUSEMOVE";
	case WM_NCLBUTTONDOWN: return  "WM_NCLBUTTONDOWN";
	case WM_NCLBUTTONUP: return  "WM_NCLBUTTONUP";
	case WM_NCLBUTTONDBLCLK: return  "WM_NCLBUTTONDBLCLK";
	case WM_NCRBUTTONDOWN: return  "WM_NCRBUTTONDOWN";
	case WM_NCRBUTTONUP: return  "WM_NCRBUTTONUP";
	case WM_NCRBUTTONDBLCLK: return  "WM_NCRBUTTONDBLCLK";
	case WM_NCMBUTTONDOWN: return  "WM_NCMBUTTONDOWN";
	case WM_NCMBUTTONUP: return  "WM_NCMBUTTONUP";
	case WM_NCMBUTTONDBLCLK: return  "WM_NCMBUTTONDBLCLK";
	case WM_KEYDOWN: return  "WM_KEYDOWN";
	case WM_KEYUP: return  "WM_KEYUP";
	case WM_CHAR: return  "WM_CHAR";
	case WM_DEADCHAR: return  "WM_DEADCHAR";
	case WM_SYSKEYDOWN: return  "WM_SYSKEYDOWN";
	case WM_SYSKEYUP: return  "WM_SYSKEYUP";
	case WM_SYSCHAR: return  "WM_SYSCHAR";
	case WM_SYSDEADCHAR: return  "WM_SYSDEADCHAR";
	case WM_KEYLAST: return  "WM_KEYLAST";
	case WM_IME_STARTCOMPOSITION: return  "WM_IME_STARTCOMPOSITION";
	case WM_IME_ENDCOMPOSITION: return  "WM_IME_ENDCOMPOSITION";
	case WM_IME_COMPOSITION: return  "WM_IME_COMPOSITION";
	case WM_INITDIALOG: return  "WM_INITDIALOG";
	case WM_COMMAND: return  "WM_COMMAND";
	case WM_SYSCOMMAND: return  "WM_SYSCOMMAND";
	case WM_TIMER: return  "WM_TIMER";
	case WM_HSCROLL: return  "WM_HSCROLL";
	case WM_VSCROLL: return  "WM_VSCROLL";
	case WM_INITMENU: return  "WM_INITMENU";
	case WM_INITMENUPOPUP: return  "WM_INITMENUPOPUP";
	case WM_MENUSELECT: return  "WM_MENUSELECT";
	case WM_MENUCHAR: return  "WM_MENUCHAR";
	case WM_ENTERIDLE: return  "WM_ENTERIDLE";
	case WM_CTLCOLORMSGBOX: return  "WM_CTLCOLORMSGBOX";
	case WM_CTLCOLOREDIT: return  "WM_CTLCOLOREDIT";
	case WM_CTLCOLORLISTBOX: return  "WM_CTLCOLORLISTBOX";
	case WM_CTLCOLORBTN: return  "WM_CTLCOLORBTN";
	case WM_CTLCOLORDLG: return  "WM_CTLCOLORDLG";
	case WM_CTLCOLORSCROLLBAR: return  "WM_CTLCOLORSCROLLBAR";
	case WM_CTLCOLORSTATIC: return  "WM_CTLCOLORSTATIC";
	case WM_MOUSEMOVE: return  "WM_MOUSEMOVE";
	case WM_LBUTTONDOWN: return  "WM_LBUTTONDOWN";
	case WM_LBUTTONUP: return  "WM_LBUTTONUP";
	case WM_LBUTTONDBLCLK: return  "WM_LBUTTONDBLCLK";
	case WM_RBUTTONDOWN: return  "WM_RBUTTONDOWN";
	case WM_RBUTTONUP: return  "WM_RBUTTONUP";
	case WM_RBUTTONDBLCLK: return  "WM_RBUTTONDBLCLK";
	case WM_MBUTTONDOWN: return  "WM_MBUTTONDOWN";
	case WM_MBUTTONUP: return  "WM_MBUTTONUP";
	case WM_MBUTTONDBLCLK: return  "WM_MBUTTONDBLCLK";
//	case WM_MOUSEWHEEL: return  "WM_MOUSEWHEEL";
	case WM_PARENTNOTIFY: return  "WM_PARENTNOTIFY";
	case WM_ENTERMENULOOP: return  "WM_ENTERMENULOOP";
	case WM_EXITMENULOOP: return  "WM_EXITMENULOOP";
	case WM_NEXTMENU: return  "WM_NEXTMENU";
	case WM_SIZING: return  "WM_SIZING";
	case WM_CAPTURECHANGED: return  "WM_CAPTURECHANGED";
	case WM_MOVING: return  "WM_MOVING";
	case WM_POWERBROADCAST: return  "WM_POWERBROADCAST";
	case WM_DEVICECHANGE: return  "WM_DEVICECHANGE";
	case WM_MDICREATE: return  "WM_MDICREATE";
	case WM_MDIDESTROY: return  "WM_MDIDESTROY";
	case WM_MDIACTIVATE: return  "WM_MDIACTIVATE";
	case WM_MDIRESTORE: return  "WM_MDIRESTORE";
	case WM_MDINEXT: return  "WM_MDINEXT";
	case WM_MDIMAXIMIZE: return  "WM_MDIMAXIMIZE";
	case WM_MDITILE: return  "WM_MDITILE";
	case WM_MDICASCADE: return  "WM_MDICASCADE";
	case WM_MDIICONARRANGE: return  "WM_MDIICONARRANGE";
	case WM_MDIGETACTIVE: return  "WM_MDIGETACTIVE";
	case WM_MDISETMENU: return  "WM_MDISETMENU";
	case WM_ENTERSIZEMOVE: return  "WM_ENTERSIZEMOVE";
	case WM_EXITSIZEMOVE: return  "WM_EXITSIZEMOVE";
	case WM_DROPFILES: return  "WM_DROPFILES";
	case WM_MDIREFRESHMENU: return  "WM_MDIREFRESHMENU";
	case WM_IME_SETCONTEXT: return  "WM_IME_SETCONTEXT";
	case WM_IME_NOTIFY: return  "WM_IME_NOTIFY";
	case WM_IME_CONTROL: return  "WM_IME_CONTROL";
	case WM_IME_COMPOSITIONFULL: return  "WM_IME_COMPOSITIONFULL";
	case WM_IME_SELECT: return  "WM_IME_SELECT";
	case WM_IME_CHAR: return  "WM_IME_CHAR";
	case WM_IME_KEYDOWN: return  "WM_IME_KEYDOWN";
	case WM_IME_KEYUP: return  "WM_IME_KEYUP";
//	case WM_MOUSEHOVER: return  "WM_MOUSEHOVER";
//	case WM_MOUSELEAVE: return  "WM_MOUSELEAVE";
	case WM_CUT: return  "WM_CUT";
	case WM_COPY: return  "WM_COPY";
	case WM_PASTE: return  "WM_PASTE";
	case WM_CLEAR: return  "WM_CLEAR";
	case WM_UNDO: return  "WM_UNDO";
	case WM_RENDERFORMAT: return  "WM_RENDERFORMAT";
	case WM_RENDERALLFORMATS: return  "WM_RENDERALLFORMATS";
	case WM_DESTROYCLIPBOARD: return  "WM_DESTROYCLIPBOARD";
	case WM_DRAWCLIPBOARD: return  "WM_DRAWCLIPBOARD";
	case WM_PAINTCLIPBOARD: return  "WM_PAINTCLIPBOARD";
	case WM_VSCROLLCLIPBOARD: return  "WM_VSCROLLCLIPBOARD";
	case WM_SIZECLIPBOARD: return  "WM_SIZECLIPBOARD";
	case WM_ASKCBFORMATNAME: return  "WM_ASKCBFORMATNAME";
	case WM_CHANGECBCHAIN: return  "WM_CHANGECBCHAIN";
	case WM_HSCROLLCLIPBOARD: return  "WM_HSCROLLCLIPBOARD";
	case WM_QUERYNEWPALETTE: return  "WM_QUERYNEWPALETTE";
	case WM_PALETTEISCHANGING: return  "WM_PALETTEISCHANGING";
	case WM_PALETTECHANGED: return  "WM_PALETTECHANGED";
	case WM_HOTKEY: return  "WM_HOTKEY";
	case WM_PRINT: return  "WM_PRINT";
	case WM_PRINTCLIENT: return  "WM_PRINTCLIENT";
	case WM_HANDHELDFIRST: return  "WM_HANDHELDFIRST";
	case WM_HANDHELDLAST: return  "WM_HANDHELDLAST";
	case WM_AFXFIRST: return  "WM_AFXFIRST";
	case WM_AFXLAST: return  "WM_AFXLAST";
	case WM_PENWINFIRST: return  "WM_PENWINFIRST";
	case WM_PENWINLAST: return  "WM_PENWINLAST";
	default: return "WM_UNKNOWN";
	};
}
#endif

// WndProc ====================================================================
/** Window Procedure - 窗口程序 */
//=============================================================================
LRESULT CALLBACK WndProc( HWND hWnd, UINT message,
													WPARAM wParam, LPARAM lParam )
{

	try
	{
		// First let the IME manager do it's stuff.
		if ( TheIMEManager )
		{
			if ( TheIMEManager->serviceIMEMessage( hWnd, message, wParam, lParam ) )
			{
				// The manager intercepted an IME message so return the result - 管理器截获了一条IME消息，因此返回结果
				return TheIMEManager->result();
			}
		}

#ifdef	DEBUG_WINDOWS_MESSAGES
		static msgCount=0;
		char testString[256];
		sprintf(testString,"\n%d: %s (%X,%X)", msgCount++,messageToString(message), wParam, lParam);
		OutputDebugString(testString);
#endif

		// handle all window messages - 处理所有窗口消息
		switch( message )
		{
			//-------------------------------------------------------------------------
			case WM_NCHITTEST:
			// Prevent the user from selecting the menu in fullscreen mode - 防止用户在全屏模式下选择菜单
            if( !TheGlobalData->m_windowed )
                return HTCLIENT;
            break;

			//-------------------------------------------------------------------------
			case WM_POWERBROADCAST:
            switch( wParam )
            {
                #ifndef PBT_APMQUERYSUSPEND
                    #define PBT_APMQUERYSUSPEND 0x0000
                #endif
                case PBT_APMQUERYSUSPEND:
                    // At this point, the app should save any data for open - 此时，应用程序应该保存所有数据以供打开
                    // network connections, files, etc., and prepare to go into - 网络连接，文件等，并准备进入
                    // a suspended mode. - 暂停模式。
                    return TRUE;

                #ifndef PBT_APMRESUMESUSPEND
                    #define PBT_APMRESUMESUSPEND 0x0007
                #endif
                case PBT_APMRESUMESUSPEND:
                    // At this point, the app should recover any data, network - 在这一点上，应用程序应该恢复任何数据，网络
                    // connections, files, etc., and resume running from when - 连接、文件等，并从何时开始恢复运行
                    // the app was suspended. - 该应用程序被暂停。
                    return TRUE;
            }
            break;
			//-------------------------------------------------------------------------
			case WM_SYSCOMMAND:
            // Prevent moving/sizing and power loss in fullscreen mode - 防止移动/大小和电力损失在全屏模式
            switch( wParam )
            {
                case SC_KEYMENU:
                    // TheSuperHackers @bugfix Mauller 10/05/2025 Always handle this command to prevent halting the game when left Alt is pressed. - 总是处理这个命令，以防止停止游戏时，左键Alt被按下。
                    return 1;
                case SC_MOVE:
                case SC_SIZE:
                case SC_MAXIMIZE:
                case SC_MONITORPOWER:
                    if( !TheGlobalData->m_windowed )
                        return 1;
                    break;
            }
            break;

			case WM_QUERYENDSESSION:
			{
				TheMessageStream->appendMessage(GameMessage::MSG_META_DEMO_INSTANT_QUIT);
				return 0;	//don't allow Windows to shutdown while game is running. - 不允许Windows在游戏运行时关闭。
			}

			// ------------------------------------------------------------------------
			case WM_CLOSE: //关闭
			if (!TheGameEngine->getQuitting())
			{
				//user is exiting without using the menus - 用户在未使用菜单的情况下退出

				//This method didn't work in cinematics because we don't process messages. - 这种方法并不适用于动画，因为我们不处理信息。
				//But it's the cleanest way to exit that's similar to using menus. - 但这是最干净的退出方式，类似于使用菜单。
				TheMessageStream->appendMessage(GameMessage::MSG_META_DEMO_INSTANT_QUIT);

				//This method used to disable quitting.  We just put up the options screen instead. - 此方法用于禁用退出。我们只是用选项屏幕来代替。
				//TheMessageStream->appendMessage(GameMessage::MSG_META_OPTIONS);

				//This method works everywhere but isn't as clean at shutting down. - 这种方法在任何地方都有效，但在关闭时就不那么干净了。
				//TheGameEngine->checkAbnormalQuitting();	//old way to log disconnections for - 记录断开连接的旧方法 ALT-F4
				//TheGameEngine->reset();
				//TheGameEngine->setQuitting(TRUE);
				//_exit(EXIT_SUCCESS);
				return 0;
			}

			// ------------------------------------------------------------------------
			case WM_SETFOCUS: //设置焦点
			{

				//
				// reset the state of our keyboard cause we haven't been paying
				// attention to the keys while focus was away - 注意力不在的时候注意按键
				//
				if( TheKeyboard )
					TheKeyboard->resetKeys();

				if (TheMouse)
					TheMouse->regainFocus();

				break;

			}

			//-------------------------------------------------------------------------
			case WM_MOVE: //移动
			{
				if (TheMouse)
					TheMouse->refreshCursorCapture();

				break;
			}

			//-------------------------------------------------------------------------
			case WM_SIZE:
			{
				// When W3D initializes, it resizes the window.  So stop repainting. - 当W3D初始化时，它会调整窗口的大小。所以不要再重新粉刷了。
				if (!gInitializing)
					gDoPaint = false;

				if (TheMouse)
					TheMouse->refreshCursorCapture();

				break;
			}

			//-------------------------------------------------------------------------
			case WM_KILLFOCUS:
			{
				if (TheKeyboard )
					TheKeyboard->resetKeys();

				if (TheMouse)
					TheMouse->loseFocus();

				break;
			}

			//-------------------------------------------------------------------------
			case WM_ACTIVATEAPP: //激活应用
			{
				if ((bool) wParam != isWinMainActive)
				{
					// TheSuperHackers @bugfix xezon 11/05/2025 This event originally called DX8Wrapper::Reset_Device - 此事件最初称为DX8Wrapper::Reset_Device
					// intended to clear resources on a lost device in fullscreen, but effectively also in - 旨在清除资源上丢失的设备在全屏，但有效地也在
					// windowed mode, if the DXMaximizedWindowedMode shim was applied in newer versions of Windows, - 如果DXMaximizedWindowedMode shim在较新版本的Windows中应用
					// which lead to unfortunate application crashing. Resetting the device on WM_ACTIVATEAPP instead - 这会导致不幸的应用程序崩溃。重置WM_ACTIVATEAPP上的设备
					// of TestCooperativeLevel() == D3DERR_DEVICENOTRESET is not a requirement. There are other code - testcooperativellevel () == D3DERR_DEVICENOTRESET不是必需的。还有其他的代码
					// paths that take care of that. - 处理这个的路径。

					isWinMainActive = (BOOL) wParam;

					if (TheGameEngine)
						TheGameEngine->setIsActive(isWinMainActive);

					if (isWinMainActive)
					{	//restore mouse cursor to our custom version. - 将鼠标光标恢复到自定义版本。
						if (TheWin32Mouse)
							TheWin32Mouse->setCursor(TheWin32Mouse->getMouseCursor());
					}
				}
				return 0;
			}
			//-------------------------------------------------------------------------
			case WM_ACTIVATE:
			{
				Int active = LOWORD( wParam );

				if( active == WA_INACTIVE )
				{
					if (TheAudio)
						TheAudio->loseFocus();
				}
				else
				{
					if (TheAudio)
						TheAudio->regainFocus();

					// Cursor can only be captured after one of the activation events. - 游标只能在其中一个激活事件之后捕获。
					if (TheMouse)
						TheMouse->refreshCursorCapture();
				}
				break;

			}

			//-------------------------------------------------------------------------
			case WM_KEYDOWN: //按下按键
			{
				Int key = (Int)wParam;

				switch( key )
				{

					//---------------------------------------------------------------------
					case VK_ESCAPE:
					{

						PostQuitMessage( 0 );
						break;

					}


				}

				return 0;

			}

			//-------------------------------------------------------------------------
			// 鼠标按键消息处理组 - Mouse Button Message Handling Group [ 待验证 ]
			case WM_LBUTTONDOWN: 
			case WM_LBUTTONUP:
			case WM_LBUTTONDBLCLK:

			case WM_MBUTTONDOWN:
			case WM_MBUTTONUP:
			case WM_MBUTTONDBLCLK:

			case WM_RBUTTONDOWN:
			case WM_RBUTTONUP:
			case WM_RBUTTONDBLCLK:
			{

				if( TheWin32Mouse )
					TheWin32Mouse->addWin32Event( message, wParam, lParam, TheMessageTime );

				return 0;

			}

			//-------------------------------------------------------------------------
			case 0x020A: // WM_MOUSEWHEEL 鼠标滚轮 [ 待验证 ]
			{
				long x = (long) LOWORD(lParam);	// 从lParam低16位获取鼠标X坐标
				long y = (long) HIWORD(lParam);	// 从lParam高16位获取鼠标Y坐标
				RECT rect;

				// ignore when outside of client area - 在客户端区域之外忽略
				GetWindowRect( ApplicationHWnd, &rect );
				if( x < rect.left || x > rect.right || y < rect.top || y > rect.bottom )
					return 0;

				// 如果鼠标在窗口内，将滚轮事件添加到输入系统
				if( TheWin32Mouse )
					TheWin32Mouse->addWin32Event( message, wParam, lParam, TheMessageTime );

				return 0;

			}


			//-------------------------------------------------------------------------
			case WM_MOUSEMOVE: //鼠标移动
			{
				Int x = (Int)LOWORD( lParam );
				Int y = (Int)HIWORD( lParam );
				RECT rect;
//				Int keys = wParam;

				// ignore when outside of client area - 在客户端区域之外忽略
				GetClientRect( ApplicationHWnd, &rect );
				if( x < rect.left || x > rect.right || y < rect.top || y > rect.bottom )
					return 0;

				if( TheWin32Mouse )
					TheWin32Mouse->addWin32Event( message, wParam, lParam, TheMessageTime );

				return 0;

			}

			//-------------------------------------------------------------------------
			case WM_SETCURSOR:
			{
				if (TheWin32Mouse && (HWND)wParam == ApplicationHWnd)
					TheWin32Mouse->setCursor(TheWin32Mouse->getMouseCursor());
				return TRUE;	//tell Windows not to reset mouse cursor image to default. - 告诉Windows不要将鼠标光标图像重置为默认值。
			}

			case WM_PAINT:
			{
				if (gDoPaint) {
					PAINTSTRUCT paint;
					HDC dc = ::BeginPaint(hWnd, &paint);
#if 0
					::SetTextColor(dc, RGB(255,255,255));
					::SetBkColor(dc, RGB(0,0,0));
					::TextOut(dc, 30, 30, "Loading Command & Conquer Generals...", 37);
#endif
					if (gLoadScreenBitmap!=NULL) {
						Int savContext = ::SaveDC(dc);
						HDC tmpDC = ::CreateCompatibleDC(dc);
						HBITMAP savBitmap = (HBITMAP)::SelectObject(tmpDC, gLoadScreenBitmap);
						::BitBlt(dc, 0, 0, DEFAULT_DISPLAY_WIDTH, DEFAULT_DISPLAY_HEIGHT, tmpDC, 0, 0, SRCCOPY);
						::SelectObject(tmpDC, savBitmap);
						::DeleteDC(tmpDC);
						::RestoreDC(dc, savContext);
					}
					::EndPaint(hWnd, &paint);
					return TRUE;
				}
				break;
			}

			case WM_ERASEBKGND:
			{
				if (!gDoPaint)
					return TRUE;	//we don't need to erase the background because we always draw entire window. - 我们不需要擦除背景，因为我们总是绘制整个窗口。
				break;
			}

// Well, it was a nice idea, but we don't get a message for an ejection. - 这主意不错，但我们没有收到弹出的信息。
// (Really unforunate, actually.) I'm leaving this in in-case some one wants - （实际上，真的很不幸。）我把这个留在这里，以防有人想要
// to trap a different device change (for instance, removal of a mouse) - jkmcd - 捕获不同设备的变化（例如，移除鼠标）- JKMCD
#if 0
			case WM_DEVICECHANGE:
			{
				if (((UINT) wParam) == DBT_DEVICEREMOVEPENDING)
				{
					DEV_BROADCAST_HDR *hdr = (DEV_BROADCAST_HDR*) lParam;
					if (!hdr) {
						break;
					}

					if (hdr->dbch_devicetype != DBT_DEVTYP_VOLUME)  {
						break;
					}

					// Lets discuss how Windows is a flaming pile of poo. I'm now casting the header 
					// directly into the structure, because its the one I want, and this is just how
					// its done. I hate Windows. - jkmcd
					DEV_BROADCAST_VOLUME *vol = (DEV_BROADCAST_VOLUME*) (hdr);

					// @todo - Yikes. This could cause us all kinds of pain. I don't really want
					// to even think about the stink this could cause us.
					TheFileSystem->unloadMusicFilesFromCD(vol->dbcv_unitmask);
					return TRUE;
				}
				break;
			}
#endif
		}

	}
	catch (...)
	{
		RELEASE_CRASH(("Uncaught exception in Main::WndProc... probably should not happen"));
		// no rethrow - 没有重新抛出
	}

//In full-screen mode, only pass these messages onto the default windows handler. - 在全屏模式下，只将这些消息传递给默认的窗口处理程序。
//Appears to fix issues with dual monitor systems but doesn't seem safe? - 似乎解决了双监视器系统的问题，但似乎不安全？
///@todo: Look into proper support for dual monitor systems. - 查看对双监视器系统的适当支持。
/*	if (!TheGlobalData->m_windowed)
	switch (message)
	{
		case WM_PAINT:
		case WM_NCCREATE:
		case WM_NCDESTROY:
		case WM_NCCALCSIZE:
		case WM_NCPAINT:
				return DefWindowProc( hWnd, message, wParam, lParam );
	}
	return 0;*/

	return DefWindowProc( hWnd, message, wParam, lParam );

}

// initializeAppWindows =======================================================
/** Register windows class and create application windows. - 注册windows类并创建应用程序窗口 */
//=============================================================================
static Bool initializeAppWindows( HINSTANCE hInstance, Int nCmdShow, Bool runWindowed )
{
	DWORD windowStyle;
	Int startWidth = DEFAULT_DISPLAY_WIDTH,
			startHeight = DEFAULT_DISPLAY_HEIGHT;

	// register the window class - 注册窗口类

  WNDCLASS wndClass = { CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS, WndProc, 0, 0, hInstance,
                       LoadIcon (hInstance, MAKEINTRESOURCE(IDI_ApplicationIcon)),
                       NULL/*LoadCursor(NULL, IDC_ARROW)*/,
                       (HBRUSH)GetStockObject(BLACK_BRUSH), NULL,
	                     TEXT("Game Window") };
  RegisterClass( &wndClass );

   // Create our main window - 创建主窗口
	windowStyle =  WS_POPUP|WS_VISIBLE;
	if (runWindowed)
		windowStyle |= WS_DLGFRAME | WS_CAPTION | WS_SYSMENU;
	else
		windowStyle |= WS_EX_TOPMOST | WS_SYSMENU;

	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = startWidth;
	rect.bottom = startHeight;
	AdjustWindowRect (&rect, windowStyle, FALSE);
	if (runWindowed) {
		// Makes the normal debug 800x600 window center in the screen. - 使正常调试窗口位于屏幕中心800x600。
		startWidth = DEFAULT_DISPLAY_WIDTH;
		startHeight= DEFAULT_DISPLAY_HEIGHT;
	}

	gInitializing = true;

  HWND hWnd = CreateWindow( TEXT("Game Window"),
                            TEXT("Command and Conquer Generals"),
                            windowStyle,
														(GetSystemMetrics( SM_CXSCREEN ) / 2) - (startWidth / 2), // original position X - 初始位置X
														(GetSystemMetrics( SM_CYSCREEN ) / 2) - (startHeight / 2),// original position Y - 初始位置Y
														// Lorenzen nudged the window higher
														// so the constantdebug report would
														// not get obliterated by assert windows, thank you.
														//(GetSystemMetrics( SM_CXSCREEN ) / 2) - (startWidth / 2),   //this works with any screen res
														//(GetSystemMetrics( SM_CYSCREEN ) / 25) - (startHeight / 25),//this works with any screen res
														rect.right-rect.left,
														rect.bottom-rect.top,
														0L,
														0L,
														hInstance,
														0L );


	if (!runWindowed)
	{	SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0,SWP_NOSIZE |SWP_NOMOVE);
	}
	else
		SetWindowPos(hWnd, HWND_TOP, 0, 0, 0, 0,SWP_NOSIZE |SWP_NOMOVE);

	SetFocus(hWnd);

	SetForegroundWindow(hWnd);
	ShowWindow( hWnd, nCmdShow );
	UpdateWindow( hWnd );

	// save our application window handle for future use - 保存我们的应用程序窗口句柄以供将来使用
	ApplicationHWnd = hWnd;
	gInitializing = false;
	if (!runWindowed) {
		gDoPaint = false;
	}

	return true;  // success - 成功

}

// Necessary to allow memory managers and such to have useful critical sections - 必须允许内存管理器等具有有用的临界区
static CriticalSection critSec1, critSec2, critSec3, critSec4, critSec5;

// UnHandledExceptionFilter - 未处理异常过滤器 ===================================================
/** Handler for unhandled win32 exceptions. - 处理未处理的win32异常。 */
//=============================================================================
static LONG WINAPI UnHandledExceptionFilter( struct _EXCEPTION_POINTERS* e_info )
{
	DumpExceptionInfo( e_info->ExceptionRecord->ExceptionCode, e_info );
	return EXCEPTION_EXECUTE_HANDLER;
}

// WinMain ====================================================================
/** Application entry point */
//=============================================================================
Int APIENTRY WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                      LPSTR lpCmdLine, Int nCmdShow )
{
	Int exitcode = 1;

#ifdef RTS_PROFILE
  Profile::StartRange("init");
#endif

	try {

		SetUnhandledExceptionFilter( UnHandledExceptionFilter );
		//
		// there is something about checkin in and out the .dsp and .dsw files - 有一些关于签入和签出的。DSP和。dsw文件下手
		// that blows the working directory information away on each of the - 将每个目录的工作目录信息清除
		// developers machines so we're going to hack it for a while and set our - 开发者的机器，所以我们要破解它一段时间，并设置我们的
		// working directory to the directory with the .exe since that's not the - 工作目录到带有。exe的目录，因为它不是
		// default in a DevStudio project - DevStudio项目的默认设置
		//

		TheAsciiStringCriticalSection = &critSec1;
		TheUnicodeStringCriticalSection = &critSec2;
		TheDmaCriticalSection = &critSec3;
		TheMemoryPoolCriticalSection = &critSec4;
		TheDebugLogCriticalSection = &critSec5;

		// initialize the memory manager early - 尽早初始化内存管理器
		initMemoryManager();

		/// @todo remove this force set of working directory later - @todo稍后删除工作目录的强制集
		Char buffer[ _MAX_PATH ];
		GetModuleFileName( NULL, buffer, sizeof( buffer ) );
		if (Char *pEnd = strrchr(buffer, '\\'))
		{
			*pEnd = 0;
		}
		::SetCurrentDirectory(buffer);


		#ifdef RTS_DEBUG
			// Turn on Memory heap tracking - 打开内存堆跟踪
			int tmpFlag = _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG );
			tmpFlag |= (_CRTDBG_LEAK_CHECK_DF|_CRTDBG_ALLOC_MEM_DF);
			tmpFlag &= ~_CRTDBG_CHECK_CRT_DF;
			_CrtSetDbgFlag( tmpFlag );
		#endif



		// install debug callbacks - 安装调试回调
	//	WWDebug_Install_Message_Handler(WWDebug_Message_Callback);
	//	WWDebug_Install_Assert_Handler(WWAssert_Callback);


// Force "splash image" to be loaded from a file, not a resource so same exe can be used in different localizations. - 强制“splash image”从文件加载，而不是从资源加载，以便相同的exe可以在不同的本地化中使用。
#if defined(RTS_DEBUG) || defined RTS_PROFILE

			// check both localized directory and root dir - 检查本地化目录和根目录
		char filePath[_MAX_PATH];
		const char *fileName = "Install_Final.bmp";
		static const char *localizedPathFormat = "Data/%s/";
		sprintf(filePath,localizedPathFormat, GetRegistryLanguage().str());
		strlcat(filePath, fileName, ARRAY_SIZE(filePath));
		FILE *fileImage = fopen(filePath, "r");
		if (fileImage) {
			fclose(fileImage);
			gLoadScreenBitmap = (HBITMAP)LoadImage(hInstance, filePath, IMAGE_BITMAP, 0, 0, LR_SHARED|LR_LOADFROMFILE);
		}
		else {
			gLoadScreenBitmap = (HBITMAP)LoadImage(hInstance, fileName, IMAGE_BITMAP, 0, 0, LR_SHARED|LR_LOADFROMFILE);
		}
#else

		// in release, the file only ever lives in the root dir - 在发布版本中，该文件只存在于根目录中
		gLoadScreenBitmap = (HBITMAP)LoadImage(hInstance, "Install_Final.bmp", IMAGE_BITMAP, 0, 0, LR_SHARED|LR_LOADFROMFILE);
#endif

		CommandLine::parseCommandLineForStartup();

		// register windows class and create application window - 注册Windows类并创建应用程序窗口
		if(!TheGlobalData->m_headless && initializeAppWindows(hInstance, nCmdShow, TheGlobalData->m_windowed) == false)
			return exitcode;

		// save our application instance for future use - 保存我们的应用程序实例以供将来使用
		ApplicationHInstance = hInstance;

		if (gLoadScreenBitmap!=NULL) {
			::DeleteObject(gLoadScreenBitmap);
			gLoadScreenBitmap = NULL;
		}


		// BGC - initialize COM
	//	OleInitialize(NULL);



		// Set up version info - 设置版本信息
		TheVersion = NEW Version;
		TheVersion->setVersion(VERSION_MAJOR, VERSION_MINOR, VERSION_BUILDNUM, VERSION_LOCALBUILDNUM,
			AsciiString(VERSION_BUILDUSER), AsciiString(VERSION_BUILDLOC),
			AsciiString(__TIME__), AsciiString(__DATE__));

		// TheSuperHackers @refactor The instance mutex now lives in its own class.

		if (!rts::ClientInstance::initialize())
		{
			HWND ccwindow = FindWindow(rts::ClientInstance::getFirstInstanceName(), NULL);
			if (ccwindow)
			{
				SetForegroundWindow(ccwindow);
				ShowWindow(ccwindow, SW_RESTORE);
			}

			DEBUG_LOG(("Generals is already running...Bail!"));
			delete TheVersion;
			TheVersion = NULL;
			shutdownMemoryManager();
			return exitcode;
		}
		DEBUG_LOG(("Create Generals Mutex okay."));

		DEBUG_LOG(("CRC message is %d", GameMessage::MSG_LOGIC_CRC));

		// run the game main loop - 运行游戏主循环
		exitcode = GameMain();

		delete TheVersion;
		TheVersion = NULL;

	#ifdef MEMORYPOOL_DEBUG
		TheMemoryPoolFactory->debugMemoryReport(REPORT_POOLINFO | REPORT_POOL_OVERFLOW | REPORT_SIMPLE_LEAKS, 0, 0);
	#endif
	#if defined(RTS_DEBUG)
		TheMemoryPoolFactory->memoryPoolUsageReport("AAAMemStats");
	#endif

		shutdownMemoryManager();

		// BGC - shut down COM - BGC -关闭COM
	//	OleUninitialize();
	}
	catch (...)
	{

	}

	TheUnicodeStringCriticalSection = NULL;
	TheDmaCriticalSection = NULL;
	TheMemoryPoolCriticalSection = NULL;

	return exitcode;

}

// CreateGameEngine - 创建游戏引擎 ===========================================================
/** Create the Win32 game engine we're going to use - 创建我们将要使用的Win32游戏引擎 */
//=============================================================================
GameEngine *CreateGameEngine( void )
{
	Win32GameEngine *engine;

	engine = NEW Win32GameEngine;
	//game engine may not have existed when app got focus so make sure it - 当应用获得焦点时，游戏引擎可能还不存在，所以要确保它存在
	//knows about current focus state. - 知道当前的焦点状态。
	engine->setIsActive(isWinMainActive);

	return engine;

}
