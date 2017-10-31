#include <iostream>
#include <stdio.h>    
#include <stdlib.h>   
#include <time.h>  

using namespace std;

int main()
{
	srand (time(NULL));
	
//declare map values
	int axisx = 30;
	int axisy = 30;
	int terrainmap[axisx][axisy][2];

//fill map with boolean values	
	for (int i = 0; i < axisx; i++) {
		for (int j = 0; j < axisy; j++) {
			
			terrainmap[i][j][0] = rand()%2;
			terrainmap[i][j][1] = 1;
		}
	}
	
//print map as grid
	cout << "\n Perlin noise map\n ";
	for (int i = 0; i < axisx; i++) {
		for (int j = 0; j < axisy; j++) {
			
			cout << terrainmap[i][j][0] << " ";
			
			if (j == axisy - 1) {
				cout << "\n ";
			}
		}
	}
	cout << "\n";
	
//smooth map
	for (int loop = 0; loop < 3; loop++) {
		for (int i = 1; i < axisx - 1; i++) {
			for (int j = 1; j < axisy - 1; j++) {			
					
				if ((terrainmap[i - 1][j - 1][0] +
				terrainmap[i][j - 1][0] +
				terrainmap[i + 1][j - 1][0] +
				terrainmap[i - 1][j][0] +
				terrainmap[i + 1][j][0] +
				terrainmap[i - 1][j + 1][0] +
				terrainmap[i][j + 1][0] +
				terrainmap[i + 1][j + 1][0]) > 4) {
				
					terrainmap[i][j][1] = 1;
					
				} else {
					terrainmap[i][j][1] = 0;
				}
			}
		}
		for (int i = 0; i < axisx; i++) {
			for (int j = 0; j < axisy; j++) {
				terrainmap[i][j][0] = terrainmap[i][j][1];
			}
		}
	}
	
//print map as grid
	cout << " Post automata map\n ";
	for (int i = 0; i < axisx; i++) {
		for (int j = 0; j < axisy; j++) {
			
			cout << terrainmap[i][j][1] << " ";
			
			if (j == axisy - 1) {
				cout << "\n ";
			}
		}
	}
	cout << "\n";
	
	return 0;
}

	
#pragma once
#include <iostream>
#include <stdio.h>    
#include <stdlib.h> 
using namespace std;
//declare map values

int maxaxisx = 0;
int maxaxisy = 0;
int mapSeedBase = 0;
int roomCenterX = 0;
int roomCenterY = 0;
int roomWidth = 0;
int roomHeight = 0;




////--------------special map functions-----

int getUserMapData(){
	
	while((maxaxisx <= 19)||(maxaxisx >= 65)){
			cout << "you will be prompted to answer questions in number format\n please no letters"<<endl;
			cout << "choose a map width \n 20-64"<<endl;

			cin >> maxaxisx;
		
		}
		
		while((maxaxisy <= 19)||(maxaxisy >= 65)){
			cout << "choose a map height \n 20-64"<<endl;
	
			cin >> maxaxisy;
		}
		
		cout << "choose a map seed\n 0 for random"<<endl;

		cin >> mapSeedBase;
		 if (mapSeedBase == 0){
			 mapSeedBase = rand();	 
		}
		srand (mapSeedBase);
		
		cout << mapSeedBase<<endl;
		return 0;
}
////--------------the map class-----

class Map{
	
	public:
	
		Map(){
			setMapDimensionX(maxaxisx);
			setMapDimensionY(maxaxisy);
			setMapSeed(mapSeedBase);
			
			//----------------------display map properties----------------
			cout <<"the Map dimensions will be "<< getMapDimensionX()<<" wide and "<<getMapDimensionY()<<" tall"<<endl;
			cout <<"with a seed number of "<<getMapSeed()<<endl;
		
		};

		
		//---------------------fill map layer with given value---------------------
		void fillMap(int layer, int fillNumber);
		/*
		void fillMap(int layer, int fillNumber){
			cout << "\n fill map with "<<fillNumber<<"\n";
			for(int i=0;i< getMapDimensionX(); i++){
				for(int j=0;j< getMapDimensionY(); j++){
					setMapArray(i, j, layer, fillNumber);
				}
			}
		}; 
		*/
		//---------------------fill map layer with binary noise---------------------
		void fillMapNoise(int layer, int fillRange){
			cout << "\n fill map with noise from 0 to "<<fillRange <<"\n";
			int noiseValue;
			for(int i=0;i< getMapDimensionX(); i++){
				for(int j=0;j< getMapDimensionY(); j++){
					noiseValue=rand()%(fillRange+1);
					setMapArray(i, j, layer, noiseValue );
				}
			}
		}; 
		
		
		//---------------------smooth out the binary noise maps
		void smoothMap(int layerGet, int layerSet, int neighborCount){
				for (int i = 1; i < getMapDimensionX() - 1; i++) {
					for (int j = 1; j < getMapDimensionY() - 1; j++) {			
							
						if(getMapArray(i - 1,j - 1,layerGet) +
							getMapArray(i,j - 1,layerGet) +
							getMapArray(i + 1,j - 1,layerGet) +
							getMapArray(i - 1,j ,layerGet) +
							getMapArray(i + 1,j ,layerGet) +
							getMapArray(i - 1,j + 1,layerGet) +
							getMapArray(i,j + 1,layerGet) +
							getMapArray(i + 1,j + 1,layerGet) 
							> neighborCount)
							{
							
								setMapArray(i,j,1,1);
							
						}

					}
				}
				
		};
		//---------------------smooth out the binary noise maps
		void killLoners(int layerGet, int layerSet, int neighborCount){
				for (int i = 1; i < getMapDimensionX() - 1; i++) {
					for (int j = 1; j < getMapDimensionY() - 1; j++) {			
							
						if(getMapArray(i - 1,j - 1,layerGet) +
							getMapArray(i,j - 1,layerGet) +
							getMapArray(i + 1,j - 1,layerGet) +
							getMapArray(i - 1,j ,layerGet) +
							getMapArray(i + 1,j ,layerGet) +
							getMapArray(i - 1,j + 1,layerGet) +
							getMapArray(i,j + 1,layerGet) +
							getMapArray(i + 1,j + 1,layerGet) 
							< neighborCount)
							{
							
								setMapArray(i,j,1,0);
							
						} 
					
					}
				}
		};
		
//		//-----------------------find contiguous zones
//		void findZones(int layerGet, int layerSet, int zoneSet, int zoneMap) {
//			for (int i = 0; i < getMapDimensionX; i++) {
//				for (int j = 0; j < getMapDimensionY; j++) {
//					
//				}
//			}
//		}
		
		
		
		
		
		
		
		//--------------------print the map
		
		void printMap(int layer){
			cout << "\n print the map";
			int scanValue;
		
			for(int i=0;i< getMapDimensionX(); i++){
				cout << endl;
				for(int j=0;j< getMapDimensionY(); j++){
					
					
					scanValue=getMapArray(i, j, layer);
					
					switch(scanValue){
 
						case 0 :
							cout << "0 ";
							break;
					
						case 1 :
							cout << "1 ";
							break;
					
						case 2 :
							cout << "2 ";
							break;
					
						default :
							cout << "  ";
						}
				}
			}
			cout << endl;
		};
		//--------------------print the map fancy
		
		void printMapFancy(int layer){
			cout << "\n print the map";
			cout << endl;
			int scanValue;
		
			for(int i=0;i< getMapDimensionX(); i++){
				
				for(int j=0;j< getMapDimensionY(); j++){
					
					
					scanValue=getMapArray(i, j, layer);
					
					switch(scanValue){
 
						case 0 :
							cout << (char)178u<<(char)178u;
							break;
					
						case 1 :
							cout << (char)176u<<(char)176u;
							break;
					
						case 2 :
							cout << "2 ";
							break;
					
						default :
							cout << "  ";
						}
				}
			cout << endl;
			}
			cout << endl;
		}; 
		
		
		
		
		
		
		
		
		
		
		
		//---------------------setters and getters ---------------------
		//---------------------the width of the map
		void setMapDimensionX(int xDimension){
			mapDimensionX = xDimension;
		}
		int getMapDimensionX(){
			return mapDimensionX;
		}
		//---------------------the height of the map
		void setMapDimensionY(int yDimension){
			mapDimensionY = yDimension;
		}
		int getMapDimensionY(){
			return mapDimensionY;
		}
		//---------------------the seed number of the map
		void setMapSeed(int seedNumber){
			mapSeed = seedNumber;
		}
		int getMapSeed(){
			return mapSeed;
		}
		//---------------------the array
		void setMapArray(int xScan, int yScan, int layerScan, int value){
			mapArray[xScan][yScan][layerScan]= value;
		}
		int getMapArray(int xScan, int yScan, int layerScan){
			return mapArray[xScan][yScan][layerScan];
		}
	
	
	private:
	
		int mapDimensionX;
		int mapDimensionY;
		int mapSeed;
		int mapArray[64][64][4];
		
	protected:
	
	
};
	
	
#include "stdafx.h"

#include <iostream>
#include <stdio.h>    
#include <stdlib.h>   
#include <time.h>  
#include <limits>  
#include <sstream>

#include "mapHandler.h"

using namespace std;


void Map::fillMap(int layer,int fillNumber){
	
	for(int i=0;i< getMapDimensionX(); i++){
		for(int j=0;j< getMapDimensionY(); j++){
		setMapArray(i, j, layer, fillNumber);
		}
	
	
	}
}
/*
void Map::printMap(int layer){
	
	for(i=0;i< getMapDimensionX(); i++){
		for(j=0;j< getMapDimensionY(); j++){
			
			
		}
	}
	
	
}


//gameActive = displayTitleScreen(0,0,0,3); // display the title screen with version numbers
//	
//	gameStartTime = clock();
//	srand (time(NULL));
//	
//	bool gameActive;
//int playTicks;
//int maxGameTicks;
//int gameStartTime;
//
//#include <iostream>
//#include <stdio.h>   
//#include <windows.h> 
//
//#include <stdlib.h>   
//#include <time.h>  
//#include <limits>  
//#include <sstream>
////gui headers
//#include "titleScreen.h"
////logic headers
//#include "mapHandler.h"


if (gameActive == true){
	
	
		//TODO: make initial map
		getUserMapData();
		
			
		Map firstMap;
		firstMap.fillMap(0,0);
		firstMap.fillMap(1,0);
		firstMap.printMap(0);
		firstMap.fillMapNoise(0,1);
		firstMap.printMap(0);
		firstMap.smoothMap(0,1,4);
		firstMap.printMap(1);
		firstMap.killLoners(1,1,3);
		firstMap.printMap(0);
		firstMap.smoothMap(0,1,4);
		firstMap.printMap(1);
		firstMap.smoothMap(0,1,3);
		firstMap.printMap(1);
		firstMap.killLoners(1,1,3);
		firstMap.printMap(1);
		firstMap.smoothMap(1,1,6);
		firstMap.printMap(1);
		
			system("pause");
		system("CLS");
		//--------BEGIN GAME----------------------------
		while (gameActive == true){
			firstMap.printMapFancy(1);
			/*
			---------------------code block for time monitoring and testing------------
			
			playTicks++;
			cout << "gameTicks = " <<playTicks<< "    gameTime = " <<clock()<< endl;
			if (playTicks >= maxGameTicks){
				gameActive = false;
			}
			cout << gameStartTime<< endl;
			cout << clock()<< endl;
			----------------------------------------------------------------------------
			*/
			gameActive = false;
		}
	}
	
	//header file for splash screens at the begining and ending of play
#pragma once
#include <windows.h> 

using namespace std;


// display the splash screen and prompt player on wether they wanna be here and such
// returns a boolean result true being
bool displayTitleScreen(int vNRelease,int vNInternal,int vNAsset,int vNScript) // the four inputs are the versions
{
	
	char playerTitleDecision;
	bool playerTitleResult = false;
	
	
	system("CLS");
	cout << "                                                          Trevor Haggerty & Zachary Drummond's    "<< endl;
	cout << "   #############################################################################################  "<< endl;
	cout << "        -             -                   -             -                       -                 "<< endl;
	cout << "   ##  ##     ##  -  ####     ##   ########  ######        ####  ##  ##  ######   ####     ####   "<< endl;
	cout << "   ## ##   - ## ##   ##  ##  ## ##    ##     ##          ##      ##  ##  ##      ##  ##   ##  ##  "<< endl;
	cout << "   ####   -  #####   ####    #####    ##     ####   -   ##       ######  ####     ##       ##     "<< endl;
	cout << "   ##  ##   ##   ##  ##  ## ##   ##   ##     ##         ##       ##  ##  ##         ##       ##   "<< endl;
	cout << "   ##  ##   ##   ##  ##  ## ##   ##   ##     ##          ##      ##  ##  ##      ##  ##   ##  ##  "<< endl;
	cout << "   ##  ## - ##   ##  ##  ## ##   ##   ##     ######        ####  ##  ##  ######   ####     ####   "<< endl;
	cout << "       -                    -                      -            -                                 "<< endl;
 	cout << "   #############################################################################################  "<< endl;
	cout << "   version "<< vNRelease <<"."<< vNInternal <<"."<< vNAsset<<"."<< vNScript <<"\n\n\n"<< endl;
	 
	 
	 //ask the player if they would like to play and read the results for a y,Y,n,or N
	 while ((playerTitleDecision != 'y')&&(playerTitleDecision != 'Y')&&(playerTitleDecision != 'n')&&(playerTitleDecision != 'N')){
		cout << " Would you like to play (y/n) "<<endl;
		cin >> playerTitleDecision;
	 }
	 
	  system("CLS");
	 //if the player said yes set the bool to yes telling the game to start
	 if ((playerTitleDecision == 'y')||(playerTitleDecision == 'Y')){
		 playerTitleResult = true;
	 } else{
	 //if the player is lame and doesnt want to play our game they can leave
		  playerTitleResult = false; 
	 }
	 
	 //return if the player is wanting to play the game and thus cool or not
	return playerTitleResult;
	 
	 
	
}


	 //display the exiting splash screen
int displayEndScreen(float playTime)
{
	system("CLS");
	 cout << "   #############################################################################################"<< endl;
	 cout << "                                                                                                "<< endl;
	 cout << "               ####       ####         ####     ####       ######   ##  ##   ######             "<< endl;
	 cout << "             ##         ##    ##     ##    ##   ##  ##     ## ##    ##  ##   ##                 "<< endl;
	 cout << "            ##         ##      ##   ##      ##  ##   ##    ####     ######   ####               "<< endl;
	 cout << "            ##  ####   ##      ##   ##      ##  ##   ##    ##  ##     ##     ##                 "<< endl;
	 cout << "             ##   ##    ##    ##     ##    ##   ##  ##     ##  ##     ##     ##                 "<< endl;
	 cout << "               ####       ####         ####     ####       ######     ##     ######             "<< endl;
	 cout << "                                                                                                "<< endl;
	 cout << "   #############################################################################################"<< endl;
	 cout << "   you played "<< playTime<<" 'seconds'"<< endl;
	return 0;
}
