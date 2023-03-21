#include "pch.h"
#include "Graph.h"

#pragma once
#include "draw3.h"


Graph::Graph(UINT drawtype, int PenStyle, int Width, COLORREF Color) :m_nDrawType(drawtype)
{
	m_nPenStyle = PenStyle;
	m_nWidth = Width;
	m_crColor = Color;
}

void Graph::AddPoint(CPoint point)
{
	m_Points.Add(point);
}

void Graph::AddPoint(CPoint start, CPoint end)
{
	m_Points.Add(start);
	m_Points.Add(end);
}

void Graph::Draw(CDC* pDC)
{
	switch (m_nDrawType)
	{
	case DT_LINE:
	{
		CPen pen(m_nPenStyle, m_nWidth, m_crColor);
		CPen* pOldPen = pDC->SelectObject(&pen);
		pDC->MoveTo(m_Points.GetAt(0));
		pDC->LineTo(m_Points.GetAt(1));
		pDC->SelectObject(pOldPen);
		break;
	}
	case DT_RECT:
	{
		CPen pen(m_nPenStyle, m_nWidth, m_crColor);
		CPen* pOldPen = pDC->SelectObject(&pen);
		pDC->Rectangle(CRect(m_Points.GetAt(0), m_Points.GetAt(1)));
		pDC->SelectObject(pOldPen);
		break;
	}
	case DT_ELLIPSE:
	{
		CPen pen(m_nPenStyle, m_nWidth, m_crColor);
		CPen* pOldPen = pDC->SelectObject(&pen);
		pDC->Ellipse(CRect(m_Points.GetAt(0), m_Points.GetAt(1)));
		pDC->SelectObject(pOldPen);
		break;
	}
	case DT_PEN:
	{
		CPen pen(m_nPenStyle, m_nWidth, m_crColor);
		CPen* pOldPen = pDC->SelectObject(&pen);
		int num = m_Points.GetSize();
		for (int j = 0; j < num - 1; j++)
		{
			pDC->MoveTo(m_Points.GetAt(j));
			pDC->LineTo(m_Points.GetAt(j + 1));
		}
		pDC->SelectObject(pOldPen);
		break;
	}
	}
}
