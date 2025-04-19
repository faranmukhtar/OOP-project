#include "player.h"

Player::Player(double x, double y, double width, double height, int health){
    this->health = health;
    this->hitbox.x = x;
    this->hitbox.y = y;
    this->hitbox.height = height;
    this->hitbox.width = width;
};

void Player::move(int x, int y){

};

//Recheck later
void Player::useWeapon(int x, int y){

}

bool Player::isAlive(){
    return health == 0;
}

int Player::getHealth(){
    return health;
}

Rectangle Player::getHitbox(){
    return hitbox;
}

void User::draw(){
    DrawRectangleRec(hitbox, BLUE);
}

void User::jump(){

}