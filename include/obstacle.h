#pragma once
#include "raylib.h"
#include "resource_dir.h"
#include "constants.h"
using namespace std;

const double OBSTACLE_LENGTH = 50;

const string OBSTACLE_PATTERN[][3][3] = {{{"O", "O", "O"},
                                          {"O", "X", "O"},
                                          {"X", "X", "X"}},

                                         {{"O", "O", "O"},
                                          {"O", "X", "X"},
                                          {"X", "X", "X"}},

                                         {{"O", "X", "O"},
                                          {"O", "X", "O"},
                                          {"O", "X", "O"}},

                                         {{"O", "O", "O"},
                                          {"X", "X", "O"},
                                          {"X", "X", "X"}},
                                        
                                         {{"X", "O", "O"},
                                          {"X", "X", "O"},
                                          {"X", "X", "X"}},

                                          {{"O", "O", "O"},
                                          {"X", "X", "X"},
                                          {"X", "X", "X"}},

                                          {{"O", "O", "X"},
                                          {"O", "X", "X"},
                                          {"X", "X", "X"}}};

class Obstacle{
    private:
        Rectangle hitbox;
    public:
        Obstacle(double x, double y);
        Rectangle getHitbox();
        void draw();
};