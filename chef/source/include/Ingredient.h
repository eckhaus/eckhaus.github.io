#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>


enum class IngredientType {Liquid, Dry, Unspecified};
enum class MeasureType{ml, l, dash, g, kg, pinch, cup, teaspoon, tablespoon, none};
enum class MeasureModifierType{heaped, level, none};

/** \brief Structure for program's variables - ingredients.*/
class Ingredient
{
public:
    std::string name; /**< Name of the ingredient */
    int value; /**< Value of the ingredient */
    IngredientType type; /** Type, can be Liquid, Dry or Unspecified */

    Ingredient () {};
    Ingredient (std::string name, int value, IngredientType type) : name(name), value(value), type(type) {};
};

#endif // INGREDIENT_H
