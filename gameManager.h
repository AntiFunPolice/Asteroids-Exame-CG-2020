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
    bool action = false;
    

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
        nave_min_y = nave->obj->get_min_z();
        
        nave_max_x = nave->obj->get_max_x();
        nave_max_y = nave->obj->get_max_z();
       

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
        asteroids[asteroids_number]->posx      = (oneor2==1 ? (rand()%(15-13)+13) * (rand()%2 ==1 ? 1 : -1) : rand()%15 * (rand()%2 ==1 ? 1 : -1) );
        asteroids[asteroids_number]->posz      = (oneor2==0 ? (rand()%(15-13)+13) * (rand()%2 ==1 ? 1 : -1) : rand()%15 * (rand()%2 ==1 ? 1 : -1) );
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
            beam_min[1] = beam->get_min_z() +beams[j]->posz;
            beam_max[0] = beam->get_max_x() +beams[j]->posx;
            beam_max[1] = beam->get_max_z() +beams[j]->posz;
        
       
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
    
    
        //printf("Numero Asteroides %d  Numero Asteroides Vivos %d killed %d\n", asteroids_number,living_asteroids,killed);
    
        if(!game_Ends){
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

            if (!game_Start)
        {
            glDisable(GL_LIGHTING);
            glDisable(GL_DEPTH_TEST);
            glDisable(GL_TEXTURE_2D);
            glMatrixMode(GL_PROJECTION);
            glPushMatrix();
            glLoadIdentity();
            gluOrtho2D(0, 1000, 0, 1000);
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadIdentity();
            glBegin(GL_QUADS);
            glColor4f(0.1, 0.1, 0.1, 0.9);
            glVertex2i(100, 360);
            glVertex2i(100, 600);
            glVertex2i(900, 600);
            glVertex2i(900, 360);
            glEnd();
            glColor3f(1.0, 0.0, 0.0);
            string text = "Welcome to Asteroides!";
            void *font = GLUT_BITMAP_HELVETICA_12;

            glColor3f(0.0, 1.0, 1.0);
            glRasterPos2i(420, 560);
            for (string::iterator i = text.begin(); i != text.end(); ++i){
                char c = *i;
                glutBitmapCharacter(font, c);
            }
            glColor3f(1.0, 1.0, 1.0);
            glRasterPos2i(360, 520);
            text = "You can turn your ship with the A and D keys!";
            for (string::iterator i = text.begin(); i != text.end(); ++i){
                char c = *i;
                glutBitmapCharacter(font, c);
            }

             glRasterPos2i(270, 500);
            text = "You can move the ship using the trust in the direction it faces with the W key !";
            for (string::iterator i = text.begin(); i != text.end(); ++i){
                char c = *i;
                glutBitmapCharacter(font, c);
            }

             glRasterPos2i(370, 480);
            text = "You can shoot a special beam with SPACE!";
            for (string::iterator i = text.begin(); i != text.end(); ++i){
                char c = *i;
                glutBitmapCharacter(font, c);
            }


            glRasterPos2i(350, 460);
            text = "You can change the camera to 6 views press F1-F6!";
            for (string::iterator i = text.begin(); i != text.end(); ++i){
                char c = *i;
                glutBitmapCharacter(font, c);
            }


            glRasterPos2i(320, 440);
            text = "You can use add zoom to the camera using + - keys in numpad!";
            for (string::iterator i = text.begin(); i != text.end(); ++i){
                char c = *i;
                glutBitmapCharacter(font, c);
            }

            glColor3f(1.0, 0.0, 0.0);
            text = "WATCH OUT THE TRUST AND BEAM FUNCIONS NEED TO COOLDOWN BEFORE USING THEM AGAIN!";
            glRasterPos2i(200, 400);
            for (string::iterator i = text.begin(); i != text.end(); ++i){
                char c = *i;
                glutBitmapCharacter(font, c);
            }

            glColor3f(0.0, 1.0, 0.0);
            text = "Press A or D to play!";
            glRasterPos2i(430, 380);
            for (string::iterator i = text.begin(); i != text.end(); ++i){
                char c = *i;
                glutBitmapCharacter(font, c);
            }

            glMatrixMode(GL_PROJECTION);
            glPopMatrix();
            glMatrixMode(GL_MODELVIEW);
            glPopMatrix();
            glEnable(GL_TEXTURE_2D);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_LIGHTING);

            if(action){
                //reset
                asteroids_number=0;
                lvl=1;
                lives=3;
                points=0;
                create_asteroids();
                game_Ends=false;
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
                        asteroids[i]->asteroid_add_mov(0);



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
        if (game_Ends)
        {
            glDisable(GL_LIGHTING);
            glDisable(GL_DEPTH_TEST);
            glDisable(GL_TEXTURE_2D);
            glMatrixMode(GL_PROJECTION);
            glPushMatrix();
            glLoadIdentity();
            gluOrtho2D(0, 1000, 0, 1000);
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadIdentity();
            glBegin(GL_QUADS);
            glColor4f(0.1, 0.1, 0.1, 0.9);
            glVertex2i(300, 400);
            glVertex2i(300, 600);
            glVertex2i(700, 600);
            glVertex2i(700, 400);
            glEnd();
            glColor3f(1.0, 0.0, 0.0);
            string text = "Nice Try!";
            void *font = GLUT_BITMAP_HELVETICA_18;

            glColor3f(1.0, 0.0, 0.0);
            glRasterPos2i(450, 540);
            for (string::iterator i = text.begin(); i != text.end(); ++i){
                char c = *i;
                glutBitmapCharacter(font, c);
            }

            glRasterPos2i(393, 500);
            text = "You scored: "+ to_string(points)+" Points!";
            for (string::iterator i = text.begin(); i != text.end(); ++i){
                char c = *i;
                glutBitmapCharacter(font, c);
            }


            text = "Press P to play again!";
            glRasterPos2i(410, 460);
            for (string::iterator i = text.begin(); i != text.end(); ++i){
                char c = *i;
                glutBitmapCharacter(font, c);
            }

            glMatrixMode(GL_PROJECTION);
            glPopMatrix();
            glMatrixMode(GL_MODELVIEW);
            glPopMatrix();
            glEnable(GL_TEXTURE_2D);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_LIGHTING);

            if(action){
                //reset
                asteroids_number=0;
                lvl=1;
                lives=3;
                points=0;
                create_asteroids();
                game_Ends=false;
            }
        }
    }

};