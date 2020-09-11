#include "player.h"
#include "asteroids.h"
#include "beams.h"
#include "particles.h"
#include <time.h>

class GameManager
{
public:
    Obj *skybox;
    Nave *nave;
    Obj *explosao;
    Obj *beam;

    Asteroid *asteroid;
    Asteroid *asteroids[3000];
    Beam *beams[10000];
    Particles *particle[3000];


    float asteroid_min_x,asteroid_min_y,asteroid_min_z,asteroid_max_x,asteroid_max_y,asteroid_max_z;
    float nave_min_x, nave_min_y, nave_max_x, nave_max_y;
    int asteroids_number=0, beam_number=0, lives=3, points=0, lvl = 1,living_asteroids=7,explosion_number=0;
    bool colliding=false,shoting= false,game_Start;
    bool game_Ends=false;
    bool infinity=false;
    int killed =0;
    bool deleted= false;
    

    float player_min[2],player_max[2];
    float object_min[2],object_max[2];

    float beam_min[2],beam_max[2];
    float b_object_min[2],b_object_max[2];
 

    GameManager(){
        explosao = new Obj("explosion");
        skybox = new Obj("espacob");
        beam = new Obj("beams");
        create_asteroids();
        create_nave();
        create_asteroid_model();

    }

    ~GameManager(){
        
        delete skybox;
    }

    create_asteroid_model(){
        asteroid = new Asteroid(); 
        asteroid_min_x = asteroid->obj->get_min_x();
        asteroid_min_y = asteroid->obj->get_min_y();
      
        asteroid_max_x = asteroid->obj->get_max_x();
        asteroid_max_y = asteroid->obj->get_max_y();
        
    }

    create_nave(){
        nave = new Nave();
        nave_min_x = nave->obj->get_min_x();
        nave_min_y = nave->obj->get_min_y();
        
        nave_max_x = nave->obj->get_max_x();
        nave_max_y = nave->obj->get_max_y();
       

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
        for(int i = 0; i< (lvl * 7);i++){

            srand(time(NULL)*(i +2));
            asteroids[i] = new Asteroid(0);
             int oneor2 = rand()%2 +1;
            asteroids[i]->posx      = (oneor2==0 ? (rand()%(15-13)+13) * (rand()%2 ==1 ? 1 : -1) : rand()%15 * (rand()%2 ==1 ? 1 : -1) );
            asteroids[i]->posz      = (oneor2==1 ? (rand()%(15-13)+13) * (rand()%2 ==1 ? 1 : -1) : rand()%15 * (rand()%2 ==1 ? 1 : -1) );
            asteroids[i]->speedx    = ((rand()%10 +1))*(rand()%2 ==1 ? 1 : -1);
            asteroids[i]->speedz    = ((rand()%10 +1))*(rand()%2 ==1 ? 1 : -1);
            asteroids_number++;


        }
    }
    
    void remove_beams(){
        for (int j = 0; j < beam_number; ++j)
        {
            if(beams[j]->out){
        
                for (int i = j; i < beam_number-1; ++i){
                    beams[i]=beams[i+1];
                }
                beam_number-=1;
            }
         }
    }


    void remove_particles(){
        for (int j = 0; j < explosion_number; ++j){
            /* code */
            if(!particle[j]->in){
                  for (int i = j; i < explosion_number-1; ++i){
                     particle[i]=particle[i+1];
                 }
                 explosion_number-=1;
            }
        }

    }

    
    void remove_asteroids(){
        
        for (int j = 0; j < asteroids_number; ++j){
            /* code */
            if(asteroids[j]->dead){
                  for (int i = j; i < asteroids_number-1; ++i){
                     asteroids[i]=asteroids[i+1];
                 }
                 asteroids_number-=1;
            }
        }
    }


    void generate_one(){
        srand(time(NULL));

        asteroids[asteroids_number] = new Asteroid(0);
        int oneor2 = rand()%2 +1;
        asteroids[asteroids_number]->posx      = (oneor2==0 ? (rand()%(15-13)+13) * (rand()%2 ==1 ? 1 : -1) : rand()%15 * (rand()%2 ==1 ? 1 : -1) );
        asteroids[asteroids_number]->posz      = (oneor2==1 ? (rand()%(15-13)+13) * (rand()%2 ==1 ? 1 : -1) : rand()%15 * (rand()%2 ==1 ? 1 : -1) );
        asteroids[asteroids_number]->speedx    = ((rand()%10 +1))*(rand()%2 ==1 ? 1 : -1);
        asteroids[asteroids_number]->speedz    = ((rand()%10 +1))*(rand()%2 ==1 ? 1 : -1);
    
        asteroids_number++;
    }


    void generate_2one(){
        srand(time(NULL));

        asteroids[asteroids_number] = new Asteroid(0);
        int oneor2 = rand()%2 +1;
        asteroids[asteroids_number]->posx      = (oneor2==0 ? (rand()%(15-13)+13) * (rand()%2 ==1 ? 1 : -1) : rand()%15 * (rand()%2 ==1 ? 1 : -1) );
        asteroids[asteroids_number]->posz      = (oneor2==1 ? (rand()%(15-13)+13) * (rand()%2 ==1 ? 1 : -1) : rand()%15 * (rand()%2 ==1 ? 1 : -1) );
        asteroids[asteroids_number]->speedx    = ((rand()%10 +1))*(rand()%2 ==1 ? 1 : -1);
        asteroids[asteroids_number]->speedz    = ((rand()%10 +1))*(rand()%2 ==1 ? 1 : -1);
    
        asteroids_number++;

        asteroids[asteroids_number] = new Asteroid(0);
        asteroids[asteroids_number]->posx      = (oneor2==0 ? (rand()%(15-13)+13) * (rand()%2 ==1 ? 1 : -1) : rand()%15 * (rand()%2 ==1 ? 1 : -1) );
        asteroids[asteroids_number]->posz      = (oneor2==1 ? (rand()%(15-13)+13) * (rand()%2 ==1 ? 1 : -1) : rand()%15 * (rand()%2 ==1 ? 1 : -1) );
        asteroids[asteroids_number]->speedx    = ((rand()%10 +1))*(rand()%2 ==1 ? 1 : -1);
        asteroids[asteroids_number]->speedz    = ((rand()%10 +1))*(rand()%2 ==1 ? 1 : -1);
    
        asteroids_number++;
    }
    
    void player_asteroid_colision_detection(){
      
       
        float coliding_number;
        int living_asteroids_counter=0;
    
        player_min[0]= nave_min_x + nave->xx;
        player_min[1]= nave_min_y + nave->zz;
        player_max[0]= nave_max_x + nave->xx;
        player_max[1]= nave_max_y + nave->zz;
       
    
        for (int i = 0; i < asteroids_number; ++i){
          
            if(!asteroids[i]->dead){
                living_asteroids_counter++;
                object_min[0] = asteroid_min_x +asteroids[i]->posx;
                object_min[1] = asteroid_min_y +asteroids[i]->posz;
                object_max[0] = asteroid_max_x +asteroids[i]->posx;
                object_max[1] = asteroid_max_y +asteroids[i]->posz;
                
                
                if((player_min[0] <= object_max[0] && player_max[0] >= object_min[0]) && 
                   (player_min[1] <= object_max[1] && player_max[1] >= object_min[1])){
                    //retirar vida
                     
                      lives--;
                      asteroids[i]->dead=true;
                      explosion(i);
                      generate_one();
                      deleted =true;
           
                 
    
                }
            }
        }
        
        living_asteroids = living_asteroids_counter;
        colliding =false;
    }
    
    void generate_lvls(){
        
        if(living_asteroids == 0 && lvl==1){
               infinity =true;
                generate_lvl2();
               
           
        }
        if( lvl == 2 && living_asteroids == 0){
            
            generate_lvl2();
            infinity =true;
            lvl=3;
        }
    }
    
    void generate_lvl2(){
        
        int lvls=2;
        asteroids_number=0;
        while(asteroids_number <  (lvls * 7)){
            
            srand(time(NULL)*(asteroids_number));
            asteroids[asteroids_number] = new Asteroid(0);
            int oneor2 = rand()%2 +1;
            asteroids[asteroids_number]->posx      = (oneor2==0 ? (rand()%(15-13)+13) * (rand()%2 ==1 ? 1 : -1) : rand()%15 * (rand()%2 ==1 ? 1 : -1) );
            asteroids[asteroids_number]->posz      = (oneor2==1 ? (rand()%(15-13)+13) * (rand()%2 ==1 ? 1 : -1) : rand()%15 * (rand()%2 ==1 ? 1 : -1) );
            asteroids[asteroids_number]->speedx    = ((rand()%10 +1))*(rand()%2 ==1 ? 1 : -1);
            asteroids[asteroids_number]->speedz    = ((rand()%10 +1))*(rand()%2 ==1 ? 1 : -1);
              asteroids_number++; 
        
        }
        
        lvl=2;
    }
   
    void generate_infinity(){
        
        generate_2one();

    }
    
    void beam_asteroid_colision_detection(){
      
    
        for (int j = 0; j < beam_number; ++j){
            beam_min[0] = beam->get_min_x() +beams[j]->posx;
            beam_min[1] = beam->get_min_y() +beams[j]->posz;
            beam_max[0] = beam->get_max_x() +beams[j]->posx;
            beam_max[1] = beam->get_max_y() +beams[j]->posz;
        
       
            if(!beams[j]->out){
                for (int i = 0; i < asteroids_number; ++i){
                    if(!asteroids[i]->dead){
                        b_object_min[0] = asteroid_min_x +asteroids[i]->posx;
                        b_object_min[1] = asteroid_min_y +asteroids[i]->posz;
                        b_object_max[0] = asteroid_max_x +asteroids[i]->posx;
                        b_object_max[1] = asteroid_max_y +asteroids[i]->posz;
                         
                        
                        if((beam_min[0] <= b_object_max[0] && beam_max[0] >= b_object_min[0]) && 
                           (beam_min[1] <= b_object_max[1] && beam_max[1] >= b_object_min[1])){
                              
                              beams[j]->out = true;
                              asteroids[i]->dead=true;
                              killed++;
                              explosion(i);
                              deleted =true;
                              points+=10;
                              
                        }
                    }      
                }
            }
        }
        colliding =false;
    }
    
    void explosion(int i){
        particle[explosion_number] = new Particles(asteroids[i]->posx ,asteroids[i]->posy,asteroids[i]->posz);
        explosion_number++;
    }
    
    
    
    
    void display(){
           
        
        for (int i = 0; i < explosion_number; ++i){
           particle[i]->display(explosao);
        }
    
    
        if(lives==0)
            game_Ends=true;
    
        create_beam();
        nave->display();
            
        glDisable(GL_LIGHTING);
        glPushMatrix(); 
        glRotatef(180,0,0,1);
        skybox->display();
        glPopMatrix();
        glEnable(GL_LIGHTING);
    
    
        printf("Numero Asteroides %d  Numero Asteroides Vivos %d killed %d\n", asteroids_number,living_asteroids,killed);
    
    
        if(!infinity)
            generate_lvls();
            
                
        if(infinity){
           
        
            if(killed>0){
                if(asteroids_number<40){
                    generate_infinity();
                }else
                    generate_one();
                killed=0;
            }
        }
    
        if(game_Start){
            player_asteroid_colision_detection();
                        
                    
            if(beam_number>0)
                beam_asteroid_colision_detection();
                        
            for (int i = 0; i < asteroids_number; i++){
                if(!asteroids[i]->dead){
                
                    asteroids[i]->pre_display();
                    glPushMatrix();
                    glTranslatef(asteroids[i]->posx,0,asteroids[i]->posz);
                    glRotatef( asteroids[i]->increment_rot,asteroids[i]->rotx,asteroids[i]->roty,asteroids[i]->rotz);
                    asteroid->obj->display();
                    glPopMatrix();
                    asteroids[i]->asteroid_add_mov();
                }
            }
                        
            for (int i = 0; i < beam_number; i++){
                if(!beams[i]->out)
                    beams[i]->display(beam);      
            }
        }
        remove_particles();
        remove_beams();
        if(deleted=true)
            remove_asteroids();       
    }

};