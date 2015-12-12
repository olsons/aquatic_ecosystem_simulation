//This program creates a visual display of an acquatic ecosystem

#include "gfx4.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

void createLayout();
void createSun(double *ySun);
void createDuckHead(double *x1, double *y1, double *beakMovement);
void createBird(double *bX, double *bY, double *i, double *l, double velocity, double *doRotate, double *dX, double *dY, int *numCount);
void createFish(double *fX, double *fY);
void createMoreFish(double *mX, double *mY);
void createLobster(double *lX, double *lY);
void printGrass();
void createShark(double *sX, double *sY);

int main()
{
	gfx_open(800, 800, "Carnival Ride: The Duck");

        //Declare variables of the ride
        char c; //check to see if someone presses a button
	int numCount=0; 
        double i=.01; //used in delta t
	double l=.01;
	double beakMovement=0; //used to help measure when the beak is fully closed (so it can be opened again)
        double deltat=.01;  //used in change of time
        double x1=50; //Where the duck starts (on left hand of page)
        double y1=120; 
        double bX=400;//the starting point for the bird
	double bY=50;
	double fX=10; //starting point for the fish
	double fY=400;
	double lX=0; //starting point for the lobster
	double lY=600;
	double dX=500; //dead fish
	double dY=200;
	double mX=1;
	double mY=220;
	double doRotate=1;
	double ySun=50; //the sun is always setting/rising
	int velocity=5; //basic velocity of the bird in the air
	double sX=1;
	double sY=300;

        while(1){
                gfx_clear();
		createLayout(); //create the layout of the structure
		createSun(&ySun); //create a visual of the sun in the corner
		createDuckHead(&x1, &y1, &beakMovement);
		createBird(&bX, &bY, &i, &l, velocity, &doRotate, &dX, &dY, &numCount);
		createFish(&fX, &fY);
		createLobster(&lX, &lY);
		createMoreFish(&mX, &mY);
		createShark(&sX, &sY);
                gfx_flush();

                //Check if the user has decided to quit the program
                if (gfx_event_waiting())
                {
                        c=gfx_wait();
                        if (c=='q')
                        {
                                break;
                        }
                }
		
                usleep(8000);
	}
	return 0;
}

//Create the structure/support for the ride (what will hold up the duck)
void createLayout(){
	//Water
	gfx_color(17,167,242); 
	int i;
	gfx_fill_rectangle(0,200, 800,600);

	//Set up sand bank
  	XPoint xp = {300,450}; // initialize a point (using X11's Xpoint struct)

	// set up 2 arrays of points
 	XPoint mypts1[] = { {1,500},{1,800},{400,800} };
 	XPoint mypts2[] = { {400,800},{800,500},{800,800} };

	gfx_color(242, 220, 132);
	gfx_fill_polygon(mypts1, 3);
	gfx_fill_polygon(mypts2, 3);
	gfx_fill_rectangle(0, 700, 800, 100); 

	printGrass();
}

void printGrass(){
	//Grass life
	gfx_color(43, 198, 25);
	gfx_line(20, 700, 20, 780);
	gfx_line(30, 680, 30, 760);
	gfx_line(25, 690, 25, 770);
	gfx_line(15, 676, 18, 750);
	gfx_line(35, 705, 35, 770);
	gfx_line(26, 680, 26, 750);
	gfx_line(17, 760, 15, 700);
	gfx_line(34, 760, 38, 700);

	gfx_line(140, 740, 140, 780);
	gfx_line(150, 720, 150, 760);
	gfx_line(145, 710, 145, 770);
	gfx_line(155, 726, 158, 750);
	gfx_line(165, 715, 165, 770);
	gfx_line(156, 720, 156, 750);
	gfx_line(167, 790, 170, 720);
	gfx_line(154, 780, 158, 740);


	gfx_line(720, 700, 720, 780);
	gfx_line(730, 680, 730, 760);
	gfx_line(725, 690, 725, 770);
	gfx_line(715, 676, 718, 750);
	gfx_line(735, 705, 735, 770);
	gfx_line(726, 680, 726, 750);
	gfx_line(717, 760, 715, 700);
	gfx_line(734, 760, 738, 700);
}	

//Create a filled in sun
void createSun(double *ySun){
	gfx_color(255,255,0); //bright yellow
        gfx_fill_arc(550, *ySun, 80, 80,0,360); //fill in beautiful sun
	*ySun=*ySun+.01;
	if (*ySun>=120)
	{
		*ySun=0;
	}
}

//Create the duck's head
void createDuckHead(double *x1, double *y1, double *beakMovement){
	*x1+=.2;
	if (*x1>=750){
		*x1=50;
	}
	//Move the beak
	*beakMovement=*beakMovement+.5; 
        //Y2 goes back to original position after the line is completely horizontal so beak won't over extend
        if (*beakMovement==50){
              	*beakMovement=0;
       	}
	gfx_color(255, 160, 36); //Beak's color
        gfx_line((int)*x1+45, (int)*y1-10, (int)*x1+110, (int)*y1-50+*beakMovement); //top beak of the bird
        gfx_line((int)*x1+45, (int)*y1+10, (int)*x1+110, (int)*y1+50-*beakMovement); //bottom beak of the bird
	gfx_color(12, 115, 0); //Duck's head's color
        gfx_fill_circle((int)*x1, (int)*y1, 45); //Duck's head
	gfx_color(169, 116, 8);
	gfx_fill_circle((int)*x1-45, (int)*y1+40, 55); //Duck's body
	gfx_color(17,2,2);
	gfx_fill_circle((int)*x1+20, (int)*y1-10, 5);
}

//Create person moving in the cart
void createBird(double *bX, double *bY, double *i, double *l, double velocity, double *doRotate, double *dX, double *dY, int *numCount){
	double deltat=.01;
	//Recalculate i, l by multiplying by delta t. This changes the angle of rotation. 
	if (*doRotate<10){
        	*i+=(double)(deltat*velocity); //Movement of the carts
        	*l+=(double)(deltat*velocity*1.1); //velocity of the line
		*bX =50+(double)(cos(*i)*20);
        	*bY =20+(double)(sin(*i)*10);
		*doRotate=*doRotate+.1;
	}
	else{
		*bX=*bX+.5;
		if (*bX>300 && *bX<=750 && *bY <= 200){
			*bY=*bY+.7;
		}
		if (*bX>=780){
			*doRotate=1;
			*bX=40;
			*dX=900;
			*numCount=1;
		}
		if(*bX>=500 && *bX<=780){
			*bY=*bY-.8;
		}
	}
	gfx_color(255, 1, 2);
	gfx_line((int)*bX, (int)*bY, (int)*bX-20, (int)*bY-20); //Bird's wings
        gfx_line((int)*bX, (int)*bY, (int)*bX-20, (int)*bY+20); //Bird's wings

	if (*bX >= 500 && *bX <=780){
		*dX=*bX;
		*dY=*bY;
	}
	if (*numCount==0){
		gfx_color(247, 246, 242); //picking up a dead fish on his first try
	}
	else{
		gfx_color(252, 206, 25); //now he picks up live fish
	}
	//Dead fish that the bird will pick up
	XPoint xp = {300,450}; // initialize a point (using X11's Xpoint struct)
	// set up 2 arrays of points
 	XPoint mypts1[] = { {*dX,*dY-10},{*dX,*dY+10},{*dX+10,*dY} };
	gfx_fill_polygon(mypts1, 3);
	gfx_fill_circle((int)*dX+10, (int)*dY, 8);
}

void createFish(double *fX, double *fY){
	gfx_color(100, 100, 100);
	*fX=*fX+5;
	if (*fY==780){
		*fY=*fY+1;
	}
	if (*fX==780){
		*fX=20;
	}
	gfx_line((int)*fX, (int)*fY, (int)*fX+20, (int)*fY);
	gfx_line((int)*fX+10, (int)*fY, (int)*fX+30, (int)*fY);
	gfx_line((int)*fX+15, (int)*fY+10, (int)*fX+35, (int)*fY+10);
	gfx_line((int)*fX-20, (int)*fY-10, (int)*fX, (int)*fY-10);
	gfx_line((int)*fX-30, (int)*fY-20, (int)*fX-10, (int)*fY-20);
	gfx_line((int)*fX-40, (int)*fY+20, (int)*fX-20, (int)*fY+20);
	gfx_line((int)*fX-30, (int)*fY+7, (int)*fX-10, (int)*fY+7);
	gfx_line((int)*fX, (int)*fY+20, (int)*fX, (int)*fY+20);
}

void createMoreFish(double *mX, double *mY){
	gfx_color(252, 206, 25);
	//Dead bird that it will pick up eventually
	XPoint xp = {300,450}; // initialize a point (using X11's Xpoint struct)
	// set up 2 arrays of points
 	XPoint mypts1[] = { {*mX,*mY-10},{*mX,*mY+10},{*mX+10,*mY} };
	XPoint mypts2[] = { {*mX+2,*mY+40},{*mX+2,*mY+20},{*mX+12,*mY+30} };
	XPoint mypts3[] = { {*mX-8,*mY+60},{*mX-8,*mY+80},{*mX,*mY+70} };
	gfx_fill_polygon(mypts1, 3);
	gfx_fill_circle((int)*mX+10, (int)*mY, 8);
	gfx_fill_polygon(mypts2, 3);
	gfx_fill_circle((int)*mX+12, (int)*mY+30, 8);
	gfx_fill_polygon(mypts3, 3);
	gfx_fill_circle((int)*mX, (int)*mY+70, 8);
	if (*mX<=790){
		*mX=*mX+.5;
	}
	else{
		*mX=0;
	}
}

void createLobster(double *lX, double *lY){
	if (*lX<=280){
		*lX=*lX+.05;
		*lY=*lY+.03;
	}
	if (*lX<=500 && *lX>=280){
		*lX=*lX+.05;
	}
	if (*lX>=500){
		*lX=*lX+.05;
		*lY=*lY-.03;
	}
	if (*lX>=795){
		*lX=0;
	}
	gfx_color(255, 4, 4);
	//Eye
	gfx_fill_circle((int)*lX, (int)*lY, 8);
	gfx_fill_circle((int)*lX+2, (int)*lY-10, 6);
	gfx_fill_circle((int)*lX-2, (int)*lY-10, 6);
	//Crab hook
	gfx_line((int)*lX+8, (int)*lY-2, (int)*lX+14, (int)*lY-10);
	gfx_line((int)*lX+14, (int)*lY-10, (int)*lX+18, (int)*lY-20);
	gfx_line((int)*lX+14, (int)*lY-10, (int)*lX+11, (int)*lY-18);
	gfx_line((int)*lX-8, (int)*lY-2, (int)*lX-14, (int)*lY-10);
	gfx_line((int)*lX-14, (int)*lY-10, (int)*lX-18, (int)*lY-20);
	gfx_line((int)*lX-14, (int)*lY-10, (int)*lX-11, (int)*lY-18);
	//Leg additions
	gfx_line((int)*lX+5, (int)*lY+2, (int)*lX+16, (int)*lY+1);
	gfx_line((int)*lX+5, (int)*lY+3, (int)*lX+16, (int)*lY+3);
	gfx_line((int)*lX+5, (int)*lY+4, (int)*lX+16, (int)*lY+5);
	gfx_line((int)*lX-5, (int)*lY+2, (int)*lX-16, (int)*lY+1);
	gfx_line((int)*lX-5, (int)*lY+3, (int)*lX-16, (int)*lY+3);
	gfx_line((int)*lX-5, (int)*lY+4, (int)*lX-16, (int)*lY+5);
	//Pupil of the eye
	gfx_color(0,0,0); 
	gfx_fill_circle((int)*lX+2, (int)*lY-10, 2);
	gfx_fill_circle((int)*lX-2, (int)*lY-10, 2);
	//Lips of lobster
	gfx_line((int)*lX-3, (int)*lY+2, (int)*lX+3, (int)*lY+2);
}

void createShark(double *sX, double *sY){
        gfx_ellipse((int)*sX, (int)*sY, 40, 20); //body
        gfx_line((int)*sX, (int)(*sY-20), (int)*sX, (int)(*sY-20-8)); //top fin
        gfx_line((int)*sX, (int)(*sY-20-8), (int)(*sX-20*cos(45)), (int)(*sY-20*sin(45)));
        gfx_circle((int)(*sX+10), (int)(*sY-7), 3); //eye
        gfx_line((int)(*sX-40), (int)*sY, (int)(*sX-10*cos(M_PI/3)), (int)(*sY-10*sin(M_PI/3)));
        gfx_line((int)(*sX-10*cos(M_PI/3)), (int)(*sY-10*sin(M_PI/3)), (int)(*sX-10*cos(M_PI/3)), (int)(*sY+10*sin(M_PI/3)));
	gfx_line((int)(*sX-10*cos(M_PI/3)), (int)(*sY+10*sin(M_PI/3)), (int)(*sX-40), (int)*sY);
	
	*sX+=.5;
}
