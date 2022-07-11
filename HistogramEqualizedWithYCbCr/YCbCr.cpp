#include "stdafx.h"
#include "YCbCr.h"


YCbCr::YCbCr()
{

}

YCbCr::~YCbCr()
{
}

BYTE YCbCr::GetY() {
	return Y;
}

BYTE YCbCr::GetCb() {
	return Cb;
}
BYTE YCbCr::GetCr() {
	return Cr;
}

void YCbCr::SetY(BYTE Y)
{
	this->Y = Y;
}

void YCbCr::ConvertRGBIntoYCbCr(BYTE R, BYTE G, BYTE B)
{
	BYTE Y = (BYTE)limit(0.2126*R + 0.7152*G + 0.0722*B + 0.5);
	BYTE Cb = (BYTE)limit(-0.11457*R - 0.38543*G + 0.500 * B + 128 + 0.5);
	BYTE Cr = (BYTE)limit(0.500*R - 0.45415*G - 0.04585*B + 128 + 0.5);
	SetYCbCr(Y, Cb, Cr);
}

void YCbCr::SetYCbCr(BYTE Y, BYTE Cb, BYTE Cr) {
	this->Y = Y;
	this->Cb = Cb;
	this->Cr = Cr;
}

COLORREF YCbCr::ConvertYCbCrIntoRGB()
{
	BYTE R = (BYTE)limit(Y + 1.5748*(Cr - 128) + 0.5);
	BYTE G = (BYTE)limit(Y - 0.18732*(Cb - 128) - 0.46812*(Cr - 128) + 0.5);
	BYTE B = (BYTE)limit(Y + (Cb - 128)*1.8556 + 0.5);
	return RGB(R,G,B);
}



