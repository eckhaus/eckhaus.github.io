#ifndef DISH_H
#define DISH_H

#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/** \brief Item stored in stack (Dish), stores value and type of Ingredient.*/

struct StackInfo
{
public:
    int value = 0; /**< Value of ingredient */
    bool liquid = false; /**< Is ASCII character? */
    StackInfo (int value, bool liquid) : value(value), liquid(liquid) {};
    StackInfo (int value) : value(value) {};
    StackInfo () {};
};

/** \brief Stack of Ingredients.*/

class Dish : public stack<StackInfo>
{
public:
    int ID;

    void print (ostream * os); /**< Print out the stack */
    bool popTop (StackInfo & i); /**< Pop top of the stack into i */
    void append (Dish d); /**< Append stack d to the end of this stack */

    void liquify (); /**< Convert all items in the stack to liquids (characters) */
    void stir (int places); /** Pushes top of the stack 'places' items deeper into the stack */
    void randomize (); /** Shuffle the stack */
    void clear (); /** Clear the stack */

private:
    void init (vector <int> & v); /** Initialize the stack with vector v */
    void rev (); /** Reverse the stack */
};

/** \brief Stack (Dish) used as a output stack.*/
class BakingDish : public Dish {};

/** \brief Stack (Dish) used as a memory stack.*/
class MixingBowl : public Dish {};


#endif // DISH_H
