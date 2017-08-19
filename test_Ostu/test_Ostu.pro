TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    myostu.cpp

RESOURCES += qml.qrc

INCLUDEPATH += C:\opencv\include\
               C:\opencv\include\opencv\
               C:\opencv\include\opencv2
LIBS += C:\opencv\x86\mingw\lib\libopencv_calib3d310.dll.a\
        C:\opencv\x86\mingw\lib\libopencv_core310.dll.a\
        C:\opencv\x86\mingw\lib\libopencv_features2d310.dll.a\
        C:\opencv\x86\mingw\lib\libopencv_flann310.dll.a\
        C:\opencv\x86\mingw\lib\libopencv_highgui310.dll.a\
        C:\opencv\x86\mingw\lib\libopencv_imgcodecs310.dll.a\
        C:\opencv\x86\mingw\lib\libopencv_imgproc310.dll.a\
        C:\opencv\x86\mingw\lib\libopencv_ml310.dll.a\
        C:\opencv\x86\mingw\lib\libopencv_objdetect310.dll.a\
        C:\opencv\x86\mingw\lib\libopencv_photo310.dll.a\
        C:\opencv\x86\mingw\lib\libopencv_shape310.dll.a\
        C:\opencv\x86\mingw\lib\libopencv_stitching310.dll.a\
        C:\opencv\x86\mingw\lib\libopencv_superres310.dll.a\
        C:\opencv\x86\mingw\lib\libopencv_ts310.a\
        C:\opencv\x86\mingw\lib\libopencv_video310.dll.a\
        C:\opencv\x86\mingw\lib\libopencv_videoio310.dll.a\
        C:\opencv\x86\mingw\lib\libopencv_videostab310.dll.a

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    myostu.h
