#include "classes.h"

//------------------Weapon------------------------//
Weapon::Weapon(int a){
    this->maxAmmo = ammo;
}

//Returns probably a projectile object. Check later
void Weapon::shoot(){

};

//Unsure whether this is needed. The idea is that the opponent self destructs if it runs out of ammo but the user character might reload or discard the weapon
void Weapon::reload(){

}

int Weapon::getAmmo(){
    return ammo;
}

//------------------Player------------------------//
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

//------------------Obstacle------------------------//
Obstacle::Obstacle(int x, int y){
    position.x = x;
    position.y = y;
}

Vector2 Obstacle::getPosition(){
    return position;
}

void Obstacle::draw(){

}