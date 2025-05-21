#pragma once
#include "afxdialogex.h"


// search dialog

class search : public CDialogEx
{
	DECLARE_DYNAMIC(search)

public:
	search(CWnd* pParent = nullptr);   // standard constructor
	virtual ~search();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	CEdit m_name;
	CEdit m_mono;
	CButton m_search;
	afx_msg void OnEnChangeEditname();
	afx_msg void OnEnChangeEditmono();
	afx_msg void OnBnClickedButtonsearch();
	CListCtrl m_resultlist;
	CButton m_delete;
	CButton m_edit;
	CButton cancel;
	afx_msg void OnBnClickedButtondelete();
	afx_msg void OnBnClickedButtonedit();
	afx_msg void OnBnClickedButtoncancel();
};
