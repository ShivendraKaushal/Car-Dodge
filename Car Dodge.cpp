#include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;
//Game Speed
int KMPH = 50;
int is = 50;
//Game Track
int start=0;
int gv=0;
int level = 1;
int last;
int i=0;
//Track Score
int score = 0;
//Form move track
int roadDivTopMost = 0;
int roadDivTop = 0;
int roadDivMdl = 0;
int roadDivBtm = 0;
//For Card Left / RIGHT
int lrIndex = 0 ;
//Car Coming
int car1 = 0;
int lrIndex1=0;
int car2 = +35;
int lrIndex2=0;
int car3 = +70;
int lrIndex3=0;
int il = 1;
//For Display TEXT
int l=0;
const int font1=(int)GLUT_BITMAP_TIMES_ROMAN_24;
const int font2=(int)GLUT_BITMAP_HELVETICA_18 ;
const int font3=(int)GLUT_BITMAP_8_BY_13;
char s[30];
void renderBitmapString(float x, float y, void *font,const char *string){
    const char *c;
    glRasterPos2f(x, y);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}
void startGame(){
    //Road
    glColor3f(0.412, 0.412, 0.412);
    glBegin(GL_POLYGON);
    glVertex2f(20,0);
    glVertex2f(20,100);
    glVertex2f(80,100);
    glVertex2f(80,0);
    glEnd();
    //Road Left Border
    glColor3f(1.000, 1.000, 1.000);
    glBegin(GL_POLYGON);
    glVertex2f(20,0);
    glVertex2f(20,100);
    glVertex2f(23,100);
    glVertex2f(23,0);
    glEnd();
    //Road Right Border
    glColor3f(1.000, 1.000, 1.000);
    glBegin(GL_POLYGON);
    glVertex2f(77,0);
    glVertex2f(77,100);
    glVertex2f(80,100);
    glVertex2f(80,0);
    glEnd();
    //Road Middle Border
    //TOP
    glColor3f(1.000, 1.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(48,roadDivTop+80);
    glVertex2f(48,roadDivTop+100);
    glVertex2f(52,roadDivTop+100);
    glVertex2f(52,roadDivTop+80);
    glEnd();
    roadDivTop--;
    if(roadDivTop<-100){
        roadDivTop =20;
        score++;
    }
        //Middle
    glColor3f(1.000, 1.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(48,roadDivMdl+40);
    glVertex2f(48,roadDivMdl+60);
    glVertex2f(52,roadDivMdl+60);
    glVertex2f(52,roadDivMdl+40);
    glEnd();
    roadDivMdl--;
    if(roadDivMdl<-60){
        roadDivMdl =60;
        score++;
    }
        //Bottom
    glColor3f(1.000, 1.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(48,roadDivBtm+0);
    glVertex2f(48,roadDivBtm+20);
    glVertex2f(52,roadDivBtm+20);
    glVertex2f(52,roadDivBtm+0);
    glEnd();
    roadDivBtm--;
    if(roadDivBtm<-20){
        roadDivBtm=100;
        score++;
    }
    //Score Board
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(80,97);
    glVertex2f(100,97);
    glVertex2f(100,98-8);
    glVertex2f(80,98-8);
    glEnd();
    //Print Score
    char buffer [50];
    sprintf (buffer, "SCORE: %d", score);
    glColor3f(0.000, 1.000, 0.000);
    renderBitmapString(80.5,95,(void *)font3,buffer);
    //Speed Print
    char buffer1 [50];
    sprintf (buffer1, "SPEED:%dKm/h", KMPH);
    glColor3f(0.000, 1.000, 0.000);
    renderBitmapString(80.5,95-2,(void *)font3,buffer1);
    //level Print
    if(score >= 10 && score % 10 == 0){
        if(last != score){
            last = score;
            level += 1;
            KMPH = KMPH + 10;
        }
    }
    char level_buffer [50];
    sprintf (level_buffer, "LEVEL: %d", level);
    glColor3f(0.000, 1.000, 0.000);
    renderBitmapString(80.5,95-4,(void *)font3,level_buffer);
    //Increase Speed With level
    //MAIN car
    //Front Tire
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex+26-2,5);
    glVertex2f(lrIndex+26-2,7);
    glVertex2f(lrIndex+30+2,7);
    glVertex2f(lrIndex+30+2,5);
    glEnd();
        //Back Tire
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex+26-2,1);
    glVertex2f(lrIndex+26-2,3);
    glVertex2f(lrIndex+30+2,3);
    glVertex2f(lrIndex+30+2,1);
    glEnd();
        //Car Body
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex+26,1);
    glVertex2f(lrIndex+26,8);
    glColor3f(0.000, 0.0, 1.0);
    glVertex2f(lrIndex+27,10);
    glVertex2f(lrIndex+29,10);
    glVertex2f(lrIndex+30,8);
    glVertex2f(lrIndex+30,1);
    glEnd();
    //Opposite car 1
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex1+26-2,car1+100-4);
    glVertex2f(lrIndex1+26-2,car1+100-6);
    glVertex2f(lrIndex1+30+2,car1+100-6);
    glVertex2f(lrIndex1+30+2,car1+100-4);
    glEnd();
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex1+26-2,car1+100);
    glVertex2f(lrIndex1+26-2,car1+100-2);
    glVertex2f(lrIndex1+30+2,car1+100-2);
    glVertex2f(lrIndex1+30+2,car1+100);
    glEnd();
    glColor3f(1.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex1+26,car1+100);
    glVertex2f(lrIndex1+26,car1+100-7);
    glVertex2f(lrIndex1+27,car1+100-9);
    glVertex2f(lrIndex1+29,car1+100-9);
    glVertex2f(lrIndex1+30,car1+100-7);
    glVertex2f(lrIndex1+30,car1+100);
    glEnd();
    car1--;
    if(car1<-100){
        car1=0;
        lrIndex1=lrIndex;
    }
    //KIll check car1
    if((abs(lrIndex-lrIndex1)<8) && (car1+100<10)){
            start = 0;
            gv=1;

    }
    //Opposite car 2
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex2+26-2,car2+100-4);
    glVertex2f(lrIndex2+26-2,car2+100-6);
    glVertex2f(lrIndex2+30+2,car2+100-6);
    glVertex2f(lrIndex2+30+2,car2+100-4);
    glEnd();
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex2+26-2,car2+100);
    glVertex2f(lrIndex2+26-2,car2+100-2);
    glVertex2f(lrIndex2+30+2,car2+100-2);
    glVertex2f(lrIndex2+30+2,car2+100);
    glEnd();
    glColor3f(0.294, 0.000, 0.510);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex2+26,car2+100);
    glVertex2f(lrIndex2+26,car2+100-7);
    glVertex2f(lrIndex2+27,car2+100-9);
    glVertex2f(lrIndex2+29,car2+100-9);
    glVertex2f(lrIndex2+30,car2+100-7);
    glVertex2f(lrIndex2+30,car2+100);
    glEnd();
    car2--;
    if(car2<-100){
        car2=0;
        lrIndex2=lrIndex;
    }
    //KIll check car2
    if((abs(lrIndex-lrIndex2)<8) && (car2+100<10)){
            start = 0;
            gv=1;
    }
    //Opposite car 3
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex3+26-2,car3+100-4);
    glVertex2f(lrIndex3+26-2,car3+100-6);
    glVertex2f(lrIndex3+30+2,car3+100-6);
    glVertex2f(lrIndex3+30+2,car3+100-4);
    glEnd();
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex3+26-2,car3+100);
    glVertex2f(lrIndex3+26-2,car3+100-2);
    glVertex2f(lrIndex3+30+2,car3+100-2);
    glVertex2f(lrIndex3+30+2,car3+100);
    glEnd();
    glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex3+26,car3+100);
    glVertex2f(lrIndex3+26,car3+100-7);
    glVertex2f(lrIndex3+27,car3+100-9);
    glVertex2f(lrIndex3+29,car3+100-9);
    glVertex2f(lrIndex3+30,car3+100-7);
    glVertex2f(lrIndex3+30,car3+100);
    glEnd();
    car3--;
    if(car3<-100){
        car3=0;
        lrIndex3=lrIndex;
    }
    //KIll check car3
    if((abs(lrIndex-lrIndex3)<8) && (car3+100<10)){
            start = 0;
            gv=1;
    }
}
void home_page(){
        //Menu Place Holder
        glColor3f(0.098, 0.098, 0.439);
        glBegin(GL_POLYGON);
        glVertex2f(32-4,50+8);
        glVertex2f(32+46,50+8);
        glVertex2f(32+46,50-6+10);
        glVertex2f(32-4,50-6+10);
        glEnd();
        glColor3f(0.098, 0.098, 0.439);
        glBegin(GL_POLYGON);
        glVertex2f(32-4,50+8-5);
        glVertex2f(32+46,50+8-5);
        glVertex2f(32+46,50-6-5+10);
        glVertex2f(32-4,50-6-5+10);
        glEnd();
        glColor3f(0.098, 0.098, 0.439);
        glBegin(GL_POLYGON);
        glVertex2f(32-4,50+8-10);
        glVertex2f(32+46,50+8-10);
        glVertex2f(32+46,50-6-10+10);
        glVertex2f(32-4,50-6-10+10);
        glEnd();
        glColor3f(0.098, 0.098, 0.439);
        glBegin(GL_POLYGON);
        glVertex2f(32-4,50+8-15);
        glVertex2f(32+46,50+8-15);
        glVertex2f(32+46,50-6+10-15);
        glVertex2f(32-4,50-6+10-15);
        glEnd();
        //Text Information in HOME Page
        if(gv==1){
            glColor3f(1.0,0.0,0.0);
            renderBitmapString(35,60+10,(void *)font1,"GAME OVER");
            char buffer2 [50];
            sprintf (buffer2, "Your Score is : %d", score);
            renderBitmapString(33,60-4+10,(void *)font1,buffer2);
        }
        //CadetBlue = color red 0.372549 green 0.623529 blue 0.623529
        glColor3f(1.0, 1.0, 0.0);
        renderBitmapString(30,80,(void *)font1,"NEED FOR SPEED");
        glColor3f(1.0, 0.25, 0.0);
        renderBitmapString(30+10,50-5+10,(void *)font2,"      START");
        renderBitmapString(30+10,50-10+10,(void *)font2,"INSTRUCTION");
        renderBitmapString(30+10,50-15+10,(void *)font2,"      LEVEL");
        renderBitmapString(30+10,50-20+10,(void *)font2,"       EXIT");
}
void level_(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.25, 0.0);
     glColor3f(0.098, 0.098, 0.439);
        glBegin(GL_POLYGON);
        glVertex2f(32-3,50+8);
        glVertex2f(32+35,50+8);
        glVertex2f(32+35,50-6+10);
        glVertex2f(32-3,50-6+10);
        glEnd();
        glColor3f(0.098, 0.098, 0.439);
        glBegin(GL_POLYGON);
        glVertex2f(32-3,50+8-5);
        glVertex2f(32+35,50+8-5);
        glVertex2f(32+35,50-6-5+10);
        glVertex2f(32-3,50-6-5+10);
        glEnd();
        glColor3f(0.098, 0.098, 0.439);
        glBegin(GL_POLYGON);
        glVertex2f(32-3,50+8-10);
        glVertex2f(32+35,50+8-10);
        glVertex2f(32+35,50-6-10+10);
        glVertex2f(32-3,50-6-10+10);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(0,98);
        glVertex2f(12,98);
        glVertex2f(12,94);
        glVertex2f(0,94);
        glEnd();

    glColor3f(1.000, 1.000, 0.000);
    renderBitmapString(30,80,(void *)font1,"CHOOSE LEVEL");
    glColor3f(1.0, 0.25, 0.0);
    renderBitmapString(1,95,(void *)font2,"BACK");
    renderBitmapString(30+11,50-5+10,(void *)font2,"LEVEL 1");
    renderBitmapString(30+11,50-10+10,(void *)font2,"LEVEL 2");
    renderBitmapString(30+11,50-15+10,(void *)font2,"LEVEL 3");
}
void instructions(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.25, 0.0);
    glColor3f(0.098, 0.098, 0.439);
        glBegin(GL_POLYGON);
        glVertex2f(0,98);
        glVertex2f(12,98);
        glVertex2f(12,94);
        glVertex2f(0,94);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(32-15,50+8);
        glVertex2f(32+50,50+8);
        glVertex2f(32+50,50-6+10);
        glVertex2f(32-15,50-6+10);
        glEnd();
        glColor3f(0.098, 0.098, 0.439);
        glBegin(GL_POLYGON);
        glVertex2f(32-15,50+8-5);
        glVertex2f(32+50,50+8-5);
        glVertex2f(32+50,50-6-5+10);
        glVertex2f(32-15,50-6-5+10);
        glEnd();
    glColor3f(1.000, 1.000, 0.000);
    renderBitmapString(30,80,(void *)font1,"INSTRUCTION");
    glColor3f(1.0, 0.25, 0.0);
    renderBitmapString(1,95,(void *)font2,"BACK");
    renderBitmapString(30-9,50-5+10,(void *)font2,"USE LEFT KEY TO MOVE LEFT");
    renderBitmapString(30-10,50-10+10,(void *)font2,"USE RIGHT KEY TO MOVE RIGHT");
}
void OnMouseClick(int button,int state,int x,int y){
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        if((x>=140&&x<=390)&&(y>=270&&y<=300)&& (i==0 && l==0 && start==0)){
            if(start==0){
                start = 1;
                gv = 0;
                KMPH = is;
                roadDivTopMost = 0;
                roadDivTop = 0;
                roadDivMdl = 0;
                roadDivBtm = 0;
                lrIndex = 0 ;
                car1 = 0;
                lrIndex1 = 0;
                car2 = +35;
                lrIndex2 = 0;
                car3 = +70;
                lrIndex3 = 0;
                score = 0;
                last = 0;
                level = il;
            }
        }
       else if((x>=140&&x<=390)&&(y>=305&&y<=330)&&(i==0 && l==0 && start==0)){
            i = 1;
       }
       else if((x>=0 && x<=59)&& (y>=13 && y<=38)&&(i==1 && l==0 && start==0)){
            i=0 ;
       }
       else if((x>=140&&x<=390)&&(y>=335&&y<=360)&&(i==0 && l==0 && start==0)){
            l=1;
       }
       else if((x>=0 && x<=59)&& (y>=13 && y<=38)&&(i==0 && l==1 && start==0)){
            l=0;
       }
       else if((x>=139 && x<=328)&& (y>=274 && y<=299)&&(i==0 && l==1 && start==0)){
            level = 1;
            KMPH = 50;
            l = 0;
            il = 1;
            is = 50;
       }
       else if((x>=139 && x<=328)&& (y>=306 && y<=328)&&(i==0 && l==1 && start==0)){
            level = 2;
            KMPH = 60;
            l = 0;
            il = 2;
            is = 60;
       }
       else if((x>=139 && x<=328)&& (y>=338 && y<=360)&&(i==0 && l==1 && start==0)){
            level = 3;
            KMPH = 70;
            l = 0;
            il = 3;
            is = 70;
       }
       else if((x>=140&&x<=390)&&(y>=365&&y<=390)&&(i==0 && l==0 && start==0)){
            exit(0);
       }
    }
}
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    if(start==1){
        startGame();
    }
    else if(i == 1){
        instructions();
    }
    else if(l==1){
        level_();
    }
    else{
        home_page();
    }
    glFlush();
    glutSwapBuffers();
}
void spe_key(int key, int x, int y){
        switch (key) {
        case GLUT_KEY_LEFT:
            if(lrIndex>=0){
                lrIndex = lrIndex - (KMPH/10);
                if(lrIndex<0){
                    lrIndex=-1;
                }
            }
            break;
        case GLUT_KEY_RIGHT:
            if(lrIndex<=44){
                lrIndex = lrIndex + (KMPH/10);
                if(lrIndex>44){
                    lrIndex = 45;
                }
            }
            break;
        default:
                break;
        }
}
void timer(int){
    glutPostRedisplay();
    glutTimerFunc(1000/KMPH,timer,0);
}
int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(500,650);
    glutInitWindowPosition(200,20);
    glutCreateWindow("NFS");
    glutMouseFunc(OnMouseClick);
    glutDisplayFunc(display);
    glutSpecialFunc(spe_key);
    glOrtho(0,100,0,100,-1,1);
    glClearColor(0.184, 0.310, 0.310,1);
    glutTimerFunc(1000,timer,0);
    glutMainLoop();
}
