
// HistogramEqualizedWithYCbCrView.h : CHistogramEqualizedWithYCbCrView 클래스의 인터페이스
//

#pragma once
#include "YCbCr.h"
const short MAX_INTENSITY_LEVEL = 256; //최대 밝기 수준 정의

class CHistogramEqualizedWithYCbCrView : public CView
{
protected: // serialization에서만 만들어집니다.
	CHistogramEqualizedWithYCbCrView();
	DECLARE_DYNCREATE(CHistogramEqualizedWithYCbCrView)

// 특성입니다.
public:
	CHistogramEqualizedWithYCbCrDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CHistogramEqualizedWithYCbCrView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
private:
	CImage Input_image;
	CImage Output_image;
	int InputImageHeight;
	int InputImageWidth;
	bool isAlreadyEqualized;
	int histogramOfYInYCbCr[MAX_INTENSITY_LEVEL];
	int cumulativeNumberOfIntensity[MAX_INTENSITY_LEVEL];
	int resultHistogramOfYInYCbCr[MAX_INTENSITY_LEVEL];
	YCbCr** YCbCrImage;
public:
	bool getIsAlreadyEqualized();
	int *getHistogramOfYInYCbCr();
	int *getResultHistogramOfYInYCbCr();
	void LoadInputImage();
	void InitializeArray();
	void InitializeYCbCr();
	void CalculationHistogramFromImage();
	void ConvertRGBIntoYCbCr(int x, int y);
	void Histogram_Equalized();
	void CalculateCumulativeNumberOfIntensity();
	void SetOutputImage();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
#ifndef _DEBUG  // HistogramEqualizedWithYCbCrView.cpp의 디버그 버전
inline CHistogramEqualizedWithYCbCrDoc* CHistogramEqualizedWithYCbCrView::GetDocument() const
   { return reinterpret_cast<CHistogramEqualizedWithYCbCrDoc*>(m_pDocument); }
#endif


