/*==================================================================
=  �������ݣ�GVF Snake                                      
=  �޸�����: 2010.10.20                                                                                                        
=  ����:BeanYoung
=  email:guobasanxian@gmail.com                                                
====================================================================*/
#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include "cv.h"
#include <vector>

//ͼ���ļ���
extern char* g_strImageFileName; 
//ԭʼͼ��ָ��
extern IplImage* g_pSrcImage;
//ԭʼͼ���С
extern CvSize g_ImageSize;
//GVF��u,v
extern CvMat* g_u;
extern CvMat* g_v;
//���cvSobel�������
extern IplImage* g_TmpEdge;
//edge map�߽�ͼ
extern IplImage* g_edge;
//��ʼ�߽�����
extern std::vector< CvPoint > g_InitContour;
//�߽�ͼ��
extern IplImage* g_ContourImage;
//��¼����
extern char g_cKey;

//GVF������
extern double g_alpha;
extern double g_beta;
extern double g_gamma;
extern double g_kappa;
extern double g_mu;

//snake��������
extern int g_SnakeIter;
//GVF����������
extern int g_GVFIter;
//deform����
extern int g_DeformIter;

//��ʼ��ȫ�ֱ���
void InitGlobalData();
void DeleteGlobalData();

#endif