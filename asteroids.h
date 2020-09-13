
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
    

    Asteroid(){
        obj = new Obj("asteroid");       
    }


    Asteroid(int x){
         get_Increments();
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
    
    void check_Limits(int x){
        if(abs(posx) > 16-x||abs(posz) > 16-x){
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

    void pre_display(){
        check_Limits(0);
       
    }

   

    void asteroid_add_mov(int x){
        increment_rot+=1;
        posx+=(speedx/(600 + x));
        posz+=(speedz/(600 + x));
    }

    
   

};