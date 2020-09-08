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

       // 3 levels  up to 20 translactions for the box
    //float asteroids_children[][];
    //bool game_start = false;
 

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
        srand(time(NULL));
        for(int i = 0; i< (lvl * 4);i++){
            asteroids[i] = new Asteroid();
            asteroids[i]->posx      = rand()%10 * (rand()%2 ==1 ? 1 : -1);
            asteroids[i]->posz      = rand()%10 * (rand()%2 ==1 ? 1 : -1);
            asteroids[i]->rotx      = rand()%1 *  (rand()%2 ==1 ? 1 : -1);
            asteroids[i]->roty      = rand()%1 *  (rand()%2 ==1 ? 1 : -1);
            asteroids[i]->rotz      = rand()%1 *  (rand()%2 ==1 ? 1 : -1);
            asteroids[i]->direction = rand()%360;
            asteroids_number++;

        }
    }
   

    void display(){
        glDisable(GL_LIGHTING);
        obj->display();
        glEnable(GL_LIGHTING);
        for (int i = 0; i < asteroids_number; ++i)
        {
            asteroids[i]->display();
        }


 
    }
};