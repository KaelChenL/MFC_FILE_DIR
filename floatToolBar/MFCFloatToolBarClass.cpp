/************************************************************************************/
/****	MFCFloatToolBarClass.cpp : implementation file							 ****/
/****	MFCFloatToolBarClass.cpp : implementation file							 ****/
/****	Author: Marius C. 1998 Dec 14.				 // do not remove this line  ****/
/****				The code is supplied without any waranty. The code can		 ****/
/****				be changed or modified.										 ****/
/************************************************************************************/
#include "stdafx.h"
#include "DialogCuTBar.h"
#include "StTbar.h"
#include "MFCFloatToolBarClass.h"

/************************************************************************************/
/****	CFloatBar class															 ****/
/************************************************************************************/

CFlaotToolBar::CFlaotToolBar() {}
CFlaotToolBar::~CFlaotToolBar() {}
BEGIN_MESSAGE_MAP(CFlaotToolBar, CStatic)
	ON_WM_DESTROY()
END_MESSAGE_MAP()
/************************************************************************************/
// CStTbar message handlers
// the static is used as a place holder for miniframe wns
/************************************************************************************/
void CFlaotToolBar::PreSubclassWindow()
{
	CStatic::PreSubclassWindow();

	RECT rt; 
	GetWindowRect(&rt);
	GetParent()->ScreenToClient(&rt);
	// hide the place holder, no not destro it I need it to rerout the messages
	ShowWindow(SW_HIDE);

	// make it on the heap as long  CMyMiniFrm::OnNcDestroy call 'delete this' 
	// save me to map one more message
	m_minifrm = new CMyMiniFrm();
	m_minifrm->Create(
		AfxRegisterWndClass(0, 0, 0),
		"", 
		WS_VISIBLE | WS_CHILD, 
		rt, 
		GetParent()/*of placeholder*/
		);

	if (!m_wndToolBar.Create(m_minifrm) ||
		!m_wndToolBar.LoadToolBar(GetDlgCtrlID()))//在这里加载对话框的TOOLBAR的资源ID，根据需要修改
	{
		TRACE0("Failed to create toolbar\n");
		return;      // fail to create
	}
	m_wndToolBar.SetBarStyle(
		m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | 
		CBRS_FLYBY | 
		CBRS_BORDER_ANY | 
		CBRS_SIZE_DYNAMIC | 
		0x800 | 
		CBRS_GRIPPER
		);
	// show the window

	//在这里可以对m_wndToolBar进行操作，添加ico图标等
	FloatToolBarInit();

	m_wndToolBar.ShowWindow(SW_SHOW);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_minifrm->EnableDocking(CBRS_ALIGN_ANY);
	// dock horiz if cx of static is bigger than cy
	if (rt.right - rt.left > rt.bottom - rt.top)
		m_minifrm->DockControlBar(&m_wndToolBar, AFX_IDW_DOCKBAR_TOP);
	else
		// dock verically
		m_minifrm->DockControlBar(&m_wndToolBar, AFX_IDW_DOCKBAR_RIGHT);
	m_minifrm->RecalcLayout();
}
/*根据需要修改*/
void CFlaotToolBar::FloatToolBarInit()
{
	CImageList m_ImageList;
	//设置图标
	m_ImageList.Create(32, 32, ILC_COLOR32 | ILC_MASK, 2, 2); //后面两个参数2,2，不重要。随便指定

	m_ImageList.Add(AfxGetApp()->LoadIcon(IDR_MAINFRAME));//加载ico图标
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDR_MAINFRAME));//加载ico图标

	m_wndToolBar.GetToolBarCtrl().SetImageList(&m_ImageList);
	m_ImageList.Detach();//imageList附加到ToolBar
	m_wndToolBar.SetButtons(NULL, 2); //共2个按钮
									  // 下面设置每个工具按钮文字，设置后，每个图标下面就显示相应的文字。也可以不设置
	m_wndToolBar.SetButtonInfo(0, ID_TOOLBAR_1, TBSTYLE_BUTTON, 0);//ID_TOOLBAR_1为ToolBar按键的资源ID
	m_wndToolBar.SetButtonText(0, _T("SEARCH"));//图标下面就显示的文字

	m_wndToolBar.SetButtonInfo(0, ID_TOOLBAR_2, TBSTYLE_BUTTON, 0);//ID_TOOLBAR_2为ToolBar按键的资源ID
	m_wndToolBar.SetButtonText(0, _T("SEARCH"));//图标下面就显示的文字

	m_wndToolBar.SetSizes(CSize(51, 51), CSize(32, 32));//第一个参数设置按键大小，第二个参数设置图标大小
}


void CFlaotToolBar::OnDestroy()
{
	// nothing to clean
	CStatic::OnDestroy();
}

void CFlaotToolBar::PreTranslate(MSG* pMsg)
{
	// forward this to the toolbar 
	if (m_wndToolBar.IsWindowVisible())
	{
		m_wndToolBar.OnUpdateCmdUI(m_minifrm, TRUE);
	}
}

/************************************************************************************/
/****	CFlaotToolBarMiniFrame class											 ****/
/************************************************************************************/
CFlaotToolBarMiniFrame::CFlaotToolBarMiniFrame() {}
CFlaotToolBarMiniFrame::~CFlaotToolBarMiniFrame() {}
BEGIN_MESSAGE_MAP(CFlaotToolBarMiniFrame, CMiniFrameWnd)

END_MESSAGE_MAP()

/************************************************************************************/
// CMyMiniFrm message handlers
/************************************************************************************/
BOOL CFlaotToolBarMiniFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// pass those up in the dialog to leave the OnUpdateUI mechanism to flow
	BOOL br = GetParent()->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
	// leave the default proc to handles the tooltip updating mechanism
	CMiniFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
	return br;	// return what the parent returns
}

