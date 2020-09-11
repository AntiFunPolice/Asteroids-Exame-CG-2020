


class Particles
{
public:
    
    float pos[3][26];
    float increment[3][26];

    float center[3];   

    float min_x,min_y,min_z,max_x,max_y,max_z;
    bool in =true;

 

    Particles(int x ,int y ,int z){

        center[0]= x;
        center[1]= y;
        center[2]= z;

        set_circle();
        add_asteroid_position();
        get_Increments();
    }




    void set_circle(){
        
        pos[0][0] = 0;       pos[1][0] = 0;       pos[2][0] =  0.11; 
        pos[0][1] = 0;       pos[1][1] = 0;       pos[2][1] = -0.11;
         
        pos[0][2] = 0;       pos[1][2] =  0.1;    pos[2][2] =  0.01; 
        pos[0][3] = 0;       pos[1][3] = -0.1;    pos[2][3] =  0.01; 
        pos[0][4] = 0;       pos[1][4] = -0.1;    pos[2][4] = -0.01; 
        pos[0][5] = 0;       pos[1][5] =  0.1;    pos[2][5] = -0.01;
        
        pos[0][6] = 0;       pos[1][6] =  0.1;    pos[2][6] = 0; 
        pos[0][7] = 0;       pos[1][7] = -0.1;    pos[2][7] = 0; 
        pos[0][8] = -0.1;    pos[1][8] = 0;       pos[2][8] = 0; 
        pos[0][9] =  0.1;    pos[1][9] = 0;       pos[2][9] = 0;
        
        pos[0][10] = -0.1;   pos[1][10] = 0;      pos[2][10] =  0.1; 
        pos[0][11] =  0.1;   pos[1][11] = 0;      pos[2][11] =  0.1; 
        pos[0][12] =  0.1;   pos[1][12] = 0;      pos[2][12] = -0.1; 
        pos[0][13] = -0.1;   pos[1][13] = 0;      pos[2][13] = -0.1;
        
        pos[0][14] = -0.1;   pos[1][14] =  0.1;   pos[2][14] = 0; 
        pos[0][15] = -0.1;   pos[1][15] = -0.1;   pos[2][15] = 0; 
        pos[0][16] =  0.1;   pos[1][16] = -0.1;   pos[2][16] = 0; 
        pos[0][17] =  0.1;   pos[1][17] =  0.1;   pos[2][17] = 0; 
          
        pos[0][18] = -0.06;   pos[1][18] = -0.06;  pos[2][18] = 0.08; 
        pos[0][19] = -0.06;   pos[1][19] =  0.06;  pos[2][19] = 0.08; 
        pos[0][20] =  0.06;   pos[1][20] = -0.06;  pos[2][20] = 0.08; 
        pos[0][21] =  0.06;   pos[1][21] =  0.06;  pos[2][21] = 0.08;
           
        pos[0][22] = -0.06;  pos[1][22] = -0.06;  pos[2][22] = -0.08; 
        pos[0][23] = -0.06;  pos[1][23] =  0.06;  pos[2][23] = -0.08; 
        pos[0][24] =  0.06;  pos[1][24] = -0.06;  pos[2][24] = -0.08; 
        pos[0][25] =  0.06;  pos[1][25] =  0.06;  pos[2][25] = -0.08; 

    }



    void get_Increments(){
        for (int i = 0; i < 26; ++i){
            increment[0][i] = pos[0][i] - center[0];
            increment[1][i] = pos[1][i] - center[1];
            increment[2][i] = pos[2][i] - center[2];
        }
    }

    void add_asteroid_position(){
        for (int i = 0; i < 26; ++i){
            for (int j = 0; j < 3; ++j){
               pos[j][i]+=center[j];
            }
        }
    }

    void add_increments(int i){
        pos[0][i] += increment[0][i]/10;
        pos[1][i] += increment[1][i]/10;
        pos[2][i] += increment[2][i]/10;
    }
    
    void check_Limits(){
        if(abs(pos[2][0] - center[2]) > 2)
            in=false;
    }

    void pre_display(){
        check_Limits();
       
    }

  
   
    void display(Obj *a){
        check_Limits();
        if(in){
            for (int i = 0; i < 26; ++i){
                glPushMatrix();
                glTranslatef(pos[0][i],pos[1][i],pos[2][i]);
                a->display();
                glPopMatrix();
                add_increments(i);
            }
        }
    }
};