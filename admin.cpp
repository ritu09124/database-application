// admin.cpp : implementation file
//

#include "pch.h"
#include "database application.h"
#include "afxdialogex.h"
#include "admin.h"
#include "database applicationDlg.h"
#include "studentdata.h"
#include "search.h"

// admin dialog

IMPLEMENT_DYNAMIC(admin, CDialogEx)

admin::admin(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

admin::~admin()
{
}

void admin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_view, m_view);
	DDX_Control(pDX, IDC_BUTTON_search, m_search);

}


BEGIN_MESSAGE_MAP(admin, CDialogEx)
	
	ON_BN_CLICKED(IDC_BUTTON_search, &admin::OnBnClickedButtonsearch)
	ON_BN_CLICKED(IDC_BUTTON_view, &admin::OnBnClickedButtonview)
END_MESSAGE_MAP()


// admin message handlers
void admin::OnBnClickedButtonview()
{
	studentdata s1;
	s1.DoModal();
}

void admin::OnBnClickedButtonsearch()
{
	search s;
	s.DoModal();
}
