#include "model.h"

class Nave
{
public:
    Obj *obj;
    float xx = 0 ,yy = 0, zz = 0;
     float min_x,min_y,max_x,max_y,min_z,max_z;
    int dir = 1;
    float rot = 0 , inc = 0;
    bool walking = false;
    float speedx=0,posy=0,speedz=0;
    
   

    Nave()
    {
        obj = new Obj("nave_smaller_2");
        min_x = obj->get_min_x();
        min_y = obj->get_min_y();
        max_x = obj->get_max_x();
        max_y = obj->get_max_y();
        min_z = obj->get_min_z();
        max_z = obj->get_max_z();
    }

    ~Nave()
    {
        delete obj;
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
   

    void display()
    {
        
        glPushMatrix();
        glTranslatef(xx,yy,zz);
        glRotatef(180+rot,0,-1,0);
        //glRotatef(inc,1,0,0);
        obj->display();
        glPopMatrix();
    }
};