﻿
// draw3.h: draw3 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"       // 主符号

enum ID_MSG
{
	ID_MSG_DRAW_LINE = (WM_USER + 1),
	ID_MSG_DRAW_RECT,
	ID_MSG_DRAW_ELLIPSE,
	ID_MSG_DRAW_PEN
};

// Cdraw3App:
// 有关此类的实现，请参阅 draw3.cpp
//

class Cdraw3App : public CWinApp
{
public:
	Cdraw3App() noexcept;


// 重写
public:
	virtual BOOL InitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Cdraw3App theApp;
