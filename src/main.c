/** 
* @author  Douglas Brandão
* @version 1.0
* @since   2020-10-24 
*/

#include <stdio.h>
#include <stdlib.h>

void writeInOutput(FILE* output, int integerAngle, float floatAngle,  float sin, float cos) {
  float pi = 3.14159;

  float angleInRad;

  if(integerAngle != -1)
    angleInRad = (integerAngle * pi)/180;
  else
    angleInRad = (floatAngle * pi)/180;

  if(integerAngle != -1)
    fprintf(output, "angle: %d°\n", integerAngle);
  else
    fprintf(output, "angle: %.*f°\n", 2, floatAngle);

  fprintf(output, "angle in rad: %f\n", angleInRad);
  fprintf(output, "sin = %f\n", sin);
  fprintf(output, "cos = %f\n\n", cos);
}

float findCos(int inferiorAngle, int superiorAngle, float inferiorCos, float superiorCos, float angle) {
    float slope = (superiorCos - inferiorCos) / (superiorAngle - inferiorAngle);

    float cos = ((angle - inferiorAngle) * slope) + inferiorCos;

    return cos;
}

float findSin(int inferiorAngle, int superiorAngle, float inferiorSin, float superiorSin, float inputSin) {
    float slope = (superiorSin - inferiorSin) / (superiorAngle - inferiorAngle);

    float angle = ((inputSin - inferiorSin) / slope) + inferiorAngle;
    
    return angle;
}

int isCloseEnough(float inputSin, float tableSin) {
  if(
    (inputSin < tableSin && inputSin / tableSin >= 0.999) || 
    (inputSin > tableSin && tableSin != 0 && inputSin / tableSin <= 1.001) || 
    inputSin == tableSin
  ) return 1;

  return 0;
}

void calculateOutput(float sin[], float cos[], int angles[], float inputSins[], int numberOfSins) {
    FILE* output = fopen("../files/senocosseno.txt", "w");

    for(int inputIndex = 0; inputIndex < numberOfSins; inputIndex++) {
      for(int tableIndex = 0; tableIndex <= 90; tableIndex++) {
        float inputSin = inputSins[inputIndex];

        if (
          isCloseEnough(inputSin, sin[tableIndex]) == 1 &&
          isCloseEnough(inputSin, sin[tableIndex+1]) != 1
        ) {
          writeInOutput(output, angles[tableIndex], -1, inputSin, cos[tableIndex]);
        }
        
        else if(isCloseEnough(inputSin, sin[tableIndex+1]) != 1) {
          float outputAngle;
          float outputCos;

          if(sin[tableIndex] < inputSin && sin[tableIndex+1] > inputSin) {
            outputAngle = findSin(
              angles[tableIndex], angles[tableIndex + 1], 
              sin[tableIndex], sin[tableIndex+1], inputSin
            );

            outputCos = findCos(
              angles[tableIndex], angles[tableIndex + 1], 
              cos[tableIndex], cos[tableIndex + 1], outputAngle
            );

            writeInOutput(output, -1, outputAngle, inputSin, outputCos);
          }
        }
      }
    }

}

void setTrigonometricTable(float sin[], float cos[], int angles[]) {
  FILE* trigonometricTable = fopen("../files/trigo.txt", "r");

  for(int index = 0; index <= 90; index++) {
    fscanf(trigonometricTable, "%d", &angles[index]);
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

void readInputSins(float array[], int numberOfElements) {
  FILE* file = fopen("../files/seno.txt", "r");

  for(int index = 0; index < numberOfElements; index++)
    fscanf(file, "%f", &array[index]);
}

int main() {
  float sin[91];
  float cos[91];

  int angles[91];
  int numberOfSins = getNumberOfSins();

  float inputSins[numberOfSins];

  readInputSins(inputSins, numberOfSins);

  setTrigonometricTable(sin, cos, angles);

  calculateOutput(sin, cos, angles, inputSins, numberOfSins);

  return 0;
}