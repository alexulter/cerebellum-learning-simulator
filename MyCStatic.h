#include "mauk.h"
#pragma once


// MyCStatic

class MyCStatic : public CStatic
{
	DECLARE_DYNAMIC(MyCStatic)

public:
	MyCStatic();
	virtual ~MyCStatic();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void DrawImage(void);
	CImage * img;
	//afx_msg void OnBnClickedBtnPause();
	//std::deque<double> draw_vect_1;
private:
	UINT my_NumSteps;
	UINT my_TimeStep;
	UINT my_PointSparce;
	int my_MaxVal;
	UINT timepoint;
	UINT timewindow;
	Purkinje * purk;
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
};


