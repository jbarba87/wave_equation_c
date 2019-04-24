#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <unistd.h>


using namespace std;

class Vector{

  private:
    float *data;
    int Ndata;
  public:
    Vector(int);
    Vector(float, float, float);
    int getNdata();
    float getData(int);
    void setData(float, int);
    int getbigger();
    int getlower();
    void show();
    void plot();

};
