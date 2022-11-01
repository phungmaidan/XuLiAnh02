#include "Blur.h"
int Blur::BlurImage(const Mat& sourceImage, Mat& destinationImage, int kWidth, int kHeight, int method)
{
	Convolution convol;
	vector<float> kernel;
	if (method == 0)
	{
		//Lọc trung bình
		for (int i = 0; i < kWidth * kHeight; i++)
		{
			kernel.push_back(1.0 / (kWidth * kHeight));
		}
		convol.SetKernel(kernel, kWidth, kHeight);
		if (convol.DoConvolution(sourceImage, destinationImage) == 0)
			return 0;
		return 1;
	}
	else if (method == 1)
	{
		//Xử lý lọc trung vị
		destinationImage.create(sourceImage.rows, sourceImage.cols, sourceImage.type());

		int width = sourceImage.cols, height = sourceImage.rows;
		int nChannels = sourceImage.channels();
		int widthStep = sourceImage.step[0];

		//Tạo bảng offsets theo kích thước cửa sổ lọc
		int WidthOffsets = (int)(kWidth / 2) * nChannels;
		int HeightOffsets = (int)(kHeight / 2);
		vector<int> offsets;
		for (int y = -HeightOffsets; y <= HeightOffsets; y++)
			for (int x = -WidthOffsets; x <= WidthOffsets + nChannels - 1; x++)
				offsets.push_back(y * widthStep + x);
		int n = offsets.size();
		uchar* pDstData = destinationImage.data;
		uchar* pSrcData = sourceImage.data;
		//Sao chép ảnh gốc vào ảnh đích để được dữ liệu ảnh từ những hàng và cột pixel đầu
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
		uchar** I = new uchar * [nChannels];
		int nI = kWidth * nChannels;
		for (int i = 0; i < nChannels; i++)
		{
			I[i] = new uchar[nI];
		}

		uchar temp;
		//Xét dữ liệu ảnh bỏ qua những hàng và cột pixel đầu
		pDstData = destinationImage.data + widthStep;
		pSrcData = sourceImage.data + widthStep;
		int idx;
		for (int i = 1; i < height - 1; i++, pSrcData += widthStep, pDstData += widthStep)
		{
			uchar *pSrcRow = pSrcData;
			uchar *pDstRow = pDstData;
			for (int j = 1; j < width - 1; j++, pSrcRow += nChannels, pDstRow += nChannels)
			{
				//Tìm trung vị của các điểm ảnh theo kích thước cửa sổ lọc
				for (int k = 0; k < nChannels; k++)
				{
					idx = 0;
					for (int count = 0; count < n; count = count + nChannels)
					{
						I[k][idx] = pSrcRow[offsets[k + count]];
						idx++;
					}
				}
				//Sắp xếp lại mảng giá trị theo thứ tự tăng dần để tìm trung vị
				for (int count = 0; count < nChannels; count++)
				{
					for (int k = 0; k < nI / 2 + 1; k++)
						for (int t = k + 1; t < nI; t++)
							if (I[count][k] > I[count][t])
							{
								temp = I[count][k];
								I[count][k] = I[count][t];
								I[count][t] = temp;
							}
				}
				//Gán giá trị điểm ảnh là chính giữa trong mảng vừa sắp xếp
				for (int count = 0; count < nChannels; count++)
				{
					pDstRow[count] = I[count][nI / 2];
				}
			}
		}
		return 0;
	}
	else if (method == 2)
	{
		//Tạo kernel với trường hợp lọc Gaussian
		int n = kHeight * kWidth;
		
		//Tính sigma
		float sigma = 0.5;
		float s = 1.57;
		float temp = 0.0, idx = 0.0;

		//Tính kernel 
		for (int y = -(int)(kHeight / 2); y <= (int)(kHeight / 2); y++)
			for (int x = -(int)(kWidth / 2); x <= (int)(kWidth / 2); x++)
			{
				idx = expf((-1 * (x * x + y * y)) / sigma) / s;
				temp = temp + idx;
				kernel.push_back(idx);
			}

		//Chuẩn hóa kernel 
		for (int i = 0; i < n; i++)
		{
			kernel[i] /= temp;
		}

		convol.SetKernel(kernel, kWidth, kHeight);

		if (convol.DoConvolution(sourceImage, destinationImage) == 0)
		{
			return 0;
		}
		return 1;
	}
	else return 1;

}

Blur::Blur()
{
}

Blur::~Blur()
{
}
