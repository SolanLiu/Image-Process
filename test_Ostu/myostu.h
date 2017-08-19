#ifndef MYOSTU_H
#define MYOSTU_H

#include <QObject>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class MyOstu : public QObject
{
    Q_OBJECT

public:
    explicit MyOstu(QObject *parent = 0);

signals:

public slots:
    void thresholdValue (CvMat *pGrayMat, int width, int height, unsigned char &nThreshold);

    void on_threshold_clicked();
};

#endif // MYOSTU_H
