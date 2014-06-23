#include "stdio.h"
#include "image.h"
#include "ray_trace.h"
extern scene myscene;
void main(){
	myscene.init();
	myscene.build_scene();
	image_input("input.bmp");
	for (int i=0;i<H;i++)
		for (int j=0;j<W;j++){
			printf("i:%d,j:%d\n",i,j);


			double I=i,J=j;
			vec ori( 0 , -1 , 0 ); //�й�Ԫ����λ��
			vec arc; //����������Ļ�Ľ���
			arc.x = ( ( double ) I * 2 / (double)H - 1 ); //widΪ��Ļ��ȵ�һ��
			arc.y = 0;
			arc.z = ( ( double ) J * 2 / (double)W - 1 );
			vec dir = arc - ori;
			color_s tmp = raytrace( ori , dir ,1);
			tmp.limit();
			ima[i][j].red = ( int ) ( tmp.r * 255 );
			ima[i][j].green = ( int ) ( tmp.g * 255 );
			ima[i][j].blue = ( int ) ( tmp.b * 255 );
		}
	image_output("output.bmp");
}