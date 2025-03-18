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

void ComputeMaxPosArrayInts(const int array[], int const size, int & max, int & posMax) {
    
    max = array[0];
    
    if (size > 1){
        for (int i = 1; i < size; i++){

            if (array[i] > max){
                
                max = array[i];
                posMax = i;
            }
        }
    }
    
}

void PrintHistogramArrayCrimes(int dataField, const int histogram[]) {
    
    if (dataField == 0){
        
        for (int i = 0; i < 7; i++){
            
            cout << DateTime::dayName(i) << " " << histogram[i] << endl;
        }
        
    }
    
    if (dataField == 1){
        
        for (int i = 0; i < 24; i++){
            
            cout << i << " " << histogram[i] << endl;
        }
    }
        
}

void PrintArrayCrimes(const Crime crimes[], int nCrimes) {
    
    for (int i = 0; i < nCrimes; i++){
        
        cout << crimes[i].toString() << endl;
        
    }
}

int PosMinArrayCrimes(const Crime array[], int initialPos, int finalPos) {
    
    if (initialPos > finalPos){
        return -1;
    }
    
    int pos_minimo = initialPos;
    Crime minimo = array[pos_minimo];
    
    for(int pos = initialPos; pos <= finalPos; pos++){
        
        if((array[pos].getDateTime() < minimo.getDateTime()) || 
            (array[pos].getDateTime() == minimo.getDateTime() &&
             array[pos].getId() < minimo.getId())){
            minimo = array[pos];
            pos_minimo = pos;
        } //if 
    } //for
    
    return pos_minimo;
}

void SwapElementsArrayCrimes(Crime array[], int nElements, int first,
        int second) {
    
    if (0 > first || first >= nElements || 0 > second || second >= nElements){
        
        throw std::out_of_range(
                std::string("void SwapElementsArrayCrimes(Crime array[], int nElements, int first, int second): ")
                + "elemento fuera del array");
    }   
    
    Crime cambiar = array[second];
    
    array[second] = array[first];
    array[first] = cambiar;
}

void SortArrayCrimes(Crime array[], int nElements) {
    
    for (int i = 0; i < nElements; i++){
        
        int pos_min = PosMinArrayCrimes(array, i, nElements);
        SwapElementsArrayCrimes(array, nElements, i, pos_min);
    }
}

int FindCrimeInArrayCrimes(const Crime array[], const Crime & crime,
        int initialPos, int finalPos) {
    
    //REVISAR SI EL ID ES UN ENTERO O UN STRING
    string id = crime.getId();
    int pos = initialPos;
    bool no_encontrado = true;
    
    while(pos <= finalPos && no_encontrado){
        if(id == array[pos].getId()){
            no_encontrado = false;
        }
        if (no_encontrado) pos++;
    }
    
    if (no_encontrado) pos = -1;
    
    return pos;
}

void ComputeHistogramArrayCrimes(const Crime crimes[], int nCrimes,
        int dataField, int histogram[]) {
    
    if (dataField != 0 && dataField != 1){
        
        throw std::out_of_range(
                std::string("void ComputeHistogramArrayCrimes(const Crime crimes[], int nCrimes, int dataField, int &histogram[])")
                + "dataField distinto de 0 o 1");
    }
    
    int num_datos = (dataField == 0)? 7 : 24;
   
    InitializeArrayInts(histogram, num_datos);
    
    for (int i = 0; i < num_datos; i++){
        
        if (dataField == 0){
            for (int j = 0; j < nCrimes; j++){
              
                if (crimes[j].getDateTime().weekDay() == i){
                histogram[i]++;
                }
            }
        }
        else{
            for (int k = 0; k < nCrimes; k++){
              
                if (crimes[k].getDateTime().hour() == i){
                histogram[i]++;
                }
            }
            
        }
             
    }
}

void SelectWhereEQArrayCrimes(const Crime inputCrimes[], int inputCrimesSize, 
    const string  field, const string value, Crime outputCrimes[], 
    int & outputCrimesSize) {
    
    int j = 0;
    
    for (int i = 0; i < inputCrimesSize; i++){
        
        if (inputCrimes[i].getField(field) == value){
            outputCrimes[j] = inputCrimes[i];
            j++; 
        }
    }
}

