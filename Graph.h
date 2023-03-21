#pragma once
#include <afx.h>

class Graph :
    public CObject
{
public:
    Graph(UINT drawtype, int PenStyle, int Width, COLORREF Color);
    //��ӵ㵽����
    void AddPoint(CPoint point);
    void AddPoint(CPoint start, CPoint end);
    void Draw(CDC* pDC);
public:
    //��������
    UINT m_nDrawType;
    //�������
    CArray<CPoint>m_Points;
    //���ʵ�����
    int m_nPenStyle;
    int m_nWidth;
    COLORREF m_crColor;
};

