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
    float increment_rot=1;
    
   
    //float asteroids_children[][];
   // bool game_start = false;
 

    Asteroid(){
        get_Increments();
        
        if(type=1){ 
            obj = new Obj("asteroid");
           
            //posx  = rand()%10 * (rand()%2 ==1 ? 1 : -1);
            //posz  = rand()%10 * (rand()%2 ==1 ? 1 : -1);
            
              
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
                     
        
    
        dir_x += cos(direction*PI /180)/100;
        dir_z += sin(direction*PI /180)/100;
    }
    
    void check_Limits(){
        if(abs(posx) > 20||abs(posz) > 20){
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

        glPushMatrix();
        glTranslatef(posx,posy,posz);
        glRotatef(increment_rot,rotx,roty,rotz);
        obj->display();
        glPopMatrix();
        //adicionar incrementos

        increment_rot+=1;
        posx+=dir_x;
        posz+=dir_z;

    
    }
};