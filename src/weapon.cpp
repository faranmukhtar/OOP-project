#include <weapon.h>

Weapon::Weapon(int a){
    this->maxAmmo = ammo;
}

void Weapon::shoot(){

};

//Unsure whether this is needed. The idea is that the opponent self destructs if it runs out of ammo but the user character might reload or discard the weapon
void Weapon::reload(){

}

int Weapon::getAmmo(){
    return ammo;
}