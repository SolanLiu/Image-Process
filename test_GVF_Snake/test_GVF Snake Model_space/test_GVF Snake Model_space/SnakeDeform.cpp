/*==================================================================
=  代码内容：GVF Snake                                      
=  修改日期: 2010.10.20                                                                                                        
=  作者:BeanYoung
=  email:guobasanxian@gmail.com                                                
====================================================================*/

#include "GVFFun.h"
#include <iostream>

/////////////////////////////////////////////////////////////////////////
//function [x,y] = snakedeform(x,y,alpha,beta,gamma,kappa,fx,fy,ITER)
//% SNAKEDEFORM  Deform snake in the given external force field
//%     [x,y] = snakedeform(x,y,alpha,beta,gamma,kappa,fx,fy,ITER)
//%
//%     alpha:   elasticity parameter 弹性参数
//%     beta:    rigidity parameter   刚性参数
//%     gamma:   viscosity parameter  粘性参数
//%     kappa:   external force weight   权重
//%     fx,fy:   external force field    力量场
//
//%      Chenyang Xu and Jerry L. Prince, 4/1/95, 6/17/97
//%      Copyright (c) 1995-97 by Chenyang Xu and Jerry L. Prince
//%      Image Analysis and Communications Lab, Johns Hopkins University
//
//
//% generates the parameters for snake
//
//N = length(x);    % x的长度
//
//alpha = alpha* ones(1,N); 
//beta = beta*ones(1,N);
//
//% produce the five diagnal vectors
//alpham1 = [alpha(2:N) alpha(1)];
//alphap1 = [alpha(N) alpha(1:N-1)];
//betam1 = [beta(2:N) beta(1)];
//betap1 = [beta(N) beta(1:N-1)];
//
//a = betam1;
//b = -alpha - 2*beta - 2*betam1;
//c = alpha + alphap1 +betam1 + 4*beta + betap1;
//d = -alphap1 - 2*beta - 2*betap1;
//e = betap1;
//
//% generate the parameters matrix
//A = diag(a(1:N-2),-2) + diag(a(N-1:N),N-2);
//A = A + diag(b(1:N-1),-1) + diag(b(N), N-1);
//A = A + diag(c);
//A = A + diag(d(1:N-1),1) + diag(d(N),-(N-1));
//A = A + diag(e(1:N-2),2) + diag(e(N-1:N),-(N-2));
//
//invAI = inv(A + gamma * diag(ones(1,N)));
//
//for count = 1:ITER,
//   vfx = interp2(fx,x,y,'*linear');
//   vfy = interp2(fy,x,y,'*linear');
//
//   % deform snake
//   x = invAI * (gamma* x + kappa*vfx);
//   y = invAI * (gamma* y + kappa*vfy);
//end
/////////////////////////////////////////////////////////////////

using namespace std;

void SnakeDeform( std::vector<CvPoint>& Contour,
				 double alpha,
				 double beta,
				 double gamma,
				 double kappa,
				 CvMat* u,
				 CvMat* v,
				 int iter )
{
	//a = betam1;
	//b = -alpha - 2*beta - 2*betam1;
	//c = alpha + alphap1 +betam1 + 4*beta + betap1;
	//d = -alphap1 - 2*beta - 2*betap1;
	//e = betap1;

	double l_fA = beta;
	double l_fB = - alpha - 4.0 * beta;
	double l_fC = 2.0 * alpha + 6.0 * beta;
	double l_fD = - alpha - 4.0 * beta;
	double l_fE = beta;

	int l_ContourSize = Contour.size();

	//求解A

	CvMat* A = cvCreateMat( l_ContourSize, l_ContourSize, CV_32FC1 );
	cvZero( A );
	//A = diag(a(1:N-2),-2) + diag(a(N-1:N),N-2);
	//A = A + diag(b(1:N-1),-1) + diag(b(N), N-1);
	//A = A + diag(c);
	//A = A + diag(d(1:N-1),1) + diag(d(N),-(N-1));
	//A = A + diag(e(1:N-2),2) + diag(e(N-1:N),-(N-2));

	for ( int j = 0; j < l_ContourSize; j ++ )
	{
		int l_ap = ( j + 2 + l_ContourSize ) % l_ContourSize;
		int l_bp = ( j + 1 + l_ContourSize ) % l_ContourSize;
		int l_cp = j;
		int l_dp = ( j - 1 + l_ContourSize ) % l_ContourSize;
		int l_ep = ( j - 2 + l_ContourSize ) % l_ContourSize;

		cvmSet( A, l_ap, j, l_fA );
		cvmSet( A, l_bp, j, l_fB );
		cvmSet( A, l_cp, j, l_fC );
		cvmSet( A, l_dp, j, l_fD );
		cvmSet( A, l_ep, j, l_fE );
	}//for ( int j = 0; j < l_ContourSize; j ++ )

	//invAI = inv(A + gamma * diag(ones(1,N)));

	for ( int i = 0; i < l_ContourSize; i ++ )
	{
		double l_fGamma = cvmGet( A, i, i ) + gamma;
		cvmSet( A, i, i, l_fGamma );
	}//for ( int i = 0; i < l_ContourSize; i ++ )
	cvInvert( A, A );

	//for count = 1:ITER,
	//   vfx = interp2(fx,x,y,'*linear');
	//   vfy = interp2(fy,x,y,'*linear');
	//
	//   % deform snake
	//   x = invAI * (gamma* x + kappa*vfx);
	//   y = invAI * (gamma* y + kappa*vfy);
	//end

	//存储点的横纵坐标

	CvMat* l_mXi = cvCreateMat( l_ContourSize, 1, CV_32FC1 );
	CvMat* l_mYi = cvCreateMat( l_ContourSize, 1, CV_32FC1 );

	for ( int i = 0; i < l_ContourSize; i ++ )
	{
		cvmSet( l_mXi, i, 0, Contour[ i ].x );
		cvmSet( l_mYi, i, 0, Contour[ i ].y );
	}//for ( int i = 0; i < l_ContourSize; i ++ )

	CvMat* l_mVfx = cvCreateMat( l_ContourSize, 1, CV_32FC1 );
	CvMat* l_mVfy = cvCreateMat( l_ContourSize, 1, CV_32FC1 );

	for ( int k = 0; k < iter; k ++ )
	{

		for ( int i = 0; i < l_ContourSize; i ++ )
		{
			int l_iXi = ( int )cvmGet( l_mXi, i, 0 );
			int l_iYi = ( int )cvmGet( l_mYi, i, 0 );
			double l_fVfx = cvmGet( u, l_iYi, l_iXi );
			double l_fVfy = cvmGet( v, l_iYi, l_iXi );

			cvmSet( l_mVfx, i, 0, l_fVfx );
			cvmSet( l_mVfy, i, 0, l_fVfy );
		}//for ( int i = 0; i < l_ContourSize; i ++ )
		//   x = invAI * (gamma* x + kappa*vfx);
		//   y = invAI * (gamma* y + kappa*vfy);
		cvConvertScale( l_mXi, l_mXi, gamma );
		cvConvertScale( l_mYi, l_mYi, gamma );
		cvConvertScale( l_mVfx, l_mVfx, kappa );
		cvConvertScale( l_mVfy, l_mVfy, kappa );

		cvAdd( l_mXi, l_mVfx, l_mVfx );
		cvAdd( l_mYi, l_mVfy, l_mVfy );
		cvmMul( A, l_mVfx, l_mXi );
		cvmMul( A, l_mVfy, l_mYi );

		Contour.clear();

		for ( int i = 0; i < l_ContourSize; i ++ )
		{
			int l_tempX = ( int )cvmGet( l_mXi, i, 0 );
			int l_tempY = ( int )cvmGet( l_mYi, i, 0 );
			Contour.push_back( cvPoint( l_tempX, l_tempY ) );
		}//for ( int i = 0; i < l_ContourSize; i ++ )
	}//for ( int k = 0; k < iter; k ++ )
}