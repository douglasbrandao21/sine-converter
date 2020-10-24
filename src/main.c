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

  while(fscanf(sinsFile, "%f", &aux) == 1)
    numberOfSins++;

  return numberOfSins;
}

void filesToArray(float *array, int numberOfElements) {
  FILE* file = fopen("../files/seno.txt", "r");

  int index;

  for(index = 0; index < numberOfElements; index++)
    fscanf(file, "%f", &array[index]);
}

void getTrigonometricTable(float *sin, float *cos, int *degrees) {
  FILE* trigonometricTable = fopen("../files/trigo.txt", "r");

  for(int index = 0; index <= 90; index++) {
    fscanf(trigonometricTable, "%d", &degrees[index]);
    fscanf(trigonometricTable, "%f", &sin[index]);
    fscanf(trigonometricTable, "%f", &cos[index]);
  }
}

int main() {
  int numberOfSins = getNumberOfSins();

  float inputSins[numberOfSins];

  int degrees[91];

  float sin[91];
  float cos[91];

  filesToArray(&inputSins[0], numberOfSins);

  getTrigonometricTable(&sin[0], &cos[0], &degrees[0]);

  return 0;
}