#pragma once
class YCbCr
{
private:
	BYTE Y;
	BYTE Cb;
	BYTE Cr;
public:
	BYTE GetY();
	BYTE GetCb();
	BYTE GetCr();
	void SetY(BYTE Y);
	void ConvertRGBIntoYCbCr(BYTE R, BYTE G, BYTE B);
	void SetYCbCr(BYTE Y, BYTE Cb, BYTE Cr);
	COLORREF ConvertYCbCrIntoRGB();
	YCbCr();
	~YCbCr();
};
template<typename T>
inline T limit(const T& value)
{
	return ((value > 255) ? 255 : ((value < 0) ? 0 : value));
}

