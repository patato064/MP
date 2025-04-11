/*
 * Metodología de la Programación
 * Curso 2024/2025
 */

/** 
 * @file  ArrayCrimeSetFunctions.cpp
 * @note To be implemented by students
 *  
 * Created on November 26, 2024, 11:04 AM
 */

#include <iostream>
#include "ArrayCrimeSetFunctions.h"
#include <fstream>

using namespace std;

void ReadArrayCrimeSet(istream &inputStream, CrimeSet * &arrayCrimeSet, 
        int & nCrimeSets){
    
    string fileName; 
    while (getline(inputStream, fileName)) {        
        
       if (!fileName.empty()) {
           
           CrimeSet newCrimeSet;
           newCrimeSet.load(fileName);
           
           AppendCrimeArrayCrimeSet(arrayCrimeSet, nCrimeSets, newCrimeSet);
           
       } 
       else {
           
       } 
 
    } 
}

void PrintArrayCrimeSet(const CrimeSet * &arrayCrimeSet, int nCrimeSets){
    for(int i = 0; i < nCrimeSets; i++){
        cout << arrayCrimeSet[i].toString();
    }
}

CrimeSet * AllocateArrayCrimeSet(int nCrimeSets){
    CrimeSet* array = nullptr;
    if(nCrimeSets > 0){
        array = new CrimeSet[nCrimeSets];
    }
   return array;
}

void DeallocateArrayCrimeSet(CrimeSet * arrayCrimeSet){
    delete[] arrayCrimeSet;
    arrayCrimeSet = nullptr;
}

void AppendCrimeArrayCrimeSet(CrimeSet * &arrayCrimeSet, int &nCrimeSets, 
        const CrimeSet &newCrimeSet){
    
    CrimeSet*  auxiliar = new CrimeSet[nCrimeSets + 1];
    
    for(int i = 0; i < nCrimeSets; i++){
        auxiliar[i] = arrayCrimeSet[i];
    }
    
    auxiliar[nCrimeSets] = newCrimeSet;
    delete[] arrayCrimeSet;
    arrayCrimeSet = auxiliar;
    
    nCrimeSets++;
}
