// Histogram.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "HistogramEqualizedWithYCbCr.h"
#include "Histogram.h"
#include "afxdialogex.h"
#include "HistogramEqualizedWithYCbCrDoc.h"
#include "ChildFrm.h"
#include "MainFrm.h"
#include "Resource.h"
#include "HistogramEqualizedWithYCbCrView.h"
// Histogram 대화 상자입니다.

IMPLEMENT_DYNAMIC(Histogram, CDialogEx)

Histogram::Histogram(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HISTOGRAM, pParent)
{

}

Histogram::~Histogram()
{
}

void Histogram::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Histogram, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// Histogram 메시지 처리기입니다.


void Histogram::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오
	CMainFrame *pMainFrame = (CMainFrame *)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pMainFrame->GetActiveFrame();
	CHistogramEqualizedWithYCbCrView *pView = (CHistogramEqualizedWithYCbCrView*)pChild->GetActiveView();
	dc.SetDCPenColor(RGB(0, 0, 0));
	for (int i = 0; i < 256; i++) {
		dc.MoveTo(50 + (2 * i), 270);
		dc.LineTo(50 + (2 * i), 270 - (pView->getHistogramOfYInYCbCr()[i] / 16));
	}
	if (pView->getIsAlreadyEqualized()) {
		for (int i = 0; i < 256; i++) {
			dc.MoveTo(50 + (2 * i), 500);
			dc.LineTo(50 + (2 * i), 500 - (pView->getResultHistogramOfYInYCbCr()[i] / 16));
		}
	}
}

