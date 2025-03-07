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
#include <cctype>

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
    
    set(line);
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
    
    
    string crimen = to_string(_counter) + "," +_id + "," + _code + "," +
        _group + "," + _description + "," + _district + "," + _areaReport +
          "," + to_string(_shooting) + "," + _dateTime.toString() + "," +
        _street + "," + _location.toString();
    
    return crimen;
}

void Crime::setCounter(int c) {
    
    _counter = c;
}

void Crime::setId(const std::string &id) {
    string trimmedId = id;
    Trim(trimmedId); //quitamos espacios del inicio y el final
    if (trimmedId.size() == 0){
        //primero describimos donde se da el error y luego describimos el error
        throw std::invalid_argument(
                std::string("void Crime::setId(const std::string &id): ") + 
                "id esta vacio");
    }
    
    this->_id = trimmedId;
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
    
    _district = district;
}

void Crime::setAreaReport(const std::string &areaReport) {
    
    _areaReport = areaReport;
}

void Crime::setStreet(const std::string &street) {
    
    _street = street;
}

void Crime::setShooting(bool shooting) {
    
    _shooting = shooting;
}

void Crime::setDateTime(const string & time) {
    
    _dateTime = time;
}

void Crime::setLocation(const Coordinates & coordinates) {
    
    _location = coordinates;
}

void Crime::set(const std::string & line) {
    const int NFIELDS = 12;
    string data;        //piece of data detached from line;
    size_t pos, posn;   // aux for the beginning of the fields
 
    Coordinates coords;
    
    pos = 0;
    posn = line.find(',', pos); // beginning of the next field
    for (int nfield = 0; nfield < NFIELDS - 1 && posn != string::npos; nfield++) {
        posn = line.find(',', pos); // Actualizar posn en cada iteración
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
                setDistrict(data);
                break;
            case 6: // Area Report
                setAreaReport(data);
                break;
            case 7: // Shooting
                setShooting(stoi(data));
                break;
            case 8: // DateTime
                setDateTime(data);
                break;
            case 9: // Street
                setStreet(data);
                break;
                
        } // switch
        
        
    } // for
        coords.setLatitude(stod(data));
        
         posn = line.find(',', pos);
         data = line.substr(pos, posn - pos);
      
        coords.setLongitude(stod(data));
                
        setLocation(coords);

} //end of set()

void Trim(string & myString) {
    
    // Eliminar espacios y tabulaciones al principio
    
    size_t start = 0;
    while (start < myString.length() && isspace(myString.at(start))) start++;
    
    // Eliminar espacios y tabulaciones al final
    
    size_t end = myString.length();
    while (end > start && isspace(myString[end-1])) end--;
    
    // Crear subcadena que contenga solo los caracteres relevantes
    
    myString = myString.substr(start, end - start);
}

void Capitalize(string & myString) {
    
    string nueva;
    int longitud = myString.length();
    
    for (int i = 0; i < longitud; i++){
        
        nueva += toupper(myString.at(i));
    }
    
    myString = nueva;
}

void Normalize(Crime & crime) {
    
    string id = crime.getId();
    Capitalize (id);
    Trim(id);
    crime.setId(id);
    
    string group = crime.getGroup();
    Capitalize (group);
    Trim(group);
    crime.setGroup(group);
    
    string description = crime.getDescription();
    Capitalize (description);
    Trim(description);
    crime.setDescription(description);
    
    string district = crime.getDistrict();
    Capitalize (district);
    Trim(district);
    crime.setDistrict(district);
    
    string street = crime.getStreet();
    Capitalize (street);
    Trim(street);
    crime.setStreet(street);
    
    string code = crime.getCode();
    Capitalize (code);
    Trim(code);
    crime.setCode(code);
    
    string areareport = crime.getAreaReport();
    Capitalize (areareport);
    Trim(areareport);
    crime.setAreaReport(areareport);
    
}
