#include "player.h"

Player::Player(int x, int y, int h, Weapon* w){
    this->health = h;
    this->weapon = w;
    position.x = x;
    position.y = y;
};

void Player::assignWeapon(Weapon* w){
    weapon = w;
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

Vector2 Player::getPosition(){
    return position;
}

void Player::draw(){

}

void User::jump(){

}