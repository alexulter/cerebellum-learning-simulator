#include "resource.h"
#pragma once


// CMyDlg dialog


class CMyDlg : public CDialog
{
//	DECLARE_DYNAMIC(CMyDlg)

public:
	CMyDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMyDlg();

// Dialog Data
	enum { IDD = IDD_MYDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
