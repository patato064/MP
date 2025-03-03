/*
 * Metodología de la Programación
 * Curso 2024/2025
 */

/** 
 * @file Crime.cpp
 *  
 * Last modified on February 12, 20245, 15:13 PM
 */

#include "Crime.h"

using namespace std;

/*
 * Initialization of the static string that contains the value assigned to any 
 * string field (string) which is found empty in the data of a Crime
 */
const std::string Crime::UNKNOWN_VALUE = "UNKNOWN";

/*
 * Initialization of the static string that contain the default value for the
 * DateTime field in a Crime 
 */
const string Crime::DATETIME_DEFAULT = "2017-01-20 02:00:00";

/* 
 * Initialization of the static string with the default values for every field in 
 * a Crime
 */
const string Crime::CRIME_DEFAULT("0," + UNKNOWN_VALUE + "," + UNKNOWN_VALUE + "," +
        UNKNOWN_VALUE + "," + UNKNOWN_VALUE + "," + UNKNOWN_VALUE + "," + UNKNOWN_VALUE +
        "," + ((std::string)"1") + "," + Crime::DATETIME_DEFAULT + "," +
        UNKNOWN_VALUE + ",181,181");

Crime::Crime() {
    
    Crime (Crime::CRIME_DEFAULT);
}


Crime::Crime(const string &line) {

    int i = 0;
    int k = 0;
    
    const int MAX_VALORES = 20;
    
    string valores[MAX_VALORES];
    
    // Convertimos la string total en un vector de strings que contienen
    // individualmente los datos a rellenar
    
    while (i < line.length()){
        
        int j = i;
        
        while (j < line.length() && line.at(j + 1) != ';') {
            
            j++;
        }
        
        line.substr(i,j) = valores[k];
        k++;
        
        i = j + 2;
    }
    
    // Ahora asignamos cada valor a su correspondiente dato miembro de la clase
    
    _counter = stoi(valores[0]);
    if (!valores[1].empty()) _id = valores[1];
    _code = valores[2];
    _group = valores[3];
    _description = valores[4];
    _district = valores[5];
    _areaReport = valores[6];
    bool _shooting = stoi(valores[7]);
    _dateTime = DateTime(valores[8]); 
    _street = valores[9];
    _location = Coordinates(stod(valores[10]), stod(valores[11]));
    
}


int Crime::getCounter() const {
    
 return _counter;   
}

std::string Crime::getId() const {
    
    return _id;
}


std::string Crime::getCode() const {
    
    return _code;
}


std::string Crime::getGroup() const {
    
    return _group;
}

std::string Crime::getDescription() const {
    
    return _description;
}


std::string Crime::getDistrict() const {
    
    return _district;
}


std::string Crime::getStreet() const {
    
    return _street;
}


std::string Crime::getAreaReport() const {
    
    return _areaReport;
}


bool Crime::isShooting() const {
    
    return _shooting;
}


DateTime Crime::getDateTime() const {
    
    return _dateTime;
}

Coordinates Crime::getLocation() const {
    
    return _location;
}


bool Crime::isIDUnknown() const {
    
    return (_id == UNKNOWN_VALUE);
}


std::string Crime::toString() const {
}

void Crime::setCounter(int c) {
    
    _counter = c;
}

void Crime::setId(const std::string &id) {
    
    
    _id = id;
}
}

void Crime::setCode(const std::string &code) {
    
    _code = code;
}

void Crime::setGroup(const std::string &group) {
    
    _group = group;
}

void Crime::setDescription(const std::string &description) {
    
    _description = description;
}

void Crime::setDistrict(const std::string &district) {
}

void Crime::setAreaReport(const std::string &areaReport) {
}

void Crime::setStreet(const std::string &street) {
}

void Crime::setShooting(bool shooting) {
}

void Crime::setDateTime(const string & time) {
}

void Crime::setLocation(const Coordinates & coordinates) {
}

void Crime::set(const std::string & line) {
    const int NFIELDS = 12;
    string data;        //piece of data detached from line;
    size_t pos, posn;   // aux for the beginning of the fields
 
    pos = 0;
    posn = line.find(',', pos); // beginning of the next field
    for (int nfield = 0; nfield < NFIELDS - 1 && posn != string::npos; nfield++) {
        data = line.substr(pos, posn - pos);
        pos = posn + 1;

        switch (nfield) {
            case 0: // counter
                setCounter(stoi(data));
                break;
            case 1: // ID
                setId(data);
                break;
            case 2: // code
                setCode(data);
                break;
            case 3: // group
                setGroup(data);
                break;
            case 4: // desc
                setDescription(data);
                break;
            case 5: // District alphaNumeric
                ...
        }
  ...
} //end of set()

void Trim(string & myString) {
}

void Capitalize(string & myString) {
}

void Normalize(Crime & crime) {
}
