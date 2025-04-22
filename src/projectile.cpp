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

void Projectile::draw(){ 
    DrawCircleV(center, radius, color);
}

void Projectile::move(){
    center.x += speed.x;
    center.y += speed.y;
}

void Projectile::adjustSpeed(double x, double y){
    speed.x = x;
    speed.y = y;
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