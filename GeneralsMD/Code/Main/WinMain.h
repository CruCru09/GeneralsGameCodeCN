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

// FILE: WinMain.h ////////////////////////////////////////////////////////////
//
// Header for entry point for Win32 application - Win32应用程序入口点的头
//
// Author: Colin Day, April 2001
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

// SYSTEM INCLUDES - 包含Windows API头文件，提供基础系统功能
#include <windows.h> 

// USER INCLUDES - 包含自定义鼠标处理模块
#include "Win32Device/GameClient/Win32Mouse.h"

// EXTERNAL - 外部
extern HINSTANCE ApplicationHInstance;  ///< our application instance - 应用程序实例句柄 标识当前程序实例的系统句柄
extern HWND ApplicationHWnd;  ///< our application window handle - 应用程序窗口句柄 主窗口的系统标识
extern Win32Mouse *TheWin32Mouse;  ///< global for win32 mouse only! - 全局鼠标指针 专用于管理Win32系统鼠标输入的全局对象指针
