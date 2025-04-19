#include "obstacle.h"

Obstacle::Obstacle(double x, double y){
    hitbox.x = x;
    hitbox.y = y;
    hitbox.width = OBSTACLE_LENGTH;
    hitbox.height = OBSTACLE_LENGTH;
}

Rectangle Obstacle::getHitbox(){
    return hitbox;
}

void Obstacle::draw(){
    DrawRectangleRec(hitbox, WHITE);
}

void Obstacle::move(double x, double y){
    hitbox.x += x;
    hitbox.y += y;
}