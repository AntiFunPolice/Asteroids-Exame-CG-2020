
#include <iostream>
#include <GL/glew.h>
#include <GL/glext.h>
#include <GL/glut.h>
#include <cstdio>
#include <GL/freeglut.h> 

#include "gameManager.h"

using namespace std;
#define PI 3.14159265

int min_width = 1000, min_height = 1000;
float zoom = 1, zoom_increment = 0.1;
Nave *nave;
Obj *objects[30];
GameManager *game;
int n_objects = 0;
int active_camera = 1;
bool game_start=true;
int colliding_with=-1;
bool _ri = false;
bool _le = false;
bool _w = false;                                                                            //  <<-global->> bool for whether the w key is down
bool _a = false;                                                                            //  <<-global->> bool for whether the a key is down
bool _s = false;                                                                            //  <<-global->> bool for whether the s key is down
bool _d = false;                                                                            //  <<-global->> bool for whether the d key is down
bool _q = false;                                                                            //  <<-global->> bool for whether the q key is down
bool _e = false;                                                                            //  <<-global->> bool for whether the e key is down
                                                                      
bool fuel = true;
int fuel_counter=0;    
bool colliding = false;
	


void create_objects()
{	


    nave = new Nave();
    game = new GameManager();
  	//objects[n_objects++] = new Obj("espaco");
    //objects[n_objects++] = new Obj("asteroid");
    //objects[n_objects++] = new Obj("beams");
    //objects[n_objects++] = new Obj("door");
    //objects[n_objects++] = new Obj("chao");
    
}
void init_lights()
{

    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);

    GLfloat light_ambient[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 0.8};
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 0.8};
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    GLfloat light_pos[] = {0.0, 1.0, 1.0, 0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    glShadeModel(GL_SMOOTH);
}

void init(){

    glClearColor(0.1, 0.1, 0.1, 0.1);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, 1, 0.5, 50);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    create_objects();
    init_lights();
    

}

void set_camera(GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ, GLdouble centerX, GLdouble centerY, GLdouble centerZ, GLdouble upX, GLdouble upY, GLdouble upZ){
    eyeX = (eyeX - centerX) / zoom + centerX;
    eyeY = (eyeY - centerY) / zoom + centerY;
    eyeZ = (eyeZ - centerZ) / zoom + centerZ;
    gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
}

void camera(){
    switch (active_camera)
    {
        case 1:
            set_camera(nave->xx , 7, nave->zz+1 , nave->xx, nave->yy, nave->zz-3, 0.0, 1, 0);
            break;
        case 2:
            set_camera(nave->xx , 2, nave->zz , nave->xx, nave->yy, nave->zz-3, 0.0, 1, 0);
            break;

        case 3:
           set_camera(nave->xx , 0.5+ nave->yy, 1+nave->zz , nave->xx, nave->yy, nave->zz-3, 0.0, 1, 0);
            break;
      
    }
}

//void camerachaser(){
    //set_camera(nave->xx , 7, nave->zz , nave->xx, nave->yy, nave->zz-3, 0.0, 1, 0);
  //  set_camera(nave->xx , 7, nave->zz+1 , nave->xx, nave->yy, nave->zz-3, 0.0, 1, 0);
//}



void collision_solver(){
    
    //bool Axis_x,Axis_y;
    float increment=0;
    //float player_min_x= nave->get_min_x();
    float player_min_y= nave->get_min_y();
    //float player_max_x= nave->get_max_x();
    float player_max_y= nave->get_max_y(); 

     
    //float object_min_x = objects[colliding_with]->get_min_x();
    float object_min_y = objects[colliding_with]->get_min_y()-1;
    //float object_max_x = objects[colliding_with]->get_max_x();
    float object_max_y = objects[colliding_with]->get_max_y()-1;

    //float object_height = abs(object_max_y) - abs(object_min_y);
    //float player_height = abs(player_max_y) - abs(player_min_y);

   // if(player_max_y>object_max_y){
        
        increment = abs(object_max_y)-abs(player_min_y);
        nave->yy   -= increment-0.01;
        nave->max_y -=increment-0.01;
        nave->min_y -=increment-0.01;
        

    //}else if(player_max_y<object_max_y){
        
       //increment =abs(player_max_y) - abs(object_min_y);
       //nave->yy+=increment;
       //nave->max_y-=increment;
       //nave->min_y-=increment;
        
    //}

    


}

void colision_detection(){
	
    float player_min[2],player_max[2];
    float object_min[2],object_max[2];
    int collidings = 0;
    player_min[0]= nave->get_min_x();
    player_min[1]= nave->get_min_y();
    player_max[0]= nave->get_max_x();
    player_max[1]= nave->get_max_y(); 

    for (int i = 0; i < n_objects; ++i){
    	object_min[0] = objects[i]->get_min_x();
    	object_min[1] = objects[i]->get_min_y();
    	object_max[0] = objects[i]->get_max_x();
    	object_max[1] = objects[i]->get_max_y();
    	
    	if((player_min[0] <= object_max[0] && player_max[0] >= object_min[0]) && 
    	   (player_min[1] <= object_max[1]-1 && player_max[1] >= object_min[1]-1)){
			collidings++;
            colliding_with=i;
		}
		
    }

    if (collidings>0){
			colliding = true;
           
            collision_solver();

	}else{
		colliding = false;
        colliding_with=-1;
    }

    

}



void move_hit_box_x(float increment_x){
	nave->min_x =nave->min_x  + increment_x;
	nave->max_x =nave->max_x  + increment_x;
}

void move_hit_box_y(float increment_y){
	nave->min_y =nave->min_y  + increment_y;
	nave->max_y =nave->max_y  + increment_y;
}

void trust(){
	nave->xx += nave->speedx;
	nave->zz += nave->speedz;
} 

void vectorget(){
	float xsda = nave->rot;
    float div  = xsda/360;
    float rem = (xsda - ((floor(div)+27)*360)-90);

    float origin_x = nave->xx;
    float origin_z = nave->zz;
    
    
    nave->speedx=0;
   	nave->speedz=0;
    

   	nave->speedx += cos(rem*PI /180)/10;
    nave->speedz += sin(rem*PI /180)/10;
}


void movement2(){

	 if(_a||_d||_w||_s||_q||_e){
      

          if(_w){
        
          	if(fuel){
            	vectorget();
            	fuel=false;
   			}
        }

        

        if(_a){
    		nave->rot -= 5;
    		
    	}

   	 	if(_d){
   	 		nave->rot += 5;
   	 			
   	 	}
    }  
}


void get_player_box_display(){
	float min_x = nave->get_min_x();
	float min_y = nave->get_min_y();
	float max_x = nave->get_max_x();
	float max_y = nave->get_max_y();

	if(colliding){
		glColor3f(1,0,0);
	}else{
		glColor3f(1,1,1);
	}

	//glBegin(GL_QUADS);
    //glVertex3f(min_x,min_y,min_z);
    //glVertex3f(max_x,min_y,);
    //glVertex3f(max_x,max_y);
    //glVertex3f(min_x,max_y);

   	

    glEnd();
}

void get_map_box_display(){
	
	for (int i = 0; i < n_objects; i++){
     	
		float min_x = objects[i]->get_min_x();
		float min_y = objects[i]->get_min_y();
		float max_x = objects[i]->get_max_x();
		float max_y = objects[i]->get_max_y();
		printf("min: %f max: %f\n",min_x,max_x);

	    //glBegin(GL_QUADS);
	    //glVertex2f(min_x,min_y);
	    //glVertex2f(max_x,min_y);
	    //glVertex2f(max_x,max_y);
	    //glVertex2f(min_x,max_y);
    	//glEnd();

   }
}

void display_text_color(string text, GLint y,bool x){	
	if(x)
		glColor3f(0.0, 1.0, 0.0);
	else	
    	glColor3f(1.0, 0.0, 0.0);
    void *font = GLUT_BITMAP_HELVETICA_18;
    glRasterPos2i(20, y);
    for (string::iterator i = text.begin(); i != text.end(); ++i)
    {
        char c = *i;
        glutBitmapCharacter(font, c);
    }
}




void display_text(string text, GLint y){	
		
    glColor3f(1.0, 1.0, 1.0);
    void *font = GLUT_BITMAP_HELVETICA_18;
    glRasterPos2i(20, y);
    for (string::iterator i = text.begin(); i != text.end(); ++i)
    {
        char c = *i;
        glutBitmapCharacter(font, c);
    }
}

void display_labels(){
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

    int label_box_height = 200, n_text = 1;

    //glColor4f(0.0, 0.0, 0.0, 0.5);
    //glBegin(GL_QUADS);
    //glVertex2i(370, 10);
    //glVertex2i(10, 8);
    //glVertex2i(10, label_box_height);
    //glVertex2i(370, label_box_height);
    //glEnd();

    //if(fuel){
    	
   // }else

    display_text("Labels (L): Showing", label_box_height - 25 * n_text++);
    display_text_color(" Thrust: " +  string(fuel ? "Ready" : "Cooldown"), label_box_height - 25 * n_text++,fuel);
    display_text("Exit program (ESC)", 20);



    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
   
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

void axis_diplay(){
	
	glDisable(GL_LIGHTING);
	glColor3f(1.0,0.0,0.0); // red x
    glBegin(GL_LINES);
    // x aix
 
    glVertex3f(-4.0, 0.0f, 0.0f);
    glVertex3f(4.0, 0.0f, 0.0f);
 
    // arrow
    glVertex3f(4.0, 0.0f, 0.0f);
    glVertex3f(3.0, 1.0f, 0.0f);
 
    glVertex3f(4.0, 0.0f, 0.0f);
    glVertex3f(3.0, -1.0f, 0.0f);
    glEnd();
    glFlush();
 
 
 
    // y 
    glColor3f(0.0,1.0,0.0); // green y
    glBegin(GL_LINES);
    glVertex3f(0.0, -4.0f, 0.0f);
    glVertex3f(0.0, 4.0f, 0.0f);
 
    // arrow
    glVertex3f(0.0, 4.0f, 0.0f);
    glVertex3f(1.0, 3.0f, 0.0f);
 
    glVertex3f(0.0, 4.0f, 0.0f);
    glVertex3f(-1.0, 3.0f, 0.0f);
    glEnd();
    glFlush();
 
    // z 
    glColor3f(0.0,0.0,1.0); // blue z
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0f ,-4.0f );
    glVertex3f(0.0, 0.0f ,4.0f );
 
    // arrow
    glVertex3f(0.0, 0.0f ,4.0f );
    glVertex3f(0.0, 1.0f ,3.0f );
 
    glVertex3f(0.0, 0.0f ,4.0f );
    glVertex3f(0.0, -1.0f ,3.0f );
    glEnd();

    glFlush();

    glEnable(GL_LIGHTING);
}

void display(){


fuel_counter++;
if(fuel_counter==100){
	fuel=true;
	fuel_counter=0;
}
// Limpa os "buffers"
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// Indica que as próximas operações de matrizes serão feitas sobre
// a matriz "ModelView"
    glMatrixMode(GL_MODELVIEW);
// Limpa a matriz "ModelView" (transforma-a na matriz identidade)
    glLoadIdentity();
// ---
// Os objetos serão desenhados e animados aqui
// ---
   
    camera();
    

    glPushMatrix();
   
    glRotatef(180,0,1,0);
    glRotatef(180,0,0,1);
	game->display(); 

    glPopMatrix();  
    
    movement2();
    
    glColor3f(1, 1, 1);
 	 //axis_diplay();
    trust();
    nave->display();

   
   //printf("%d\n", asteroides);
    
    
    //glTranslatef(-nave->xx,-nave->yy,-nave->zz);
   	//for (int i = 0; i < n_objects; i++)
   	//     objects[i]->display();
   	 
    //get_map_box_display();
    
     

    //colision_detection();

     //get_player_box_display();
     

  	display_labels();
// Troca os dois "buffers" de "display", e imprime na janela o
// atualizado. Substitui o "glFlush", quando em modo "GLUT_DOUBLE".
    glutSwapBuffers();
}

void reshape(int w, int h)
{
// Define o "Viewport" como o tamanho da janela
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}




void call_display(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000 / 120, call_display, 0);
}

//<-------------------------------------------------------------------------------------------------------------------------------------------------------------->
//<-------------------------------------------------------keyboard function: called each key press--------------------------------------------------------------->
//<-------------------------------------------------------------------------------------------------------------------------------------------------------------->

void keyboard(unsigned char key, int x, int y){
    if(key == 0x1B)(*(int*)0) = 69; //if esc is pressed crash program
    if(key == 0x1B){
        glutDestroyWindow ( glutGetWindow() );
    }
    switch(key){
        case 'w': _w = true; break;
        case 'a': _a = true; break;
        case 's': _s = true; break;
        case 'd': _d = true; break;
        case 'q': _q = true; break;
        case 'e': _e = true; break;
       

    }
}


//<-------------------------------------------------------------------------------------------------------------------------------------------------------------->
//<------------------------------------------------------keyboard function: called each key release-------------------------------------------------------------->
//<-------------------------------------------------------------------------------------------------------------------------------------------------------------->

void keyboardup(unsigned char key, int x, int y){
    switch(key){
        case 'w': _w = false; break;
        case 'a': _a = false; break;
        case 's': _s = false; break;
        case 'd': _d = false; break;
        case 'q': _q = false; break;
        case 'e': _e = false; break;
     
    }
}


void keyboard_special(int key, int, int)
{
    switch (key)
    {
    case GLUT_KEY_F1:
        active_camera = 1;
        break;
    case GLUT_KEY_F2:
        active_camera = 2;
        break;
    case GLUT_KEY_F3:
        active_camera = 3;
        break;
 
   // case GLUT_KEY_RIGHT:
//   //     _ri = true;
//   //     nave->rot += 0.9;
//   //     break;
//
   // case GLUT_KEY_LEFT:
   //     _le = true;
   //     nave->rot -= 0.9;
   //     break;
    
    }
}




int main(int argc, char **argv)
{
// Inicializa o GLUT
    glutInit(&argc, argv);
// Indica que o "display" utilizará duplo "buffer", o esquema de
// cores "RBG" ("Red, Green, Blue") e um "buffer" de profundidade
    glutSetOption(GLUT_MULTISAMPLE, 8);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
  
// Indica a posição da janela
    glutInitWindowPosition(0, 0);
// Indica o tamanho da janela
    glutInitWindowSize(min_width, min_height);
// Cria a janela, com o título dado
    glutCreateWindow("Asteroids");
// Define mais algumas opções
    init();
// Define a função de "display", que é chamada no início e sempre
// que a função "glutPostRedisplay é chamada
    glutDisplayFunc(display);
// Define a função de "reshape", que é chamada sempre que o tamanho
// da janela muda
    //glutReshapeFunc(reshape);
    call_display(0);

    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardup);
    glutSpecialFunc(keyboard_special);
// Inicia o ciclo de vida do GLUT
    glutMainLoop();
    return 1;
}