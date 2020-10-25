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

  fprintf(output, "Angle: %d\n\n", angle);
  fprintf(output, "Rad: %f\n", angleInRad);
  fprintf(output, "Sin: %f\n", sin);
  fprintf(output, "Cos: %f\n", cos);
  fprintf(output, "--------------\n");
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

void calculateOutput(float sin[], float cos[], int angles[], float inputSins[], int numberOfSins) {
    FILE* output = fopen("../files/senocosseno.txt", "w");

    for(int inputIndex = 0; inputIndex < numberOfSins; inputIndex++) {
      for(int tableIndex = 0; tableIndex <= 90; tableIndex++) {
        float inputSin = inputSins[inputIndex];
        float tableSin = sin[tableIndex];
        
        if(
          (inputSin < tableSin && inputSin / tableSin >= 0.999) || 
          (inputSin > tableSin && tableSin != 0 && inputSin / tableSin <= 1.001) || 
          inputSin == tableSin
        ) {
          writeInOutput(output, angles[tableIndex], inputSin, cos[tableIndex]);
        }
        else {
          float outputAngle;
          float outputCos;

          float inferiorSin = sin[tableIndex];
          float superiorSin = sin[tableIndex + 1];

          float inferiorCos = cos[tableIndex];
          float superiorCos = cos[tableIndex + 1];

          int inferiorAngle = angles[tableIndex];
          int superiorAngle = angles[tableIndex + 1];

          if(inferiorSin < inputSin && superiorSin > inputSin) {
            outputAngle = findSin(inferiorAngle, superiorAngle, inferiorSin, superiorSin, inputSin);
            outputCos = findCos(inferiorAngle, superiorAngle, inferiorCos, superiorCos, outputAngle);

            writeInOutput(output, outputAngle, inputSin, outputCos);
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