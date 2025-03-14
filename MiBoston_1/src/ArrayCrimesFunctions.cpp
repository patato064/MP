/*
 * Metodología de la Programación
 * Curso 2024/2025
 */

/* 
 * @file ArrayCrimesFunctions.cpp 
 * 
 * Created on September 19, 2024, 1:14 PM
 */

#include "ArrayCrimesFunctions.h"

using namespace std;

void InitializeArrayInts(int array[], int const & size) {
    
    for (int i = 0; i < size; i++){
        
        array[i] = 0;
    }
}

void ComputeMaxPosArrayInts(int array[], int const & size, int & max, int & posMax) {
    
    max = array[0]
    
    if (size > 1){
        for (int i = 1; i < size; i++){

            if (array[i]) > max){
                
                max = array[i];
                posMax = i
            }
        }
    }
    
}

void PrintHistogramArrayCrimes(int dataField, int histogram[]) {
}

void PrintArrayCrimes(Crime crimes[], int nCrimes) {
    
    for (int i = 0; i < nCrimes; i++){
        
        cout << crimes[i].toString() << endl;
        
    }
}

int PosMinArrayCrimes(Crime array[], int initialPos, int finalPos) {
}

void SwapElementsArrayCrimes(Crime array[], int nElements, int first,
        int second) {
    
    if (0 > first || first >= nElements || 0 > second || second >= nElements){
        
        throw std::out_of_range(
                std::string("void SwapElementsArrayCrimes(Crime array[], int nElements, int first, int second): ")
                + "elemento fuera del array")
    }
    
    Crime cambiar = array[second];
    
    array[second] = array[first];
    array[first] = cambiar;
}

void SortArrayCrimes(Crime array[], int nElements) {
}

int FindCrimeInArrayCrimes(Crime array[], Crime crime,
        int initialPos, int finalPos) {
}

void ComputeHistogramArrayCrimes(Crime crimes[], int nCrimes,
        int dataField, int histogram[]) {
}

void SelectWhereEQArrayCrimes(Crime inputCrimes[], int inputCrimesSize, 
    string  field, string value, Crime outputCrimes[], 
    int outputCrimesSize) {
}

