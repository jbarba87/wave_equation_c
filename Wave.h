#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

class Wave{

  private:
    float dt, dx;
    float t_end, x_end;
    float coef;
    float *b;
    Vector *data;
    Vector *x;
    Vector *t;
    Vector (*pf)(Vector); // Pointer to function (takes one Vector argument and return also a Vector argument )
    int NTimeVectors;
    int NPosElements;

  public:
    Wave(float, float, float, float, float, float*, Vector (*)(Vector));  
    Vector *getTimeVector(int);

    void Wave_Solve();
    void Wave_Plot(int);
    void Wave_nPlot(int);
};


