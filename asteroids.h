#include <time.h>
#define PI 3.14159265
class Asteroid
{
public:
    
    Obj *obj;
    int type = 1;
    float posx,posy=0,posz;
    float dir_x = 0,dir_y = 0,dir_z = 0;
    float rotx=0,roty=0,rotz=0;
    float direction;
    float speedx=0,speedz=0;
    float increment_rot=1;
    float dead=false;
    
   
    //float asteroids_children[][];
   // bool game_start = false;
 

    Asteroid(){
        
        
        if(type=1){ 
            obj = new Obj("asteroid");
            
       }else{
            obj = new Obj("asteroid_small");
           
        }
    }

    ~Asteroid(){

        delete obj;
    }


    void get_Increments(){
        

        int pick = (rand()%3)+1;
        if(pick==1){
            rotx=1;
        }else if(pick==2){
            roty=1;
        }else
            rotz=1;

    }
    
    void check_Limits(){
        if(abs(posx) > 16||abs(posz) > 16){
            posx*=-1;
            posz*=-1;
    
            if(posx>0)
                posx-=0.5;
    
            else
                posx+=0.5;
            
            if(posz>0)
                posz-=0.5;
            else
                posz+=0.5;
            
    
        }
    }
   

    void display(){
       check_Limits();
        get_Increments();
        glPushMatrix();
        glTranslatef(posx,posy,posz);
        glRotatef(increment_rot,rotx,roty,rotz);
        obj->display();
        glPopMatrix();
        //adicionar incrementos
         
        increment_rot+=1;
        posx+=(speedx/600);
        posz+=(speedz/600);

    
    }
};