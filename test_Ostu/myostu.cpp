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
    //�������
    * pGrayMat����ֵͼ������
    * width��ͼ�γߴ���
    * height��ͼ�γߴ�߶�
    * nTreshold�������㷨����õ��Ķ�ֵ���ָ���ֵ
*/
    double nHistogram[256];         //�Ҷ�ֱ��ͼ
    double dVariance[256];          //��䷽��
    int N = height*width;           //��������

    //��ʼ��nHistogram[]��dVariance[]
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
            nHistogram[nData]++;     //����ֱ��ͼ
        }
    }

    double Pa=0.0;      //�������ָ���
    double Pb=0.0;      //Ŀ����ָ���
    double Wa=0.0;      //����ƽ���Ҷ�ֵ
    double Wb=0.0;      //Ŀ��ƽ���Ҷ�ֵ
    double W0=0.0;      //ȫ��ƽ���Ҷ�ֵ
    double dData1=0.0,  dData2=0.0;

    for(int i=0; i<256; i++)     //����ȫ��ƽ���Ҷ�
    {
        nHistogram[i] /= N;
        W0 += i*nHistogram[i];
    }

    for(int i=0; i<256; i++)     //��ÿ���Ҷ�ֵ������䷽��
    {
        Pa += nHistogram[i];
        Pb = 1-Pa;
        dData1 += i*nHistogram[i];
        dData2 = W0-dData1;
        Wa = dData1/Pa;
        Wb = dData2/Pb;
        dVariance[i] = (Pa*Pb* pow((Wb-Wa), 2));
    }

    //����ÿ�������ȡ�����󷽲�����Ӧ�ĻҶ�ֵ
    double temp=0.0;
    for(int i=0; i<256; i++)
    {
        if(dVariance[i]>temp)
        {
            temp = dVariance[i];
            nThreshold = i;
        }
    }

    cout << "nThreshold��ֵΪ��" << (int)nThreshold << endl;

    IplImage *srcImage, *dstImage;
    Mat midImage = cvarrToMat(pGrayMat); //��CvMat����ת��ΪMat����
    //Mat midImage(pGrayMat->rows, pGrayMat->cols, CV_32F, pGrayMat->data.fl);
    //Mat midImage = Mat(pGrayMat, true); //��CvMat����ת��ΪMat����
    *srcImage = midImage; //��Mat����ת��ΪIplImage����
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

//��ֵ������ť��Ӧ����
void MyOstu::on_threshold_clicked()
{
    Mat img = imread("F://Qt5.8.0//myProcedure//test_Ostu//testImage.bmp", 1);
    Mat grey, pGrayMat;
    cvtColor(img, grey,CV_BGR2GRAY);
    grey.convertTo(pGrayMat, CV_32F);

    cout << "pGrayMat����Ϊ��" << pGrayMat.type() << endl;

    CvMat cvMat = pGrayMat;

    cout << "cvMat����Ϊ��" << CV_MAT_TYPE(cvMat.type) << endl;
    cout << "cvMatͨ����Ϊ��" << pGrayMat.channels() << endl;

    int testWidth = pGrayMat.cols;
    int testHeight = pGrayMat.rows;
    unsigned char nThreshold = 0;

    thresholdValue(&cvMat, testWidth, testHeight, nThreshold);
}


