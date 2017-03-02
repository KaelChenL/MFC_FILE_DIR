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
		!m_wndToolBar.LoadToolBar(GetDlgCtrlID()))//��������ضԻ����TOOLBAR����ԴID��������Ҫ�޸�
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

	//��������Զ�m_wndToolBar���в��������icoͼ���
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
/*������Ҫ�޸�*/
void CFlaotToolBar::FloatToolBarInit()
{
	CImageList m_ImageList;
	//����ͼ��
	m_ImageList.Create(32, 32, ILC_COLOR32 | ILC_MASK, 2, 2); //������������2,2������Ҫ�����ָ��

	m_ImageList.Add(AfxGetApp()->LoadIcon(IDR_MAINFRAME));//����icoͼ��
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDR_MAINFRAME));//����icoͼ��

	m_wndToolBar.GetToolBarCtrl().SetImageList(&m_ImageList);
	m_ImageList.Detach();//imageList���ӵ�ToolBar
	m_wndToolBar.SetButtons(NULL, 2); //��2����ť
									  // ��������ÿ�����߰�ť���֣����ú�ÿ��ͼ���������ʾ��Ӧ�����֡�Ҳ���Բ�����
	m_wndToolBar.SetButtonInfo(0, ID_TOOLBAR_1, TBSTYLE_BUTTON, 0);//ID_TOOLBAR_1ΪToolBar��������ԴID
	m_wndToolBar.SetButtonText(0, _T("SEARCH"));//ͼ���������ʾ������

	m_wndToolBar.SetButtonInfo(0, ID_TOOLBAR_2, TBSTYLE_BUTTON, 0);//ID_TOOLBAR_2ΪToolBar��������ԴID
	m_wndToolBar.SetButtonText(0, _T("SEARCH"));//ͼ���������ʾ������

	m_wndToolBar.SetSizes(CSize(51, 51), CSize(32, 32));//��һ���������ð�����С���ڶ�����������ͼ���С
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

