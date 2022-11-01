#include "EdgeDetector.h"

int EdgeDetector::DetectEdge(const Mat& sourceImage, Mat& destinationImage, int method)
{
	if (sourceImage.empty())
		return 1;

	Convolution convol;
	destinationImage.create(sourceImage.rows, sourceImage.cols, sourceImage.type());

	if (method == 1)
	{
		//Phát hiện biên cạnh bằng Sobel
		float W_x[9] = {1.0 / 4, 0.0, -1.0 / 4,
						1.0 / 2, 0.0, -1.0 / 2,
						1.0 / 4, 0.0, -1.0 / 4};
		float W_y[9] = {-1.0 / 4, -1.0 / 2, -1.0 / 4,
						 0.0,	   0.0,		 0.0,
						 1.0 / 4,  1.0 / 2,  1.0 / 4};
		vector<float> xKernel, yKernel;
		for (int i = 0; i < 9; i++)
		{
			xKernel.push_back(W_x[i]);
			yKernel.push_back(W_y[i]);
		}

		Mat fx, fy;
		//Tính fx
		convol.SetKernel(xKernel, 3, 3);
		convol.DoConvolution(sourceImage, fx);
		//Tính fy
		convol.SetKernel(yKernel, 3, 3);
		convol.DoConvolution(sourceImage, fy);

		uchar* p_fxData = fx.data;
		uchar* p_fyData = fy.data;
		uchar* pData = destinationImage.data;

		int width = sourceImage.cols, height = sourceImage.rows;
		int nChannels = sourceImage.channels();
		int widthStep = sourceImage.step[0];

		float s = 0.0;
		for (int i = 0; i < height; i++, p_fxData += widthStep, p_fyData += widthStep, pData += widthStep)
		{
			uchar* pRow = pData;
			uchar* p_xRow = p_fxData;
			uchar* p_yRow = p_fyData;
			for (int j = 0; j < width; j++, p_xRow += nChannels, p_yRow += nChannels, pRow += nChannels)
			{
				s = p_xRow[0] * 1.0 + p_yRow[0] * 1.0;
				pRow[0] = saturate_cast<uchar>(s);
			}
		}
	}
	else if (method == 2)
	{
		//Phát hiện biên cạnh bằng Prewitt
		return 1;
	}
	else if (method == 3)
	{
		//Phát hiện biên cạnh bằng Laplace
		float W_Laplace[9] = {0, 1, 0,
						      1,-4, 1,
							  0, 1, 0};
		//Tạo kernel
		vector<float> kernel;
		for (int i = 0; i < 9; i++)
		{
			kernel.push_back(W_Laplace[i]);
		}
		convol.SetKernel(kernel, 3, 3);
		convol.DoConvolution(sourceImage, destinationImage);
	}
	return 0;
}

EdgeDetector::EdgeDetector()
{
}

EdgeDetector::~EdgeDetector()
{
}
