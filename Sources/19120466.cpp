#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "Blur.h"
#include "EdgeDetector.h"
#include <string>
using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
    if (argc < 4)
    {
        cout << "Error: no input argument." << endl;
        return -1;
    }

    string* str = new string[argc - 1];
    for (int i = 1; i < argc; i++)
    {
        str[i - 1] = argv[i];
        cout << str[i - 1] << "." << endl;
    }

    //Khai báo các biến cần thiết hỗ trợ tính toán
    Blur blurImg;
    EdgeDetector edg;

    Mat srcImage;
    Mat dstImage;
    
    if (str[0] == "-avg")
    {
        srcImage = imread(str[3], IMREAD_COLOR);
        int ky = atoi(str[1].c_str()), kx = atoi(str[2].c_str());
        if ((ky * kx) % 2 == 0)
        {
            cout << "kx, ky must be odd numbers!!!\n";
            return -1;
        }
        if (blurImg.BlurImage(srcImage, dstImage, kx, ky, 0) == 1)
        {
            cout << "Error!!!\n";
            return -1;
        }
        imwrite(str[4], dstImage);
    }
    if (str[0] == "-med")
    {
        srcImage = imread(str[3], IMREAD_COLOR);
        int ky = atoi(str[1].c_str()), kx = atoi(str[2].c_str());
        if ((ky * kx) % 2 == 0)
        {
            cout << "kx, ky must be odd numbers!!!\n";
            return -1;
        }
        if (blurImg.BlurImage(srcImage, dstImage, kx, ky, 1) == 1)
        {
            cout << "Error!!!\n";
            return -1;
        }
        imwrite(str[4], dstImage);
    }
    if (str[0] == "-gau")
    {
        srcImage = imread(str[3], IMREAD_COLOR);
        int ky = atoi(str[1].c_str()), kx = atoi(str[2].c_str());
        if ((ky * kx) % 2 == 0)
        {
            cout << "kx, ky must be odd numbers!!!\n";
            return -1;
        }
        if (blurImg.BlurImage(srcImage, dstImage, kx, ky, 2) == 1)
        {
            cout << "Error!!!\n";
            return -1;
        }
        imwrite(str[4], dstImage);
    }
    if (str[0] == "-sobel")
    {
        srcImage = imread(str[1], IMREAD_GRAYSCALE);
        if (edg.DetectEdge(srcImage, dstImage, 1) == 1)
        {
            cout << "Error!!!\n";
            return -1;
        }
        imwrite(str[2], dstImage);
    }
    if (str[0] == "-prew")
    {
        cout << "Incomplete!!!\n";
        return -1;
    }
    if (str[0] == "-lap")
    {
        srcImage = imread(str[1], IMREAD_GRAYSCALE);
        if (edg.DetectEdge(srcImage, dstImage, 3) == 1)
        {
            cout << "Error!!!\n";
            return -1;
        }
        imwrite(str[2], dstImage);
    }
    imshow("SourceImage", srcImage);
    imshow("DstImage", dstImage);
    waitKey(0);
    return 0;
}
