
// FTech_ButtonExDlg.h : header file
//

#pragma once

#include "ButtonEx.h"

// CFTech_ButtonExDlg dialog
class CFTech_ButtonExDlg : public CDialogEx
{
// Construction
public:
	CFTech_ButtonExDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_FTECH_BUTTONEX_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CButtonEx m_btnTest1;
	CButtonEx m_btnTest2;
	CButtonEx m_btnTest3;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
};
