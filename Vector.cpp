#include"Vector.h"


// Constructor #1: 
// Return vector with _Ndata elements
Vector::Vector(int _Ndata){
  this->data = new float[_Ndata];
  this->Ndata = _Ndata;
};

// Constructor #2: 
// Return a vector with equaly spaced elements (steps)
Vector::Vector(float start, float end, float step){
  int i, ndata = int( (end - start)/step) + 1;
  this->Ndata = ndata;
  this->data = new float[ndata];

  float dat;

  for (i = 0; i<this->Ndata; i++){
    dat =  ((float) i)*step;
    this->setData(dat , i);
  }

}

// Getters y Setters

int Vector::getNdata(){
  return this->Ndata;
}

float Vector::getData(int pos){
  return this->data[pos];
}

void Vector::setData(float x, int pos){
  this->data[pos] = x;
}


int Vector::getbigger(){

  int ndata = this->Ndata;
  int i;
  float max = 0.0;
  float aux = 0.0;

  for (i=0; i<ndata; i++){
    aux = this->getData(i);

    if (aux > max){
      max = aux; 
      break;   
    }
  }
  return i;
}




int Vector::getlower(){

  int ndata = this->Ndata;
  int i;
  float min = 0.0;
  float aux = 0.0;

  for (i=0; i<ndata; i++){
    aux = this->getData(i);

    if (aux < min){
      min = aux; 
      break;   
    }
  }
  return i;
}




// Method Show: Print the values of the vector
void Vector::show(){
  int i, Ndata = this->Ndata;

  float *data = this->data;

  for(i=0;i<Ndata; i++){
    std::cout << this->getData(i) << std::endl;
  }
  std::cout << std::endl;
}

// Method plot: Plot the vector using Gnuplot
void Vector::plot(){

  FILE *pipe = popen("gnuplot -persist", "w");

  int i;
  fprintf(pipe, "plot '-' w lp \n"  );
  
  for (i=0; i<this->getNdata(); i++){
    fprintf(pipe, "%i %f\n", i, this->getData(i)  );
  }
  fprintf(pipe, "e\n"  );

  fflush(pipe);
  fclose(pipe);

}

