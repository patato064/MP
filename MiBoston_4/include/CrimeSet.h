/*
 * Metodología de la Programación
 * Curso 2024/2025
 */

/** 
 * @file  CrimeSet.h
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * 
 * @note To be implemented by students 
 */

#ifndef CRIMESET_H
#define CRIMESET_H


#include <string>
#include <iostream>
#include <fstream>
#include <cmath>       /* ceil */

#include "DateTime.h"
#include "Crime.h"

/**
 * @class CrimeSet
 * @brief A CrimeSet defines a set of instances of the Crime class that includes 
 * data on crimes (offenses) committed anywhere in the world and with the types 
 * of crimes specifically considered within its own jurisdiction. 
 * This class uses a dynamic array of objects of the Crime class to store 
 * the set of crimes. 
 * This class also contains a field to store comments, free text that allows, 
 * for example, to describe in natural language the time period considered, 
 * the origin, the query applied to obtain the set, etc. 
 * In general, the records in the set are not sorted by date and time 
 * when each crime was committed. 
 * Usually the records appear in the order in which they were recorded when 
 * the crimes were collected by the police department.
 * The public methods of this class do not allow a CrimeSet to contain two 
 * Crime objects with identical IDs.
 * 
 * @see See the content of the files *.crm in the DataSets folder as examples
 * of files that contain information about CrimeSets
 */

class CrimeSet {
public:
     // Retrieve all previous declarations and take into account
    
    
     // Retrieve all previous declarations and take into account
     // the new declarations included here... 
     // 

    /**
     * @brief Basic constructor and initializer. It builds a CrimeSet object
     * with a set of of 0 Crimes and a capacity calculated as follows: 
     * - If size>=0 and size<INITIAL_CAPACITY, then the capacity of the
     * dynamic array will be set to INITIAL_CAPACITY. 
     * - If size>=INITIAL_CAPACITY, then the capacity of the dynamic array 
     * will be equals to size.
     * The field for the comments is set as an empty string
     * @throw std::out_of_range Throws a std::out_of_range exception if
     * @p size<0. In this case, the fields of the object are initialized 
     * as follows: 
     * - _comment = ""
     * - _capacity = 0
     * - _nCrimes = 0
     * - _crimes = nullptr 
     * After the fields are initialized as described above, the exception 
     * is thrown.
     * @param size The capacity that will have the dynamic array of Crimes
     * for this object
     */
    CrimeSet(int size=0);
    
    /**
     * @brief Copyructor. Builds a deep copy of the provided CrimeSet 
     * @p orig.   
     * @param orig CrimeSet original. Input parameter
     */
    CrimeSet(const CrimeSet &orig);
    
    /**
     * @brief Destructor
     */
    ~CrimeSet();

    /**
     * @brief Overloads the assignment operator for CrimeSet class.
     * Modifier method
     * @param orig the CrimeSet object used as source for the assignment. 
     * Input parameter
     * @return A reference to this object
     */
    CrimeSet & operator=(const CrimeSet & orig);
    
    /**
     * @brief Basic constructor and initializer. It builds a CrimeSet object
     * with a set of 0 Crimes and a capacity of DIM_VECTOR_CRIMES. The field for
     * the comments is set as an empty string
     */
    
    
    int getSize() const;
    
    /**
     * @brief Gets the capacity of the array of CrimeSet objects 
     * Query method
     * @return The capacity of the array of CrimeSet objects
     */
    int getCapacity() const;
    
    /**
     * @brief Returns the field comment of this CrimeSet. This is a string that
     * may be composed of zero or several lines of free text. 
     * Query method
     * @return A string with the lines of comments
     */
    std::string getComment() const;
    
    /**
     * @brief Sets the string comment for this CrimeSet object using
     * the provided string @p text. The string @p text can contain zero or 
     * several lines; each one ends with '\n'.
     * If the last line in the string  @p text does not end with '\n' then
     * the character '\n' will be appended at the end of the comment string
     * of this object.
     * If @p text is an empty string, the comment string of this object will
     * be an empty string
     * Modifier method
     * @param text string with several lines of comments. Input parameter
     */
    void setComment(const std::string & text);

    /**
     * @brief Obtains a string with information about this CrimeSet object, 
     * in the following format:
     * - First line, the number of crimes 
     * - A line for each Crime with information about that Crime. Each line
     * is obtained using the method Crime::toString()
     * Query method
     * @return string with information about this CrimeSet object
     */
    std::string toString() const;
    
    /**
     * @brief Removes all the Crimes from this object, leaving the container 
     * with a size of 0 and an empty comment
     * Modifier method
     */
    void clear();
    
    /**
     * @brief Appends the given Crime at the end of the array of Crimes of
     * this CrimeSet object, but only if that Crime was not found in this 
     * CrimeSet.  
     * @throw std::out_of_range Throws a std::out_of_range exception if the
     * number of elements in the array of Crimes is equals to the capacity
     * of that array. In that case, the array is full, and no more elements
     * can be appended to the array.
     * @param crime The Crime to append to this object. Input parameter
     * @return true if the given Crime was inserted in this CrimeSet object;
     * false otherwise
     */
    bool append(const Crime & crime);
    
    /**
     * @brief Gets the crime at the provided position
     * Query method
     * @param pos position in the CrimeSet. Input parameter
     * @throw std::out_of_range Throws an std::out_of_range exception if the 
     * provided position is not valid.
     * @return A reference to the Crime at the provided position
     */
    const Crime & at(int pos) const;
     
    /**
     * @brief Searches the provided Crime in the array of crimes in this
     * CrimeSet. If found, it returns the position where it was found. If not,
     * it returns -1. We consider that position 0 is the first crime in the 
     * list of crimes and this->getSize()-1 the last crime.
     * In order to find a crime, consider only equality in the ID field.
     * Query method
     * @param crime A crime. Input parameter
     * @param initialPos initial position where to do the search. 
     * Input parameter
     * @param finalPos final position where to do the search. Input parameter
     * @return If found, it returns the position where the crime 
     * was found. Otherwise it returns -1
     */
    int findCrime(const Crime & crime, int initialPos, int finalPos) const;

    /**
     * @brief Searches the provided Crime in the array of crimes in this
     * CrimeSet. If found, it returns the position where it was found. If not,
     * it returns -1. We consider that position 0 is the first crime in the 
     * list of crimes and this->getSize()-1 the last crime.
     * In order to find a crime consider only equality in the ID field.
     * Query method
     * @param crime A crime. Input parameter
     * @return If found, it returns the position where the crime 
     * was found. Otherwise it returns -1
     */
    int findCrime(const Crime & crime) const;
       
    /**
     * @brief Loads into this object the CrimeSet information stored in the 
     * given file. See files *.crm in the folder DataSets as example of files
     * with CrimeSet information. 
     * @note Note that this method should remove the Crime objects that 
     * this object previously contained.
     * @note This method throws an exception in some error cases (see below). 
     * Before throwing the corresponding exception, this method clears
     * the object (it calls to clear() method) to leave the object in a 
     * consistent state.
     * Modifier method
     * @param fileName The name of the file where the CrimeSet is stored. 
     * Input parameter
     * @throw std::ios_base::failure Throws a std::ios_base::failure exception 
     * if the given file cannot be opened or if an error occurs while reading
     * from the file. 
     * @throw throw std::invalid_argument Throws a std::invalid_argument 
     * exception if an invalid magic string is found in the given file
     * @throw std::out_of_range Throws a std::out_of_range exception if the 
     * number of crimes in the given file is negative.
     */
    void load(const std::string & fileName);
    
    /**
     * @brief Saves this CrimeSet object in the given file. 
     * @note This method sends each Crime to the output stream in the same 
     * format as the one described in the Crime::toString() method
     * Query method
     * @param fileName A string with the name of the file where this CrimeSet 
     * object will be saved. Input parameter
     * @throw std::ios_base::failure Throws a std::ios_base::failure exception 
     * if the given file cannot be opened or if an error occurs while writing
     * to the file
     */
    void save(const std::string & fileName);
    
    /**
     * @brief Appends to this CrimeSet object, the list of  
     * Crime objects contained in the provided CrimeSet @p crimeSet that are
     * not found (using CrimeSet::findCrime(Crime)) in this CrimeSet. 
     * This method could be implemented with the help of the method 
     * CrimeSet::append(Crime crime), to append to this 
     * CrimeSet, the Crimes of the provided CrimeSet @p crimeSet.
     * Modifier method
     * @param crimeSet A CrimeSet object. Input parameter
     */
    void join(const CrimeSet & crimeSet);
    
    /**
     * @brief Normalizes each one of the Crime objects in this CrimeSet
     * Modifier method
     */
    void normalize();

    /**
     * @brief It takes the array of Crimes of this object as input and 
     * calculates the cumulative frequency distribution of crimes (histogram) by 
     * days of the week or by hours of the day. The histogram is saved in the 
     * array @p histogram. 
     * The DateTime field of each Crime contains the information about when it 
     * took place.
     * Query method
     * @pre the array @p histogram should have enough capacity to save the 
     * calculated frequencies. Otherwise, possible runtime errors will be obtained 
     * @throw std::out_of_range if @p dataField is neither 0 nor 1
     * @param dataField Integer to select the type of calculation to be performed: 
     * - value 0 to calculate by day of the week 
     * - value 1 to calculate by hours of the day 
     * Input parameter
     * @param histogram output array where the cumulative frequencies will be saved. 
     * Input/output parameter
     */
    void computeHistogram(int dataField, int histogram[]) const;

    /**
     * @brief Returns a CrimeSet object with those crimes whose label of 
     * attribute is provided with the provided @p field parameter and whose 
     * value is equals to the provided @p value parameter. 
     * This function enables simple queries as: Code = "unknown" or 
     * Code = "3114" as well as Street = "WASHINGTON ST" or 
     * DateTime = dd.toString() (being dd, a DateTime object),
     * but no other relational operators as greater than, etc. 
     * The new CrimeSet will have the same comments as this object plus a line
     * with the content: "Restricted to " + field + " = " + value + "\n" 
     * Query method
     * @param field The label of the selected attribute of the Crime class. See
     * the description of method Crime::getField(string) for possible values. 
     * Input parameter
     * @param value The value of the selected attribute. Input parameter
     * @return A CrimeSet with the selected Crimes.
     */
    CrimeSet selectWhereEQ(const std::string & field, const std::string & value) const;

    /**
     * @brief Returns a CrimeSet object with those crimes whose latitude and 
     * longitude are both valid.
     * Example of invalid location for a crime are: 
     * - (91,100) latitude is out of range
     * - (90,181) longitude is out of range
     * - (181,181) both are not valid
     * The new CrimeSet will have the same comments as this object plus a line
     * with the content: "Restricted to valid Coordinates\n"" 
     * Query method
     * @return A CrimeSet with those crimes whose latitude and longitude are 
     * both valid
     */
    CrimeSet selectValidLocation() const;
    
    /**
     * Sorts the array of Crimes by increasing alphabetical order of the field 
     * with the DateTime (sorting by date and time when the Crime took place). 
     * If two Crimes objects have the same DateTime, then  increasing 
     * alphabetical order of the field ID of those two objects will  
     * be considered.
     * Modifier method
     */
    void sort();
    
     // the new declarations included here... 
     // ...

    
    /**
     * @brief Overloading of the [] operator for CrimeSet class
     * Query method
     * @param index index of the element 
     * @return Aant reference to the Crime object at position @p index
     */
    Crime operator[](int index);   

    /**
     * @brief Overloads the operator += for the CrimeSet class. It appends to 
     * this CrimeSet object, the list of Crime objects contained in the 
     * provided CrimeSet @p crimeSet that are not found in this CrimeSet.  
     * Modifier method
     * @param other The right CrimeSet operand. Input parameter
     * @return A reference to this object
     */
    CrimeSet operator+=(CrimeSet other);
    
    friend std::ostream operator<<(std::ostream os, CrimeSet crimeSet);
    friend std::istream operator>>(std::istream is, CrimeSet crimeSet);
    
private:
    
    
        
    static const int INITIAL_CAPACITY = 8; ///< Default initial capacity for the dynamic array _crimes. Should be a number >= 0

    /**
     * Ratio to be used to compute the next capacity to allocate in the
     * dynamic array of Crimes. When the dynamic array is full and a new
     * Crime must be appended, it is reallocated with a 
     * capacity calculated as ceil(_capacity * GROWING_RATIO) 
     */
    static const float GROWING_RATIO; 
    
    static const std::string MAGIC_STRING_T; ///< A string with the magic string for text files

    /**
     * string that contains several lines of comments (text in natural 
     * language). Each line, except possibly the last one, ends with the 
     * character '\n'
     */
    std::string _comment; 

    Crime *_crimes; ///< Pointer to a dynamic array of crimes
    int _nCrimes; ///< Number of used elements in the dynamic array _crimes
    int _capacity; ///< Number of reserved elements in the dynamic array _crimes
    

    // fill free to define as much method to manage the dynamic memory
    // ...
    /**
     * @brief Gets the crime at the provided position. 
     * Modifier method
     * @param pos position in the CrimeSet. Input parameter
     * @throw std::out_of_range Throws an std::out_of_range exception if the 
     * given pos is not valid
     * @return A reference to the Crime at the given position.
     * 
     */
    
    void allocate (int capacidad);
    
    void deallocate();
    
    void copy(const CrimeSet &original);
    
    void reallocate();
    
    Crime & at(int pos);
    
    /**
     * @brief Reads comment lines from the provided input stream and appends
     * them to the end of the string _comment. 
     * In the provided input stream, comment lines are text lines that 
     * begin with the character '#'.
     * This method reads lines until a line is read that does not begin with 
     * the '#' character.
     * The '#' characters will not be saved in the string _comment, that is, 
     * this character will be discarded.
     * In the string _comment, each comment line will have the character '\n' at
     * the end.
     * @param inputStream input stream from which comments will be read 
     */
    void readComments(std::istream & inputStream);

    /**
     * @brief Saves the line comments contained in the field _comment in the 
     * provided output stream. Each line will be saved as '#' plus the content
     * of that line. This method can be easily implemented with the help of the 
     * function FormatAsComment()
     * Query method
     * @param outputStream output stream where the comments will be saved
     */
    void saveComments(std::ostream &outputStream)const;
    
    // Retrieve all previous declarations 
    
   /**
     * @brief Overloading of the [] operator for CrimeSet class
     * Modifier method
     * @param index index of the element 
     * @return A  reference to the Crime object at position @p index
     */
    Crime operator[](int index);
    
    

};
/**
 * @brief Overloading of the stream insertion operator for CrimeSet class.
 * @note This operator sends each Crime to the output stream in the same 
 * format as the one described in the Crime::toString() method
 * @param os The output stream to be used. Input/output parameter
 * @param crimeSet the CrimeSet object. Input parameter
 * @return @p os A reference to the output stream
 */
std::ostream operator<<(std::ostream os, const CrimeSet crimeSet);

/**
 * @brief Overloading of the stream extraction operator for CrimeSet class.
 * @note This operator should remove any crime previously contained in the
 * provided CrimeSet @p crimeSet.
 * @note This operator throws an exception in some error cases (see below). 
 * Before throwing the corresponding exception, this operator clears
 * the provided object (it calls to clear() method) to leave it in a 
 * consistent state.
 * @note This operator does not read the lines of comments, only the information
 * about crimes (an integer n with the number of crimes and n lines with Crime 
 * information).
 * @throw std::out_of_range Throws a std::out_of_range if the number of Crimes
 * read from the file is negative.
 * @param is The input stream to be used. Input/output parameter
 * @param crimeSet The CrimeSet object to be filled. Input/output parameter
 * @return @p is A reference to the input stream
 */
std::istream  operator>>(std::istream is, CrimeSet crimeSet);
#endif	// CRIMESET_H

