1.��.cpp��.h��ӵ�MFC���̣�������Ҫ��ͷ�ļ�
2.�ڶԻ��������static�ؼ����󶨱���Ϊ.cpp��class���ͣ�
	DDX_Control(pDX, IDC_STATICTBAR, m_stbar);
3.��Dlg.cpp����Ӻ�����
BOOL Cfloat_toolbar_dlgDlg::PreTranslateMessage(MSG* pMsg)	// << ADD THIS
{
	// Reroute message to the miniframe wnd
	if(m_stbar.m_hWnd)
	{
		m_stbar.PreTranslate(pMsg);
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}