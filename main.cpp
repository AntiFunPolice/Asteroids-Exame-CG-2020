
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
GameManager *game;

int active_camera = 1;
bool game_start=true;
int colliding_with=-1;

bool _ri = false;
bool _le = false;
bool _w = false;                                                                            //  <<-global->> bool for whether the w key is down
bool _a = false;                                                                            //  <<-global->> bool for whether the a key is down
bool _s = false;                                                                            //  <<-global->> bool for whether the s key is down
bool _d = false;                                                                            //  <<-global->> bool for whether the d key is down


bool _space = false;                                                                  
bool fuel = true;
int fuel_counter=0,beam_counter=0;    
bool colliding = false;
bool beam_ready = true;
	


void create_objects(){	

    game = new GameManager();
  	nave = game->nave;
}

void init_lights(){

    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);

    GLfloat light_ambient[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 0.8};
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 0.8};
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    GLfloat light_pos[] = {0.0, 0, 1, 0.0};
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
            set_camera(nave->xx , 16, nave->zz , nave->xx, nave->yy, nave->zz-3, 0.0, 1, 0);
            break;

        case 3:
           set_camera((nave->xx - 10*nave->x_Camera3d) ,  0.7 ,(nave->zz-10*nave->z_Camera3d) , nave->xx + nave->x_Camera3d, 0, nave->zz +nave->z_Camera3d , 0, 1, 0);
            break;
        case 4:
           set_camera( (nave->xx + 10*nave->x_Camera3d) ,  0.6 ,(nave->zz+10*nave->z_Camera3d) , nave->xx - nave->x_Camera3d, 0, nave->zz -nave->z_Camera3d , 0, 1, 0);
            break;

        case 5:
           set_camera( 11, 11, 11, nave->xx, nave->yy, nave->zz , 0, 1, 0);
            break;

        case 6:
           set_camera( -11 , -11 ,-11 , nave->xx, nave->yy, nave->zz , 0, 1, 0);
            break;
      
    }
}


void trust(){
	nave->xx += nave->speedx;
	nave->zz += nave->speedz;
} 

void get_3d_Camera(){
   
    float xsda = nave->rot;
    float div  = xsda/360;
    float rem = (xsda - ((floor(div)+27)*360)-90);
 
    
    

    nave->x_Camera3d = cos(rem*PI /180)/10;
    nave->z_Camera3d = sin(rem*PI /180)/10;
}

void vectorget(){
	float xsda = nave->rot;
    float div  = xsda/360;
    float rem = (xsda - ((floor(div))*360)-90);
 
    nave->speedx=0;
    nave->speedz=0;
   	nave->speedx += cos(rem*PI /180)/30;
    nave->speedz += sin(rem*PI /180)/30;
}


void movement2(){

	 if(_a||_d||_w||_s||_space){
        game->game_Start=true;

        if(_space){
            if(beam_ready){
                game->shoting= true;
                beam_ready=false;
            }
        }

        if(_w){
        
          	if(fuel){
            	vectorget();
            	fuel=false;
   			}
        }

        if(_s){
            
            nave->speedx/=1.02;
            nave->speedz/=1.02;
        }

        

        if(_a){
    		nave->rot -= 2;
    		
    	}

   	 	if(_d){
   	 		nave->rot += 2;		
   	 	}
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

    int points = game->points;
    int lives = game->lives;
    display_text("Labels (L): Showing", label_box_height - 25 * n_text++);
    display_text(" Lifes "+to_string(lives),label_box_height - 25 * n_text++);
    display_text(" Ponts: " +  to_string(points), label_box_height - 25 * n_text++);
    display_text_color(" Thrust: " +  string(fuel ? "Ready" : "Cooldown"), label_box_height - 25 * n_text++,fuel);
    display_text_color(" Beam: " +  string(beam_ready ? "Ready" : "Cooldown"), label_box_height - 25 * n_text++,beam_ready);
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

beam_counter++;
if(beam_counter==50){
    beam_ready=true;
    beam_counter=0;
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
    

    game->display();  
    
    movement2();
    
    glColor3f(1, 1, 1);
 	 //axis_diplay();
    trust();
    //nave->display();
    get_3d_Camera();
   
    //game->nave->obj->hitbox();
    
    

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
        //case 'q': _q = true; break;
        //case 'e': _e = true; break;
        case ' ': _space = true; break;
       

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
       // case 'q': _q = false; break;
       // case 'e': _e = false; break;
        case ' ': _space = false; break;
     
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
    case GLUT_KEY_F4:
        active_camera = 4;
        break;
    case GLUT_KEY_F5:
        active_camera = 5;
        break;
    case GLUT_KEY_F6:
        active_camera = 6;
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