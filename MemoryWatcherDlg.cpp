﻿// MemoryWatcherDlg.cpp : implementation file
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
	m_TimeStep = 100;//100; // 0.1 sec
	m_ImgWidth = 1000;
	m_ImgHeight = 400;
	running = false;
	m_ProcessName = GetCurrentProcessName();
	//f.open(L"log.txt");
	//f << L"# process " << m_ProcessName << "\n" << L"# step " << m_TimeStep << L"\n";
	peak = 20;
	peak_pagefile = 0;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
void CMemoryWatcherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_SELECT, m_btnSelect);
	DDX_Control(pDX, IDC_BTN_SETTINGS, m_btnSettings);
	DDX_Control(pDX, IDC_BTN_PAUSE, m_btnPause);
}

BEGIN_MESSAGE_MAP(CMemoryWatcherDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_SELECT, &CMemoryWatcherDlg::OnBnClickedBtnSelect)
	ON_BN_CLICKED(IDC_BTN_SETTINGS, &CMemoryWatcherDlg::OnBnClickedBtnSettings)
	ON_BN_CLICKED(IDC_BTN_PAUSE, &CMemoryWatcherDlg::OnBnClickedBtnPause)
END_MESSAGE_MAP()


// CMemoryWatcherDlg message handlers

BOOL CMemoryWatcherDlg::OnInitDialog()
{
	//int number = 10;
 //   char str[256];
 //   sprintf_s(str, "It works! - number: %d \n", number);
 //   OutputDebugString((LPCWSTR)str);
	//Sleep(10000);
	//printf("OK\n");

	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	purk = new Purkinje;
	img = new CImage();
	img->Create(m_ImgWidth, m_ImgHeight, 32);
	SetTimer(1, m_TimeStep, NULL);
	running = true;
	for (UINT i = 0; i < m_NumSteps; i++)
	{
		//points.push(0);
		//points_pagefile.push(0);
		points_mauk.push(0);
		points_liana.push(0);
	}
	m_ProcessID = 0;
	h = NULL;
	CString caption;
	caption.Format(L"Memory Watcher - process %s", m_ProcessName);
	SetWindowText(caption);
	CRect R, R1;
	m_btnSelect.GetWindowRect(&R1);
	GetWindowRect(&R);
	ClientToScreen(&R1);
	R.bottom = R.top + 26 + R1.Height() + 15 + m_ImgHeight + 10;
	R.right = R.left + m_ImgWidth + 25;
	SetWindowPos(0, R.left, R.top, R.Width(), R.Height(), 0);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMemoryWatcherDlg::OnPaint()
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
		CDialog::OnPaint();
	}
	DrawImage();
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMemoryWatcherDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMemoryWatcherDlg::DrawImage(void)
{
	if (!img)
	{
		CDC * dc = GetDC();
		CRect R;
		GetWindowRect(&R);
		dc->FillSolidRect(-1, -1, R.Width() + 2, R.Height() + 2, RGB(255, 255, 255));
		ReleaseDC(dc);
		return;
	}
	CDC * dc = GetDC(), * idc = CDC::FromHandle(img->GetDC());
	CRect R;
	m_btnSelect.GetWindowRect(&R);
	dc->BitBlt(10, R.Height() + 15, img->GetWidth(), img->GetHeight(), idc, 0, 0, SRCCOPY);
	ReleaseDC(dc);
	img->ReleaseDC();
}
void CMemoryWatcherDlg::OnOK(void)
{
	Clear();
	if (purk!=NULL) delete purk;	// удалить динамический объект
//	purk = NULL;
//	f.close();
	CDialog::OnOK();
}

void CMemoryWatcherDlg::OnCancel(void)
{
	Clear();
	if (purk!=NULL) delete purk;	// удалить динамический объект
//	purk = NULL;
//	f.close();
	CDialog::OnCancel();
}

void CMemoryWatcherDlg::Clear(void)
{
	KillTimer(1);
	running = false;
	CloseHandle(h);
	h = NULL;
	delete img;
	img = NULL;
	peak = 0;
	peak_pagefile = 0;
}

void CMemoryWatcherDlg::OnTimer(UINT_PTR nIDEvent)
{

	if (nIDEvent == 1)
	{
		//		SIZE_T l, total;
		//CDC * idc = CDC::FromHandle(img->GetDC());
		//CPen pen, * oldpen, * oldpen2, pen2, pen3;
		//CString s;
		//int x,y;

			for (int step = 0; step<200; step++) 
			{
			//HANDLE hThread;
			//unsigned threadID;
			//hThread = (HANDLE)_beginthreadex( NULL, 0, &purk->ComputingThread, NULL, 0, &threadID );
			//WaitForSingleObject( hThread, INFINITE );
			//CloseHandle( hThread );
			purk->StartThreadFunc();

/*				for (int mytimevar = 0; mytimevar<50; mytimevar++) 
			{
				purk->timestep++;
				purk->StepForwardOptimized();
			}//*/

			points_mauk.push(purk->PurkinjeFreqPublic/2);
			//points_liana.push(purk->PurkinjeFreqPublic+purk->alpha_Public-200);//400e+5-purk->alpha_Public);
			points_liana.push(purk->Liana_Public/2+10);
		if (points_mauk.size() > m_NumSteps + 1)
		{
			points_mauk.pop();
			points_liana.pop();
		}
		SIZE_T l, total;
		CDC * idc = CDC::FromHandle(img->GetDC());
		CPen pen, * oldpen, * oldpen2, pen2, pen3;
		CString s;
		// setting pen color
		pen.CreatePen(PS_SOLID, 3, RGB(0, 200, 0));
		oldpen = idc->SelectObject(&pen);
		double dx = double(img->GetWidth()) / (m_NumSteps - 1), dy = double(img->GetHeight()) / (m_MaxMem - 1);
		int x, y;
		// clearing image
		idc->FillSolidRect(-1, -1, img->GetWidth() + 2, img->GetHeight() + 2, RGB(0, 0, 0));
		// drawing grid
		pen2.CreatePen(PS_SOLID, 1, RGB(150, 150, 150));
		oldpen2 = idc->SelectObject(&pen2);
		//for (UINT i = 0; i < points_mauk.size(); i++)
		//{
		//	x = int(i * dx);
		//	idc->MoveTo(x, 0);
		//	idc->LineTo(x, img->GetHeight());
		//}
		//for (double i = 0.0; i < img->GetHeight(); i += img->GetHeight() / 10.0)
		//{
		//	idc->MoveTo(0, int(i));
		//	idc->LineTo(img->GetWidth(), int(i));
		//}
		idc->SelectObject(oldpen2);
		// setting text color
		idc->SetTextColor(RGB(0, 200, 0));
		// drawing points_mauk
		for (UINT i = 0; i < points_mauk.size(); i++)
		{
			l = points_mauk._Get_container()[i];
			x = int(i * dx);
			y = img->GetHeight() - int(l * dy) - 1;
			if (!i)
			{
				//idc->MoveTo(x, y);
				idc->SetPixel(x,y, RGB(150,150,150));
			}
			else
			{
				//idc->LineTo(x, y);
				idc->SetPixel(x,y, RGB(150,150,150));
			}
			if (i == points_mauk.size() - 1)
			{
	//			s.Format(L"Purkinje frequency:  %u", l /100000);
				s.Format(L"time:  %d s", purk->timestep/1000);
				idc->TextOutW(1, 1, s);
				total = l;
			}
		}
		// drawing points_liana
		// setting other pen color
		pen3.CreatePen(PS_SOLID, 3, RGB(200, 0, 0));
		oldpen2 = idc->SelectObject(&pen3);
		// setting text color
		idc->SetTextColor(RGB(200, 0, 0));
		for (UINT i = 0; i < points_liana.size(); i++)
		{
			l = points_liana._Get_container()[i];
			x = int(i * dx);
			y = img->GetHeight() - int(l * dy) - 1;
			if (!i)
			{
				//idc->MoveTo(x, y);
				idc->SetPixel(x,y, RGB(200,0,0));
			}
			else
			{
				//idc->LineTo(x, y);
				idc->SetPixel(x,y, RGB(200,0,0));
			}
//			if (i == points_liana.size() - 1)
//			{
//				s.Format(L"Swap: %u KB, peak %u KB", l / 1024, 2 / 1024);
//				idc->TextOutW(1, 17, s);
//				total += l;
//			}
		}
		// setting text color
//		idc->SetTextColor(RGB(200, 200, 0));
//		s.Format(L"Total: %u KB, peak %u KB", total / 1024, 2 / 1024);
//		idc->TextOutW(1, 33, s);
//		idc->SelectObject(oldpen2);
//		idc->SelectObject(oldpen);
		img->ReleaseDC();
		// displaying image
		DrawImage();
		// saving to file
		//f << l << L"\n";
			}
	}
	CDialog::OnTimer(nIDEvent);
}

void CMemoryWatcherDlg::OnBnClickedBtnSelect()
{
	CSelectProcessDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CloseHandle(h);
		h = NULL;
		m_ProcessID = dlg.GetSelectedProcessID();
		m_ProcessName = dlg.GetSelectedProcessName();
		//f << L"# process " << m_ProcessName.GetBuffer() << L"\n";
		CString caption;
		caption.Format(L"Memory Watcher - process %s", m_ProcessName);
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
	Clear();
	img = new CImage;
	img->Create(m_ImgWidth, m_ImgHeight, 32);
	SetTimer(1, m_TimeStep, NULL);
	running = true;
//	while (points.size()) points.pop();
//	while (points_pagefile.size()) points_pagefile.pop();
	while (points_liana.size()) points_liana.pop();
	while (points_mauk.size()) points_mauk.pop();
	for (UINT i = 0; i < m_NumSteps; i++)
	{
		//points.push(0);
		//points_pagefile.push(0);
		points_mauk.push(0);
		points_liana.push(0);
	}
	CRect R, R1;
	m_btnSelect.GetWindowRect(&R1);
	GetWindowRect(&R);
	ClientToScreen(&R1);
	R.bottom = R.top + 26 + R1.Height() + 15 + m_ImgHeight + 10;
	R.right = R.left + m_ImgWidth + 25;
	SetWindowPos(0, R.left, R.top, R.Width(), R.Height(), 0);
	this->RedrawWindow();
}

void CMemoryWatcherDlg::OnBnClickedBtnPause()
{
	if (running)
		KillTimer(1);
	else
		SetTimer(1, m_TimeStep, NULL);
	running = !running;
}
