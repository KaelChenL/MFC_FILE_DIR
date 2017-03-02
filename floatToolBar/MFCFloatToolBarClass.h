/************************************************************************************/
/****	MFCFloatToolBarClass.h : implementation file							 ****/
/****	MFCFloatToolBarClass.h : implementation file							 ****/
/****	Author: Marius C. 1998 Dec 14.				 // do not remove this line  ****/
/****				The code is supplied without any waranty. The code can		 ****/
/****				be changed or modified.										 ****/
/************************************************************************************/

#pragma once
#ifndef _MFC_FLOATTOOLBAR_CLASS_H_
#define _MFC_FLOATTOOLBAR_CLASS_H_

/************************************************************************************/
/****	CFlaotToolBarMiniFrame class											 ****/
/************************************************************************************/
class CFlaotToolBarMiniFrame : public CMiniFrameWnd
{

public:
	CFlaotToolBarMiniFrame();           // protected constructor used by dynamic creation

public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

protected:
	virtual ~CFlaotToolBarMiniFrame();

	DECLARE_MESSAGE_MAP()
};

/************************************************************************************/
/****	CFloatBar class															 ****/
/************************************************************************************/
class CFlaotToolBar : public CStatic
{
	// Construction
public:
	CFlaotToolBar();

protected:
	virtual void PreSubclassWindow();

	void FloatToolBarInit();

public:
	virtual ~CFlaotToolBar();

	// Generated message map functions
protected:
	afx_msg void OnDestroy();

	DECLARE_MESSAGE_MAP()
	CToolBar		m_wndToolBar;
	CFlaotToolBarMiniFrame*		m_minifrm;
public:
	void PreTranslate(MSG* pMsg);
	CToolBar& GetTBar() { return m_wndToolBar; };
};


#endif //_MFC_FLOATTOOLBAR_CLASS_H_