// search.cpp : implementation file
//

#include "pch.h"
#include "database application.h"
#include "afxdialogex.h"
#include "search.h"
#include "database applicationDlg.h"
#include "c:\Users\LENOVO\Documents\c++ examples\sqlite3.h"
#include "admin.h"
#include "registerform.h"

// search dialog

IMPLEMENT_DYNAMIC(search, CDialogEx)

search::search(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
{

}

search::~search()
{
}

void search::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_name, m_name);
    DDX_Control(pDX, IDC_EDIT_mono, m_mono);
    DDX_Control(pDX, IDC_BUTTON_search, m_search);
    DDX_Control(pDX, IDC_LIST1, m_resultlist);
    DDX_Control(pDX, IDC_BUTTON_delete, m_delete);
   
    DDX_Control(pDX, IDC_BUTTON_cancel, cancel);
}


BEGIN_MESSAGE_MAP(search, CDialogEx)
	
	ON_EN_CHANGE(IDC_EDIT_name, &search::OnEnChangeEditname)
	ON_EN_CHANGE(IDC_EDIT_mono, &search::OnEnChangeEditmono)
	ON_BN_CLICKED(IDC_BUTTON_search, &search::OnBnClickedButtonsearch)
    ON_BN_CLICKED(IDC_BUTTON_delete, &search::OnBnClickedButtondelete)
    
    ON_BN_CLICKED(IDC_BUTTON_cancel, &search::OnBnClickedButtoncancel)
END_MESSAGE_MAP()


// search message handlers


void search::OnEnChangeEditname()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void search::OnEnChangeEditmono()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

BOOL search::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    m_resultlist.InsertColumn(0, _T("Name"), LVCFMT_LEFT, 200);
    m_resultlist.InsertColumn(1, _T("Email"), LVCFMT_LEFT, 170);
    m_resultlist.InsertColumn(2, _T("Phone"), LVCFMT_LEFT, 150);
    m_resultlist.InsertColumn(3, _T("Gender"), LVCFMT_LEFT, 100);
    m_resultlist.InsertColumn(4, _T("Course"), LVCFMT_LEFT, 100);
    m_resultlist.InsertColumn(5, _T("College"), LVCFMT_LEFT, 150);
    m_resultlist.InsertColumn(6, _T("Address"), LVCFMT_LEFT, 200);

    return TRUE; 
}


void search::OnBnClickedButtonsearch()
{
    CString nameInput, phoneInput;
    m_name.GetWindowTextW(nameInput);
    m_mono.GetWindowTextW(phoneInput);

    m_resultlist.DeleteAllItems();



    sqlite3* db;
    sqlite3_stmt* stmt;
    int rc = sqlite3_open("student_database.db", &db);

    if (rc != SQLITE_OK) {
        AfxMessageBox(_T("Failed to open database."));
        return;
    }

    
    CStringA query;
    if (!nameInput.IsEmpty() && !phoneInput.IsEmpty()) {
        CT2A nameA(nameInput);
        CT2A phoneA(phoneInput);
        query.Format("SELECT * FROM Students WHERE Name LIKE '%%%s%%' AND Phone LIKE '%%%s%%';",
            (LPCSTR)nameA, (LPCSTR)phoneA);
    }
    else if (!nameInput.IsEmpty()) {
        CT2A nameA(nameInput);
        query.Format("SELECT * FROM Students WHERE Name LIKE '%%%s%%';", (LPCSTR)nameA);
    }
    else if (!phoneInput.IsEmpty()) {
        CT2A phoneA(phoneInput);
        query.Format("SELECT * FROM Students WHERE Phone LIKE '%%%s%%';", (LPCSTR)phoneA);
    }
    else {
        AfxMessageBox(_T("Please enter a Name or Phone Number to search."));
        sqlite3_close(db);
        return;
    }

    rc = sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        AfxMessageBox(_T("Failed to execute search query."));
        sqlite3_close(db);
        return;
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

        m_resultlist.InsertItem(row, name);
        m_resultlist.SetItemText(row, 1, email);
        m_resultlist.SetItemText(row, 2, phone);
        m_resultlist.SetItemText(row, 3, gender);
        m_resultlist.SetItemText(row, 4, course);
        m_resultlist.SetItemText(row, 5, college);
        m_resultlist.SetItemText(row, 6, address);

        row++;
    }

    if (row == 0) {
        AfxMessageBox(_T("No records found."));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}


void search::OnBnClickedButtondelete()
{
    CString nameInput, phoneInput;
    m_name.GetWindowTextW(nameInput);
    m_mono.GetWindowTextW(phoneInput);

    if (nameInput.IsEmpty() && phoneInput.IsEmpty()) {
        AfxMessageBox(_T("Please enter a Name or Phone Number to delete."));
        return;
    }

    int response = AfxMessageBox(_T("Are you sure you want to delete the matching record(s)?"), MB_YESNO | MB_ICONWARNING);
    if (response != IDYES) return;

    sqlite3* db;
    sqlite3_stmt* stmt;
    int rc = sqlite3_open("student_database.db", &db);

    if (rc != SQLITE_OK) {
        AfxMessageBox(_T("Failed to open database."));
        return;
    }

    CStringA query;
    if (!nameInput.IsEmpty() && !phoneInput.IsEmpty()) {
        CT2A nameA(nameInput);
        CT2A phoneA(phoneInput);
        query.Format("DELETE FROM Students WHERE Name LIKE '%%%s%%' AND Phone LIKE '%%%s%%';", (LPCSTR)nameA, (LPCSTR)phoneA);
    }
    else if (!nameInput.IsEmpty()) {
        CT2A nameA(nameInput);
        query.Format("DELETE FROM Students WHERE Name LIKE '%%%s%%';", (LPCSTR)nameA);
    }
    else if (!phoneInput.IsEmpty()) {
        CT2A phoneA(phoneInput);
        query.Format("DELETE FROM Students WHERE Phone LIKE '%%%s%%';", (LPCSTR)phoneA);
    }

    rc = sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);
    if (rc == SQLITE_OK) {
        rc = sqlite3_step(stmt);
        if (rc == SQLITE_DONE) {
            AfxMessageBox(_T("Record deleted successfully."));
            m_resultlist.DeleteAllItems(); 
        }
        else {
            AfxMessageBox(_T("Failed to delete record(s)."));
        }
    }
    else {
        AfxMessageBox(_T("Error preparing delete statement."));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}




void search::OnBnClickedButtoncancel()
{
    EndDialog(IDCANCEL); 
    admin a;
    a.DoModal();
}
