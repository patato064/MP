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
#include <fstream>

#include "CrimeSet.h"

using namespace std;

const string CrimeSet::MAGIC_STRING_T="MP-CRIME-T-1.0";


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
    
    if (text != ""){
        
        if (text.at(text.length()-1) != '\n' && text != ""){
            _comment = text + "\n";
        }
        else{
        _comment = text;
        }
    }
}

std::string CrimeSet::toString() const{
    
    string recorcholis = to_string(_nCrimes) + '\n';
    
    for (int i = 0; i < _nCrimes; i++){
        
       recorcholis += _crimes[i].toString();
       
       if (i != _nCrimes-1){
           
           recorcholis+= '\n';
       }
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
        
        if (_crimes[i].getId() == crime.getId()){
            encontrado = true;
        }           
        else i++;
    }
    
    if (!encontrado && _nCrimes < DIM_VECTOR_CRIMES){
        _crimes[_nCrimes] = crime;
        _nCrimes++;
    }
    
    return !encontrado;
}

const Crime & CrimeSet::at (int pos) const{
    
    if (0 > pos || pos >= _nCrimes){
        throw std::out_of_range(std::string("const Crime & at(int pos) const: ") +
                "La posicion dada no es valida"); 
    }
    
    return _crimes[pos];
}

int CrimeSet::findCrime(const Crime & crime, int initialPos, int finalPos) const{
    
    int pos = initialPos;
    bool encontrado = false;
    
    
    if (initialPos < 0 || finalPos >= _nCrimes || initialPos > finalPos){
        while (pos <= finalPos && !encontrado){

            if (crime.getId() == _crimes[pos].getId()) encontrado = true;
            else pos++;
        }
    }
    
    if (!encontrado) pos = -1;
    return pos;
}

int CrimeSet::findCrime(const Crime & crime) const{
    
    return findCrime(crime, 0, _nCrimes -1);
}

void CrimeSet::load(const std::string & fileName){
    
    string magica;
    
    this-> clear();
    
    ifstream fentrada;
    fentrada.open(fileName);
    
    getline(fentrada, magica);
    
    if (magica == MAGIC_STRING_T){
        
        readComments(fentrada);
        
        string num;
        getline(fentrada, num);
        
        int num_crimes = stoi(num);
        
        
        for (int i = 0; i < num_crimes; i++){
            
            string crimen_actual;
            
            getline(fentrada, crimen_actual);
            
            
            if (!crimen_actual.empty()){
                
               Crime crimen(crimen_actual);
               
               
               this->append(crimen);
            }
            
        }
            
    }
    
    fentrada.close();
}


void CrimeSet::save(const std::string & fileName){
    
    ofstream fsalida;
    
    fsalida.open(fileName);
    fsalida << MAGIC_STRING_T << endl;
    saveComments(fsalida);
    
    fsalida << toString();
    
    fsalida.close();
}

void CrimeSet::join(const CrimeSet & crimeSet){
    
    for (int i = 0; i < crimeSet.getSize(); i++){
        
       this->append(crimeSet.at(i));
       
    }
}

void CrimeSet::normalize(){
    
    for (int i = 0; i < _nCrimes; i++){
        
        Normalize(_crimes[i]);
    }
}


void CrimeSet::computeHistogram(int dataField, int histogram[]) const{
    
     if (dataField != 0 && dataField != 1){
        
        throw std::out_of_range(
                std::string("void CrimeSet::computeHistogram(int dataField, int histogram[]) const")
                + "dataField distinto de 0 o 1");
    }
    
    int num_datos = (dataField == 0)? 7 : 24;
   
    InitializeArrayInts(histogram, num_datos);

    if (dataField == 0){
        for (int j = 0; j < _nCrimes; j++){
            
            int dia = _crimes[j].getDateTime().weekDay();
            
            if (dia >= 0 && dia < 7){
                histogram[dia]++;
            }
        }
    }
    else{
        for (int k = 0; k < _nCrimes; k++){
            
            int hora = _crimes[k].getDateTime().hour();
            
            if (hora >= 0 && hora <= 23){
                histogram[hora]++;
            }
        }
    }
}


CrimeSet CrimeSet::selectWhereEQ(const std::string &field, const std::string &value)const{
    
    CrimeSet nuevo;
    
    for (int i = 0; i < _nCrimes; i++){
        
        if (_crimes[i].getField(field) == value){
            
            nuevo.append(_crimes[i]);
        }
    }
    
    return nuevo;
}

CrimeSet CrimeSet::selectValidLocation() const{
    
    CrimeSet valido;
    
    for (int i = 0; i < _nCrimes; i++){
        
        if (_crimes[i].getLocation().isValid()){
            
            valido.append(_crimes[i]);
        }
    }
    
    return valido;
}


void CrimeSet::sort(){
    
    for (int i = 0; i < _nCrimes; i++){
        
        int pos_min = PosMinArrayCrimes(_crimes, i, _nCrimes - 1);
        
        Crime cambiar = _crimes[pos_min];
        
        _crimes[pos_min] = _crimes[i];
        _crimes[i] = cambiar;
    }
}


// Métodos Privados de la clase CrimeSet

    Crime & CrimeSet::at (int pos){
    
    if (0 > pos || pos >= _nCrimes){
        throw std::out_of_range(std::string("Crime & at(int pos): ") +
                "La posicion dada no es valida");
    }
    
    return _crimes[pos];
}

void CrimeSet::readComments(std::istream & inputStream){
    
    
    char c = inputStream.get();
    
    
    string comentario;
    
    while (c ==  '#'){
        
        string linea;
        getline(inputStream, linea);
        
        
        
        comentario = comentario +  linea + '\n';
        
        c = inputStream.get();
    }
    
    _comment = comentario;
    
    inputStream.putback(c);
} 


void CrimeSet::saveComments(std::ostream &outputStream) const{
    
    string comment = FormatAsComment(_comment);
    
    outputStream << comment;
}

// Funciones complementarias a la clase CrimeSet


void InitializeArrayInts(int array[], int size){
    
    for (int i = 0; i < size; i++){
        
        array[i] = 0;
    }
}

void PrintHistogramArrayCrimes(int dataField, const int histogram[]) {
    
    if (dataField == 0){
        
        for (int i = 0; i < 7; i++){
            
            cout << DateTime::dayName(i) << " " << histogram[i] << endl;
        }
        
    }
    
    else if (dataField == 1){
        
        for (int i = 0; i < 24; i++){
            
            cout << i << " " << histogram[i] << endl;
        }
    }
        
}

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


// Función para facilitar void CrimeSet::sort()

int PosMinArrayCrimes(const Crime array[], int initialPos, int finalPos) {
    
    int pos_minimo = initialPos;
    
    if (initialPos > finalPos){
        pos_minimo = -1;
    }
        else{
        Crime minimo = array[pos_minimo];

        for(int pos = initialPos; pos <= finalPos; pos++){

            if((array[pos].getDateTime() < minimo.getDateTime()) || 
                (array[pos].getDateTime() == minimo.getDateTime() &&
                 array[pos].getId() < minimo.getId())){
                minimo = array[pos];
                pos_minimo = pos;
            } //if 
        } //for
    }
    
    return pos_minimo;
}