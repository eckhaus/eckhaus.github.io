#ifndef PROGRAM_H
#define PROGRAM_H

#include "Recipe.h"
#include <regex>
#include <fstream>
#include <algorithm>

/**
 *  \brief Parses and interprets the source code. Handles the execution of the main script.
 */
class Program
{
public:
    void parse (); /**< Calls the parser. Parsed file is stored as  {@link main_recipe} */
  //  Program (string fileName) : fileName (fileName)  {};
    Program (string input, string output, bool v, bool t);

private:
    /** Stores the main chef script. */
    Recipe main_recipe;

    bool printParserOutput = false; /**< If true prints out the parser output (parsed commands and their parameters) */
    bool printProgramInfo = false; /**<  If true prints out detailed information about program's main method (recipe) using {@link Recipe::printInfo}. */
    bool printAuxiliaryPrograms = true; /**< If true outputs also information about auxliary recipes */
    bool trace = false; /**< When set to true, allows the user to exectue the script in step-by-step manner */

    /** Path to source code */
    string fileName;
    string outputName;
    istream * fs;
    ostream * os;

    /** Regexps for parsing chef commands (first argument denotes the command, second corresponding regexp)*/
    map <string, string> regexp_string;
    /** Position of relevant arguments in regexp for each chef command */
    map <string, vector<int>> parameter_positions;

    /** Replaces multiple spaces with single space, removes leading and trailing whitespace and converts the string to lowercase
      * @param s string to normalize */
    void normalize (string & s);

    /** Converts a string to corresponding IngredientType enum item.
      * @param s input string (e.g. "ml", "g" or "pinches")*/
    IngredientType typeFromString (const string & s);

    /** Sets up regular expressions for input parsing */
    void setUpRegex ();

    /** Reads name and comments from input file. Processes the file until the "Ingredients." line is found.
      *  If no such line is found, the source file is faulty, function returns false and the execution of the
      *  parser is stopped
      * @param r Recipe in which the output will be stored */
    bool LoadHeader (Recipe & r);

    /** Loads the ingredients. Proceeds line-by-line until the "Method." expression is found
      * @param r Recipe in which the output will be stored */
    void LoadIngredients (Recipe & r);

    /** Loads the whole recipe into r. Calls LoadHeader, LoadIngredients and then parses commands of the source file.
      * @param r Recipe in which the output will be stored */
    bool LoadRecipe (Recipe & r);


    bool parseCommand (Recipe & r, string & line);
};

#endif // PROGRAM_H
