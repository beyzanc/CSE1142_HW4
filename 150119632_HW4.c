// Beyzanur Çabuk - 150119632
// This program aims to suggest a route to go from a starting point to a destination point on a metro line using the shortest distance.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 10     // defining a constant variable SIZE with value 10


typedef struct {

    char name[20];
    double x;
    double y;

} MetroStation;


typedef struct {

    char color[20];
    MetroStation MetroStations[SIZE];

} MetroLine;


typedef struct {

    char name[20];
    MetroLine MetroLines[SIZE];

} MetroSystem;

int equals(MetroStation s1, MetroStation s2){   // checks if two stations given as parameters are with same name properties.

    return (strcmp(s1.name, s2.name) == 0 ? 1 : 0);

}

void addStation( MetroLine *mLine,  MetroStation mStation){ // adds given station to metro stations array pointed by line pointer.

	for(int i=0; i<SIZE; i++){

		if(mLine -> MetroStations[i].name[0] == 0){

			mLine -> MetroStations[i] = mStation;
			printf("%s station is added to %s line!\n",mStation.name,mLine->color);
			break;

		}
	}
}

int hasStation(MetroLine mLine, MetroStation mStation){ // checks if the station is on the given line.

	for(int i=0; i<SIZE; i++){

		for(int j=0; j<SIZE; j++){

 			if(strcmp((mLine.MetroStations[i]).name,mStation.name)==0){

 				printf("Station %s is in %s line.   //  ",mStation.name,mLine.color);
 				return 1;

 			}

 			else{

                printf("Station %s is not in %s line.   //  ",mStation.name,mLine.color);
 				return 0;

 			}
        }
    }
}

MetroStation getFirstStop(MetroLine mLine){    // returns the first station of the given metro line.

    int i=strlen(mLine.MetroStations[0].name);

    if (i==0){

        MetroStation empty;
        return empty;

    }

    else{

        return mLine.MetroStations[0];

    }
}

MetroStation getPreviousStop(MetroLine mLine, MetroStation mStation){   // provides to find the previous stop of the given metro station.

    MetroStation previous;

    for (int i=0; i<SIZE; i++){

        if (strcmp(mLine.MetroStations[i].name,mStation.name)==0){

            if (i==0){

                return previous;

            }
            else{

                return mLine.MetroStations[i-1];

            }
        }
    }
    return previous;
}

MetroStation getNextStop(MetroLine mLine, MetroStation mStation){   // provides to find the next stop of the given metro station.

    MetroStation next;

    for (int i=0; i<SIZE; i++){

        if (strcmp(mLine.MetroStations[i].name,mStation.name) == 0){

            if (i == (SIZE-1)){

                return next;

            }
            else{

                return mLine.MetroStations[i+1];

            }
        }
    }

    return next;
}

void addLine(MetroSystem *mSystem, MetroLine mLine){    // adds the given metro line to the end of the metro lines array pointed by metro system pointer.

    int line=0;
    mSystem->MetroLines[line]=mLine;
    printf("%s line is added to %s metro system!",mLine.color,mSystem->name);
    line++;
    printf("\n");

}

void printLine(MetroLine mLine){

	int i=0;

    printf("Metroline %s:  ",mLine.color);

    while(mLine.MetroStations[i].name[0]!=0){

        if(mLine.MetroStations[i+1].name[0]!=0){

          printf("%s, ",mLine.MetroStations[i].name);

        }
        else if(mLine.MetroStations[i+1].name[0] == 0){

          printf("%s.",mLine.MetroStations[i].name);

        }

        i++;
    }

    printf("\n");

}

void printPath(MetroStation mStation[]){    // prints the given metro station array.

    int i=0;

    while (i<(sizeof(mStation))){

        printf("%s\n",mStation[i].name);
        i++;

    }
}

double getDistanceTravelled(MetroStation mStation[]){   // returns the total distance travelled between stations.

    double distance=0, totalDistance=0;

    for (int i=0; i<SIZE-1; i++){

        if (mStation[i].name[0]!='\0'){

            distance=sqrt(pow(mStation[i + 1].x - mStation[i].x, 2) + pow(mStation[i + 1].y - mStation[i].y, 2));
            totalDistance+=distance;

        }
    }

    return totalDistance;


}

MetroStation findNearestStation(MetroSystem mSystem, double x,double y){    // finds the nearest station of given x and y values.

    double initialDistance, tempDistance, tempX, tempY;

    MetroStation initialStation=mSystem.MetroLines[0].MetroStations[0];

    initialDistance= sqrt(pow((mSystem.MetroLines[0].MetroStations[0].x)-x,2)
                        + pow((mSystem.MetroLines[0].MetroStations[0].y)-y,2));

    for (int i=0;i<SIZE;i++){

        for (int j=0;j<SIZE;j++){

            tempDistance=sqrt(pow((mSystem.MetroLines[i].MetroStations[j].x)-x,2)
                            + pow((mSystem.MetroLines[i].MetroStations[j].y)-y,2));


            if (tempDistance<initialDistance){

                initialDistance=tempDistance;
                initialStation=mSystem.MetroLines[i].MetroStations[j];

            }
        }
    }

    return initialStation;

}

void getNeighboringStations(MetroSystem mSystem, MetroStation mStation,  MetroStation neighboringStations[]){   // gets the neighboring stations the given metro station in the metro system.

    MetroStation previous, next, ms;
    int k = 0;

    for(int i = 0; i < SIZE; i++){

        for(int j = 0; j < SIZE; j++){

            ms = mSystem.MetroLines[i].MetroStations[j];
            int a=equals(ms,mStation);

            if(a==1){

                previous = mSystem.MetroLines[i].MetroStations[j -1];
                next = mSystem.MetroLines[i].MetroStations[j  + 1];

                if(k < SIZE){

                    if(previous.name[0] != '\0'){

                        neighboringStations[k] = previous;
                        k++;

                    }

                    if(next.name[0] != '\0'){

                        neighboringStations[k] = next;
                        k++;

                    }
                }
            }
        }
    }
}

/*

void findPath(MetroStation start, MetroStation finish, MetroStation path[]){

	MetroStation partialPath[SIZE];
	recursiveFindPath(start,finish,path,partialPath);

}

void recursiveFindPath( MetroStation start, MetroStation finish, MetroStation partialPath[],MetroStation bestPath[]){}

*/

MetroSystem istanbul = {"istanbul", '\0'};

int main(){ // main function to testing

    int i;
	double myX=1, myY=2;
	double goalX=62, goalY=45;

	MetroLine red={'\0'}, blue={'\0'}, green={'\0'};
	MetroStation s1, s2, s3, s4, s5, s6, s7, s8, s9;
	MetroStation myPath[SIZE]={'\0'};

	strcpy(red.color, "red");
	strcpy(blue.color, "blue");
	strcpy(green.color, "green");

	strcpy(s1.name, "Haydarpasa"); 		s1.x=0; 	s1.y=0;
	strcpy(s2.name, "Sogutlucesme"); 	s2.x=10; 	s2.y=5;
	strcpy(s3.name, "Goztepe"); 		s3.x=20; 	s3.y=10;
	strcpy(s4.name, "Kozyatagi"); 		s4.x=30; 	s4.y=35;
	strcpy(s5.name, "Bostanci"); 		s5.x=45; 	s5.y=20;
	strcpy(s6.name, "Kartal"); 			s6.x=55; 	s6.y=20;
	strcpy(s7.name, "Samandira"); 		s7.x=60; 	s7.y=40;
	strcpy(s8.name, "Icmeler"); 		s8.x=70; 	s8.y=15;

	addStation(&red, s1); addStation(&red, s2); addStation(&red, s3); addStation(&red, s4); addStation(&red, s5); addStation(&red, s8);

	addStation(&blue, s2); addStation(&blue, s3); addStation(&blue, s4); addStation(&blue, s6); addStation(&blue, s7);

	addStation(&green, s2); addStation(&green, s3); addStation(&green, s5); addStation(&green, s6); addStation(&green, s8);

    MetroStation path[SIZE]={s1,s2,s3,s4};
    MetroStation myNeighbors[SIZE]={'\0'};

    printf("------------------------------------------------------------------------------------------------\n");

	addLine(&istanbul, red);
	addLine(&istanbul, blue);
	addLine(&istanbul, green);

    printf("------------------------------------------------------------------------------------------------\n");

	printLine(red);
	printLine(blue);
	printLine(green);

    printf("------------------------------------------------------------------------------------------------\n");

	MetroStation nearMe = findNearestStation(istanbul, myX, myY);
	MetroStation nearGoal = findNearestStation(istanbul, goalX, goalY);

	printf("The best path from %s to %s is:\n", nearMe.name, nearGoal.name);

    printf("------------------------------------------------------------------------------------------------\n");

	if(equals(nearMe, nearGoal)){
		printf("Your target location and your current location are close to each other. It is better to walk!\n");
		return 0;
	}
	else{
        printf("Your target location and your current location are not close to each other. You should use metro system!\n");
	}

    printf("------------------------------------------------------------------------------------------------\n");

	printf("Boolean value of function hasStation: %d\n",hasStation(red,s1));         // test of valid option
    printf("Boolean value of function hasStation: %d\n",hasStation(blue,s8));        // test of invalid option

    printf("------------------------------------------------------------------------------------------------\n");

    printf("getFirstStop in line red: %s\n",getFirstStop(red).name);
    printf("getPreviousStop of %s in line red: %s\n",s3.name,getPreviousStop(red,s3).name);
    printf("getNextStop of %s in line red: %s\n",s3.name,getNextStop(red,s3).name);

    printf("------------------------------------------------------------------------------------------------\n");

    printf("Print path: \n");
    printPath(path);

    printf("------------------------------------------------------------------------------------------------\n");

    double distance=getDistanceTravelled(path);
    printf("Distance travelled: %.2f\n",(float)distance);

	/*
	findPath(nearMe, nearGoal, myPath);

	if(strlen(myPath[0].name) == 0)
		printf("There is no path on the metro!\n");
	else{
		printPath(myPath);
	}

	return 0;

	*/

}
