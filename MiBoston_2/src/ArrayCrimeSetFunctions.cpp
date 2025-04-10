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
    
    bool fin = false;
    
    while(!fin){
        getline(inputStream, fileName);
        
        if(inputStream){ //Comprueba que se ha leido correctamente un archivo
            if(!fileName.empty()){ //Comprobamos que no es una cadena vacia
                ifstream file(fileName); //Abre el archivo con ese nombre
                if(file){ //Comprobamos que se ha abierto el archivo
                    
                    
                    
                    string newCrimeSetString;
                    file >> newCrimeSetString;
                    
                    CrimeSet newCrimeSet;
                    newCrimeSet.load(newCrimeSetString);
                    
                    AppendCrimeArrayCrimeSet(arrayCrimeSet, nCrimeSets, newCrimeSet);
                    
                    nCrimeSets++;
                } //if file
            }  //if fileName.empty
        } //if inputStream
        else{
            fin = true;
        } //else
    }//while
} //metodo

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
    
}
