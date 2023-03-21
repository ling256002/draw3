#pragma once
#include <afx.h>

class Graph :
    public CObject
{
public:
    Graph(UINT drawtype, int PenStyle, int Width, COLORREF Color);
    //添加点到数组
    void AddPoint(CPoint point);
    void AddPoint(CPoint start, CPoint end);
    void Draw(CDC* pDC);
public:
    //绘制类型
    UINT m_nDrawType;
    //点的数组
    CArray<CPoint>m_Points;
    //画笔的属性
    int m_nPenStyle;
    int m_nWidth;
    COLORREF m_crColor;
};

