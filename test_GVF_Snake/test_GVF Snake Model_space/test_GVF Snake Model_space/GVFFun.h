/*==================================================================
=  �������ݣ�GVF Snake                                      
=  �޸�����: 2010.10.20                                                                                                        
=  ����:BeanYoung
=  email:guobasanxian@gmail.com                                                
====================================================================*/

#ifndef GVFFUN_H
#define GVFFUN_H

#include "cv.h"
#include <vector>

//���GVF��
void GVFC( IplImage* ,CvMat* ,CvMat* ,double ,int );

//��������ֵ
void SnakeInterp( std::vector<CvPoint>& );

//�������snake
void SnakeDeform( std::vector < CvPoint >& ,
				 double ,
				 double ,
				 double ,
				 double ,
				 CvMat* ,
				 CvMat* ,
				 int  );

//���߽���Ƶ�ľ���
void GetContourDistance( std::vector < CvPoint >&,
						std::vector< double >& );

#endif