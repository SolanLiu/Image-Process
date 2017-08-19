#include "myostu.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

MyOstu::MyOstu(QObject *parent) : QObject(parent)
{

}

void MyOstu::thresholdValue(CvMat *pGrayMat, int width, int height, unsigned char &nThreshold)
{
/*
    //输入参数
    * pGrayMat：二值图像数据
    * width：图形尺寸宽度
    * height：图形尺寸高度
    * nTreshold：经过算法处理得到的二值化分割阈值
*/
    double nHistogram[256];         //灰度直方图
    double dVariance[256];          //类间方差
    int N = height*width;           //总像素数

    //初始化nHistogram[]、dVariance[]
    for(int i=0; i<256; i++)
    {
        nHistogram[i] = 0.0;
        dVariance[i] = 0.0;
    }

    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            //int nData = (int)cvmGet(pGrayMat, i, j);
            unsigned char nData = (unsigned char)cvmGet(pGrayMat, i, j);
            nHistogram[nData]++;     //建立直方图
        }
    }

    double Pa=0.0;      //背景出现概率
    double Pb=0.0;      //目标出现概率
    double Wa=0.0;      //背景平均灰度值
    double Wb=0.0;      //目标平均灰度值
    double W0=0.0;      //全局平均灰度值
    double dData1=0.0,  dData2=0.0;

    for(int i=0; i<256; i++)     //计算全局平均灰度
    {
        nHistogram[i] /= N;
        W0 += i*nHistogram[i];
    }

    for(int i=0; i<256; i++)     //对每个灰度值计算类间方差
    {
        Pa += nHistogram[i];
        Pb = 1-Pa;
        dData1 += i*nHistogram[i];
        dData2 = W0-dData1;
        Wa = dData1/Pa;
        Wb = dData2/Pb;
        dVariance[i] = (Pa*Pb* pow((Wb-Wa), 2));
    }

    //遍历每个方差，求取类间最大方差所对应的灰度值
    double temp=0.0;
    for(int i=0; i<256; i++)
    {
        if(dVariance[i]>temp)
        {
            temp = dVariance[i];
            nThreshold = i;
        }
    }

    cout << "nThreshold的值为：" << (int)nThreshold << endl;

    IplImage *srcImage, *dstImage;
    Mat midImage = cvarrToMat(pGrayMat); //将CvMat类型转换为Mat类型
    //Mat midImage(pGrayMat->rows, pGrayMat->cols, CV_32F, pGrayMat->data.fl);
    //Mat midImage = Mat(pGrayMat, true); //将CvMat类型转换为Mat类型
    *srcImage = midImage; //将Mat类型转换为IplImage类型
    dstImage = cvCreateImage(cvGetSize(srcImage), srcImage->depth, 1);

    cvThreshold(srcImage, dstImage, 86, 255, CV_THRESH_BINARY);

    cvNamedWindow("srcImage");
    cvNamedWindow("dstImage");
    cvShowImage("srcImage",srcImage);
    cvShowImage("dstImage",dstImage);

    cvWaitKey(0);
    cvDestroyWindow("srcImage");
    cvDestroyWindow("dstImage");

    cvReleaseImage(&srcImage);
    cvReleaseImage(&dstImage);
}

//阈值化处理按钮响应函数
void MyOstu::on_threshold_clicked()
{
    Mat img = imread("F://Qt5.8.0//myProcedure//test_Ostu//testImage.bmp", 1);
    Mat grey, pGrayMat;
    cvtColor(img, grey,CV_BGR2GRAY);
    grey.convertTo(pGrayMat, CV_32F);

    cout << "pGrayMat类型为：" << pGrayMat.type() << endl;

    CvMat cvMat = pGrayMat;

    cout << "cvMat类型为：" << CV_MAT_TYPE(cvMat.type) << endl;
    cout << "cvMat通道数为：" << pGrayMat.channels() << endl;

    int testWidth = pGrayMat.cols;
    int testHeight = pGrayMat.rows;
    unsigned char nThreshold = 0;

    thresholdValue(&cvMat, testWidth, testHeight, nThreshold);
}


