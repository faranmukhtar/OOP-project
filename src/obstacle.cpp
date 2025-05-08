#include "obstacle.h"

Obstacle::Obstacle(float x, float y){
    hitbox.x = x;
    hitbox.y = y;
    hitbox.width = OBSTACLE_LENGTH;
    hitbox.height = OBSTACLE_LENGTH;
}

Rectangle Obstacle::getHitbox(){
    return hitbox;
}

void Obstacle::draw(Texture2D texture) {
    //Mapping the texture onto the hitbox
    DrawTexturePro(texture, Rectangle{0, 0, (float)texture.width, (float)texture.height}, hitbox, Vector2{0, 0}, 0.0f, WHITE);
}

void Obstacle::move(float x, float y){
    hitbox.x += x;
    hitbox.y += y;
}