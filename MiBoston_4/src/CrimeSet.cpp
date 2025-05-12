/*
 * Metodología de la Programación
 * Curso 2024/2025
 */

/** 
 * @file  CrimeSet.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * @note To be implemented by students 
 * Created on September 18, 2024, 5:43 PM
 */

#include "CrimeSet.h"

using namespace std;

const string CrimeSet::MAGIC_STRING_T="MP-CRIME-T-1.0";
const float  CrimeSet::GROWING_RATIO = 1.5;

CrimeSet::CrimeSet(int size){

    if (size < 0){
        
        _comment = "";
        _capacity = 0;
        _nCrimes = 0;
        _crimes = nullptr;
        
         throw std::out_of_range(
                std::string("CrimeSet::CrimeSet(int size): ") + 
                "size debe ser siempre mayor o igual que 0");
                
    } 
    
    //    allocate(INITIAL_CAPACITY);
    else if (size >= 0 && size < INITIAL_CAPACITY) {
        allocate(INITIAL_CAPACITY);
    } else if (size >= INITIAL_CAPACITY) {
        allocate(size);
    }
    _nCrimes = 0; //size;

}

CrimeSet::CrimeSet(const CrimeSet &orig){ // llamar a allocate() y llamar a copy()
    
    allocate (orig.getCapacity());
    copy(orig);
}

CrimeSet::~CrimeSet(){ //llamar a deallocate()
    
    deallocate();
}

CrimeSet& CrimeSet::operator=(const CrimeSet & orig){ 
    
    if (this != & orig){
        
        deallocate();
        
        allocate(orig.getCapacity());
        
        copy(orig);
    }
    
    return *this;
}

int CrimeSet::getSize() const{
    
    return _nCrimes;
}

int CrimeSet::getCapacity() const{
    
    return _capacity;
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

void CrimeSet::clear(){  // REVISAR
    
    deallocate();
    
    _comment = "";
    _nCrimes = 0;
}

bool CrimeSet::append(const Crime & crime){  //REVISAR (REDIMENSIONAR CUANDO NO QUEPA)
    
    bool encontrado = false;
    int i = 0;
    
    
    while (i < _nCrimes && !encontrado){
        
        if (_crimes[i].getId() == crime.getId()){
            encontrado = true;
        }           
        else i++;
    }
    
    if (!encontrado){
        
        if(_nCrimes >= _capacity){
            reallocate();
        }
        
        _crimes[_nCrimes] = crime;
        _nCrimes++;
    }
    
    return !encontrado;
}

const Crime & CrimeSet::at (int pos) const{
    
    if (0 > pos || pos > _nCrimes){
        throw std::out_of_range(std::string("const Crime & at(int pos) const: ") +
                "La posicion dada no es valida"); 
    }
    
    return _crimes[pos];
}

int CrimeSet::findCrime(const Crime & crime, int initialPos, int finalPos) const{
    
    int pos = initialPos;
    bool encontrado = false;
    
    
    if (initialPos >= 0 && finalPos < _nCrimes && initialPos <= finalPos){
            
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

void CrimeSet::load(const std::string & fileName){ // REVISAR
    
    string magica;
    
    this-> clear();
    
    allocate(INITIAL_CAPACITY);
    
    ifstream fentrada;
    fentrada.open(fileName);
    
    if (!fentrada.is_open()){
        
        throw std::ios_base::failure(
                std::string("void CrimeSet::load(const std::string & fileName): ") + 
                "el archivo no ha sido abierto correctamente");
    }
    
    else{
        
        getline(fentrada, magica);

        if (magica == MAGIC_STRING_T){

            readComments(fentrada);

            string num;
            getline(fentrada, num);

            int num_crimes = stoi(num);
            
            if (num_crimes < 0){
                
                throw std::out_of_range(
                std::string("void CrimeSet::load(const std::string & fileName): ") + 
                "El número de crímenes no puede ser negativo");
            }

            else{
                
                for (int i = 0; i < num_crimes; i++){

                    string crimen_actual;

                    getline(fentrada, crimen_actual);


                    if (!crimen_actual.empty()){

                       Crime crimen(crimen_actual);


                       this->append(crimen);
                    }

                }
            }

        }
        
        else{
            
            throw std::invalid_argument (std::string("void CrimeSet::load(const std::string & fileName): ") + 
                "MAGIC_STRING inválida");
        }

        fentrada.close();
    }
}


void CrimeSet::save(const std::string & fileName){ 
    
    ofstream fsalida;
    
    fsalida.open(fileName);
    
    if (!fsalida.is_open()){
        
        throw std::ios_base::failure(
                std::string("void CrimeSet::save(const std::string & fileName): ") + 
                "el archivo no ha sido abierto correctamente");
    }

    else{
        
        fsalida << MAGIC_STRING_T << endl;
        saveComments(fsalida);

        fsalida << toString();

        fsalida.close();
    }
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

// HACER METODO ALLOCATE PARA RESERVAR MEMORIA DINAMICA para usar en el constructor, constructor de copia, operador de asignación y clear()
    void CrimeSet::allocate(int capacidad){
        
        _crimes = nullptr;
        if (capacidad > 0){
            _crimes = new Crime[capacidad];
        }
        
        _capacity = capacidad;
    }

// HACER METODO PARA LIBERAR MEMORIA DINAMICA QUE TIENE RESERVADA UN OBJETO DE LA CLASE CRIMESET para usar en el destructor, operador de asignacion y clear()
    void CrimeSet::deallocate(){
        
        delete[] _crimes;
        _crimes = nullptr;
        _capacity = 0;
    }

// HACER METODO PARA COPIAR EL CONTENIDO DE UN OBJETO CRIMESET EN EL OBJETO IMPLICITO sin reservar ni 
// liberar memoria. para que funcione nos tenemos que asegurar que el oi tiene un array dinamico del mismo tamaño que el objeto a copiar. para usar en el constructor de copia y operador de asignacion
    void CrimeSet::copy(const CrimeSet &original){
        
        if (original.getCapacity() <= this->getCapacity()){ // No se utiliza el clear porque libera memoria dinámica
            
             _comment = "";
            _nCrimes = 0;
            
            for (int i = 0; i < original.getSize(); i++){ // No se utiliza el append porque puede reservar memoria diámica
                
                this->at(i) = original.at(i);
                _nCrimes++;
            }
            
            _comment = original.getComment();
        }
    }

// HACER UN METODO PARA REDIMENSIONAR EL ARRAY DINAMICO para usar en el append()
    void CrimeSet::reallocate(){
        
        _capacity *= GROWING_RATIO;
                
        Crime* auxiliar = new Crime[_capacity];
        
        for(int i = 0; i < _nCrimes; i++){
            
            auxiliar[i] = _crimes[i];
        }
        
        delete[] _crimes;
        
        _crimes = auxiliar;
        
    }

    Crime & CrimeSet::at (int pos){
    
    if (0 > pos || pos > _nCrimes){
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