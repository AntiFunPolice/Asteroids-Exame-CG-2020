
class Asteroid
{
public:
    
    Obj *obj;
    int type = 1;
    float posx,posy=0,posz;
    float rotx,roty,rotz;
    float direction;

   
    //float asteroids_children[][];
   // bool game_start = false;
 

    Asteroid(){
        if(type=1) 
            obj = new Obj("asteroid");
       else
        obj = new Obj("asteroid_small");
    }

    ~Asteroid(){

        delete obj;
    }

   

    void display(){
        glPushMatrix();
        glTranslatef(posx,posy,posz);
        glRotatef(5,rotx,roty,rotz);
        obj->display();
        glPopMatrix();
        //adicionar incrementos
        
    }
};