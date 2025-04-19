#include "projectile.h"

Projectile::Projectile(double speedX, double SpeedY, double x, double y, double radius, Color color){
    speed.x = speedX;
    speed.y = SpeedY;
    center.x = x;
    center.y = y;
    this->radius = radius;
    this->color = color;
}

void Projectile::drawProjectile(){
    void DrawCircleV(Vector2 center, float radius, Color color);
}

void Projectile::move(){
    center.x += speed.x;
    center.y += speed.y;
}

void Projectile::adjustSpeed(double x, double y){
    speed.x = x;
    speed.y = y;
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