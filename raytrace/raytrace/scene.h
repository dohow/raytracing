#include "object.h"
static vec ori( 0 , -2 , 0 ) , x_axis , y_axis( 0.4 , 1 , -0.5 ) , z_axis;
static double wid_x = 0.5 , wid_z = 0.5;
class scene
{
public:
	int objectnum;
	object objectList[10];
	void build_scene();
	void init(){objectnum=0;}
	int intersectNear(vec dir, vec origin, int &objID,vec &nP,vec &nN);
	int intersect(vec origin , vec dir , int i , vec &nP , vec &nN );
	void addcuboid(vec P[],double Refl , double Diff , double Spec,color_s c);
	void addcylinder(vec C,vec N,double r,double h,double Refl , double Diff , double Spec,color_s c);
protected:
private:
};



vec direction( double x , double z );