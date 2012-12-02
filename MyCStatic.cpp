// MyCStatic.cpp : implementation file
//

#include "stdafx.h"
#include "MyCStatic.h"
//#include "mauk.h"

// MyCStatic

IMPLEMENT_DYNAMIC(MyCStatic, CStatic)

MyCStatic::MyCStatic()
{
	my_NumSteps = 4000;//200;
	my_PointSparce = 1;
	my_MaxVal = 300;
	timewindow = 1000;
	timepoint = timewindow+1;
	purk = NULL;
	purk = new Purkinje;
	purk->StartThreadFunc();	
}

MyCStatic::~MyCStatic()
{
		if (purk!=NULL) delete purk;	// „…„t„p„|„y„„„Ž „t„y„~„p„}„y„‰„u„ƒ„{„y„z „€„q„Œ„u„{„„
}
void MyCStatic::DrawImage(void)
{
		//CDC * dc = GetDC();
		//
		//dc->FillSolidRect(-1, 0, R.Width() + 2, R.Height() + 2, RGB(255, 255, 255));
		//if (timepoint < (purk->timestep)) dc->FillSolidRect(-1, 0, purk->out_var_1[timepoint], 100, RGB(0, 255, 255));
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
	dc->BitBlt(0, 0, img->GetWidth(), img->GetHeight(), idc, 0, 0, SRCCOPY);
	ReleaseDC(dc);
	img->ReleaseDC();
}
void MyCStatic::OnPaint()
{
	CStatic::OnPaint();
	DrawImage();
}
void MyCStatic::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1) 
	{
		timepoint += 100;

		CDC * dc = GetDC(), * idc = CDC::FromHandle(img->GetDC());
		CRect R;
		GetWindowRect(&R);
		int l, l2, l3;
		double dx = double(img->GetWidth()) / (my_NumSteps - 1), dy = double(img->GetHeight()) / (my_MaxVal - 1);
		int x, y;
		// clearing image
		idc->FillSolidRect(-1, -1, img->GetWidth() + 2, img->GetHeight() + 2, RGB(255, 255, 255));
		//drawing
		for (UINT i = 0; i < my_NumSteps/my_PointSparce; i++)
		{
			if (timepoint< i*my_PointSparce) break;
			l = purk->out_var_1[timepoint-i*my_PointSparce];
			l2 = purk->out_var_2[timepoint-i*my_PointSparce];
			l3 = purk->out_var_3[timepoint-i*my_PointSparce];
			x = int(my_PointSparce* i * dx);
			y = R.Height() - int(l * dy) - 1;
			idc->SetPixel(x,y, RGB(0,0,0));
			y = R.Height() - int(l2 * dy) - 1;
			idc->SetPixel(x,y, RGB(200,0,0));
			y = R.Height() - int(l3 * dy) - 1;
			idc->SetPixel(x,y, RGB(0,200,0));
		}
		img->ReleaseDC();
		DrawImage();
	}
	CStatic::OnTimer(nIDEvent);
}

BEGIN_MESSAGE_MAP(MyCStatic, CStatic)
	ON_WM_PAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// MyCStatic message handlers


