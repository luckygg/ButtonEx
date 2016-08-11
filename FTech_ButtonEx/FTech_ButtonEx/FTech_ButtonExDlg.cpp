
// FTech_ButtonExDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FTech_ButtonEx.h"
#include "FTech_ButtonExDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFTech_ButtonExDlg dialog

CFTech_ButtonExDlg::CFTech_ButtonExDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFTech_ButtonExDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pbtnTest4 = NULL;
}

void CFTech_ButtonExDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_btnTest1);
	DDX_Control(pDX, IDC_BUTTON2, m_btnTest2);
	DDX_Control(pDX, IDC_BUTTON3, m_btnTest3);
}

BEGIN_MESSAGE_MAP(CFTech_ButtonExDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CFTech_ButtonExDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CFTech_ButtonExDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CFTech_ButtonExDlg message handlers

BOOL CFTech_ButtonExDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_btnTest1.SetEnable(true);
	m_btnTest1.SetColorBkg(255,41,41,41);
	m_btnTest1.SetColorBorder(255,41,41,41);
	m_btnTest1.LoadImageFromResource(IDB_PNG1, true);
	m_btnTest1.SetText(L"Button");
	m_btnTest1.SetAlignTextRM();
	m_btnTest1.SetOffsetText(-10,0);
	m_btnTest1.SetSizeImage(5,5,50,50);

	m_btnTest2.LoadImageFromFile(L"save.png");
	m_btnTest2.SetColorBkg(255,61,61,61);
	m_btnTest2.SetColorBorder(255,61,61,61);
	m_btnTest2.SetText(L"");

	m_btnTest3.SetEnable(false);
	m_btnTest3.SetText(L"Disabled");

	m_pbtnTest4 = new CButtonEx();
	m_pbtnTest4->CreateContol(this,CRect(145,75,270,130),2000);
	m_pbtnTest4->SetText(L"Dynamic");
	m_pbtnTest4->SetColorBkg(255,128,128,128);
	m_pbtnTest4->SetColorBorder(255,0,255,0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFTech_ButtonExDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFTech_ButtonExDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFTech_ButtonExDlg::OnBnClickedButton1()
{
	AfxMessageBox(L"click");
}


void CFTech_ButtonExDlg::OnBnClickedButton3()
{
	AfxMessageBox(L"click");
}

BOOL CFTech_ButtonExDlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{ 
	if(wParam == m_pbtnTest4->GetDlgCtrlID())
	{
		AfxMessageBox(L"Dynamic Button");
	} 

	return CDialogEx::OnCommand(wParam, lParam); 
}