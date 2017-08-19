#ifndef MYCANNY_H
#define MYCANNY_H

#include <QObject>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class MyCanny : public QObject
{
    Q_OBJECT

public slots:
    void on_canny_clicked();
};

#endif // MYCANNY_H
