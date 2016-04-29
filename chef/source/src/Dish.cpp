#include "../include/Dish.h"

void Dish::init (vector <int> & v)
{
    for (auto a : v)
        push(StackInfo(a));
}

void Dish::rev ()
{
    vector <StackInfo> v;
    while (!empty())
    {
        v.push_back(top());
        pop();
    }
    reverse(v.begin(), v.end());
    for (int i = v.size()-1; i>=0; i--)
        push(v[i]);
}

void Dish::print (ostream * os)
{
    vector <StackInfo> v;
    while (!empty())
    {
        v.push_back(top());
        pop();
    }

    for (int i = v.size()-1; i>=0; i--)
        push(v[i]);

    reverse(v.begin(), v.end());
    for (int i = v.size()-1; i>=0; i--)
    {
        if (v[i].liquid)
            *os << (char)v[i].value;
        else
            *os << v[i].value <<  " ";
    }

    if (empty()) *os << "Empty";
    *os << endl;
}

void Dish::liquify ()
{
    vector <StackInfo> v;
    while (!empty())
    {
        v.push_back(top());
        pop();
    }
    for (int i = v.size()-1; i>=0; i--)
    {
        v[i].liquid = true;
        push(v[i]);
    }
}

bool Dish::popTop (StackInfo & i)
{
    if (size() > 0)
    {
        i = top();
        pop();
        return true;
    }
    else
        return false;
}

void Dish::stir (int places)
{
    StackInfo i;
    if (!popTop(i)) return;
    vector<StackInfo> v;
    while (places-- && !empty())
    {
        v.push_back(top());
        pop();
    }
    push(i);
    for (int i = v.size(); i!=0; --i)
        push(v[i-1]);
}

void Dish::randomize ()
{
    vector<StackInfo> v;
    while (!empty())
    {
        v.push_back(top());
        pop();
    }
    random_shuffle(v.begin(), v.end());
    for (auto a: v)
        push(a);
}

void Dish::clear ()
{
    while (!empty())
        pop();
}

void Dish::append (Dish d)
{
    vector <StackInfo> v;
    while (!d.empty())
    {
        v.push_back(d.top());
        d.pop();
    }

    for (int i = v.size()-1; i>=0; i--)
        push(v[i]);
}
