#pragma once
#include "afxdialogex.h"


// admin dialog

class admin : public CDialogEx
{
	DECLARE_DYNAMIC(admin)

public:
	admin(CWnd* pParent = nullptr);   // standard constructor
	virtual ~admin();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CButton m_view;
	CButton m_search;
	CButton m_daleteview;
	afx_msg void OnBnClickedButtondeleteview();
	afx_msg void OnBnClickedButtonsearch();
	afx_msg void OnBnClickedButtonview();
};
