/** 
* @author  Douglas Brandão
* @version 1.0
* @since   2020-10-24 
*/

#include <stdio.h>
#include <stdlib.h>


/**
   * This function writes the resulting values ​​to the output file.
   * @param output Output file.
   * @param integerAngle Angle value in degrees (null if the output angle is not integer).
   * @param floatAngle Angle value in degrees (null if the output angle is not float).
   * @param sine Value of the output sine.
   * @param cosine Value of the output cosine.
*/
void writeInOutput(FILE* output, int integerAngle, float floatAngle,  float sine, float cosine) {
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
  fprintf(output, "sine = %f\n", sine);
  fprintf(output, "cosine = %f\n\n", cosine);
}


/**
   * This function calculates cosine based on the line segment formed by the interval 
   * of two cosines values ​​and their determined angles.
   * @param inferiorAngle Value of the lower angle of the line segment.
   * @param superiorAngle Value of the upper angle of the line segment.
   * @param inferiorCos Value of the lower cosine of the line segment.
   * @param superiorCos Value of the upper cosine of the line segment.
   * @param angle Value of the cosine angle to be determined.
*/
float findCos(int inferiorAngle, int superiorAngle, float inferiorCos, float superiorCos, float angle) {
    float slope = (superiorCos - inferiorCos) / (superiorAngle - inferiorAngle);

    float cosine = ((angle - inferiorAngle) * slope) + inferiorCos;

    return cosine;
}


/**
   * This function calculates the angle based on the line segment formed by the interval 
   * of two sines values ​​and their determined angles.
   * @param inferiorAngle Value of the lower angle of the line segment.
   * @param superiorAngle Value of the upper angle of the line segment.
   * @param inferiorSin Value of the lower sine of the line segment.
   * @param superiorSin Value of the upper sine of the line segment.
   * @param inputSin Value of the input sine.
*/
float findAngle(int inferiorAngle, int superiorAngle, float inferiorSin, float superiorSin, float inputSin) {
    float slope = (superiorSin - inferiorSin) / (superiorAngle - inferiorAngle);

    float angle = ((inputSin - inferiorSin) / slope) + inferiorAngle;
    
    return angle;
}


/**
   * This function checks if the input sine value is close enough to a sine value 
   * in the trigonometric table.
   * @param inputSin Value of the input sine.
   * @param tableSin Value of the trigonometric table sine.
*/
int isCloseEnough(float inputSin, float tableSin) {
  if(
    (inputSin < tableSin && inputSin / tableSin >= 0.999) || 
    (inputSin > tableSin && tableSin != 0 && inputSin / tableSin <= 1.001) || 
    inputSin == tableSin
  ) return 1;

  return 0;
}


/**
   * This function implements the logic for calculating the output values.
   * @param sine Array that stores the sines values of the trigonometric table.
   * @param cosine Array that stores the cosines values of the trigonometric table.
   * @param angles Array that stores the angles values of the trigonometric table.
   * @param inputSines Array that stores the input sines values.
   * @param numberOfSines Number of input sines read.
*/
void calculateOutput(float sine[], float cosine[], int angles[], float inputSines[], int numberOfSines) {
    FILE* output = fopen("../files/senocosseno.txt", "w");

    for(int inputIndex = 0; inputIndex < numberOfSines; inputIndex++) {
      for(int tableIndex = 0; tableIndex <= 90; tableIndex++) {
        float inputSin = inputSines[inputIndex];

        if (
          isCloseEnough(inputSin, sine[tableIndex]) == 1 &&
          isCloseEnough(inputSin, sine[tableIndex+1]) != 1
        ) {
          writeInOutput(output, angles[tableIndex], -1, inputSin, cosine[tableIndex]);
        }
        
        else if(isCloseEnough(inputSin, sine[tableIndex+1]) != 1) {
          float outputAngle;
          float outputCos;

          if(sine[tableIndex] < inputSin && sine[tableIndex+1] > inputSin) {
            outputAngle = findAngle(
              angles[tableIndex], angles[tableIndex + 1], 
              sine[tableIndex], sine[tableIndex+1], inputSin
            );

            outputCos = findCos(
              angles[tableIndex], angles[tableIndex + 1], 
              cosine[tableIndex], cosine[tableIndex + 1], outputAngle
            );

            writeInOutput(output, -1, outputAngle, inputSin, outputCos);
          }
        }
      }
    }

    fclose(output);
}


/**
   * This function defines the trigonometric table arrays based on the trigo.txt file read.
   * @param sine Array that stores the sines values.
   * @param cosine Array that stores the cosines values.
   * @param angles Array that stores the angles values.
*/
void setTrigonometricTable(float sine[], float cosine[], int angles[]) {
  FILE* trigonometricTable = fopen("../files/trigo.txt", "r");

  for(int index = 0; index <= 90; index++) {
    fscanf(trigonometricTable, "%d", &angles[index]);
    fscanf(trigonometricTable, "%f", &sine[index]);
    fscanf(trigonometricTable, "%f", &cosine[index]);
  }

  fclose(trigonometricTable);
}


/**
   * This function obtains the number of sines values ​​to be read from the input file.
   * @return Number of sines to be read.
*/
int getNumberOfSines() {
  FILE* sinesFile = fopen("../files/seno.txt", "r");
  
  int numberOfSines = 0;
  float aux = 0;

  while(fscanf(sinesFile, "%f", &aux) == 1)
    numberOfSines++;
  
  fclose(sinesFile);

  return numberOfSines;
}


/**
   * This function reads the sines input values ​​and stores them in an array.
   * @param array Array that stores the input values.
   * @param numberOfElements Number of elements to be read.
   * @return Nothing.
*/
void readInputSines(float array[], int numberOfElements) {
  FILE* file = fopen("../files/seno.txt", "r");

  for(int index = 0; index < numberOfElements; index++)
    fscanf(file, "%f", &array[index]);

  fclose(file);
}

int main() {
  float sine[91];
  float cosine[91];

  int angles[91];
  int numberOfSines = getNumberOfSines();

  float inputSines[numberOfSines];

  readInputSines(inputSines, numberOfSines);

  setTrigonometricTable(sine, cosine, angles);

  calculateOutput(sine, cosine, angles, inputSines, numberOfSines);

  return 0;
}