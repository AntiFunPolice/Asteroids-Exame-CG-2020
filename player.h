#include "model.h"

class Nave
{
public:
    Obj *obj;
    float xx = 0 ,yy = 0, zz = 0;
     float min_x,min_y,max_x,max_y,min_z,max_z;
    int dir = 1;
    float rot = 0;
    float speedx=0,posy=0,speedz=0;
    float x_Camera3d,z_Camera3d;
    
   

    Nave()
    {
        obj = new Obj("nave_smaller_2");
    }



     float get_min_x(){
        return min_x;
    }
    float get_min_y(){
        return min_y;
    }

    float get_max_x(){
        return max_x;
    }

    float get_max_y(){
        return max_y;
    }



   
	void check_Limits(){
		if(abs(xx) > 16||abs(zz) > 16){
			xx*=-1;
			zz*=-1;
	
			if(xx>0)
				xx-=0.5;
	
			else
				xx+=0.5;
			
			if(zz>0)
				zz-=0.5;
			else
				zz+=0.5;
			
	
		}
	}

    void display()
    {
    	check_Limits();    
        glPushMatrix();
        glTranslatef(xx,yy,zz);
        glRotatef(180+rot,0,-1,0);
        obj->display();
        glPopMatrix();
    }
};