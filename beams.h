#include <time.h>
#define PI 3.14159265
class Beam
{
public:
    
    Obj *obj;
    int type = 1;
    float posx=0,posy=0,posz=0;
    float dir_x = 0,dir_y = 0,dir_z = 0;
    float direction;
    bool out=false;
   
    //float Beamss_children[][];
   // bool game_start = false;
 

    Beam(){
        get_Increments();
        obj = new Obj("beams");

           
    }

    ~Beam(){

        delete obj;
    }


    void get_Increments(){
      
        float div = direction/360;
        float rem = (direction - ((floor(direction/360))*360)-90);
 
        
        dir_x = cos(rem*PI /180)/30;
        dir_z = sin(rem*PI /180)/30;

    }
    
    void check_Limits(){
        if(abs(posx) > 16||abs(posz) > 16){
             
            out=true;
        }
    }
   

    void display(){
        check_Limits();
        get_Increments();
        glPushMatrix();
        glTranslatef(posx,posy,posz);
        glRotatef(180+direction,0,-1,0);
        obj->display();
        glPopMatrix();
        //printf("%f\n",direction );
    
        posx+=(dir_x*5);
        posz+=(dir_z*5);

    
    }
};