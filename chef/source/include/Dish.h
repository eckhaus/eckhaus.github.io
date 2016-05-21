#ifndef DISH_H
#define DISH_H

#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

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


class Dish: public std::deque<StackInfo>
{
public:
    int ID;

    void print (std::ostream * os); /**< Print out the stack */
    bool popTop (StackInfo & i); /**< Pop top of the stack into i */
    void append (const Dish & d); /**< Append stack d to the end of this stack */

    void liquify (); /**< Convert all items in the stack to liquids (characters) */
    void stir (unsigned int places); /** Pushes top of the stack 'places' items deeper into the stack */
    void randomize (); /** Shuffle the stack */
};

/** \brief Stack (Dish) used as a output stack.*/
typedef   Dish BakingDish;
/** \brief Stack (Dish) used as a memory stack.*/
typedef   Dish MixingBowl;

#endif // DISH_H
