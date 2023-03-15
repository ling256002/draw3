
// draw3View.cpp: Cdraw3View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "draw3.h"
#endif

#include "draw3Doc.h"
#include "draw3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
	
	/*ON_COMMAND(ID_MSG_DRAW_LINE, &Cdraw3View::OnDrawLine)
	ON_COMMAND(ID_MSG_DRAW_RECT, &Cdraw3View::OnDrawRect)
	ON_COMMAND(ID_MSG_DRAW_ELLIPSE, &Cdraw3View::OnDrawEllipse)
	ON_COMMAND(ID_MSG_DRAW_PEN, &Cdraw3View::OnDrawPen)
	ON_UPDATE_COMMAND_UI(ID_MSG_DRAW_LINE, &Cdraw3View::OnUpdateDrawLine)
	ON_UPDATE_COMMAND_UI(ID_MSG_DRAW_RECT, &Cdraw3View::OnUpdateDrawRect)
	ON_UPDATE_COMMAND_UI(ID_MSG_DRAW_PEN, &Cdraw3View::OnUpdateDrawPen)
	ON_UPDATE_COMMAND_UI(ID_MSG_DRAW_ELLIPSE, &Cdraw3View::OnUpdateDrawEllipse)*/

	ON_COMMAND(ID_MSG_DRAW_LINE, &Cdraw3View::OnLine)

	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// Cdraw3View 构造/析构

Cdraw3View::Cdraw3View() noexcept
{
	// TODO: 在此处添加构造代码

	m_pOrigin = 0;
	m_bDraw = false;
	m_DrawType = DT_LINE;
	m_nWidth = 0;
}

Cdraw3View::~Cdraw3View()
{
}

BOOL Cdraw3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	m_Menu.LoadMenu(IDR_MENU1);

	return CView::PreCreateWindow(cs);
}

// Cdraw3View 绘图

void Cdraw3View::OnDraw(CDC* /*pDC*/)
{
	Cdraw3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
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
	m_bDraw = true;

	CView::OnLButtonDown(nFlags, point);
}


void Cdraw3View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CClientDC dc(this);
	CPen pen(PS_SOLID, 2, RGB(23, 53, 166));
	CPen* pOldPen = dc.SelectObject(&pen);
	switch (m_DrawType)
	{
	case DT_LINE:
	{
		dc.MoveTo(m_pOrigin);
		dc.LineTo(point);
	}
	break;
	case DT_RECT:
	{
		dc.Rectangle(CRect(m_pOrigin, point));
	}
	break;
	case DT_ELLIPSE:
	{
		dc.Ellipse(CRect(m_pOrigin, point));
	}
	break;
	case DT_PEN:
	{

	}
	break;
	default:
		break;
	}
	dc.SelectObject(pOldPen);

	m_bDraw = false;

	CView::OnLButtonUp(nFlags, point);
}


void Cdraw3View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (m_DrawType == DT_PEN)
	{
		CClientDC dc(this);
		CPen pen(PS_DASH, 5, RGB(255, 231, 233));
		CPen* pOldPen = dc.SelectObject(&pen);
		if (m_bDraw)
		{
			dc.MoveTo(m_pOrigin);
			dc.LineTo(point);
			m_pOrigin = point;
		}
		//dc.SelectObject(pOldPen);
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


void Cdraw3View::OnLine()
{
	// TODO: 在此处添加实现代码.
	MessageBox(_T("Draw Line"));
	m_DrawType = DT_LINE;
}
