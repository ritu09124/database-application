#pragma once
#include "afxdialogex.h"


// studentdata dialog

class studentdata : public CDialogEx
{
	DECLARE_DYNAMIC(studentdata)

public:
	studentdata(CWnd* pParent = nullptr);   // standard constructor
	virtual ~studentdata();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_report;
	afx_msg void OnLvnItemchangedListstudent(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();

};
