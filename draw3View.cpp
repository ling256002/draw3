
// draw3View.cpp: Cdraw3View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "draw3.h"
#endif

#pragma once
#include "draw3Doc.h"
#include "draw3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "Setup.h"


// Cdraw3View

IMPLEMENT_DYNCREATE(Cdraw3View, CView)

BEGIN_MESSAGE_MAP(Cdraw3View, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_DRAW_LINE, &Cdraw3View::OnDrawLine)
	ON_COMMAND(ID_DRAW_RECT, &Cdraw3View::OnDrawRect)
	ON_COMMAND(ID_DRAW_ELLIPSE, &Cdraw3View::OnDrawEllipse)
	ON_COMMAND(ID_DRAW_PEN, &Cdraw3View::OnDrawPen)
	ON_UPDATE_COMMAND_UI(ID_DRAW_ELLIPSE, &Cdraw3View::OnUpdateDrawEllipse)
	ON_UPDATE_COMMAND_UI(ID_DRAW_LINE, &Cdraw3View::OnUpdateDrawLine)
	ON_UPDATE_COMMAND_UI(ID_DRAW_PEN, &Cdraw3View::OnUpdateDrawPen)
	ON_UPDATE_COMMAND_UI(ID_DRAW_RECT, &Cdraw3View::OnUpdateDrawRect)
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_FILE_SETUP, &Cdraw3View::OnFileSetup)
	ON_COMMAND(ID_FILE_WRITE, &Cdraw3View::OnFileWrite)
	ON_COMMAND(ID_FILE_READ, &Cdraw3View::OnFileRead)
END_MESSAGE_MAP()

// Cdraw3View 构造/析构

Cdraw3View::Cdraw3View() noexcept
{
	// TODO: 在此处添加构造代码

	m_pOrigin = 0;
	m_bDraw = false;
	m_DrawType = DT_LINE;
	m_nWidth = 0;
	m_nLineWidth = 0;
	m_nLineStyle = 0;
}

Cdraw3View::~Cdraw3View()
{
	//释放m_pGraphs中的数据
	int cnt = m_pGraphs.GetSize();
	while (cnt--)
	{
		delete m_pGraphs.GetAt(cnt);
	}
	m_pGraphs.RemoveAll();
}

BOOL Cdraw3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	m_Menu.LoadMenu(IDR_MENU1);

	return CView::PreCreateWindow(cs);
}

// Cdraw3View 绘图

void Cdraw3View::OnDraw(CDC* pDC)
{
	Cdraw3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	
	////把兼容设备的数据拷贝到真实设备，完成显示工作
	//CRect rect;
	//GetClientRect(&rect);
	//pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &m_dcCompatible, 0, 0, SRCCOPY);

	//根据 m_pGraphs数组的绘制信息，完成重绘工作

	int cnt = m_pGraphs.GetSize(); //获得数组长度
	for (int i = 0; i < cnt; i++)
	{
		m_pGraphs.GetAt(i)->Draw(pDC);		
	}
}


// Cdraw3View 诊断

#ifdef _DEBUG
void Cdraw3View::AssertValid() const
{
	CView::AssertValid();
}

void Cdraw3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cdraw3Doc* Cdraw3View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cdraw3Doc)));
	return (Cdraw3Doc*)m_pDocument;
}
#endif //_DEBUG


// Cdraw3View 消息处理程序


void Cdraw3View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//保存起点到成员变量
	m_pOrigin = point;
	if (m_DrawType == DT_PEN)
	{
		m_bDraw = true;
		m_tmpGraph = new Graph(m_DrawType, m_nLineStyle, m_nLineWidth, m_color);
		m_tmpGraph->AddPoint(point);
	}

	//CClientDC dc(this);

	////初始化兼容设备上下文
	//if (!m_dcCompatible.m_hDC)
	//{
	//	// 创建兼容DC
	//	m_dcCompatible.CreateCompatibleDC(&dc);
	//	CRect rect;
	//	//获得客户区大小
	//	GetClientRect(&rect);
	//	CBitmap bitmap;
	//	//创建兼容Bitmap
	//	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	//	m_dcCompatible.SelectObject(&bitmap);
	//	m_dcCompatible.FillSolidRect(rect, RGB(0, 255, 0));
	//}
	

	CView::OnLButtonDown(nFlags, point);
}


void Cdraw3View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CClientDC dc(this);
	CPen pen(m_nLineStyle, m_nLineWidth, m_color);
	CPen* pOldPen = dc.SelectObject(&pen);
	//CPen* pOldPen = m_dcCompatible.SelectObject(&pen);
	switch (m_DrawType)
	{
	case DT_LINE:
	{
		dc.MoveTo(m_pOrigin);
		dc.LineTo(point);
		/*m_dcCompatible.MoveTo(m_pOrigin);
		m_dcCompatible.LineTo(point);*/
	}
	break;
	case DT_RECT:
	{
		dc.Rectangle(CRect(m_pOrigin, point));
		//m_dcCompatible.Rectangle(CRect(m_pOrigin, point));
	}
	break;
	case DT_ELLIPSE:
	{
		dc.Ellipse(CRect(m_pOrigin, point));
		//m_dcCompatible.Ellipse(CRect(m_pOrigin, point));
	}
	break;
	case DT_PEN:
	{
		m_bDraw = false;
	}
	break;
	default:
		break;
	}
	dc.SelectObject(pOldPen);
	//m_dcCompatible.SelectObject(pOldPen);

	if (m_DrawType != DT_PEN)
	{
		//  释放内存
		Graph* gh = new Graph(m_DrawType, m_nLineStyle, m_nLineWidth, m_color);
		gh->AddPoint(m_pOrigin, point);
		m_pGraphs.Add(gh);
	}
	else
	{
		//添加画笔的最后一个点
		m_tmpGraph->AddPoint(point);
		m_pGraphs.Add(m_tmpGraph);
	}

	//Invalidate();

	CView::OnLButtonUp(nFlags, point);
}


void Cdraw3View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (m_DrawType == DT_PEN)
	{
		CClientDC dc(this);
		CPen pen(m_nLineStyle, m_nLineWidth, m_color);
		CPen* pOldPen = dc.SelectObject(&pen);
		//CPen* pOldPen = m_dcCompatible.SelectObject(&pen);
		if (m_bDraw)
		{
			dc.MoveTo(m_pOrigin);
			dc.LineTo(point);
			/*m_dcCompatible.MoveTo(m_pOrigin);
			m_dcCompatible.LineTo(point);*/

			/*Graph* gh = new Graph(m_DrawType, m_nLineStyle, m_nLineWidth, m_color);
			gh->AddPoint(m_pOrigin, point);
			m_pGraphs.Add(gh);*/
			m_tmpGraph->AddPoint(point);

			m_pOrigin = point;
			//Invalidate();
		}
		dc.SelectObject(pOldPen);
		//m_dcCompatible.SelectObject(pOldPen);
	}

	

	CView::OnMouseMove(nFlags, point);
}


void Cdraw3View::OnDrawLine()
{
	// TODO: 在此添加命令处理程序代码
	m_DrawType = DT_LINE;
}


void Cdraw3View::OnDrawRect()
{
	// TODO: 在此添加命令处理程序代码
	m_DrawType = DT_RECT;
}


void Cdraw3View::OnDrawEllipse()
{
	// TODO: 在此添加命令处理程序代码
	m_DrawType = DT_ELLIPSE;
}


void Cdraw3View::OnDrawPen()
{
	// TODO: 在此添加命令处理程序代码
	m_DrawType = DT_PEN;
}


void Cdraw3View::OnUpdateDrawEllipse(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码

	//决定“画椭圆”菜单项check状态
	pCmdUI->SetCheck(m_DrawType == DT_ELLIPSE);
}


void Cdraw3View::OnUpdateDrawLine(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码

	pCmdUI->SetCheck(m_DrawType == DT_LINE);
}


void Cdraw3View::OnUpdateDrawPen(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码

	pCmdUI->SetCheck(m_DrawType == DT_PEN);

	//禁用功能
	//pCmdUI->Enable(false);
}


void Cdraw3View::OnUpdateDrawRect(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码

	pCmdUI->SetCheck(m_DrawType == DT_RECT);
}


void Cdraw3View::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CMenu* mu = m_Menu.GetSubMenu(0);
	ClientToScreen(&point);
	mu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTALIGN, point.x, point.y, this);
	CView::OnRButtonUp(nFlags, point);
}

void Cdraw3View::OnFileSetup()
{
	// TODO: 在此添加命令处理程序代码
	Setup conf;
	conf.m_nLineWidth = m_nLineWidth;
	conf.m_nLineStyle = m_nLineStyle;
	conf.m_color = m_color;
	if (IDOK == conf.DoModal())
	{
		m_nLineWidth = conf.m_nLineWidth;
		m_nLineStyle = conf.m_nLineStyle;
		m_color = conf.m_color;
	}
}


void Cdraw3View::OnFileWrite()
{
	// TODO: 在此添加命令处理程序代码
	CString hello = _T("hello,world. 你好吗！\n");
	// 文件对话框
	CFileDialog fileDlg(FALSE);
	// 如果点击确定
	if (IDOK == fileDlg.DoModal())
	{
		// 获取对话框返回的文件名
		CString path = fileDlg.GetPathName();
		// 打开文件
		CFile file(path, CFile::modeWrite | CFile::modeCreate);
		// 写入
		int len = hello.GetLength() * sizeof(TCHAR);
		file.Write(hello, len);
		// 关闭
		file.Close();
	}
}


void Cdraw3View::OnFileRead()
{
	// TODO: 在此添加命令处理程序代码
	CFileDialog fileDlg(TRUE);
	if (IDOK == fileDlg.DoModal())
	{
		CString path = fileDlg.GetPathName();
		CFile file(path, CFile::modeRead);
		// 准备缓冲区
		TCHAR* pBuf;
		int cnt = file.GetLength();
		int chars = cnt / sizeof(TCHAR);
		pBuf = new TCHAR[chars + 1];
		// 读取文件内容到缓冲区
		file.Read(pBuf, cnt);
		// 设置字符串结束位置
		pBuf[chars] = 0;

		MessageBox(pBuf);
		file.Close();
		delete[]pBuf;
	}
}
