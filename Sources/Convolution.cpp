#include "Convolution.h"

vector<float> Convolution::GetKernel()
{
	return _kernel;
}

void Convolution::SetKernel(vector<float> kernel, int kWidth, int kHeight)
{
	_kernel = kernel;
	_kernelWidth = kWidth;
	_kernelHeight = kHeight;
}

int Convolution::DoConvolution(const Mat& sourceImage, Mat& destinationImage)
{
	//Kiểm tra ảnh nguồn có phải là tập rỗng
	if (sourceImage.empty())
		return 1;

	int width = sourceImage.cols, height = sourceImage.rows;
	int nChannels = sourceImage.channels();
	int widthStep = sourceImage.step[0];
	destinationImage.create(height, width, sourceImage.type());

	//Khao báo con trỏ để thao tác dữ liệu các pixel trên ảnh
	//Con trỏ ảnh nguồn
	uchar* pSrcData = sourceImage.data;
	//Con trỏ ảnh đích
	uchar* pDstData = destinationImage.data;

	//Tạo offsets dựa trên kích thước kernel và kênh màu
	int WidthOffsets = (int)(_kernelWidth / 2) * nChannels;
	int HeightOffsets = (int)(_kernelHeight / 2);
	vector<int> offsets;
	for (int y = -HeightOffsets; y <= HeightOffsets; y++)
		for (int x = -WidthOffsets; x <= WidthOffsets + nChannels - 1; x++)
			offsets.push_back(y * widthStep + x);

	//Sao chép ảnh gốc vào ảnh đích để được dữ liệu ảnh từ những hàng và cột pixel đầu
	int n = offsets.size();
	for (int i = 0; i < height; i++, pSrcData += widthStep, pDstData += widthStep) 
	{
		uchar* pDstRow = pDstData;
		uchar* pSrcRow = pSrcData;
		for (int j = 0; j < width; j++, pSrcRow += nChannels, pDstRow += nChannels)
		{
			for (int count = 0; count < nChannels; count++)
			{
				pDstRow[count] = pSrcRow[count];
			}
		}
	}
	//Xét dữ liệu ảnh bỏ qua những hàng và cột pixel đầu
	pDstData = destinationImage.data + widthStep;
	pSrcData = sourceImage.data + widthStep;

	vector<float>s;
	for (int i = 0; i < nChannels; i++)
	{
		s.push_back(0.0);
	}
	for (int i = 1; i < height - 1; i++, pSrcData += widthStep, pDstData += widthStep)
	{
		uchar* pDstRow = pDstData;
		uchar* pSrcRow = pSrcData;
		for (int j = 1; j < width - 1; j++, pSrcRow += nChannels, pDstRow += nChannels)
		{
			//Tạo biến s tính tích chập của từng kênh màu
			for (int count = 0; count < nChannels; count++)
			{
				s[count] = 0.0;
			}
			//Tính tích chập
			int idx = 0;
			for (int k = 0; k < n; k = k + nChannels, idx++)
			{
				for (int count = 0; count < nChannels; count++)
				{
					s[count] = s[count] + pSrcRow[offsets[k + count]] * _kernel[_kernel.size() - 1 - idx];
				}
			}
			for (int count = 0; count < nChannels; count++)
			{
				pDstRow[count] = saturate_cast<uchar>(s[count]);
			}
		}
	}
	return 0;
}

Convolution::Convolution()
{
}

Convolution::~Convolution()
{
}
