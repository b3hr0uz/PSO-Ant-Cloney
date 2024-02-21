#include "stdafx.h"
#include <iostream>
#include <time.h>
#include <Windows.h>
#include <conio.h>

using namespace std ;

int MaxX, MaxY, VelocityMax ;
float VelocityX[100], VelocityY[100];
float XCoord[100], YCoord[100] ;
int IBest, IPBest ;
float ParticleBest[ 100 ];
float FuncXY[100] ;
float MinOfFunc ;
float Precise, Weight = 1;

void Initilize()
{
BEGIN:
	cout << "ENTER MAXIMAM X AND Y COORDINATION RANGE.\n(ENTERY SHOULD NOT BE ZERO i.e: 5, -10, 15, ONLY INTEGERS WILL WORK.) \nX MAX RANGE: " ;
	cin >> MaxX ;
	cout << "Y MAX RANGE: ";
	cin >> MaxY ;
	if ( MaxX == 0 || MaxY == 0 )
		goto BEGIN ;
	if ( MaxX * MaxX > 81 || MaxY * MaxY > 81 )
		Precise = 0.005 ;
	else
		Precise = 0.005 ;

	VelocityMax = 2 ;
	for ( int i = 0 ; i < 100 ; i ++ ) 
	{
		if ( rand() %2 == 0)
			XCoord[i] = ( rand() % ( 100 * MaxX ) ) / 100.00 ;
		else 
			XCoord[i] = ( rand() % ( 100 * MaxX ) ) / -100.00 ;
		if ( rand() %2 == 0)
			YCoord[i] = ( rand() % ( 100 * MaxY ) ) / 100.00 ;
		else 
			YCoord[i] = ( rand() % ( 100 * MaxY ) ) / -100.00 ;
		
		VelocityX[i] = rand() % VelocityMax ;
		VelocityY[i] = rand() % VelocityMax ;

	}
	
	for ( int i = 0 ; i < 100 ; i ++ ) 
	{
		FuncXY[i] = XCoord[i] * XCoord[i] + YCoord[i] * YCoord[i] ;
		ParticleBest[i] = FuncXY[i] ;
	}
}

void ParticleVelocity()
{
	for ( int i = 0 ; i < 100 ; i ++ )
	{
		float Rand = ( ( rand() % 200 ) / 100.00 ) + 1 ;
		Weight = ( rand() % 400 ) / 1000.00 ;
		VelocityX[i] = Weight * VelocityX[i] + Rand * ( XCoord[IPBest] - XCoord[i] ) + ( 4 - Rand ) * ( XCoord[IBest] - XCoord[i] ) ;
		VelocityY[i] = Weight * VelocityY[i] + Rand * ( YCoord[IPBest] - YCoord[i] ) + ( 4 - Rand ) * ( YCoord[IBest] - YCoord[i] ) ;
	
		if ( VelocityX[i] > VelocityMax )
			VelocityX[i] = VelocityMax ;
		if ( VelocityX[i] < (-1)* VelocityMax )
			VelocityX[i] = (-1) * VelocityMax ;
		if ( VelocityY[i] > VelocityMax )
			VelocityY[i] = VelocityMax ;
		if ( VelocityY[i] < (-1) * VelocityMax )
			VelocityY[i] = (-1) * VelocityMax ;
	}
}
void Update()
{
	for ( int i = 0 ; i < 100 ; i ++ )
	{
		XCoord[i] += VelocityX[i] ;
		YCoord[i] += VelocityY[i] ;
		if ( XCoord[i] * XCoord[i] + YCoord[i] * YCoord[i] < ParticleBest[i] ) 
		{
			ParticleBest[i] = XCoord[i] * XCoord[i] + YCoord[i] * YCoord[i] ;
			IPBest = i ;
		}
	}
}

void Cycle()
{
	
	ParticleVelocity() ;
	Update() ;

	for ( int i = 0 ; i < 100 ; i ++ ) 
		FuncXY[i] = XCoord[i] * XCoord[i] + YCoord[i] * YCoord[i] ;

	for ( int i = 1 ; i < 100 ; i ++ ) 
		if ( FuncXY[i] <= MinOfFunc )
		{
			MinOfFunc = FuncXY[i] ;
			IBest = i ; 
		}
}

int _tmain(int argc, _TCHAR* argv[])
{
	cout<< "THIS PROGRAM FINDS THE MINIMUM OF THE FUNCTION (X^2)+(Y^2)\n";
START:
	srand ( time ( NULL ) ) ;
	
	Initilize() ;
	MinOfFunc = FuncXY[0] ;
	cout << endl ;
	cout << "X VALUE" << "\t\t" << "Y VALUE" << "\t\t" << "(X^2)+(Y^2) \n";
	while ( FuncXY[IBest] > Precise )
	{		
			Cycle() ;
			cout << XCoord[IBest] << "\t\t" << YCoord[IBest] << "\t\t" << FuncXY[IBest] << endl ; 
	}

	cout << endl << endl << XCoord[IBest] << "\t\t" << YCoord[IBest] << "\t\t" << MinOfFunc << endl << endl ;

//	system( "PAUSE" );
//	cout << "PRESS 'S' TO START OVER." << endl << endl ;
	
//	if ( _getch() == 's')
		goto START ;
}
