/** 
* @author  Douglas Brandão
* @version 1.0
* @since   2020-10-24 
*/

#include <stdio.h>
#include <stdlib.h>


int getNumberOfSins() {
  FILE* sinsFile = fopen("../files/seno.txt", "r");
  
  int numberOfSins = 0;
  float aux = 0;

  while(fscanf(sinsFile, "%f", &aux) == 1) {
    numberOfSins++;
  }

  return numberOfSins;
}

void getSins(float *sin, int numberOfSins) {
  FILE* sinsFile = fopen("../files/seno.txt", "r");

  int index;

  for(index = 0; index < numberOfSins; index++)
    fscanf(sinsFile, "%f", &sin[index]);
}

int main() {
  int numberOfSins = getNumberOfSins();

  float sin[numberOfSins];

  getSins(&sin[0], numberOfSins);

  return 0;
}