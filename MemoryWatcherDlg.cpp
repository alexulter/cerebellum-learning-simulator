// MemoryWatcherDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MemoryWatcher.h"
#include "MemoryWatcherDlg.h"

#include "SelectProcessDlg.h"
#include "SettingsDlg.h"

//#include <windows.h>
//#include <stdio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMemoryWatcherDlg dialog


CMemoryWatcherDlg::CMemoryWatcherDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMemoryWatcherDlg::IDD, pParent)
{
	m_MaxMem = 300; //20971520; // 20 MB
	m_NumSteps = 200;
	m_TimeStep = 20;//40;//100; // 0.1 sec
	m_ImgWidth = 1000;
	m_ImgHeight = 400;
	running = false;
	//f.open(L"log.txt");
	//f << L"# process " << m_ProcessName << "\n" << L"# step " << m_TimeStep << L"\n";

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
void CMemoryWatcherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_SELECT, m_btnSelect);
	DDX_Control(pDX, IDC_BTN_SETTINGS, m_btnSettings);
	DDX_Control(pDX, IDC_BTN_PAUSE, m_btnPause);
	DDX_Control(pDX, IDC_MY_STATIC, MyDrawArea);
}

BEGIN_MESSAGE_MAP(CMemoryWatcherDlg, CDialog)
	//ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	//ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_SELECT, &CMemoryWatcherDlg::OnBnClickedBtnSelect)
	ON_BN_CLICKED(IDC_BTN_SETTINGS, &CMemoryWatcherDlg::OnBnClickedBtnSettings)
	ON_BN_CLICKED(IDC_BTN_PAUSE, &CMemoryWatcherDlg::OnBnClickedBtnPause)
END_MESSAGE_MAP()


// CMemoryWatcherDlg message handlers

BOOL CMemoryWatcherDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	MyDrawArea.img = new CImage();
	MyDrawArea.img->Create(m_ImgWidth, m_ImgHeight, 32);
	//purk = new Purkinje;
	MyDrawArea.SetTimer(1, m_TimeStep, NULL);
//////////	MyDrawArea.draw_vect_1 = purk.out_var_1; !!!!!!!!!!!!!!!!!!!!!!!!!!!1
	running = true;
	h = NULL;
	CString caption;
	caption.Format(L"Purkinje Watcher");
	SetWindowText(caption);
	CRect R, R1;
	m_btnSelect.GetWindowRect(&R1);
	GetWindowRect(&R);
	ClientToScreen(&R1);
	R.bottom = R.top + R1.Height() + m_ImgHeight + 75;
	R.right = R.left + m_ImgWidth + 50;
	SetWindowPos(0, R.left, R.top, R.Width(), R.Height(), 0);
	MyDrawArea.SetWindowPos(0, R.left+25, R.top+50, m_ImgWidth, m_ImgHeight, 0);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

//void CMemoryWatcherDlg::OnPaint()
//{
//	if (IsIconic())
//	{
//		CPaintDC dc(this); // device context for painting
//
//		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
//
//		// Center icon in client rectangle
//		int cxIcon = GetSystemMetrics(SM_CXICON);
//		int cyIcon = GetSystemMetrics(SM_CYICON);
//		CRect rect;
//		GetClientRect(&rect);
//		int x = (rect.Width() - cxIcon + 1) / 2;
//		int y = (rect.Height() - cyIcon + 1) / 2;
//
//		// Draw the icon
//		dc.DrawIcon(x, y, m_hIcon);
//	}
//	else
//	{
//		CDialog::OnPaint();
//	}
//	//DrawImage();
//}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMemoryWatcherDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CMemoryWatcherDlg::OnOK(void)
{
	Clear();
//	f.close();
	CDialog::OnOK();
}

void CMemoryWatcherDlg::OnCancel(void)
{
	Clear();
//	f.close();
	CDialog::OnCancel();
}

void CMemoryWatcherDlg::Clear(void)
{
	MyDrawArea.KillTimer(1);
	delete MyDrawArea.img;
	MyDrawArea.img = NULL;
	running = false;
	CloseHandle(h);
	h = NULL;
}


void CMemoryWatcherDlg::OnBnClickedBtnSelect()
{
	CSelectProcessDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CloseHandle(h);
		h = NULL;
		//f << L"# process " << m_ProcessName.GetBuffer() << L"\n";
		CString caption;
//		caption.Format(L"Memory Watcher - process %s", m_ProcessName);
		SetWindowText(caption);
	}
}

void CMemoryWatcherDlg::OnBnClickedBtnSettings()
{
	CSettingsDlg dlg;
	dlg.m_TimeStep = m_TimeStep;
	dlg.m_NumSteps = m_NumSteps;
	dlg.m_MaxMem = m_MaxMem;
	dlg.m_Height = m_ImgHeight;
	dlg.m_Width = m_ImgWidth;
	if (dlg.DoModal() == IDOK)
	{
		m_TimeStep = dlg.m_TimeStep;
		m_NumSteps = dlg.m_NumSteps;
		m_MaxMem = dlg.m_MaxMem;
		m_ImgHeight = dlg.m_Height;
		m_ImgWidth = dlg.m_Width;
		//f << L"# step " << m_TimeStep << L"\n";
		Restart();
	}
}

void CMemoryWatcherDlg::Restart(void)
{
//	Clear();
//	img = new CImage;
//	img->Create(m_ImgWidth, m_ImgHeight, 32);
//	SetTimer(1, m_TimeStep, NULL);
//	running = true;
////	while (points.size()) points.pop();
////	while (points_pagefile.size()) points_pagefile.pop();
//	while (points_liana.size()) points_liana.pop();
//	while (points_mauk.size()) points_mauk.pop();
//	for (UINT i = 0; i < m_NumSteps; i++)
//	{
//		//points.push(0);
//		//points_pagefile.push(0);
//		points_mauk.push(0);
//		points_liana.push(0);
//	}
//	CRect R, R1;
//	m_btnSelect.GetWindowRect(&R1);
//	GetWindowRect(&R);
//	ClientToScreen(&R1);
//	R.bottom = R.top + 26 + R1.Height() + 15 + m_ImgHeight + 10;
//	R.right = R.left + m_ImgWidth + 25;
//	SetWindowPos(0, R.left, R.top, R.Width(), R.Height(), 0);
//	this->RedrawWindow();
}

void CMemoryWatcherDlg::OnBnClickedBtnPause()
{
	if (running)
		MyDrawArea.KillTimer(1);
	else
		MyDrawArea.SetTimer(1, m_TimeStep, NULL);
	running = !running;
}