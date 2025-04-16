#include "obstacle.h"

Obstacle::Obstacle(int x, int y){
    position.x = x;
    position.y = y;
}

Vector2 Obstacle::getPosition(){
    return position;
}

void Obstacle::draw(){

}