#make CXX=g++-5
main:
	$(CXX) -std=c++11 -c -o main.o source/main.cpp
	$(CXX) -std=c++11 -c -o dish.o source/src/Dish.cpp
	$(CXX) -std=c++11 -c -o ingredient.o source/src/Ingredient.cpp
	$(CXX) -std=c++11 -c -o recipe.o source/src/Recipe.cpp
	$(CXX) -std=c++11 -c -o program.o source/src/Program.cpp
	$(CXX) -std=c++11 -o chef main.o dish.o  ingredient.o program.o recipe.o  -lm
	rm *.o

