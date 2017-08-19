/*==================================================================
=  代码内容：GVF Snake                                      
=  修改日期: 2010.10.20                                                                                                        
=  作者:BeanYoung
=  email:guobasanxian@gmail.com                                                
====================================================================*/

#include "GVFFun.h"
#include "cv.h"
#include "highgui.h"
#include "GlobalData.h"
#include "GlobalFun.h"

using namespace std;

void GVFC( IplImage* edge_map,CvMat* u,CvMat* v,double mu,int iter )
{

	CvSize l_ImageSize = cvGetSize( edge_map );
	CvMat* l_TmpEdge = cvCreateMat( l_ImageSize.height, l_ImageSize.width, CV_32FC1 );
	CvMat* l_mB = cvCreateMat( l_ImageSize.height, l_ImageSize.width, CV_32FC1 );
	CvMat* l_mC1 = cvCreateMat( l_ImageSize.height, l_ImageSize.width, CV_32FC1 );
	CvMat* l_mC2 = cvCreateMat( l_ImageSize.height, l_ImageSize.width, CV_32FC1 );
	CvMat* l_mFx = cvCreateMat( l_ImageSize.height, l_ImageSize.width, CV_32FC1 );
	CvMat* l_mFy = cvCreateMat( l_ImageSize.height, l_ImageSize.width, CV_32FC1 );
	CvMat* l_mLu = cvCreateMat( l_ImageSize.height, l_ImageSize.width, CV_32FC1 );
	CvMat* l_mLv = cvCreateMat( l_ImageSize.height, l_ImageSize.width, CV_32FC1 );

	cvConvertScale( edge_map, l_TmpEdge, 1 );

	//[m,n] = size(f);
	//fmin  = min(f(:));
	//fmax  = max(f(:));
	//f = (f-fmin)/(fmax-fmin);  % Normalize f to the range [0,1]   归一化处理
	double l_dMin, l_dMax;
	cvMinMaxLoc( l_TmpEdge, &l_dMin, &l_dMax, NULL, NULL, NULL );
	double l_dScale = 1.0 / ( l_dMax - l_dMin );
	double l_dShift = - 1.0 * l_dMin / ( l_dMax - l_dMin );
	cvConvertScale( l_TmpEdge, 
			l_TmpEdge,
			l_dScale, 
			l_dShift);

	//[fx,fy] = gradient(f);

	//GetGradient( l_TmpEdge, u, v );

	CvMat* l_mFilterX = cvCreateMat( 3, 3, CV_32FC1 );
	cvZero( l_mFilterX );
	cvmSet( l_mFilterX, 1, 0, - 1.0 );
	cvmSet( l_mFilterX, 1, 2, 1.0 );
	cvFilter2D( l_TmpEdge, u, l_mFilterX );
	cvConvertScale( u, u, 0.5 );

	CvMat* l_mFilterY = cvCreateMat( 3, 3, CV_32FC1 );
	cvZero( l_mFilterY );
	cvmSet( l_mFilterY, 0, 1, - 1.0 );
	cvmSet( l_mFilterY, 2, 1, 1.0 );
	cvFilter2D( l_TmpEdge, v, l_mFilterY );
	cvConvertScale( v, v, 0.5 );

	cvCopy( u, l_mFx );
	cvCopy( v, l_mFy );

	//求解论文中的b, c1, c2
	for ( int i = 0; i < l_ImageSize.width; i ++ )
	{
		for ( int j = 0; j < l_ImageSize.height; j ++ )
		{
			double l_dTmpX = cvmGet( l_mFx, j, i );
			double l_dTmpY = cvmGet( l_mFy, j, i );
			double l_dB = l_dTmpX * l_dTmpX + l_dTmpY * l_dTmpY;
			double l_dC1 = l_dB * l_dTmpX;
			double l_dC2 = l_dB * l_dTmpY;
			cvmSet( l_mB, j, i, l_dB );
			cvmSet( l_mC1, j, i, l_dC1 );
			cvmSet( l_mC2, j, i, l_dC2 );
		}//for ( int j = 0; j < l_ImageSize.height; j ++ )
	}//for ( int i = 0; i < l_ImageSize.width; i ++ )

	//% Iteratively solve for the GVF u,v  迭代求解u，v
	//for i=1:ITER,
	//  u = BoundMirrorEnsure(u);     %镜像u的边界，但是u的大小不变
	//  v = BoundMirrorEnsure(v);      %镜像v的边界，但是v的大小不变
	//  
	//  %mu=0.2
	//  u = u + mu*4*del2(u) - SqrMagf.*(u-fx);      
	//  v = v + mu*4*del2(v) - SqrMagf.*(v-fy);
	//  fprintf(1, '%3d', i);
	//  if (rem(i,20) == 0)
	//	 fprintf(1, '\n');
	//  end 
	//end
	for ( int k = 0; k < iter; k ++ )
	{
		cvZero( l_mLu );
		cvZero( l_mLv );

		//  u = u + mu*4*del2(u) - SqrMagf.*(u-fx);      
		//  v = v + mu*4*del2(v) - SqrMagf.*(v-fy);

		cvLaplace( u, l_mLu, 1 );
		cvLaplace( v, l_mLv, 1 );

		for ( int i = 0; i < l_ImageSize.width; i ++ )
		{
			for ( int j = 0; j < l_ImageSize.height; j ++ )
			{
				double l_dU = cvmGet( u, j, i );
				double l_dV = cvmGet( v, j, i );
				double l_dLu = cvmGet( l_mLu, j, i );
				double l_dLv = cvmGet( l_mLv, j, i );
				double l_dC1 = cvmGet( l_mC1, j, i );
				double l_dC2 = cvmGet( l_mC2, j, i );
				double l_dB = cvmGet( l_mB, j, i );

				l_dU = ( 1.0 - l_dB ) * l_dU + mu * l_dLu + l_dC1;
				l_dV = ( 1.0 - l_dB ) * l_dV + mu * l_dLv + l_dC2;

				cvmSet( u, j, i, l_dU );
				cvmSet( v, j, i, l_dV );
			}//for ( int j = 0; j < l_ImageSize.height; j ++ )
		}//for ( int i = 0; i < l_ImageSize.width; i ++ )
	}//for ( int k = 0; k < iter; k ++ )

	for ( int i = 0; i < l_ImageSize.width; i ++ )
	{
		for ( int j = 0; j < l_ImageSize.height; j ++ )
		{
			double l_dU = cvmGet( u, j, i );
			double l_dV = cvmGet( v, j, i );
			double l_dMag = sqrt( l_dU * l_dU + l_dV * l_dV );
			l_dMag = l_dMag + 1e-10;
			l_dU = l_dU / l_dMag;
			l_dV = l_dV / l_dMag;

			cvmSet( u, j, i, l_dU );
			cvmSet( v, j, i, l_dV );
		}//for ( int j = 0; j < l_ImageSize.height; j ++ )
	}//for ( int i = 0; i < l_ImageSize.width; i ++ )

	cvReleaseMat( &l_TmpEdge );
	cvReleaseMat( &l_mB );
	cvReleaseMat( &l_mC1 );
	cvReleaseMat( &l_mC2 );
	cvReleaseMat( &l_mFx );
	cvReleaseMat( &l_mFy );
	cvReleaseMat( &l_mLu );
	cvReleaseMat( &l_mLv );
	//cvReleaseMat( &l_mFilterY );
	//cvReleaseMat( &l_mFilterX );
}