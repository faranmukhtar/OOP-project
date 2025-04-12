#pragma once
#include "raylib.h"
#include "resource_dir.h"
#include "classes.h"

//Game logic goes here
class Game{
    private:
        User user;
        vector<Enemy*> enemies;
        vector<Obstacle*> obstacles;
};