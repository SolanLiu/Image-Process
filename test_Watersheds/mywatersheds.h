#ifndef MYWATERSHEDS_H
#define MYWATERSHEDS_H

#include <QObject>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

class MyWatersheds : public QObject
{
    Q_OBJECT

public:
    explicit MyWatersheds(QObject *parent = 0);

signals:

public slots:
    void setMarkers(const Mat& markerImage)
    {

        markerImage.convertTo(markers,CV_32S); // Convert to image of ints
    }

    Mat process(const Mat &image)
    {
        cv::watershed(image,markers); // Apply watershed
        return markers;
    }

    // Return result in the form of an image
    Mat getSegmentation()
    {
        Mat tmp;
        // all segment with label higher than 255 will be assigned value 255
        markers.convertTo(tmp, CV_8U);
        return tmp;
    }

    // Return watershed in the form of an image
    Mat getWatersheds()
    {
        Mat tmp;
        //在变换前，把每个像素p转换为255p+255（在conertTo中实现）
        markers.convertTo(tmp,CV_8U,255,255);
        return tmp;
    }

    void on_segmentationW_clicked();

private:
    Mat markers;
};

#endif // MYWATERSHEDS_H
