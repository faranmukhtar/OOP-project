#include "player.h"


Player::Player(double x, double y, double width, double height, int health){
    this->health = health;
    this->hitbox.x = x;
    this->hitbox.y = y;
    this->hitbox.height = height;
    this->hitbox.width = width;
    this->alive = true;
}

void Player::move(int x, int y){}

void Player::useWeapon(int x, int y){}

bool Player::isAlive(){
    return alive;
}

int Player::getHealth(){
    return health;
}

Rectangle Player::getHitbox(){
    return hitbox;
}

void Bomber::move(int x, int y){
    if (hasDroppedBomb) {
        hitbox.y -= moveSpeed; 
    }

    if (hitbox.y + hitbox.height < 0){  //dies when out of screen
        alive = false;
    }

}

void Bomber::useWeapon(int x, int y){
    if (!alive) return;
    timer += GetFrameTime();

    if(timer >= bombInterval && !hasDroppedBomb){
        hasDroppedBomb = true;
        //return projectile object
    }

}

void Bomber::draw(){
    if(alive){
        DrawRectangleRec(hitbox, GREEN);
    }
}

void Bomber::takeDamage(){
    if(hasDroppedBomb) alive = false;
}

void Gunner::move(int x, int y){   //moves under defined intervals
    timer += GetFrameTime();   
    if (timer >= moveInterval){
        moveDirection*= -1;
        timer = 0;
    }
    hitbox.x += moveDirection * 1.5f;
}

void Gunner::useWeapon(int x, int y){  
    if(!alive) return; 

    shootTimer += GetFrameTime();  //shoots under defined intervals
    if(shootTimer >= shootInterval){
        shootTimer = 0;
        //return projectile object
    }
}

void Gunner::draw(){
    if(alive){
        DrawRectangleRec(hitbox, BLUE);
    }
}

void Gunner::takeDamage(){
    health--;
    if (health <= 0) {
        alive = false;
    }
}

void User::draw(){
    DrawRectangleRec(hitbox, BLUE);
}

void User::jump(){}