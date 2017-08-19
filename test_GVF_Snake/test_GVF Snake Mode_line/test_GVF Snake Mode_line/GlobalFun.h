/*==================================================================
=  代码内容：GVF Snake                                      
=  修改日期: 2010.10.20                                                                                                        
=  作者:BeanYoung
=  email:guobasanxian@gmail.com                                                
====================================================================*/

#ifndef GLOBALFUN_H
#define GLOBALFUN_H

#include "cv.h"

//cvSetMouseCallback()的参数函数
void on_mouse( int event, int x, int y, int flags, void* ptr );

//on_mouse函数里调用。画出初始轮廓
void ShowContent( IplImage* img );

//计算矩阵的梯度
void GetGradient( CvMat*, CvMat*, CvMat* );

#endif