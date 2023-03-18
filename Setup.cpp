// Setup.cpp: 实现文件
//

#include "pch.h"
#include "draw3.h"
#include "Setup.h"
#include "afxdialogex.h"


// Setup 对话框

IMPLEMENT_DYNAMIC(Setup, CDialogEx)

Setup::Setup(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_SETUP, pParent)
	, m_nLineWidth(0)
	//, m_nLineWidth(0)
	, m_nLineStyle(0)
{

}

Setup::~Setup()
{
}

void Setup::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Text(pDX, IDC_EDIT1, m_nLineWidth);
	//DDV_MinMaxUInt(pDX, m_nLineWidth, 1, 30);
	DDX_Slider(pDX, IDC_SLIDER1, (int&)m_nLineWidth);
	DDX_Radio(pDX, IDC_RADIO1, m_nLineStyle);
}


BEGIN_MESSAGE_MAP(Setup, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Setup::OnBnClickedButton1)
END_MESSAGE_MAP()


// Setup 消息处理程序


BOOL Setup::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//获得滑块控件
	CSliderCtrl* slide = (CSliderCtrl*)GetDlgItem(IDC_SLIDER1);

	//修改滑块控件的属性
	slide->SetRange(1, 30);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void Setup::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//打开颜色对话框
	CColorDialog colDlg;
	/*
	* CColorDialog dlg;
	* dlg.m_cc.Flags = CC_RGBINIT;
	* 这样在运行的时候会弹出非法操作警告，
	* 其原因就是在定义dlg的时候就已经对Flags初始化了一个值。
	* 然而其解决办法就是让CC_RGBINIT与初始化的那个值做或赋值
	* 改为 dlg.m_cc.Flags |= CC_RGBINIT
	*/
	colDlg.m_cc.Flags |= CC_RGBINIT; //或赋值
	colDlg.m_cc.rgbResult = m_color;
	if (IDOK == colDlg.DoModal())
	{
		m_color = colDlg.m_cc.rgbResult;
	}
}
