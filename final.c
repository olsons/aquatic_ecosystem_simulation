//This program creates a visual display of an acquatic ecosystem

#include "gfx4.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

void createLayout();
void createSun(double *ySun);
void createDuckHead(double *x1, double *y1, double *beakMovement);
void createBird(double *bX, double *bY, double *i, double *l, double velocity, double *doRotate);
void createFish(double *fX, double *fY);

int main()
{
	gfx_open(800, 800, "Carnival Ride: The Duck");

        //Declare variables of the ride
        char c; //check to see if someone presses a button
        double i=.01; //used in delta t
	double l=.01;
	double beakMovement=0; //used to help measure when the beak is fully closed (so it can be opened again)
        double deltat=.01;  //used in change of time
        double x1=50; //Where the duck starts (on left hand of page)
        double y1=120; 
        double bX=400;//the starting point for the bird
	double bY=50;//the starting point for the bird
	double fX=10;
	double fY=400;
	double doRotate=1;
	double ySun=50; //the sun is always setting/rising
	int velocity=5; //basic velocity of the bird in the air

        while(1){
                gfx_clear();
		createLayout(); //create the layout of the structure
		createSun(&ySun); //create a visual of the sun in the corner
		createDuckHead(&x1, &y1, &beakMovement);
		createBird(&bX, &bY, &i, &l, velocity, &doRotate);
		createFish(&fX, &fY);
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
	gfx_color(17,167,242); //color for water
	int i;
	for (i=0; i<600; i++){
		gfx_line(1, 200+i, 800, 200+i); //water line
       }
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
        gfx_line((int)*x1+45, (int)*y1-10, (int)*x1+130, (int)*y1-50+*beakMovement); //top beak of the bird
        gfx_line((int)*x1+45, (int)*y1+10, (int)*x1+130, (int)*y1+50-*beakMovement); //bottom beak of the bird
	gfx_color(84, 175, 39); //Duck's head's color
        gfx_circle((int)*x1, (int)*y1, 45); //Duck's head
	gfx_circle((int)*x1-35, (int)*y1+30, 60); //Duck's body
}

//Create person moving in the cart
void createBird(double *bX, double *bY, double *i, double *l, double velocity, double *doRotate){
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
		*bX=*bX+4;
		if (*bX>=780){
			*doRotate=1;
			*bX=40;
		}
	}
	gfx_color(252, 206, 25);
	gfx_line((int)*bX, (int)*bY, (int)*bX-10, (int)*bY-10); //Bird's wings
        gfx_line((int)*bX, (int)*bY, (int)*bX-10, (int)*bY+10); //Bird's wings
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

}
