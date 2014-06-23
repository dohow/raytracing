#include "ray_trace.h"
#define MAXDEPTH 6
scene myscene;

color_s raytrace(vec origin, vec dir,int traceDepth){
	color_s res=color_s(0,0,0);
	if (traceDepth>MAXDEPTH)
		return res;
	vec interP,interN;
	int interObjID=-1;
	int hit=myscene.intersectNear(dir,origin,interObjID,interP,interN);
	interN.normalize();
	dir.normalize();
	if(hit!=0){

		if (myscene.objectList[interObjID].islight){
			res=color_s(1,1,1);
		} 
		else{
			for (int i=0;i<myscene.objectnum;i++){
				if (myscene.objectList[i].islight){

					//cal shade
					double shade=1;
					if (myscene.objectList[i].type=="sphere"){
						for (int j=0;j<myscene.objectnum;j++){
							int id;
							vec tmpN,tmpP;
							if (!myscene.objectList[j].islight && myscene.intersect(myscene.objectList[i].O,interP-myscene.objectList[i].O,j,tmpP,tmpN)){
								if (interObjID!=j && (interP-myscene.objectList[i].O).module()-(myscene.objectList[i].O-tmpP).module()>0.0001){
									shade=0;
									break;
								}
							}
						}
					}

					//diffuse
					vec L=myscene.objectList[i].O-interP;
					L.normalize();
					interN.normalize();
					if (myscene.objectList[interObjID].diffuse>0){
						double dot=L*interN;
						if (dot>0){
							double diffuse=dot*myscene.objectList[interObjID].diffuse*shade;
							res=res+myscene.objectList[i].color*myscene.objectList[interObjID].color*diffuse;
						}
					}


					//specular
					interN.normalize();
					dir.normalize();
					vec R=L-interN*(interN*L*2.0);
					R.normalize();
					double dot=dir*R;
					if (dot > 0)
					{
						double specular=pow( dot , 50 ) * myscene.objectList[interObjID].specular * shade;
						res=res+myscene.objectList[interObjID].color*specular;
					}
				}

			}

			//reflect
			
			double reflect=myscene.objectList[interObjID].reflect;
			if (reflect>0){
				vec R=dir-interN*(interN*dir*2);
				R.normalize();
				interP.normalize();
				color_s refl_res=raytrace(interP,R,traceDepth+1);
				res=res+refl_res*reflect*myscene.objectList[interObjID].color;
			}
		}
	}
	return res;
}