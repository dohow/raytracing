#include"stdio.h"
#include "math.h"
#include<iostream>
#include<string>
#include<cstdio>
#include<cmath>

using namespace std;

static const int maxobj = 1024;
static const int maxver = 8;
static const double Eps = 1e-6;
static const double Pi = 3.1415927;

struct vec{
	double x,y,z;
	vec() {}
	vec( double X , double Y , double Z ) { x = X , y = Y , z = Z; }
	vec operator - ( vec B ) {
		vec C;
		C.x = x - B.x , C.y = y - B.y , C.z = z - B.z;
		return C;
	}
	vec operator + ( vec B ) {
		vec C;
		C.x = x + B.x , C.y = y + B.y , C.z = z + B.z;
		return C;
	}
	vec operator * ( double k ) {
		vec C;
		C.x = x * k , C.y = y * k , C.z = z * k;
		return C;
	}
	double operator * ( vec B ) {
		return x * B.x + y * B.y + z * B.z;
	}


	double module() {
		return sqrt( x*x + y*y + z*z );
	}
	void normalize() {
		double len = module();
		x /= len , y /= len , z /= len;
	}

	vec cross( vec nor ) {
		return vec( nor.y * z - nor.z * y , nor.z * x - nor.x * z , nor.x * y - nor.y * x );
	}

	vec inversion() {
		vec C;
		C.x = -x , C.y = -y , C.z = -z;
		return C;
	}
};

struct color_s{
	double r,g,b;
	color_s(double R,double G,double B){r=R;g=G;b=B;}
	color_s() {}
	color_s operator * ( double k ) {
		color_s ret; ret.r = r * k , ret.g = g * k , ret.b = b * k;
		return ret;
	}
	color_s operator * ( color_s B ) {
		color_s ret; ret.r = r * B.r , ret.g = g * B.g , ret.b = b * B.b;
		return ret;
	}
	color_s operator + ( color_s B ) {
		color_s ret; ret.r = r + B.r , ret.g = g + B.g , ret.b = b + B.b;
		return ret;
	}
	color_s inverse() {
		return color_s( 1 - r , 1 - g , 1 - b );
	}
	double value() {
		return max( r , max( g , b ) );
	}
	void limit() {
		if ( r > 1 ) r = 1;
		if ( g > 1 ) g = 1;
		if ( b > 1 ) b = 1;
	}
};

struct object{
	string type;
	vec O , N;
	vec P[8];
	double radius , h;
	double reflect , diffuse , specular;
	color_s color;
	bool islight;
	int ver;

	void material( double Refl , double Diff , double Spec ) {
		reflect = Refl , diffuse = Diff , specular = Spec;
	}	

	void completion() {
		if ( type == "polygon" ) {
			N = ( P[0] - P[1] ).cross( P[0] - P[2] ) , N.normalize();
			radius = P[0] * N / ( N * N );
			if ( radius < -Eps ) {
				N = N.inversion();
				radius = -radius;
			}
		}
	}
};

int inter_sphere( vec origin,vec dir , vec O , double r , vec &nP , vec &nN );

int inter_plane( vec origin,vec dir , vec N , double r , vec &nP , vec &nN );

int inter_polygon( vec origin,vec dir , vec N , double r , int ver , vec P[] , vec &nP , vec &nN );

int inter_circle(vec origin, vec dir, vec N, double r, vec C,vec &nP,vec &nN);

int inter_cylinder(vec origin, vec dir, vec C,vec N,double r,double h,vec &nP,vec &nN);