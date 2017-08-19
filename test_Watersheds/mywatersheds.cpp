#include "mywatersheds.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

MyWatersheds::MyWatersheds(QObject *parent) : QObject(parent)
{

}

void MyWatersheds::on_segmentationW_clicked()
{
    //��ȡԭͼ����ʾ
    Mat image1 = imread("F://Qt5.8.0//myProcedure//test_Watersheds//testImage.bmp", 1);
/*
    resize(image1, image1, Size(), 0.7, 0.7);
    namedWindow("Original Image1");
    imshow("Original Image1", image1);
*/
    //��ֵ�ָ�õ��Ҷ�ͼ��Ķ�ֵͼ
    Mat binary;
    cvtColor(image1, binary, COLOR_BGRA2GRAY);
    threshold(binary, binary, 86 ,255 ,THRESH_BINARY_INV);//��ֵ�ָ�ԭͼ�ĻҶ�ͼ����ö�ֵͼ��
/*
    namedWindow("binary Image1");
    imshow("binary Image1",binary);
    waitKey();
*/
    //��̬ѧ������õ�ǰ��
    Mat element5(5, 5, CV_8U, Scalar(1));//5*5�����Σ�8λuchar�ͣ�ȫ1�ṹԪ��
    Mat fg1;
    morphologyEx(binary, fg1, MORPH_CLOSE, element5, Point(-1, -1), 1);// ���������������ϸС�ն��������ڽ�����
/*
    namedWindow("Foreground Image");
    imshow("Foreground Image", fg1);
    waitKey();
*/
    //���������Ǳ���
    Mat bg1;
    dilate(binary, bg1, Mat(), Point(-1, -1), 4);//����4�Σ�ê��Ϊ�ṹԪ�����ĵ�
    threshold(bg1, bg1, 1, 128, THRESH_BINARY_INV);//>=1����������Ϊ128����������
/*
    namedWindow("Background Image");
    imshow("Background Image", bg1);
    waitKey();
*/
    //�ϳɱ��ͼ��
    Mat markers1 = fg1 + bg1; //ʹ��Mat������������+���ϲ�ͼ��
/*
    namedWindow("markers Image");
    imshow("markers Image", markers1);
    waitKey();
*/
    // ִ�з�ˮ���㷨
    MyWatersheds segmenter1;  //ʵ����һ����ˮ��ָ���Ķ���
    segmenter1.setMarkers(markers1);//�����㷨�ı��ͼ��ʹ��ˮ�͹��̴�����Ԥ�ȶ���õı�����ؿ�ʼ
    segmenter1.process(image1);     //������ָ�ԭͼ

    namedWindow("Segmentation1");
    imshow("Segmentation1", segmenter1.getSegmentation());//���޸ĺ�ı��ͼmarkersת��Ϊ����ʾ��8λ�Ҷ�ͼ�����طָ�������ɫΪǰ������ɫΪ������0Ϊ��Ե��
    waitKey();

    namedWindow("Watersheds1");
    imshow("Watersheds1", segmenter1.getWatersheds());//��ͼ�����ʽ���ط�ˮ�루�ָ�������
    waitKey();

    //��ʾ���ͼ��
    Mat maskimage = segmenter1.getSegmentation();
    threshold(maskimage, maskimage, 250, 1, THRESH_BINARY);
    cvtColor(maskimage, maskimage, COLOR_GRAY2BGR);

    maskimage = image1.mul(maskimage);
    namedWindow("maskimage");
    imshow("maskimage", maskimage);
    waitKey();

    // Turn background (0) to white (255)
    int nl= maskimage.rows; // number of lines
    int nc= maskimage.cols * maskimage.channels(); // total number of elements per line

    for (int j=0; j<nl; j++) {
        uchar* data= maskimage.ptr<uchar>(j);
        for (int i=0; i<nc; i++)
        {
            // process each pixel
            if (*data==0) //�������ɺ�ɫ��Ϊ��ɫ��ʾ
                *data=255;
            data++; //ָ���������Ϊuchar��ָ�����ƶ�1���ֽڣ����ƶ�����1��
        }
    }
    namedWindow("result");
    imshow("result", maskimage);
    waitKey();
}

