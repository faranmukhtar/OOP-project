#include "projectile.h"

Projectile::Projectile(float speedX, float SpeedY, float x, float y, float radius, float damage){
    speed.x = speedX;
    speed.y = SpeedY;
    center.x = x;
    center.y = y;
    this->radius = radius;
    this->damage = damage;
}

void Projectile::draw(Texture2D texture) {
    // calculate angle
    float angle = atan2(speed.y, speed.x) * RAD2DEG;
    
    //using texture diagonal for better scaling
    float textureDiagonal = sqrtf(texture.width*texture.width + texture.height*texture.height);
    float scale = (radius * 4.0f) / textureDiagonal;
    
    //center from where the projectile will be rotated
    Vector2 origin = {texture.width / 2.0f, texture.height / 2.0f};

    //saving texture dimensions
    Rectangle source = {
        0,
        0, 
        (float)texture.width, 
        (float)texture.height
    };

    //saving location dimensions
    Rectangle dest = {
        center.x, 
        center.y,
        texture.width * scale,
        texture.height * scale
    };
    
    DrawTexturePro(texture, source, dest, origin, angle, WHITE);
}

void Projectile::move(){
    center.x += speed.x;
    center.y += speed.y;
}

void Projectile::adjustSpeed(float x, float y){
    speed.x = x;
    speed.y = y;
}

void Projectile::setPosition(float x, float y){
    center.x = x;
    center.y = y;
}

float Projectile::getDamage(){
    return damage;
}

Vector2 Projectile::getSpeed(){
    return speed;
}

Vector2 Projectile::getCenter(){
    return center;
}

float Projectile::getRadius(){
    return radius;
}
