/*
 * Metodología de la Programación
 * Curso 2024/2025
 */

/** 
 * @file:  CrimeCounter.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * Created on September 24, 2024, 3:19 PM
 */

#include <iostream>
#include <fstream>
#include <cmath>

#include "CrimeCounter.h"
using namespace std;


/**
 * DEFAULT_COORD_BOTTOMLEFT is set to the bottom left corner of the Boston area
 */
const Coordinates CrimeCounter::DEFAULT_COORD_BOTTOMLEFT(42.207760,-71.178673);  

/**
 * DEFAULT_COORD_TOPRIGHT is set to the top right corner of the Boston area
 */
const Coordinates CrimeCounter::DEFAULT_COORD_TOPRIGHT(42.395042,-70.953728);  


/* CrimeCounter::CrimeCounter(
...//
 */

//Constructor de la clase
CrimeCounter::CrimeCounter(int nRows, int nColumns,
            const Coordinates &  bottomLeftCoord, 
            const Coordinates & topRightCoord)
    : _frequency(nullptr), _nRows(0), _nCols(0), 
      _bottomLeftCoord(), _topRightCoord(){
    //comprobamos si las coordenadas proporcionadas son validas
    if(!bottomLeftCoord.isValid()|| !topRightCoord.isValid()){
        //No inicializamos nada ya que lo hemos hecho en la lista de inicializacion
        throw std::invalid_argument("Invalid coordinates provided.");
    }
    
    //asignamos las coordenadas validas:
    _bottomLeftCoord = bottomLeftCoord;
    _topRightCoord = topRightCoord;
    
    //Comprobamos que las filas y las columnas sean positivas
    if(nRows > 0 && nColumns > 0){
        //usamos allocate para reservar la memoria
        allocate(nRows, nColumns);
        //inicializamos la matriz con ceros usando el clear
        clear();
    } else{
        //Si las filas o columnas no son validas dejamos los valores a cero y nullptr
        _nRows = 0;
        _nCols = 0;
        _frequency = nullptr;
    }
}


//Constructor de copia

CrimeCounter::CrimeCounter(const CrimeCounter &other){
    allocate(other.getNumRows(), other.getNumCols());
    copy(other);
}

//Hacemos el destructor de la clase
CrimeCounter::~CrimeCounter(){
    deallocate();
}

//Operador de asignacion
CrimeCounter &CrimeCounter::operator=(const CrimeCounter &other){
    if(this != &other){
        deallocate();
        allocate(other.getNumRows(),other.getNumCols());
        copy(other);
    }
    
    return *this;
}

//Hacemos el allocate, deallocate y copy
/*  Nos aseguraremos antes de usar allocate de que _nRows y _nCols
    estan correctamente inicializados, tanto en el 
    constructor de copia como en el operador de asignacion
*/    
void CrimeCounter::allocate(int nRows, int nCols) {
    _frequency = nullptr;

    if (nRows > 0 && nCols > 0) {
        _frequency = new int*[nRows];
        for (int i = 0; i < nRows; ++i) {
            _frequency[i] = new int[nCols];
        }
    }

    _nRows = nRows;
    _nCols = nCols;
}

void CrimeCounter::deallocate(){
    if(_frequency != nullptr){
        for(int i = 0; i < _nRows; i++){
            delete[] _frequency[i];
        }
        delete[] _frequency;
        _frequency = nullptr;
    }
}

void CrimeCounter::copy(const CrimeCounter &other){
    _nRows = other._nRows;
    _nCols = other._nCols;
    _bottomLeftCoord = other._bottomLeftCoord;
    _topRightCoord = other._topRightCoord;
    
    for(int i = 0; i < _nRows; i++){
        for(int j = 0; j < _nCols; j++){
            _frequency[i][j] = other._frequency[i][j];
        }
    }
}

int CrimeCounter::getNumRows() const{
    return _nRows;
}

int CrimeCounter::getNumCols() const{
    return _nCols;
}

Coordinates CrimeCounter::getLeftLocation() const{
    return _bottomLeftCoord;
}

Coordinates CrimeCounter::getRightLocation() const{
    return _topRightCoord;
}

std::string  CrimeCounter::toString() const{
    std::string messi;
    
    messi += std::to_string(_nRows) + " " + std::to_string(_nCols) + "\n";
    messi += std::to_string(_bottomLeftCoord.getLatitude()) + "," 
             + std::to_string(_bottomLeftCoord.getLongitude()) + "\n";
    messi += std::to_string(_topRightCoord.getLatitude()) + ","
             + std::to_string(_topRightCoord.getLongitude()) + "\n";
    
    for(int i = 0; i < _nRows; i++){
        for(int j = 0; j < _nCols; j++){
            messi += std::to_string(_frequency[i][j]);
            if(j < _nCols - 1)
                messi += " ";
        }
        messi += "\n";
    }
    
    return messi;   
}

int CrimeCounter::getMaxFrequency() const{
    int maxFreq = 0;
    if(_nRows > 0 && _nCols > 0){
       maxFreq = _frequency[0][0];
       
       for(int i = 0; i < _nRows; i++){
           for(int j = 0; j < _nCols; j++){
               if(_frequency[i][j] > maxFreq){
                   maxFreq = _frequency[i][j];
               }
           }
       }
    }
    
    return maxFreq;
}

int CrimeCounter::getTotalLocated() const{
    int total = 0;
    for(int i = 0; i < _nRows; i++){
        for(int j = 0; j < _nCols; j++){
            total += _frequency[i][j];
        }
    }
    
    return total;
}

void CrimeCounter::clear(){
    for(int i = 0; i < _nRows; i++){
        for(int j = 0; j < _nCols; j++){
            _frequency[i][j] = 0;
        }
    }
}

void CrimeCounter::increaseFrequency(const Crime &crime, int frequency){
    Coordinates coord = crime.getLocation();
    bool validCoords = coord.isValid();
    bool insideArea = false;
    
    //Comprobamos que el crimen esta dentro del area (solo si validCoords es true)
    if(validCoords){
        insideArea = coord.isInsideArea(_bottomLeftCoord, _topRightCoord);
    }
    
    //solo continuamos si se cumplen las dos condiciones anteriores, es decir,
    // si validCoord y insideArea son true
    if(validCoords && insideArea){
        //Obtenemos los limites del area 
        double latMin = _bottomLeftCoord.getLatitude();
        double lonMin = _bottomLeftCoord.getLongitude();
        double latMax = _topRightCoord.getLatitude();
        double lonMax = _topRightCoord.getLongitude();
        
        //calculamos cuanto "mide" cada celda de la matriz en latitud y longitud
        // es decir, "altura" y "ancho" de cada celda geográfica
        double cellHeight = (latMax - latMin) / _nRows;
        double cellWidth = (lonMax - lonMin) / _nCols;
        
        /*ahora localizamos la celda en la cae el crimen, restamos el minimo
         * (latMin o lonMin) para obtener el desplazamiento relativo
         * Dividimos por el tamaño de la celda para saber el indice en el que
         * nos encontramos
         * Usamos el static_cast para obtener el indice entero de la fila/col
         */
        int row = static_cast<int>((coord.getLatitude()- latMin) / cellHeight);
        int col = static_cast<int>((coord.getLongitude()- lonMin) / cellWidth);
        
        //en caso de que caiga justo en los bordes superior o derecho restamos 1
        if(row == _nRows) row--;
        if(col == _nCols) col--;
        
        //si no se especifica una frecuencia se suma 1
        if(frequency == 0){
            _frequency[row][col]++;
        }
        else{
            _frequency[row][col] += frequency;
        } 
    } else if (validCoords & !insideArea){
        //si se dan coordenadas validas pero no dentro del area hacemos throw
        throw std::invalid_argument("the given crime Coordinates are valid but outside the target area");
    }
    //else: coordenadas invalidas asi que no se hace nada
}

void saveAsPPMTextImage(std::string fileName, 
        ColorPalette palette, std::string comment = ""){  // declaration must be revised
    // Compute maxFrequency as the maximum frequency in the frequency matrix
    // Save heading and comments into the ppm file
    // For every cell in the frequency matrix
            // colorIndex = GetIndexPalette(palette, 
                  //log(this->_frequency[row][column]+1), log(maxFrequency+1));
            // Save into the ppm file the RGB components of the color at 
                  //the position colorIndex of the palette
}

void CrimeCounter::getRowColumn(const Coordinates &coordinates, int& row, 
        int& column) const {
    if (!coordinates.isValid() || 
            !coordinates.isInsideArea(_bottomLeftCoord, _topRightCoord)) {
        throw std::invalid_argument(
            string("void CrimeCounter::getRowColumn((const Coordinates &loc, int& row, int& column) const: ") +
            coordinates.toString() + " is not a valid location or is outside the target area");
    }
    Coordinates targetArea = this->_bottomLeftCoord.length(this->_topRightCoord);
    float cellHeight = targetArea.getLatitude()/_nRows;
    float cellWidth = targetArea.getLongitude()/_nCols;
    Coordinates delta = _bottomLeftCoord.length(coordinates);
    
    row = _nRows - (delta.getLatitude() / cellHeight);
    column = (delta.getLongitude() / cellWidth);
    if (row == _nRows) row = _nRows-1;
    if (column == _nCols) column = _nCols-1;
}

// External functions
int GetIndexPalette(const ColorPalette &palette, float frequency, float maxFrequency) {
    return frequency == maxFrequency ? palette.getNumColors() - 1 : 
        frequency * palette.getNumColors() / maxFrequency;
}