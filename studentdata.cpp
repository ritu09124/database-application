// studentdata.cpp : implementation file
//

#include "pch.h"
#include "database application.h"
#include "afxdialogex.h"
#include "studentdata.h"
#include "database applicationDlg.h"
#include "admin.h"
#include "c:\Users\LENOVO\Documents\c++ examples\sqlite3.h"

// studentdata dialog

IMPLEMENT_DYNAMIC(studentdata, CDialogEx)

studentdata::studentdata(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

studentdata::~studentdata()
{
}

void studentdata::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_student, m_report);
}


BEGIN_MESSAGE_MAP(studentdata, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_student, &studentdata::OnLvnItemchangedListstudent)
END_MESSAGE_MAP()


BOOL studentdata::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    m_report.InsertColumn(0, _T("Name"), LVCFMT_LEFT, 200);
    m_report.InsertColumn(1, _T("Email"), LVCFMT_LEFT, 170);
    m_report.InsertColumn(2, _T("Phone"), LVCFMT_LEFT, 150);
    m_report.InsertColumn(3, _T("Gender"), LVCFMT_LEFT, 100);
    m_report.InsertColumn(4, _T("Course"), LVCFMT_LEFT, 100);
    m_report.InsertColumn(5, _T("College"), LVCFMT_LEFT, 150);
    m_report.InsertColumn(6, _T("Address"), LVCFMT_LEFT, 200);

    sqlite3* db;
    sqlite3_stmt* stmt;
    int rc = sqlite3_open("student_database.db", &db);

    if (rc != SQLITE_OK) {
        AfxMessageBox(_T("Failed to open database."));
        return TRUE;
    }

    const char* sql = "SELECT Name, Email, Phone, Gender, Course, College, Address FROM Students;";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        AfxMessageBox(_T("Failed to fetch data."));
        sqlite3_close(db);
        return TRUE;
    }

    int row = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        CString name = CString((const char*)sqlite3_column_text(stmt, 0));
        CString email = CString((const char*)sqlite3_column_text(stmt, 1));
        CString phone = CString((const char*)sqlite3_column_text(stmt, 2));
        CString gender = CString((const char*)sqlite3_column_text(stmt, 3));
        CString course = CString((const char*)sqlite3_column_text(stmt, 4));
        CString college = CString((const char*)sqlite3_column_text(stmt, 5));
        CString address = CString((const char*)sqlite3_column_text(stmt, 6));

        m_report.InsertItem(row, name);
        m_report.SetItemText(row, 1, email);
        m_report.SetItemText(row, 2, phone);
        m_report.SetItemText(row, 3, gender);
        m_report.SetItemText(row, 4, course);
        m_report.SetItemText(row, 5, college);
        m_report.SetItemText(row, 6, address);
        row++;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return TRUE;
}


void studentdata::OnLvnItemchangedListstudent(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}
