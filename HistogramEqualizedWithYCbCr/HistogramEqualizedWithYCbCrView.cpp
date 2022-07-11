
// HistogramEqualizedWithYCbCrView.cpp : CHistogramEqualizedWithYCbCrView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "HistogramEqualizedWithYCbCr.h"
#endif

#include "HistogramEqualizedWithYCbCrDoc.h"
#include "HistogramEqualizedWithYCbCrView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHistogramEqualizedWithYCbCrView

IMPLEMENT_DYNCREATE(CHistogramEqualizedWithYCbCrView, CView)

BEGIN_MESSAGE_MAP(CHistogramEqualizedWithYCbCrView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CHistogramEqualizedWithYCbCrView 생성/소멸

CHistogramEqualizedWithYCbCrView::CHistogramEqualizedWithYCbCrView()
	:isAlreadyEqualized(false)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	Input_image.Load(L"lena.bmp"); //풀더 내 "파일명" 이미지 불러오기
	Output_image.Load(L"lena.bmp");
	InputImageHeight = Input_image.GetHeight();
	InputImageWidth = Input_image.GetWidth();
	InitializeArray();
	//LoadInputImage();
	CalculationHistogramFromImage();
}

void CHistogramEqualizedWithYCbCrView::InitializeArray()
{
	for (int i = 0; i < MAX_INTENSITY_LEVEL; i++) {
		resultHistogramOfYInYCbCr[i] = 0;
		histogramOfYInYCbCr[i] = 0;
		cumulativeNumberOfIntensity[i] = 0;
	}
}


void CHistogramEqualizedWithYCbCrView::LoadInputImage()
{
	Input_image.Load(L"lena.bmp"); //풀더 내 "파일명" 이미지 불러오기
	Output_image.Load(L"lena.bmp");
	InputImageHeight = Input_image.GetHeight();
	InputImageWidth = Input_image.GetWidth();
	Invalidate();
}


void CHistogramEqualizedWithYCbCrView::CalculationHistogramFromImage()
{
	InitializeYCbCr();
	for (int x = 0; x < InputImageWidth; x++) {
		for (int y = 0; y < InputImageHeight; y++) {
			ConvertRGBIntoYCbCr(x, y);
			histogramOfYInYCbCr[YCbCrImage[x][y].GetY()]++;
		}
	}

}

void CHistogramEqualizedWithYCbCrView::InitializeYCbCr()
{
	YCbCrImage = new YCbCr*[InputImageWidth];
	for (int y = 0; y < InputImageWidth; y++) {
		YCbCrImage[y] = new YCbCr[InputImageHeight];
	}
}

void CHistogramEqualizedWithYCbCrView::ConvertRGBIntoYCbCr(int x, int y)
{
	BYTE R = GetRValue(Input_image.GetPixel(x, y));
	BYTE G = GetGValue(Input_image.GetPixel(x, y));
	BYTE B = GetBValue(Input_image.GetPixel(x, y));
	YCbCrImage[x][y].ConvertRGBIntoYCbCr(R, G, B);
}


CHistogramEqualizedWithYCbCrView::~CHistogramEqualizedWithYCbCrView()
{
	for (int y = 0; y < InputImageHeight; y++) {
		delete[] YCbCrImage[y];
	}
	delete[] YCbCrImage;
}

BOOL CHistogramEqualizedWithYCbCrView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CHistogramEqualizedWithYCbCrView 그리기

void CHistogramEqualizedWithYCbCrView::OnDraw(CDC* pDC)
{
	CHistogramEqualizedWithYCbCrDoc* pDoc = GetDocument();
	CClientDC dc(this);
	Input_image.Draw(dc, 0, 0);
	if (isAlreadyEqualized) {
		Output_image.Draw(dc, InputImageWidth, 0);
	}
	else {
		pDC->TextOut(InputImageWidth + 100, 300, _T("클릭시 결과 영상 출력"));
		pDC->TextOut(InputImageWidth + 100, 350, _T("보기 -> 히스토그램 ,  평활화 이후 확인 시 결과 영상 히스토그램과 같이 나옵니다"));
	}
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CHistogramEqualizedWithYCbCrView 인쇄

BOOL CHistogramEqualizedWithYCbCrView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CHistogramEqualizedWithYCbCrView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CHistogramEqualizedWithYCbCrView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CHistogramEqualizedWithYCbCrView 진단

#ifdef _DEBUG
void CHistogramEqualizedWithYCbCrView::AssertValid() const
{
	CView::AssertValid();
}

void CHistogramEqualizedWithYCbCrView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHistogramEqualizedWithYCbCrDoc* CHistogramEqualizedWithYCbCrView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHistogramEqualizedWithYCbCrDoc)));
	return (CHistogramEqualizedWithYCbCrDoc*)m_pDocument;
}
#endif //_DEBUG


// CHistogramEqualizedWithYCbCrView 메시지 처리기
void CHistogramEqualizedWithYCbCrView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	Histogram_Equalized();
	SetOutputImage();
	Invalidate();
	isAlreadyEqualized = true;
	CView::OnLButtonDown(nFlags, point);
}
void CHistogramEqualizedWithYCbCrView::Histogram_Equalized()
{
	if (!isAlreadyEqualized) {
		int ImageSize = InputImageWidth*InputImageHeight;
		CalculateCumulativeNumberOfIntensity();
		for (int x = 0; x < InputImageWidth; x++) {
			for (int y = 0; y < InputImageHeight; y++) {
				BYTE tmp_Y = YCbCrImage[x][y].GetY();
				tmp_Y = (cumulativeNumberOfIntensity[tmp_Y] * (MAX_INTENSITY_LEVEL - 1) / ImageSize);
				YCbCrImage[x][y].SetY(tmp_Y);
				resultHistogramOfYInYCbCr[tmp_Y]++;
			}
		}
	}
	else return;
}
void CHistogramEqualizedWithYCbCrView::CalculateCumulativeNumberOfIntensity() {
	int sumIntensity = 0;
	for (int i = 0; i < MAX_INTENSITY_LEVEL; i++) {
		sumIntensity += histogramOfYInYCbCr[i];
		cumulativeNumberOfIntensity[i] = sumIntensity;
	}
}

void CHistogramEqualizedWithYCbCrView::SetOutputImage()
{
	for (int x = 0; x < InputImageWidth; x++) {
		for (int y = 0; y < InputImageHeight; y++) {
			Output_image.SetPixel(x, y, YCbCrImage[x][y].ConvertYCbCrIntoRGB());
		}
	}
}

int * CHistogramEqualizedWithYCbCrView::getHistogramOfYInYCbCr()
{
	return histogramOfYInYCbCr;
}

int * CHistogramEqualizedWithYCbCrView::getResultHistogramOfYInYCbCr()
{
	return resultHistogramOfYInYCbCr;
}

bool CHistogramEqualizedWithYCbCrView::getIsAlreadyEqualized()
{
	return isAlreadyEqualized;
}