/*==================================================================
=  �������ݣ�GVF Snake                                      
=  �޸�����: 2010.10.20                                                                                                        
=  ����:BeanYoung
=  email:guobasanxian@gmail.com                                                
====================================================================*/

#ifndef GLOBALFUN_H
#define GLOBALFUN_H

#include "cv.h"

//cvSetMouseCallback()�Ĳ�������
void on_mouse( int event, int x, int y, int flags, void* ptr );

//on_mouse��������á�������ʼ����
void ShowContent( IplImage* img );

//���������ݶ�
void GetGradient( CvMat*, CvMat*, CvMat* );

#endif