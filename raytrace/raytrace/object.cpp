#include "object.h"


int inter_sphere( vec origin,vec dir , vec O , double r , vec &nP , vec &nN ) {
	dir.normalize();
	vec v = origin - O;
	double b = -( v * dir );
	double det = b * b - ( v * v ) + r*r , l = 0;
	int ret = 0;
	if ( det > Eps ) {
		det = sqrt( det );
		double i1 = b - det , i2 = b + det;
		if ( i2 < Eps ) return 0;
		if ( i1 > Eps ) l = i1 , ret = 1;
		else l = i2 , ret = -1;
	}
	if ( l < Eps ) return 0;
	nP = origin + dir * l;
	nN = nP - O;
	nN.normalize();
	if ( ret == -1 ) {
		nN.x = -nN.x;
		nN.y = -nN.y;
		nN.z = -nN.z;
	};
	return ret;
}


int inter_plane( vec origin,vec dir , vec N , double r , vec &nP , vec &nN ) {
	dir.normalize();
	N.normalize();
	double d = N * dir;
	if ( fabs( d ) < Eps ) return 0;
	double l = ( N * r - origin ) * N / d;
	if ( l < Eps ) return 0;
	nP = origin + dir * l;
	if ( d < 0 ) nN = N; else {nN.x= -N.x; nN.y=-N.y;nN.z=-N.z;}
	if ( d < 0 ) return 1;
	return -1;
}



int inter_polygon( vec origin,vec dir , vec N , double r , int ver , vec P[] , vec &nP , vec &nN ) {
	dir.normalize();
	N.normalize();
	double d = N * dir;
	if ( fabs( d ) < Eps ) return 0;
	double l = ( N * r - origin ) * N / d;
	if ( l < Eps ) return 0;
	nP = origin + dir * l;

	double area = 0;
	for ( int i = 1 ; i + 1 < ver ; i++ )
		area += fabs( ( ( P[i] - P[0] ).cross( P[i + 1] - P[0] ) ).module() );
	double cnt = fabs( ( ( nP - P[0] ).cross( nP - P[ver - 1] ) ).module() );
	for ( int i = 0 ; i + 1 < ver ; i++ )
		cnt += fabs( ( ( nP - P[i] ).cross( nP - P[i + 1] ) ).module() );
	if ( fabs( area - cnt ) > Eps ) return 0;

	if ( d < 0 ) nN = N; else nN = N.inversion();
	if ( d < 0 ) return 1;
	return -1;
}



int inter_circle(vec origin, vec dir, vec N, double r, vec C,vec &nP,vec &nN){
	vec R=C-origin;
	N.normalize();
	double l=R*N;
	double m=dir*N;
	double n=l/m;
	dir=dir*n;
	vec L=dir-R;
	vec P=C+L;
	double dist=(P-C).module();
	if (dist>r)return 0;
	nP=P;
	nN=N;
	return 1;
}


int inter_cylinder(vec origin, vec dir, vec C,vec N,double r,double h,vec &nP,vec &nN){
	dir.normalize();
	N.normalize();
	vec origin2=origin-N*(N*origin);
	
	vec dir2=dir-N*(N*dir);
	vec C2=C-N*(N*C);
	double a,b,c,d,t1,t2;
	a=dir2.x*dir2.x+dir2.y*dir2.y+dir2.z*dir2.z;
	b=2*dir2.x*(origin2.x-C2.x)+2*dir2.y*(origin2.y-C2.y)+2*dir2.z*(origin2.z-C2.z);
	c=(origin2.x-C2.x)*(origin2.x-C2.x)+(origin2.y-C2.y)*(origin2.y-C2.y)+(origin2.z-C2.z)*(origin2.z-C2.z)-r*r;
	d=b*b-4*a*c;

	if (d<0)
	{
		return 0;
	}else if (d==0)
	{
		t1=(-b/(2*a));
		vec P=origin+dir*t1;
		vec PC=P-C;
		if(N*PC<0)return 0;
		vec PC2=PC-N*(N*PC);
		if(PC*N>h)return 0;
		nP=P;
		nN=PC2;
		nN.normalize();
		return 1;

	}else if (d>0)
	{
		t1=(-b+sqrt(d))/(2*a);
		t2=(-b-sqrt(d))/(2*a);

		vec P1=origin+dir*t1;
		vec PC1=P1-C;
		vec PC2=PC1-N*(N*PC1);

		vec P3=origin+dir*t2;
		vec PC3=P3-C;
		vec PC4=PC3-N*(N*PC3);

		if(N*PC1<0&&N*PC3<0)return 0;
		
		if((P1-origin).module()<(P3-origin).module()&&PC1*N<h){
			nP=P1;
			nN=PC2;
			nN.normalize();
			return 1;
		}else if ((P1-origin).module()>=(P3-origin).module()&&PC3*N<h)
		{
			nP=P3;
			nN=PC4;
			nN.normalize();
			return 1;
		}

		return 0;

		
	}
	
}