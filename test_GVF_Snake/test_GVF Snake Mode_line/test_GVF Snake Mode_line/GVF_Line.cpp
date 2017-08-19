// GVF_Snake.cpp : �������̨Ӧ�ó������ڵ㡣

/*==================================================================
=  �������ݣ�GVF Snake                                      
=  �޸�����: 2010.10.20                                                                                                        
=  ����:BeanYoung
=  email:guobasanxian@gmail.com                                                
====================================================================*/

#include <iostream>
#include "cv.h"
#include "highgui.h"
#include "GlobalData.h"
#include "GlobalFun.h"
#include "GVFFun.h"
#include <tchar.h>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{

	//��ʼ��ȫ�ֱ���
	//cout << "��ʼ��ȫ�ֱ���"<< endl;
	InitGlobalData();

	//��ȡͼ��
	//cout << "��ȡͼ��" << endl;
	cout << "����ͼ���ļ�����" << endl;
	
	cin >> g_strImageFileName;

	g_pSrcImage = cvLoadImage( g_strImageFileName, CV_LOAD_IMAGE_GRAYSCALE );
	if ( !g_pSrcImage )
	{
		cout << "Load image error." << endl;
		return -1;
	}//if ( !g_pSrcImage )

	g_ImageSize = cvGetSize( g_pSrcImage );

	//Ϊu��v����ռ�
	//cout << "Ϊu��v����ռ�" << endl;

	g_u = cvCreateMat( g_ImageSize.height, g_ImageSize.width, CV_32FC1 );
	g_v = cvCreateMat( g_ImageSize.height, g_ImageSize.width, CV_32FC1 );

	//���edge map
	//cout << "���edge map" << endl;
	g_edge = cvCreateImage( g_ImageSize, IPL_DEPTH_8U, 1 );
	cvConvertScale( g_pSrcImage, g_edge, 1, 0 );	

	for ( int i = 0; i < g_ImageSize.height; i ++ )
	{
		for ( int j = 0; j < g_ImageSize.width; j ++ )
		{
			CvScalar l_s = cvGet2D( g_edge, i, j );
			int l_v = (int)l_s.val[ 0 ];
			if ( l_v < 127 )
			{
				l_v = 1;
			}
			else
			{
				l_v = 0;
			}
			l_s.val[ 0 ] = l_v;
			cvSet2D( g_edge, i, j, l_s );
		}//for ( int j = 0; j < g_ImageSize.width; j ++ )
	}//for ( int i = 0; i < g_ImageSize.height; i ++ )

	//[u,v] = GVF(f, 0.2, 80);         %����߽�ͼf��GVF
	//����GVF��
	cout << "����GVF��" << endl;
	GVFC( g_edge, g_u, g_v, g_mu, g_GVFIter );

	//��ʾ��ʼͼ��
	cout << "��ʾ��ʼͼ��" << endl;
	cvNamedWindow( "SrcImageWnd" );
	cvShowImage( "SrcImageWnd", g_pSrcImage );

	//��ʼ������¼���Ӧ����
	//cout << "��ʼ������¼���Ӧ����" << endl;
	cvSetMouseCallback( "SrcImageWnd", on_mouse, g_pSrcImage );

	//������ʼ��������
	//cout << "������ʼ��������" << endl;
	while ( g_cKey = cvWaitKey( 0 ) )
	{
		if ( g_cKey == 's' || g_cKey == 'S' )
		{
			break;
		}
	}//while ( g_cKey = cvWaitKey( 0 ) )

	//�������snake
	cout << "�������snake" << endl;
	for ( int l_iter = 0;
		l_iter < g_SnakeIter;
		l_iter++)
	{
		//������ɵ�
		//cout << "������ɵ�" << endl;
		vector< CvPoint > l_vecTmpContour( g_InitContour );
		vector< CvPoint >::size_type l_len = g_InitContour.size();

		g_InitContour.clear();

		for ( vector< CvPoint >::size_type l_i = 0;
			l_i < l_len;
			l_i ++ )
		{
			if ( l_vecTmpContour[ l_i ].x < 0
				|| l_vecTmpContour[ l_i ].x >= g_ImageSize.width )
			{
				continue;
			}
			if ( l_vecTmpContour[ l_i ].y < 0
				|| l_vecTmpContour[ l_i ].y >= g_ImageSize.height )
			{
				continue;
			}
			g_InitContour.push_back( l_vecTmpContour[ l_i ] );
		}//for ( vector< CvPoint >::size_type l_i = 0;
			//l_i < l_len;
			//l_i ++ )

		//���������в�ֵ
		//cout << "���������в�ֵ" << endl;
		SnakeInterp( g_InitContour );

		if ( g_InitContour.size() < 5 )
		{
			cout << "Contour interp fault." << endl;
			break;
		}//if ( g_InitContour.size() < 5 )

		//snake����
		//cout << "snake����" << endl;
		SnakeDeform( g_InitContour, g_alpha,g_beta, g_gamma, g_kappa, g_u, g_v, g_DeformIter );

		//��ʾ����Ч��
		//cout << "��ʾ����Ч��" << endl;
		ShowContent( g_pSrcImage );
		cvWaitKey( 20 );
		cout << "������ "
			<< l_iter
			<< " ��"
			<< endl;
	}//	for ( int l_iter = 0;
	 //l_iter < g_SnakeIter;
	 //l_iter++)

	DeleteGlobalData();

	cvWaitKey();

	system("pause");
	return 0;
}

