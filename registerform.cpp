// registerform.cpp : implementation file
//

#include "pch.h"
#include "database application.h"
#include "afxdialogex.h"
#include "registerform.h"
#include "database applicationDlg.h"
#include "c:\Users\LENOVO\Documents\c++ examples\sqlite3.h"
#include "string"

sqlite3* db;
// registerform dialog

IMPLEMENT_DYNAMIC(registerform, CDialogEx)

registerform::registerform(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

registerform::~registerform()
{
}

void registerform::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_add, m_add);
	
	
	DDX_Control(pDX, IDC_EDIT_mail, m_mail);
	DDX_Control(pDX, IDC_EDIT_phoneno, m_phone);
	DDX_Control(pDX, IDC_RADIO_male, m_male);
	DDX_Control(pDX, IDC_RADIO_female, m_female);
	DDX_Control(pDX, IDC_COMBO_cource, m_cource);
	DDX_Control(pDX, IDC_COMBO_collage, m_collage);
	DDX_Control(pDX, IDC_EDIT_address, m_address);
	DDX_Control(pDX, IDC_EDIT_name, m_name);
}


BEGIN_MESSAGE_MAP(registerform, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_add, &registerform::OnBnClickedButtonadd)
	
END_MESSAGE_MAP()


// registerform message handlers

void registerform::OnBnClickedButtonadd()
{
   
        // Retrieve data from form controls
        CString name, email, phone, address, course, college;
        m_name.GetWindowTextW(name);
        m_mail.GetWindowTextW(email);
        m_phone.GetWindowTextW(phone);
        m_address.GetWindowTextW(address);
        m_cource.GetLBText(m_cource.GetCurSel(), course);
        m_collage.GetLBText(m_collage.GetCurSel(), college);

        CString gender;
        if (m_male.GetCheck() == BST_CHECKED)
            gender = _T("Male");
        else if (m_female.GetCheck() == BST_CHECKED)
            gender = _T("Female");
        else
            gender = _T("Other");

        // Convert CString to std::string
        std::string nameStr = CT2A(name);
        std::string emailStr = CT2A(email);
        std::string phoneStr = CT2A(phone);
        std::string addressStr = CT2A(address);
        std::string genderStr = CT2A(gender);
        std::string courseStr = CT2A(course);
        std::string collegeStr = CT2A(college);

        // 1. Open database
        int exit = sqlite3_open("student_database.db", &db);
        if (exit != SQLITE_OK) {
            CString err = CString(sqlite3_errmsg(db));
            AfxMessageBox(_T("Database connection failed: ") + err);
            return;
        }

        // 2. Create table if it doesn't exist
        const char* createTableSQL =
            "CREATE TABLE IF NOT EXISTS Students ("
            "Name TEXT, Email TEXT, Phone TEXT, Gender TEXT, "
            "Course TEXT, College TEXT, Address TEXT);";

        char* errMsg = nullptr;
        exit = sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errMsg);
        if (exit != SQLITE_OK) {
            AfxMessageBox(_T("Failed to create table: ") + CString(errMsg));
            sqlite3_free(errMsg);
            sqlite3_close(db);
            return;
        }

        CStringA insertSQL;
        insertSQL.Format(
            "INSERT INTO Students (Name, Email, Phone, Gender, Course, College, Address) "
            "VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s');",
            nameStr.c_str(), emailStr.c_str(), phoneStr.c_str(),
            genderStr.c_str(), courseStr.c_str(), collegeStr.c_str(), addressStr.c_str());

        exit = sqlite3_exec(db, insertSQL, nullptr, nullptr, &errMsg);
        if (exit != SQLITE_OK) {
            AfxMessageBox(_T("Insert failed: ") + CString(errMsg));
            sqlite3_free(errMsg);
        }
        else {
            AfxMessageBox(_T("Data inserted successfully!"));
        }

        sqlite3_close(db);
    }


