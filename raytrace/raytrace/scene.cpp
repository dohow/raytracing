#include "scene.h"


void scene::build_scene() {
	objectList[objectnum].type = "sphere";
	objectList[objectnum].islight = true;//是否为光源
	objectList[objectnum].O = vec( 5 , 5 , 0 );
	objectList[objectnum].radius = 0.05;
	objectList[objectnum].color = color_s( 1 , 1 , 1 );
	objectnum++;

	objectList[objectnum].type = "sphere";
	objectList[objectnum].islight = true;//是否为光源
	objectList[objectnum].O = vec( 5 , 2 , 5 );
	objectList[objectnum].radius = 0.05;
	objectList[objectnum].color = color_s( 1 , 1 , 1 );
	objectnum++;


	objectList[objectnum].type = "sphere";
	objectList[objectnum].O = vec( -5 , 6 , 0 );
	objectList[objectnum].radius = 0.8;
	objectList[objectnum].color = color_s( 1 , 0 , 1 );
	objectList[objectnum].material( 0 , 0.6 , 0.5);
	objectnum++;


	objectList[objectnum].type = "sphere";
	objectList[objectnum].O = vec( -5 , 10, -2);
	objectList[objectnum].radius = 2;
	objectList[objectnum].color = color_s( 0.6 ,0.6, 0.6);
	objectList[objectnum].material( 1 , 0 , 0.5);
	objectnum++;


	objectList[objectnum].type = "plane";
	objectList[objectnum].N = vec( 0 , 0 , -1 );
	objectList[objectnum].radius = 10;
	objectList[objectnum].color = color_s(1 , 0 , 0 );
	objectList[objectnum].material( 0 ,  0.5 , 0 );
	objectnum++;

	objectList[objectnum].type = "plane";
	objectList[objectnum].N = vec( 0 , 0 , 1 );
	objectList[objectnum].radius = 10;
	objectList[objectnum].color = color_s( 0 , 0 , 1 );
	objectList[objectnum].material( 0 ,  0.5 , 0 );
	objectnum++;
	
	objectList[objectnum].type = "plane";
	objectList[objectnum].N = vec( 0 , 1 , 0 );
	objectList[objectnum].radius = 15;
	objectList[objectnum].color = color_s( 0.8 , 0.8 , 0.8 );
	objectList[objectnum].material( 0 ,  0.5 , 0.2 );
	objectnum++;

	objectList[objectnum].type = "plane";
	objectList[objectnum].N = vec( 1 , 0 , 0 );
	objectList[objectnum].radius = 10;
	objectList[objectnum].color = color_s( 0.3 , 0.3 , 0.3 );
	objectList[objectnum].material( 0 ,  1 , 0.1 );
	objectnum++;

	objectList[objectnum].type = "plane";
	objectList[objectnum].N = vec( -1 , 0 , 0 );
	objectList[objectnum].radius = 10;
	objectList[objectnum].color = color_s( 1 , 1 , 0 );
	objectList[objectnum].material( 0  , 0.5 , 0 );
	objectnum++;

	vec P[8];
	P[0]=vec(-6,10,-8);
	P[1]=vec(-8,10,-8);
	P[2]=vec(-8,10,-6);
	P[3]=vec(-6,10,-6);
	P[4]=vec(-6,12,-6);
	P[5]=vec(-8,12,-6);
	P[6]=vec(-8,12,-8);
	P[7]=vec(-6,12,-8);
	color_s c=color_s(0,1,0);
	addcuboid(P,0,0.5,0,c);

	vec C=vec(-8,12,2);
	vec N=vec(1,0,0);
	double r=1.5;
	double h=3;
	c=color_s(0.54,0.17,0.88);
	addcylinder(C,N,r,h,0,0.5,0,c);

}

int scene::intersectNear(vec dir, vec origin, int &objID,vec &nP,vec &nN){
	bool hitYet=false;
	int hitstate=0;
	vec tmpP,tmpN;
	int ret=0;
	
	for (int i=0;i<objectnum;i++)
	{
		if(objectList[i].type=="sphere")
			ret=inter_sphere(origin,dir,objectList[i].O,objectList[i].radius,tmpP,tmpN);
		else if(objectList[i].type=="plane")
			ret=inter_plane(origin,dir,objectList[i].N,objectList[i].radius,tmpP,tmpN);
		else if (objectList[i].type=="polygon")
			ret = inter_polygon( origin,dir , objectList[i].N , objectList[i].radius , objectList[i].ver , objectList[i].P , tmpP , tmpN );
		else if(objectList[i].type=="circle")
			ret = inter_circle(origin,dir,objectList[i].N,objectList[i].radius,objectList[i].O,tmpP,tmpN);
		else if (objectList[i].type=="cylinder")
			ret = inter_cylinder(origin,dir,objectList[i].O,objectList[i].N,objectList[i].radius,objectList[i].h,tmpP,tmpN);

		if(ret!=0 && (!hitYet || (tmpP-origin).module() < (nP-origin).module() )){
			hitYet=true;
			objID=i;
			nP=tmpP;
			nN=tmpN;
			hitstate=ret;
		}
	}

	return hitstate;
}

int scene::intersect( vec origin , vec dir , int i , vec &nP , vec &nN ) {
	int check = false;
	if ( objectList[i].type == "sphere" )
		check = inter_sphere( origin,dir , objectList[i].O , objectList[i].radius , nP , nN );
	if ( objectList[i].type == "plane" )
		check = inter_plane(origin,dir,objectList[i].N,objectList[i].radius,nP,nN);
	if (objectList[i].type=="polygon")
		check = inter_polygon( origin,dir , objectList[i].N , objectList[i].radius , objectList[i].ver , objectList[i].P , nP , nN );
	if (objectList[i].type=="circle")
		check = inter_circle(origin,dir,objectList[i].N,objectList[i].radius,objectList[i].O,nP,nN);
	if (objectList[i].type=="cylinder")
		check = inter_cylinder(origin,dir,objectList[i].O,objectList[i].N,objectList[i].radius,objectList[i].h,nP,nN);
	return check;
}

vec direction( double x , double z ) {
	vec dir = y_axis;
	dir = dir + x_axis * wid_x * x;
	dir = dir + z_axis * wid_z * z;
	return dir;
}


void scene::addcuboid(vec P[],double Refl ,  double Diff , double Spec,color_s c){
	objectList[objectnum].type="polygon";
	objectList[objectnum].ver = 4;
	objectList[objectnum].P[0] = P[0];
	objectList[objectnum].P[1] = P[1];
	objectList[objectnum].P[2] = P[2];
	objectList[objectnum].P[3] = P[3];
	objectList[objectnum].completion();
	objectList[objectnum].color = c;
	objectList[objectnum].material( Refl ,  Diff , Spec );
	objectnum++;

	objectList[objectnum].type="polygon";
	objectList[objectnum].ver = 4;
	objectList[objectnum].P[0] = P[3];
	objectList[objectnum].P[1] = P[2];
	objectList[objectnum].P[2] = P[5];
	objectList[objectnum].P[3] = P[4];
	objectList[objectnum].completion();
	objectList[objectnum].color = c;
	objectList[objectnum].material( Refl , Diff , Spec );
	objectnum++;

	objectList[objectnum].type="polygon";
	objectList[objectnum].ver = 4;
	objectList[objectnum].P[0] = P[4];
	objectList[objectnum].P[1] = P[5];
	objectList[objectnum].P[2] = P[6];
	objectList[objectnum].P[3] = P[7];
	objectList[objectnum].completion();
	objectList[objectnum].N.inversion();
	objectList[objectnum].color = c;
	objectList[objectnum].material( Refl ,  Diff , Spec );
	objectnum++;

	objectList[objectnum].type="polygon";
	objectList[objectnum].ver = 4;
	objectList[objectnum].P[0] = P[7];
	objectList[objectnum].P[1] = P[6];
	objectList[objectnum].P[2] = P[1];
	objectList[objectnum].P[3] = P[0];
	objectList[objectnum].completion();
	objectList[objectnum].color = c;
	objectList[objectnum].material( Refl , Diff , Spec );
	objectnum++;

	objectList[objectnum].type="polygon";
	objectList[objectnum].ver = 4;
	objectList[objectnum].P[0] = P[0];
	objectList[objectnum].P[1] = P[3];
	objectList[objectnum].P[2] = P[4];
	objectList[objectnum].P[3] = P[7];
	objectList[objectnum].completion();
	objectList[objectnum].color = c;
	objectList[objectnum].material( Refl , Diff , Spec );
	objectnum++;

	objectList[objectnum].type="polygon";
	objectList[objectnum].ver = 4;
	objectList[objectnum].P[0] = P[1];
	objectList[objectnum].P[1] = P[6];
	objectList[objectnum].P[2] = P[5];
	objectList[objectnum].P[3] = P[2];
	objectList[objectnum].completion();
	objectList[objectnum].color = c;
	objectList[objectnum].material( Refl ,  Diff , Spec );
	objectnum++;
}


void scene::addcylinder(vec C,vec N,double r,double h,double Refl , double Diff , double Spec,color_s c){
	N.normalize();

	objectList[objectnum].type="cylinder";
	objectList[objectnum].radius=r;
	objectList[objectnum].O=C;
	objectList[objectnum].N=N;
	objectList[objectnum].h=h;
	objectList[objectnum].color=c;
	objectList[objectnum].material( Refl,  Diff , Spec);
	objectnum++;

	objectList[objectnum].type="circle";
	objectList[objectnum].radius=r;
	objectList[objectnum].O=C;
	objectList[objectnum].N=N.inversion();
	objectList[objectnum].color=c;
	objectList[objectnum].material( Refl,  Diff , Spec);
	objectnum++;

	objectList[objectnum].type="circle";
	objectList[objectnum].radius=r;
	objectList[objectnum].O=C+N*h;
	objectList[objectnum].N=N;
	objectList[objectnum].color=c;
	objectList[objectnum].material( Refl,  Diff , Spec);
	objectnum++;
}