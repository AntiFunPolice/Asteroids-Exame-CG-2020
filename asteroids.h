
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
        if(type=1){ 
            obj = new Obj("asteroid");
            posx      = rand()%10 * (rand()%2 ==1 ? 1 : -1);
            posz      = rand()%10 * (rand()%2 ==1 ? 1 : -1);
            rotx      = rand()%1 *  (rand()%2 ==1 ? 1 : -1);
            roty      = rand()%1 *  (rand()%2 ==1 ? 1 : -1);
            rotz      = rand()%1 *  (rand()%2 ==1 ? 1 : -1);
            direction = rand()%360;     
       }else{
            obj = new Obj("asteroid_small");
            posx      = rand()%10 * (rand()%2 ==1 ? 1 : -1);
            posz      = rand()%10 * (rand()%2 ==1 ? 1 : -1);
            rotx      = rand()%1 *  (rand()%2 ==1 ? 1 : -1);
            roty      = rand()%1 *  (rand()%2 ==1 ? 1 : -1);
            rotz      = rand()%1 *  (rand()%2 ==1 ? 1 : -1);
            direction = rand()%360;  
        }
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