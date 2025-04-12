#include "classes.h"

// Might have to seperate all the classes here to seperate files

//Might have to change attributes for specialized weapons

Weapon::Weapon(int a){
    this->maxAmmo = ammo;
}

//Returns probably a projectile object. Check later
void Weapon::shoot(){

};

//Unsure whether this is needed
void Weapon::reload(){

}

int Weapon::getAmmo(){
    return ammo;
}

Player::Player(int x, int y, int h, Weapon* w){
    this->health = h;
    this->weapon = w;
    position.x = x;
    position.y = y;
};

void Player::assignWeapon(Weapon*){

};

void Player::move(int x, int y){

};

Vector2 Player::getPosition(){
    return position;
}

//Setup different types of obstacles later
Obstacle::Obstacle(int x, int y){
    position.x = x;
    position.y = y;
}

Vector2 Obstacle::getPosition(){
    return position;
}