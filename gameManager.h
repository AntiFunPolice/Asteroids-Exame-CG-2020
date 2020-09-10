#include "player.h"
#include "asteroids.h"
#include "beams.h"

#include <time.h>

class GameManager
{
public:
    Obj *skybox;
    Nave *nave;
    Asteroid *asteroids[30];
    Beam *beams[10000];

    int asteroids_number=0, beam_number=0, lives=3, points=0, lvl = 1;
    bool colliding=false,shoting= false,game_Start;
    int colliding_with=-1;

    
 

    GameManager(){
        skybox = new Obj("espacob");
        create_asteroids();
        create_nave();
    }

    ~GameManager(){
        
        delete skybox;
    }

    create_nave(){
        nave = new Nave();
    }


    create_beam(){
        float dir = nave->rot;
        if(shoting){
           
                beams[beam_number] = new Beam();   
                beams[beam_number] -> direction = dir; 
                beams[beam_number] -> posx      = nave->xx;
                beams[beam_number] -> posz      = nave->zz;
                beam_number++;
                
                shoting=false;
        }  
    }

    create_asteroids(){
        //srand(time(NULL));
        for(int i = 0; i< (lvl * 4);i++){

            srand(time(NULL)*(i +2));
            asteroids[i] = new Asteroid();
            asteroids[i]->posx      = 15 * (rand()%2 ==1 ? 1 : -1);
            asteroids[i]->posz      = 15 * (rand()%2 ==1 ? 1 : -1);
            asteroids[i]->speedx    = ((rand()%10 +1))*(rand()%2 ==1 ? 1 : -1);
            asteroids[i]->speedz    = ((rand()%10 +1))*(rand()%2 ==1 ? 1 : -1);
            asteroids_number++; 
        }
    }

void player_asteroid_colision_detection(){
  
    float player_min[2],player_max[2];
    float object_min[2],object_max[2];
    float coliding_number;
    int living_asteroids;

    player_min[0]= nave->obj->get_min_x() + nave->xx;
    player_min[1]= nave->obj->get_min_y() + nave->zz;
    player_max[0]= nave->obj->get_max_x() + nave->xx;
    player_max[1]= nave->obj->get_max_y() + nave->zz;
   

    for (int i = 0; i < asteroids_number; ++i){
      
        if(!asteroids[i]->dead){

            object_min[0] = asteroids[i]->obj->get_min_x() +asteroids[i]->posx;
            object_min[1] = asteroids[i]->obj->get_min_y() +asteroids[i]->posz;
            object_max[0] = asteroids[i]->obj->get_max_x() +asteroids[i]->posx;
            object_max[1] = asteroids[i]->obj->get_max_y() +asteroids[i]->posz;
            
            
            if((player_min[0] <= object_max[0] && player_max[0] >= object_min[0]) && 
               (player_min[1] <= object_max[1] && player_max[1] >= object_min[1])){
                //retirar vida
                  colliding=true;
                  lives--;
                  asteroids[i]->dead=true;
                  colliding_with=i;
            }
        }
    }
    colliding =false;
}

void generate_lvls(){
    if(points==40 && lvl==1)
        generate_lvl2();
    if(points== 120 && lvl==2)
        generate_infinity();
}

void generate_lvl2(){
    int oldnumber = asteroids_number;
    while(asteroids_number > oldnumber +(lvl * 4)){
        asteroids_number++;
        srand(time(NULL)*(asteroids_number-oldnumber));
        asteroids[asteroids_number] = new Asteroid();
        asteroids[asteroids_number]->posx      = rand()%10 * (rand()%2 ==1 ? 1 : -1);
        asteroids[asteroids_number]->posz      = rand()%10 * (rand()%2 ==1 ? 1 : -1);
        asteroids[asteroids_number]->speedx    = ((rand()%10 +1))*(rand()%2 ==1 ? 1 : -1);
        asteroids[asteroids_number]->speedz    = ((rand()%10 +1))*(rand()%2 ==1 ? 1 : -1);
         
    }
}

void generate_infinity(){}

void beam_asteroid_colision_detection(){
  
    float beam_min[2],beam_max[2];
    float object_min[2],object_max[2];
    float coliding_number;

    for (int j = 0; j < beam_number; ++j){
        beam_min[0] = beams[j]->obj->get_min_x() +beams[j]->posx;
        beam_min[1] = beams[j]->obj->get_min_y() +beams[j]->posz;
        beam_max[0] = beams[j]->obj->get_max_x() +beams[j]->posx;
        beam_max[1] = beams[j]->obj->get_max_y() +beams[j]->posz;
    
   
        if(!beams[j]->out){
            for (int i = 0; i < asteroids_number; ++i){
                if(!asteroids[i]->dead){
                    object_min[0] = asteroids[i]->obj->get_min_x() +asteroids[i]->posx;
                    object_min[1] = asteroids[i]->obj->get_min_y() +asteroids[i]->posz;
                    object_max[0] = asteroids[i]->obj->get_max_x() +asteroids[i]->posx;
                    object_max[1] = asteroids[i]->obj->get_max_y() +asteroids[i]->posz;
                     
                    
                    if((beam_min[0] <= object_max[0] && beam_max[0] >= object_min[0]) && 
                       (beam_min[1] <= object_max[1] && beam_max[1] >= object_min[1])){
                        //retirar vida
                          colliding=true;
                          asteroids[i]->dead=true;
                          beams[j]->out = true;
                          points+=10;
                    }
                }      
            }
        }
    }
    colliding =false;

}

    void display(){
        
        //float minx=nave->obj->get_min_x();
        //float miny=nave->obj->get_min_y();
        //float minz=nave->obj->get_min_z();
        //float maxx=nave->obj->get_max_x();
        //float maxy=nave->obj->get_max_y();
        //float maxz=nave->obj->get_max_z();
        
        create_beam();
        nave->display();
        
        glDisable(GL_LIGHTING);
        glPushMatrix(); 
        glRotatef(180,0,0,1);
        skybox->display();
        glPopMatrix();
        glEnable(GL_LIGHTING);
        


        
        generate_lvls();
        if(game_Start)
            player_asteroid_colision_detection();
        if(beam_number>0)
            beam_asteroid_colision_detection();

        for (int i = 0; i < asteroids_number; i++){
            if(!asteroids[i]->dead)
                asteroids[i]->display();

        }

        for (int i = 0; i < beam_number; i++){
            if(!beams[i]->out)
                beams[i]->display();
            
        }

       //printf("nave:  min_x: %f min_y: %f min_z: %f max_x: %f max_y: %f max_z: %f\n",minx,miny,minz,maxx,maxy,maxz);
       

 
    }
};