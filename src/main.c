/** 
* @author  Douglas Brandão
* @version 1.0
* @since   2020-10-24 
*/

#include <stdio.h>
#include <stdlib.h>

void writeInOutput(FILE* output, int angle, float sin, float cos) {
  float pi = 3.14159;

  float angleInRad = (angle * pi)/180;

  fprintf(output, "Rad: %f\n", angleInRad);
  fprintf(output, "Cos: %f\n", sin);
  fprintf(output, "Sin: %f\n", cos);
  fprintf(output, "--------------\n");
}

void calculateOutput(
  float *inputSins, 
  float *sin, 
  float *cos, 
  int *degrees, 
  int numberOfSins
  ) {
    FILE* output = fopen("../files/senocosseno.txt", "w");

    for(int inputIndex = 0; inputIndex < numberOfSins; inputIndex++) {
      for(int tableIndex = 0; tableIndex <= 90; tableIndex++) {
        float inputSin = inputSins[inputIndex];
        float tableSin = sin[tableIndex];
        
        if(
          (inputSin < tableSin && inputSin / tableSin >= 0.999) || 
          (inputSin > tableSin && inputSin / tableSin <= 1.001) || 
          inputSin == tableSin
        ) {
          writeInOutput(output, degrees[tableIndex], sin[tableIndex], cos[tableIndex]);
        }
      }
    }

}

void setTrigonometricTable(float *sin, float *cos, int *degrees) {
  FILE* trigonometricTable = fopen("../files/trigo.txt", "r");

  for(int index = 0; index <= 90; index++) {
    fscanf(trigonometricTable, "%d", &degrees[index]);
    fscanf(trigonometricTable, "%f", &sin[index]);
    fscanf(trigonometricTable, "%f", &cos[index]);
  }
}

int getNumberOfSins() {
  FILE* sinsFile = fopen("../files/seno.txt", "r");
  
  int numberOfSins = 0;
  float aux = 0;

  while(fscanf(sinsFile, "%f", &aux) == 1)
    numberOfSins++;

  return numberOfSins;
}

void readSins(float *array, int numberOfElements) {
  FILE* file = fopen("../files/seno.txt", "r");

  for(int index = 0; index < numberOfElements; index++)
    fscanf(file, "%f", &array[index]);
}

int main() {
  int degrees[91];

  float sin[91];
  float cos[91];

  int numberOfSins = getNumberOfSins();

  float inputSins[numberOfSins];

  readSins(&inputSins[0], numberOfSins);

  setTrigonometricTable(&sin[0], &cos[0], &degrees[0]);

  calculateOutput(&inputSins[0], &sin[0], &cos[0], &degrees[0], numberOfSins);

  return 0;
}