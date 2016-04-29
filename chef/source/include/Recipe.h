#ifndef RECIPE_H
#define RECIPE_H

#include "Dish.h"
#include "Ingredient.h"
#include <map>

using namespace std;

/// Stores command's name and arguments

struct Command
{
    string cmd;
    string arg1;
    string arg2;

    Command () {};
    Command  (string cmd, string arg1, string arg2) : cmd(cmd), arg1(arg1) , arg2(arg2) {};
};

/// Describes a single jump (used in loop statements)

struct Jump
{
    int begin; // position in recipe
    int end; // position in recipe
    string verb;
    string begin_ingredient;
    string end_ingredient;
};

/// Stores all the information about recipes & executes their commands.

/** Recipes in chef represent procedures. They contain variables (mixing bowls and baking dishes),
 *  instructons (recipe steps) and other information. Recipe class stores all this data and handles
 *  execution of the commands.
 */

class Recipe
{
public:
    Recipe * parent; /**< parent is the recipe that created this recipe. Main procedure is parent of itself. */

    string name; /**< Name of the Recipe */
    string comments; /**< Optional description following Recipe's name. */
    int serves; /**< How many mixing bowls will be printed out when the program ends. Applicable only to main procedure */

    bool trace = false; /**< Is tracing (step-by-step execution) turned on? */

    Recipe();
    Recipe(const Recipe& rhs);
    int run (); /**< Executes the Recipe */

    /** Prints out all the relevant attributes of the Recipe. Name, comments, ingredients and commands.
     *  Defaultly show information only for main recipe, not for auxliary ones.
     *  @param printAux If set to true, prints also auxliary recipes' data
     *  @param bowls_only Print only bowls
     */
    void printInfo (bool printAux = false,  bool bowls_only = false);

    /** Adds a command to the Recipe
      * @param cmd Command name
      * @param arg1 First argument
      * @param arg2 Second argument
    */
    void addCommand (string cmd, string arg1, string arg2);

    /** Adds a loop to the Recipe
      * @param verb Identifier of the loop (verb from the recipe)
      * @param ingredient Ingredient defining exit-condition of the loop (if ingredient==0 then break)
    */
    void addJump (const string & verb, const string & ingredient);

    /** Adds a loop-closing state to the Recipe
      * @param verb Identifier of the loop (verb from the recipe)
      * @param ingredient Ingredient to be decremented on each pass
    */
    void addUntil (const string & verb, string ingredient);

    /** Adds an ingredient to the Recipe
      * @param i Ingredient
    */
    void addIngredient (Ingredient i);

    /** Adds an auxliary recipe (sauce) to the Recipe
      * @param aux Auxliary recipe
    */
    void addAuxliary (Recipe & aux);
    ostream * os;
private:


    /** Instruction vector pointer */
    size_t currentCommand = 0;
    /** Mark the recipe as auxliary */
    bool isAuxliary = false;

    bool toNum (const string & s, int & n);
    string typeToString (IngredientType it);

    /** Processes single commands
      * @param cmd Command to be executed
      * @param arg1 First argument of the command
      * @param arg2 Second argument of the command
     */
    void processCommand (string cmd, string arg1, string arg2);

    // Variables & stacks

    /** Maps ingredient name to the actual ingredient object containing
      * ingredient's name, type and value */
    map <string, Ingredient> ingredients;

    /** Program stacks */
    map <int, MixingBowl> mixingBowls;
    /** Output stacks */
    map <int, BakingDish> bakingDishes;

    /** Commands vector. @link current_command point to last executed command in this vecto */
    vector<Command> commands;
    /** Auxliary recipes can be accessed by their names */
    map<string, Recipe> auxliary;
    /** Each jump (loop) has its own identifier (verb) */
    map<string, Jump> jumps;
    /** Jump stack is used in recursion. When the "set aside" (essentially break) command is issued, we need to readily
      * exit the innermost loop stored at the top of the jumpsStack. */
    stack<Jump> jumpsStack;


    StackInfo ingrToStack (const Ingredient & i);

    // Commands
    /** \defgroup Command
    *
    * \brief Chef language command as described <a href="http://www.dangermouse.net/esoteric/chef.html">here</a>.
    */
    //@{

    /** Do jump (check condition) */
    void doJump (Jump & j);
    /** End of jump (jump back to loop begining label) */
    void doUntil (Jump & j);
    /** Read value from standard input, store it in ingredient */
    void takeFromFridge (const string & ingredient);
    /** Put ingredient into the mixing bowl */
    void put (const string & ingredient, int bowlNo = 1);
    /** Remove the top value of the mixing bowl and store it in ingredient */
    void fold (const string & ingredient, int bowlNo = 1);
    /** Add value of given ingredient to the value on the top of the mixing bowl */
    void add (const string & ingredient, int bowlNo = 1);
    /** Subtract value of given ingredient from the value on the top of the mixing bowl */
    void remove (const string & ingredient, int bowlNo = 1);
    /** Multiply the value on the top of the mixing bowl by given ingredient's value */
    void combine (const string & ingredient, int bowlNo = 1);
    /** Divide the value on the top of the mixing bowl by given ingredient's value */
    void divide (const string & ingredient, int bowlNo = 1);
    /** Place the sum of quantities of dry ingredients on top of the mixing bowl */
    void addDry (int bowlNo = 1);
    /** Set ingredient's type to liquid (ASCII character) */
    void liquify (string ingredient);
    /** Move the top of the stack n positions deeper into the stack */
    void stir (int times, int bowlNo = 1);
    /** Stir the value of ingredient into the stack */
    void stirIngredient (string ingredient, int bowlNo = 1);
    /** Shuffle the stack randomly */
    void mix (int bowlNo = 1);
    /** Empty the stack */
    void clean (int bowlNo = 1);
    /** Copy the stack into the baking dish (output stack) */
    void pour (int bowlNo = 1, int dishNo = 1);
    /** Call auxliary recipe */
    int call (string aux);
    /** Break the innermost loop */
    void setAside ();

    //@}
};

#endif // RECIPE_H
