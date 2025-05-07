#include "projectile.h"

Projectile::Projectile(double speedX, double SpeedY, double x, double y, double radius, Color color, double damage){
    speed.x = speedX;
    speed.y = SpeedY;
    center.x = x;
    center.y = y;
    this->radius = radius;
    this->color = color;
    this->damage = damage;
}

void Projectile::draw(Texture2D texture) {
    // Calculate angle in degrees (Raylib uses degrees)
    float angle = atan2(speed.y, speed.x) * RAD2DEG;
    
    // Calculate the actual center point accounting for scaling
    Vector2 textureCenter = {
        center.x - (texture.width * 3.0f) / 2,
        center.y - (texture.height * 3.0f) / 2
    };
    
    // Define the rotation origin (center of texture)
    Vector2 origin = {
        (texture.width * 3.0f) / 2,
        (texture.height * 3.0f) / 2
    };
    
    // Draw rotated texture perfectly centered
    DrawTexturePro(
        texture,
        Rectangle{0, 0, (float)texture.width, (float)texture.height},
        Rectangle{center.x, center.y, texture.width * 3.0f, texture.height * 3.0f},
        origin,
        angle,
        WHITE
    );
    
    // Debug draw (remove in final version)
    DrawCircleV(center, radius, Fade(RED, 0.3f));
}

void Projectile::move(){
    center.x += speed.x;
    center.y += speed.y;
}

void Projectile::adjustSpeed(double x, double y){
    speed.x = x;
    speed.y = y;
}

void Projectile::setPosition(double x, double y){
    center.x = x;
    center.y = y;
}

double Projectile::getDamage(){
    return damage;
}

Vector2 Projectile::getSpeed(){
    return speed;
}

Vector2 Projectile::getCenter(){
    return center;
}

double Projectile::getRadius(){
    return radius;
}

Color Projectile::getColor(){
    return color;
}