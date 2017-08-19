#ifndef MYGRAPHCUTS_H
#define MYGRAPHCUTS_H

#include <QObject>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "iostream"
#include "windows.h"

using namespace cv;
using namespace std;

class MyGraphCuts : public QObject
{
    Q_OBJECT

public:
    enum { NOT_SET = 0, IN_PROCESS = 1, SET = 2 };
    static const int radius = 2;
    static const int thickness = -1;

    void reset();
    void setImageAndWinName(const Mat& _image, const string& _winName);
    void showImage() const;
    void mouseClick(int event, int x, int y, int flags, void* param);
    int nextIter();
    int getIterCount() const
    {
        return iterCount;
    }

signals:

public slots:
    void on_segementationG_clicked();

private:
    void setRectInMask();
    void setLblsInMask(int flags, Point p, bool isPr);

    const string* winName;
    const Mat* image;
    Mat mask;
    Mat bgdModel, fgdModel;

    uchar rectState, lblsState, prLblsState;
    bool isInitialized;

    Rect rect;
    vector<Point> fgdPxls, bgdPxls, prFgdPxls, prBgdPxls;
    int iterCount;
};

#endif // MYGRAPHCUTS_H
