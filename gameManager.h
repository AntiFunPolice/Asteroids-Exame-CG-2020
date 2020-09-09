#include "player.h"
#include "asteroids.h"
#include <time.h>

class GameManager
{
public:
    Obj *skybox;
    int points;
    Obj *obj;
    int lvl = 1;
    Asteroid *asteroids[30];
    int asteroids_number=0;

    
 

    GameManager(){
        obj = new Obj("espaco");
        //skybox = new Obj("espaco");
        create_asteroids();
    }

    ~GameManager(){
        
        delete obj;
    }


    checklvl(){

    }

    create_asteroids(){
        //srand(time(NULL));
        for(int i = 0; i< (lvl * 4);i++){
            srand(time(NULL)*(i +2) * time(NULL));
            asteroids[i] = new Asteroid();
            asteroids[i]->posx      = rand()%10 * (rand()%1 ==1 ? 1 : -1);
            asteroids[i]->posz      = rand()%10 * (rand()%1 ==1 ? 1 : -1);
           srand(-time(NULL));
            asteroids[i]->direction = -180   ;
            asteroids_number++;

        }
    }
   

    void display(){
        glDisable(GL_LIGHTING);
        obj->display();
        glEnable(GL_LIGHTING);
        for (int i = 0; i < asteroids_number; i++)
        {
            asteroids[i]->display();
        }


 
    }
};