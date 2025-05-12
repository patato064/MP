/*
 * Metodología de la Programación
 * Curso 2024/2025
 */

/** 
 * @file Coordinate.cpp  
 * 
 * Last modified on February 12, 20245, 15:03 PM
 */

#include "Coordinates.h"
#include <cmath>

const float Coordinates::INVALID_COORDINATE=181.0;

using namespace std;


Coordinates::Coordinates(float latitude, float longitude): 
_latitude(latitude), _longitude(longitude) {
}

float Coordinates::getLatitude() const {
    
    return _latitude;
}

float Coordinates::getLongitude() const {
    
    return _longitude;
}

bool Coordinates::isValid() const {
    
    bool es_valido = true;
    
    if (_longitude < -180 || _longitude > 180 || 
                _latitude < -90 || _latitude > 90){
        
        es_valido = false;
        }
    
    return es_valido;
}

void Coordinates::set(float latitude, float longitude){
    
    _latitude = latitude;
    _longitude = longitude;
}
    
void Coordinates::set(const std::string &coords){
        
    int pos_coma = coords.find(","); 
            
    float latitude = stod(coords.substr(0, pos_coma - 1));
    float longitude = stod(coords.substr(pos_coma + 1, coords.length() -1));
        
    set(latitude, longitude);
}

void Coordinates::setLatitude(float latitude) {
    
    _latitude = latitude;
}

void Coordinates::setLongitude(float longitude) {
    
    _longitude = longitude;
}

std::string Coordinates::toString() const {
    
    string coords = to_string(_latitude) + "," + to_string(_longitude);
    return coords;
}

Coordinates Coordinates::length(const Coordinates &second) const{
    
    double latitud_2 = second.getLatitude();
    double longitud_2 = second.getLongitude();
    
    double latitud_final = fabs(_latitude - latitud_2);
    double longitud_final = fabs(_longitude - longitud_2);
   
    return Coordinates(latitud_final, longitud_final);
}                        

bool Coordinates::isInsideArea(const Coordinates &bottomLeft, const Coordinates &topRight) const {
    
    bool esta_dentro = false;
    
    if (_latitude >= bottomLeft.getLatitude() && 
            _latitude <= topRight.getLatitude() && 
            _longitude >= bottomLeft.getLongitude() &&
            _longitude <= topRight.getLongitude()){
        
        esta_dentro = true;
    }
    
    return esta_dentro;
}  

    std::ostream &operator<<(std::ostream &os, const Coordinates &obj){
        
        os << obj.toString();
        return os;
    }
    
    std::istream &operator>>(std::istream &is, Coordinates &obj){
        
        float latitud, longitud;
        char coma;
        
        is >> latitud ;
        is >> coma;
        is >> longitud;
        
        obj.set(latitud, longitud);
        return is;
    }
