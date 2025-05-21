#pragma once
#include "afxdialogex.h"


// registerform dialog

class registerform : public CDialogEx
{
	DECLARE_DYNAMIC(registerform)

public:
	registerform(CWnd* pParent = nullptr);   // standard constructor
	virtual ~registerform();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CButton m_add;
	
	CEdit m_mail;
	CEdit m_phone;
	CButton m_male;
	CButton m_female;
	CComboBox m_cource;
	CComboBox m_collage;
	CEdit m_address;
	CEdit m_name;
	afx_msg void OnBnClickedButtonadd();


	bool m_isEditMode = false; // to track edit or insert
	CString m_editPhone;       // phone number as unique key
	

	void SetStudentData(const CString& name,
		const CString& email,
		const CString& phone,
		const CString& gender,
		const CString& course,
		const CString& college,
		const CString& address);


	
};
