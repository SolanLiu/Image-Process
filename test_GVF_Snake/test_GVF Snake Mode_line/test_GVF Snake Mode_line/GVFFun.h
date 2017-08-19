/*==================================================================
=  代码内容：GVF Snake                                      
=  修改日期: 2010.10.20                                                                                                        
=  作者:BeanYoung
=  email:guobasanxian@gmail.com                                                
====================================================================*/

#ifndef GVFFUN_H
#define GVFFUN_H

#include "cv.h"
#include <vector>

//求解GVF场
void GVFC( IplImage* ,CvMat* ,CvMat* ,double ,int );

//对轮廓插值
void SnakeInterp( std::vector<CvPoint>& );

//迭代求解snake
void SnakeDeform( std::vector < CvPoint >& ,
				 double ,
				 double ,
				 double ,
				 double ,
				 CvMat* ,
				 CvMat* ,
				 int  );

//求解边界控制点的距离
void GetContourDistance( std::vector < CvPoint >&,
						std::vector< double >& );

#endif