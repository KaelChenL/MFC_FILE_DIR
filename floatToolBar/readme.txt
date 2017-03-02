1.将.cpp和.h添加到MFC工程，包含需要的头文件
2.在对话款中添加static控件，绑定变量为.cpp的class类型：
	DDX_Control(pDX, IDC_STATICTBAR, m_stbar);
3.在Dlg.cpp中添加函数：
BOOL Cfloat_toolbar_dlgDlg::PreTranslateMessage(MSG* pMsg)	// << ADD THIS
{
	// Reroute message to the miniframe wnd
	if(m_stbar.m_hWnd)
	{
		m_stbar.PreTranslate(pMsg);
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}