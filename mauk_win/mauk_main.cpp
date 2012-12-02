#include "afxwin.h" // MFC „O„ƒ„~„€„r„~„„u „y „ƒ„„„p„~„t„p„‚„„„~„„u „{„€„}„„€„~„u„~„„„
#include "afxext.h"     // MFC „Q„p„ƒ„Š„y„‚„u„~„y„‘
#include "resource.h"	// „I„t„u„~„„„y„†„y„{„p„„„€„‚„ „‚„u„ƒ„…„‚„ƒ„€„r
#include "MyDlg.h"

//#include <psapi.h>
//#include <queue>

#define IDC_MYBUTTON 100	// „I„t„u„~„„„y„†„y„{„p„„„€„‚ „{„~„€„„{„y
#define IDC_MYEDIT 102	// „I„t„u„~„„„y„†„y„{„p„„„€„‚ „„€„|„‘ „‚„u„t„p„{„„„y„‚„€„r„p„~„y„‘

class CMyButton: public CButton
{
public:
	afx_msg void OnLButtonDblClk(UINT, CPoint);
	afx_msg void OnRButtonDblClk(UINT, CPoint);
private:
	DECLARE_MESSAGE_MAP(); // „„„p„q„|„y„ˆ„p „€„„„{„|„y„{„€„r „{„~„€„„{„y
};

void CMyButton::OnLButtonDblClk(UINT, CPoint)
{
	MoveWindow(CRect(120,100,220,150),TRUE);
}

void CMyButton::OnRButtonDblClk(UINT, CPoint)
{
	MoveWindow(CRect(120,10,220,50),TRUE);
}

BEGIN_MESSAGE_MAP(CMyButton, CButton) // „„„p„q„|„y„ˆ„p „€„„„{„|„y„{„€„r „~„p „ƒ„€„€„q„‹„u„~„y„‘
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDBLCLK()
END_MESSAGE_MAP()

//class CMaukDlg : public CDialog
//{
//public:
//	CMaukDlg(CWnd* pParent = NULL);
//	enum { IDD = IDD_DIALOGMAUKMAIN };
//	afx_msg void OnPaint();
//protected:
//	DECLARE_MESSAGE_MAP();
//private:
//	CImage * img;
//}
//CMaukDlg::CMaukDlg(CWnd* pParent /*=NULL*/)
//	: CDialog(CMaukDlg::IDD, pParent)
//{
//			//{{AFX_DATA_INIT(CDlg)
//		m_Str='';
//		//}}AFX_DATA_INIT
//}

//BEGIN_MESSAGE_MAP(CMaukDlg, CDialog)	// „„„p„q„|„y„ˆ„p „€„„„{„|„y„{„€„r „~„p „ƒ„€„€„q„‹„u„~„y„‘
//	ON_WM_PAINT()         //„}„u„ƒ„ƒ„u„t„w: „„„‚„u„q„…„u„„„ƒ„‘ „„u„‚„u„‚„y„ƒ„€„r„{„p „€„{„~„p
//END_MESSAGE_MAP()
//void CMaukDlg::OnPaint()
//{
//	CDialog::OnPaint();
//	//CPaintDC dc(this);	// „P„€„|„…„‰„y„„„ „{„€„~„„„u„{„ƒ„„ „…„ƒ„„„‚„€„z„ƒ„„„r„p
//	//dc.TextOut(200,200,"Hello MFC Programm too");	// „N„p„„y„ƒ„p„„„ „r „~„u„} „„‚„y„r„u„„
//	//dc.MoveTo(300,300);	// „N„p„‰„p„„„ „‚„y„ƒ„€„r„p„„„ „|„y„~„y„
//	//dc.LineTo(600,105);	// „I „„‚„€„t„€„|„w„y„„„ „‚„y„ƒ„€„r„p„„„ „|„y„~„y„
//	//dc.LineTo(105,105);	// „I „u„‹„u „„‚„€„t„€„|„w„y„„„ „‚„y„ƒ„€„r„p„„„ „|„y„~„y„
//}
class CMainWnd : public CFrameWnd
{
public:
	CMainWnd();	// „K„€„~„ƒ„„„‚„…„{„„„€„‚ „„€ „…„}„€„|„‰„p„~„y„
	afx_msg void OnLButtonDblClk(UINT, CPoint);	// „r„y„‚„„„…„p„|„„~„p„‘ „„‚„€„ˆ„u„t„…„‚„p „€„„„r„u„„„p „~„p „|„u„r„…„ „{„~„€„„{„…
	afx_msg void OnRButtonDblClk(UINT, CPoint);	// „r„y„‚„„„…„p„|„„~„p„‘ „„‚„€„ˆ„u„t„…„‚„p „€„„„r„u„„„p „~„p „„‚„p„r„…„ „{„~„€„„{„…
	afx_msg void OnKeyDown(UINT, UINT, UINT);	// „r„y„‚„„„…„p„|„„~„p„‘ „„‚„€„ˆ„u„t„…„‚„p „€„„„r„u„„„p „~„p „{„|„p„r„y„Š„…
	int OnCreate(LPCREATESTRUCT lpCreateStruct);	// „„„„p „†„…„~„{„ˆ„y„‘ „r„„x„„r„p„u„„„ƒ„‘ „„‚„y „ƒ„€„x„t„p„~„y„y „€„{„~„p
	afx_msg void OnPaint();	// „P„u„‚„u„€„„‚„u„t„u„|„‘„u„} „†„…„~„{„ˆ„y„ „‚„y„ƒ„€„r„p„~„y„‘ „r „€„{„~„u
	~CMainWnd();  	// „D„u„ƒ„„„‚„…„{„„„€„‚
private:
	CStatic* MyStatic[5];	// „T„{„p„x„p„„„u„|„ „~„p „€„q„Œ„u„{„„ „~„p„t„„y„ƒ„
	CMyButton* MyButton;	// „T„{„p„x„p„„„u„|„ „~„p „€„q„Œ„u„{„„ „{„~„€„„{„p
	CEdit* MyEdit;	// „T„{„p„x„p„„„u„|„ „~„p „€„q„Œ„u„{„„ „„€„|„u „‚„u„t„p„{„„„y„‚„€„r„p„~„y„‘
	CStatusBar m_wndStatusBar;	// „{„|„p„ƒ„ƒ „„p„~„u„|„y „ƒ„€„ƒ„„„€„‘„~„y„‘
	CMenu m_wndMenu;	// „^„„„€ „~„p„Š „{„|„p„ƒ„ƒ „M„u„~„
	DECLARE_MESSAGE_MAP(); // „„„p„q„|„y„ˆ„p „€„„„{„|„y„{„€„r
};
BEGIN_MESSAGE_MAP(CMainWnd, CFrameWnd)	// „„„p„q„|„y„ˆ„p „€„„„{„|„y„{„€„r „~„p „ƒ„€„€„q„‹„u„~„y„‘
	ON_WM_LBUTTONDBLCLK()		// „‚„u„p„{„ˆ„y„‘ „~„p „~„p„w„p„„„y„u „|„u„r„€„z „{„~„€„„{„y „}„„Š„y
	ON_WM_RBUTTONDBLCLK()		// „‚„u„p„{„ˆ„y„‘ „~„p „~„p„w„p„„„y„u „„‚„p„r„€„z „{„~„€„„{„y „}„„Š„{„y
	ON_WM_KEYDOWN()			// „‚„u„p„{„ˆ„y„‘ „~„p „~„p„w„p„„„y„u „{„|„p„r„y„Š„y
	ON_WM_CREATE()			// „ƒ„€„q„„„„y„u „ƒ„€„x„t„p„~„y„‘ „€„{„~„p
	ON_WM_PAINT()         //„}„u„ƒ„ƒ„u„t„w: „„„‚„u„q„…„u„„„ƒ„‘ „„u„‚„u„‚„y„ƒ„€„r„{„p „€„{„~„p
END_MESSAGE_MAP()

void CMainWnd::OnPaint()
{
	CPaintDC dc(this);	// „P„€„|„…„‰„y„„„ „{„€„~„„„u„{„ƒ„„ „…„ƒ„„„‚„€„z„ƒ„„„r„p
	dc.TextOut(200,200,"Hello MFC Programm");	// „N„p„„y„ƒ„p„„„ „r „~„u„} „„‚„y„r„u„„
	//dc.MoveTo(300,300);	// „N„p„‰„p„„„ „‚„y„ƒ„€„r„p„„„ „|„y„~„y„
	//dc.LineTo(600,105);	// „I „„‚„€„t„€„|„w„y„„„ „‚„y„ƒ„€„r„p„„„ „|„y„~„y„
	//dc.LineTo(105,105);	// „I „u„‹„u „„‚„€„t„€„|„w„y„„„ „‚„y„ƒ„€„r„p„„„ „|„y„~„y„
}
int CMainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)  return -1;
	m_wndStatusBar.Create(this); 
	m_wndMenu.LoadMenu(IDR_MENU1);	// „H„p„s„‚„…„x„y„„„ „}„u„~„ „y„x „†„p„z„|„p „‚„u„ƒ„…„‚„ƒ„p
	SetMenu(&m_wndMenu);	// „T„ƒ„„„p„~„€„r„y„„„ „}„u„~„
	return 0;
}
void CMainWnd::OnKeyDown(UINT, UINT, UINT)
{
	AfxMessageBox(_T(" Key Button Down "));
}
void CMainWnd::OnRButtonDblClk(UINT, CPoint)
{
	AfxMessageBox(_T(" Rigth Button Click "));
}
void CMainWnd::OnLButtonDblClk(UINT, CPoint)
{
	AfxMessageBox(_T(" Left Button Click "));
}


CMainWnd::CMainWnd()
{
	Create(NULL,_T("Mauk"),WS_OVERLAPPEDWINDOW,rectDefault,
		NULL,NULL);	// „R„€„x„t„p„„„ „€„{„~„€ „„‚„€„s„‚„p„}„}„
	// „€„„u„‚„p„„„€„‚ new „„€ „…„}„€„|„‰„p„~„y„ „r „ƒ„|„…„‰„p„u „€„Š„y„q„{„y „r„u„‚„~„u„„ NULL
	// „„‚„€„r„u„‚„{„p „…„{„p„x„p„„„u„|„‘ „~„p NULL „t„p„u„„ „r„€„x„}„€„w„~„€„ƒ„„„ „y„x„q„p„r„y„„„„ƒ„‘ „€„„ „t„p„|„„~„u„z„Š„y„‡ „€„Š„y„q„€„{
	for (int k = 1; k<3; k++)
	{	MyStatic[k] = new CStatic();
	if (MyStatic[k]!=NULL) MyStatic[k]->Create(_T("MyStatic"),WS_CHILD|WS_VISIBLE|SS_CENTER,
		CRect(10+100*k,10+100*k,100+100*k,50+100*k),this);	// „ƒ„€„x„t„p„|„y
	}
	MyButton = new CMyButton();
	if (MyButton!=NULL) MyButton->Create(_T("MyButton"),WS_CHILD|WS_VISIBLE|SS_CENTER,
		CRect(120,10,220,50),this,IDC_MYBUTTON);
	MyEdit = new CEdit();
	if (MyEdit!=NULL) MyEdit->Create(WS_CHILD|WS_VISIBLE|WS_BORDER,
		CRect(240,10,340,50),this,IDC_MYEDIT);
}
CMainWnd::~CMainWnd()
{
	for (int k = 1; k<3; k++)
		if (MyStatic[k]!=NULL) delete MyStatic[k];	// „…„t„p„|„y„„„ „t„y„~„p„}„y„‰„u„ƒ„{„y„z „€„q„Œ„u„{„„
	if (MyButton!=NULL) delete MyButton;	// „…„t„p„|„y„„„ „t„y„~„p„}„y„‰„u„ƒ„{„y„z „€„q„Œ„u„{„„
	if (MyEdit!=NULL) delete MyEdit;	// „…„t„p„|„y„„„ „t„y„~„p„}„y„‰„u„ƒ„{„y„z „€„q„Œ„u„{„„
}
class CMyApp : public CWinApp
{
public:
	CMyApp();			//„{„€„~„ƒ„„„‚„…„{„„„€„‚ „„€ „…„}„€„|„‰„p„~„y„
	virtual BOOL InitInstance();//„ƒ„„„p„~„t„p„‚„„„~„p„‘ „y„~„y„ˆ„y„p„|„y„x„p„ˆ„y„‘
};

CMyApp::CMyApp() // „{„€„~„ƒ„„„‚„…„{„„„€„‚ „s„|„p„r„~„€„s„€ „{„|„p„ƒ„ƒ„p „„‚„y„|„€„w„u„~„y„‘
{}

BOOL CMyApp::InitInstance() // „ƒ„„„p„~„t„p„‚„„„~„p„‘ „y„~„y„ˆ„y„p„|„y„x„p„ˆ„y„‘
{
	m_pMainWnd=new CMainWnd();	// „ƒ„€„x„t„p„„„ „{„|„p„ƒ„ƒ „€„{„~„p
	ASSERT(m_pMainWnd);	// „„‚„€„r„u„‚„y„„„ „u„s„€ „„‚„p„r„y„|„„~„€„ƒ„„„
	m_pMainWnd->ShowWindow(SW_SHOW);// „P„€„{„p„x„p„„„ „€„{„~„€
	m_pMainWnd->UpdateWindow();	// „O„q„~„€„r„y„„„ „€„{„~„€
    //CMyDlg* pPage = new CMyDlg;
    //pPage->Create(IDD_MYDLG,m_pMainWnd);
   // pPage->ShowWindow(SW_SHOW);
    //pPage->UpdateWindow();
//	CMyDlg dlg;
//	m_pMainWnd = &dlg;
//	dlg.DoModal();
	return TRUE;		// „B„u„‚„~„…„„„ „‰„„„€ „r„ƒ„u „~„€„‚„}„p„|„„~„€
};

CMyApp theApp;	// „x„p„„…„ƒ„{ „„‚„y„|„€„w„u„~„y„‘