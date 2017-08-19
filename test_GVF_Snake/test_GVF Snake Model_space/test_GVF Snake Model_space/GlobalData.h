/*==================================================================
=  代码内容：GVF Snake                                      
=  修改日期: 2010.10.20                                                                                                        
=  作者:BeanYoung
=  email:guobasanxian@gmail.com                                                
====================================================================*/
#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include "cv.h"
#include <vector>

//图像文件名
extern char* g_strImageFileName; 
//原始图像指针
extern IplImage* g_pSrcImage;
//原始图像大小
extern CvSize g_ImageSize;
//GVF场u,v
extern CvMat* g_u;
extern CvMat* g_v;
//解决cvSobel溢出问题
extern IplImage* g_TmpEdge;
//edge map边界图
extern IplImage* g_edge;
//初始边界数组
extern std::vector< CvPoint > g_InitContour;
//边界图像
extern IplImage* g_ContourImage;
//记录键盘
extern char g_cKey;

//GVF求解参数
extern double g_alpha;
extern double g_beta;
extern double g_gamma;
extern double g_kappa;
extern double g_mu;

//snake迭代次数
extern int g_SnakeIter;
//GVF场迭代次数
extern int g_GVFIter;
//deform次数
extern int g_DeformIter;

//初始化全局变量
void InitGlobalData();
void DeleteGlobalData();

#endif