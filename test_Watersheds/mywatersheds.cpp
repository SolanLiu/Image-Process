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
    //读取原图并显示
    Mat image1 = imread("F://Qt5.8.0//myProcedure//test_Watersheds//testImage.bmp", 1);
/*
    resize(image1, image1, Size(), 0.7, 0.7);
    namedWindow("Original Image1");
    imshow("Original Image1", image1);
*/
    //阈值分割得到灰度图像的二值图
    Mat binary;
    cvtColor(image1, binary, COLOR_BGRA2GRAY);
    threshold(binary, binary, 86 ,255 ,THRESH_BINARY_INV);//阈值分割原图的灰度图，获得二值图像
/*
    namedWindow("binary Image1");
    imshow("binary Image1",binary);
    waitKey();
*/
    //形态学闭运算得到前景
    Mat element5(5, 5, CV_8U, Scalar(1));//5*5正方形，8位uchar型，全1结构元素
    Mat fg1;
    morphologyEx(binary, fg1, MORPH_CLOSE, element5, Point(-1, -1), 1);// 闭运算填充物体内细小空洞、连接邻近物体
/*
    namedWindow("Foreground Image");
    imshow("Foreground Image", fg1);
    waitKey();
*/
    //膨胀运算标记背景
    Mat bg1;
    dilate(binary, bg1, Mat(), Point(-1, -1), 4);//膨胀4次，锚点为结构元素中心点
    threshold(bg1, bg1, 1, 128, THRESH_BINARY_INV);//>=1的像素设置为128（即背景）
/*
    namedWindow("Background Image");
    imshow("Background Image", bg1);
    waitKey();
*/
    //合成标记图像
    Mat markers1 = fg1 + bg1; //使用Mat类的重载运算符+来合并图像
/*
    namedWindow("markers Image");
    imshow("markers Image", markers1);
    waitKey();
*/
    // 执行分水岭算法
    MyWatersheds segmenter1;  //实例化一个分水岭分割方法的对象
    segmenter1.setMarkers(markers1);//设置算法的标记图像，使得水淹过程从这组预先定义好的标记像素开始
    segmenter1.process(image1);     //传入待分割原图

    namedWindow("Segmentation1");
    imshow("Segmentation1", segmenter1.getSegmentation());//将修改后的标记图markers转换为可显示的8位灰度图并返回分割结果（白色为前景，灰色为背景，0为边缘）
    waitKey();

    namedWindow("Watersheds1");
    imshow("Watersheds1", segmenter1.getWatersheds());//以图像的形式返回分水岭（分割线条）
    waitKey();

    //显示结果图像
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
            if (*data==0) //将背景由黑色改为白色显示
                *data=255;
            data++; //指针操作：如为uchar型指针则移动1个字节，即移动到下1列
        }
    }
    namedWindow("result");
    imshow("result", maskimage);
    waitKey();
}

