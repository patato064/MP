/*
 * Metodología de la Programación
 * Curso 2024/2025
 */

/** 
 * @file  CrimeSet.cpp
 * @note To be implemented by students
 *  
 * Created on November 26, 2024, 11:04 AM
 */

#include <iostream>
#include <string>

#include "CrimeSet.h"

using namespace std;

const string CrimeSet::MAGIC_STRING_T="MP-CRIME-T-1.0";

string FormatAsComment(string comment, char commentCharacter){
    size_t start = 0, end;
    string formatedComment;
    if (comment.size() > 0) { // If comment has at least one character
        while ((end = comment.find('\n', start)) != std::string::npos) {
            formatedComment += commentCharacter + comment.substr(start, end - start) + "\n";
            start = end + 1;
        }
        if(start<comment.size()){ // This happens when last line of comment does not have \n
            formatedComment += commentCharacter + comment.substr(start, comment.size() - start) + "\n";
        }
    }
    return formatedComment;
}

CrimeSet::CrimeSet():_comment(""), _nCrimes(0){}

int CrimeSet::getSize() const{
    
    return _nCrimes;
}

int CrimeSet::getCapacity() const{
    
    return DIM_VECTOR_CRIMES;
}

std::string CrimeSet::getComment() const{
    
    return _comment;
}

void CrimeSet::setComment(const std::string & text) {
    
    if (text.at(text.length()-1) != '\n'){
        
        text.append('\n');
    }
    
    _comment = text;
}

std::string CrimeSet::toString(){
    
    string recorcholis = to_string(_nCrimes) + "\n";
    
    for (int i = 0; i < _nCrimes; i++){
        
       recorcholis += _crimes[i].toString();
    }
            
    return recorcholis;
}

void CrimeSet::clear(){
    
    _comment = "";
    _nCrimes = 0;
}

bool CrimeSet::append(const Crime & crime){
    
    bool encontrado = false;
    int i = 0;
    
    while (i < _nCrimes && !encontrado){
        
        if (_crimes[i].getId() == crime.getId()) encontrado = true;
        else i++;
    }
    
    if (!encontrado){
        _crimes[_nCrimes + 1] = crime;
        _nCrimes++;
    }
    
    return !encontrado;
}

const Crime & CrimeSet::at (int pos) const{
    
    if (0 > pos || pos >= _nCrimes){
        
        //THROW PUTA
    }
    
    return _crimes[pos];
}

int CrimeSet::findCrime(const Crime & crime, int initialPos, int finalPos) const{
    
    int pos = initialPos;
    bool encontrado = false;
    
    while (pos <= finalPos && !encontrado){
        
        if (crime.getId() == _crimes[pos].getId()) encontrado = true;
        else pos++;
    }
    
    if (!encontrado) pos = -1;
    return pos;
}

int CrimeSet::findCrime(const Crime & crime) const{
    
    return findCrime(crime, 0, _nCrimes -1);
}