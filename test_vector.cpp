#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <unistd.h>
#include"Vector.h"

using namespace std;
// g++ -o test_vector test_vector.cpp Vector.cpp

int main(){

  Vector a(0., 1., 0.1);
  Vector b(0., 1., 0.1);
//  a.show();

 a.plot();
 b.plot();


//  fprintf(pipe, "plot abs(sin(x))\n");
/*
fprintf(pipe, "plot '-' w lp \n"  );
fprintf(pipe, "1 1\n"  );
fprintf(pipe, "2 4\n"  );
fprintf(pipe, "3 9\n"  );
fprintf(pipe, "4 16\n"  );
fprintf(pipe, "5 25\n"  );
fprintf(pipe, "e\n"  );
*/

//  pipe << "plot '-' w lp" << endl << "1 1" << endl << "2 4" << endl << "3 9" << endl << "e" << endl;








  return 0;
}
