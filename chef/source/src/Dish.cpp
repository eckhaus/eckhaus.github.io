#include "../include/Dish.h"

bool Dish::popTop (StackInfo & i){
    if (size() > 0) {
        i = back();
        pop_back();
        return true;
    }
    return false;
}

void Dish::print (ostream * os){
    for (auto & x : *this)
        if (x.liquid) *os << (char)x.value;
        else *os << x.value <<  " ";

    if (empty()) *os << "Empty";
    *os << endl;
}

void Dish::liquify (){
    std::for_each(begin(), end(), [](StackInfo & si) {si.liquid = true;});
}

void Dish::stir (int places){
    StackInfo i;
    if (!popTop(i)) return;
    std::deque<StackInfo>::iterator it = begin();
    if (size() >= places)
        it+= size() - places;
    insert (it,i);
}

void Dish::randomize (){
  random_shuffle(begin(), end());
}

void Dish::append (const Dish & d){
  copy(d.begin(), d.end(), inserter(*this, end()));
}
