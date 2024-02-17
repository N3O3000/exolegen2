#include "data.hpp"
#include "utils.hpp"
#include "movement.hpp"


RobotData PositionData;
const MazeSquare* actuelCase;
const MazeSquare* arroundMe[5][5];

Position Checker::SeeRocket(Gladiator *gladiator, int x,int y){
    const MazeSquare* rocketPosition[1][1];
    if (arroundMe[x][y]->coin.value== 1){
        rocketPosition[1][1] = arroundMe[x][y];
    Position pos = {x,y};

        return pos;
    }
}


void Checker::LookAround(Gladiator *gladiator){
    actuelCase = gladiator->maze->getNearestSquare();
    for (size_t i = 0; i < 5; i++)
    {
        for (size_t j = 0; j < 5; j++)
        {
            arroundMe[i][j]= gladiator->maze->getSquare(i,j);

            if (arroundMe[i][j]->eastSquare!=NULL){
                // you can go to...
                
            }
            if (arroundMe[i][j]->northSquare!=NULL){
                // you can go to ...
            }
            if (arroundMe[i][j]->southSquare!=NULL){
                // you can go to ...
            }
            if (arroundMe[i][j]->westSquare!=NULL){
                // you can go to ...
            }
        }   
    }

}


