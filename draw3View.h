
// draw3View.h: Cdraw3View 类的接口
//

#pragma once
#include "Graph.h"


class Cdraw3View : public CView
{
protected: // 仅从序列化创建
	Cdraw3View() noexcept;
	DECLARE_DYNCREATE(Cdraw3View)

// 特性
public:
	Cdraw3Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~Cdraw3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
	CPoint m_pOrigin;
	bool m_bDraw;
	enum DRAW_TYPE m_DrawType;
public:
	int m_nWidth;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDrawLine();
	afx_msg void OnDrawRect();
	afx_msg void OnDrawEllipse();
	afx_msg void OnDrawPen();
	afx_msg void OnUpdateDrawEllipse(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawPen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawRect(CCmdUI* pCmdUI);
protected:
	CMenu m_Menu;
public:
	//存储所有的绘制信息
	CArray<Graph*> m_pGraphs;
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);	
	afx_msg void OnFileSetup();
protected:
	UINT m_nLineWidth;
	int m_nLineStyle;
	COLORREF m_color;
	CDC m_dcCompatible;
	Graph* m_tmpGraph;
public:
	afx_msg void OnFileWrite();
	afx_msg void OnFileRead();
};

#ifndef _DEBUG  // draw3View.cpp 中的调试版本
inline Cdraw3Doc* Cdraw3View::GetDocument() const
   { return reinterpret_cast<Cdraw3Doc*>(m_pDocument); }
#endif

