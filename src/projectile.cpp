#include "projectile.h"

Projectile::Projectile(float speedX, float SpeedY, float x, float y, float radius, Color color, float damage){
    speed.x = speedX;
    speed.y = SpeedY;
    center.x = x;
    center.y = y;
    this->radius = radius;
    this->color = color;
    this->damage = damage;
}

void Projectile::draw(Texture2D texture) {
    // Calculate angle in degrees
    float angle = atan2(speed.y, speed.x) * RAD2DEG;
    
    // Calculate scale factor based on radius (using the texture's diagonal for most accurate scaling)
    float textureDiagonal = sqrtf(texture.width*texture.width + texture.height*texture.height);
    float scale = (radius * 4.0f) / textureDiagonal;
    
    // Calculate the actual drawing parameters
    Vector2 origin = {texture.width / 2.0f, texture.height / 2.0f};
    Vector2 drawPosition = center; // Start from center point
    
    // Draw with perfect centering
    DrawTexturePro(
        texture,
        {0, 0, (float)texture.width, (float)texture.height},
        {
            drawPosition.x,  // X position (will be centered via origin)
            drawPosition.y,  // Y position (will be centered via origin)
            texture.width * scale,
            texture.height * scale
        },
        origin,  // This is what ensures perfect centering
        angle,
        WHITE
    );

    // Debug visualization - should perfectly match texture edges
    // DrawCircleV(center, radius, Fade(RED, 0.1f));
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

Color Projectile::getColor(){
    return color;
}