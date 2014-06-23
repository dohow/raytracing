#include<iostream>
#include<cstdlib>
#include<cstdio>
#include"bmp.h"

const int pixel = 1024;
const int max_tex = 4;

BITMAPFILEHEADER strHead , Head;
BITMAPINFOHEADER strInfo , Info;
IMAGEDATA ima[pixel][pixel];
int H , W;


void image_input( char file[] ) {
	FILE *fpi = fopen( file , "rb" );
	WORD bfType; 
	fread( &bfType , 1 , sizeof( WORD ) , fpi );
	fread( &strHead , 1 , sizeof( tagBITMAPFILEHEADER ) , fpi );
	fread( &strInfo , 1 , sizeof( tagBITMAPINFOHEADER ) , fpi );
	
	fclose( fpi );
	H = strInfo.biHeight , W = strInfo.biWidth;
}
	
void image_output( char file[] ) {
	FILE *fpw = fopen( file , "wb" );
	WORD bfType = 0x4d42;
	fwrite( &bfType , 1 , sizeof( WORD ) , fpw );
	fwrite( &strHead , 1 , sizeof( tagBITMAPFILEHEADER ) , fpw );
	fwrite( &strInfo , 1 , sizeof( tagBITMAPINFOHEADER ) , fpw );
	for(int i = 0 ; i < strInfo.biWidth ; i++ ) {
		for(int j = 0 ;j < strInfo.biHeight ; j++ ) {
			fwrite( &ima[i][j].blue , 1 , sizeof( BYTE ) , fpw );
			fwrite( &ima[i][j].green , 1 , sizeof( BYTE ) , fpw );
			fwrite( &ima[i][j].red , 1 , sizeof( BYTE ) , fpw );
		}
	}
	fclose( fpw );
}
