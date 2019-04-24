
#include "Vector.h"
#include "Wave.h"

#define DELAY 100000

Wave::Wave(float _dt, float _dx, float _t_end, float _x_end, float _coef, float *_b, Vector (*_t0)(Vector)){

  int i;

  this->dt = _dt;
  this->dx = _dx;
  this->t_end = _t_end;
  this->x_end = _x_end;
  this->coef = _coef;
  this->b = _b;
  this->pf = _t0;

  // Generating time and space vectors
  Vector x(0., _x_end, dx);
  Vector t(0., _t_end, dt);

  this->x = &x;
  this->t = &t;
  this->NTimeVectors = t.getNdata();
  this->NPosElements = x.getNdata();

  // Allocating memory (pointer to time vectors)
  Vector *_data = (Vector *) malloc(sizeof(Vector) * t.getNdata());

  // Allocating memory for each vector time (each step time)
  Vector *aux;
  for (i=0; i<this->NTimeVectors; i++){
    aux = new Vector(this->NPosElements);
    _data[i] = *aux;
  }


  // Initial conditions   x = (*_t0)(x);   x = (*this->pf)(x);
  _data[0] = (*this->pf)(x);

  this->data = _data;

}


Vector *Wave::getTimeVector(int pos){
  return (this->data + pos);
}




void Wave::Wave_Plot(int max_height){

  int i, j;

  FILE *pipe = popen("gnuplot ", "w");
  
  Vector *vec;

  for (i=0; i<this->NTimeVectors; i+=20){

    fprintf(pipe, "plot '-' w lp \n"  );

    vec = this->getTimeVector(i);

    // Plotting each graph
    for (j=0; j<this->NPosElements; j++){
      fprintf(pipe, "%f %f\n", j*this->dx, vec->getData(j)  );
    }
    fprintf(pipe, "e\n"  );

    // Setting title and axis

    fprintf(pipe, "set title 'Time: %f' \n",  i*this->dt );
    fprintf(pipe, "set xlabel 'Distance x'\n set ylabel 'Distance y'\n");
    fprintf(pipe, "set xrange [0:%f]\n", this->x_end);
    fprintf(pipe, "set yrange [-1.5:1.5]\n"  );


    fflush(pipe);
    usleep(DELAY);

  }

  fclose(pipe);

}




void Wave::Wave_Solve(){

  float c = this->coef * this->dt / this->dx;

  int i, j;
  float aux;

  Vector *past;
  Vector *present = this->getTimeVector(0);
  Vector *future = this->getTimeVector(1);
  
  future->setData(b[0], 0);
  future->setData(b[1], NPosElements);

  for (j = 1; j < (NPosElements - 1); j++){
    aux = c*c*( present->getData(j+1) - 2*present->getData(j) + present->getData(j-1) )
          + 2*present->getData(j) - present->getData(j);
    future->setData(aux, j);
  }


  for (i = 1; i < (NTimeVectors - 1); i++){
    past = present;
    present = future;
    future = this->getTimeVector(i+1);

    future->setData(b[0], 0);
    future->setData(b[1], NPosElements);

    for (j = 1; j < (NPosElements - 1); j++){
      aux = c*c*( present->getData(j+1) - 2*present->getData(j) + present->getData(j-1) )
            + 2*present->getData(j) - past->getData(j);
      future->setData(aux, j);
    }


  }

}


void Wave::Wave_nPlot(int max_height){

  int row,col;
  int i, j;

  Vector *vec;

  initscr();

  getmaxyx(stdscr,row,col);
  int space = (int) ( ((float) col)/( (float) vec->getNdata()) );


  int alt;
  int mx = row/2;
  float factor = mx/max_height;


  for (i=0; i<this->NTimeVectors; i+=20){

    vec = this->getTimeVector(i);
    clear();

    // Title
    mvprintw( 0, 0, "Time: %f", i*this->dt);


    for (j = 0; j<vec->getNdata(); j++){

      alt = mx - (int) factor*vec->getData(j);
      mvprintw( alt, j*space, "x");
      refresh();

      
    }
    usleep(DELAY);
  }



  endwin();
}







