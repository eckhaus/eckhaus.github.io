#include "../include/Recipe.h"

using namespace std;
Recipe::Recipe() {};

Recipe::Recipe(const Recipe& rhs)
{
    os = rhs.os;
    trace  = rhs.trace;
    parent = rhs.parent;
    name = rhs.name;
    comments =  rhs.comments;
    ingredients.insert(rhs.ingredients.begin(), rhs.ingredients.end());
    //    mixingBowls.insert(rhs.mixingBowls.begin(), rhs.mixingBowls.end());
    commands.clear();
    commands= rhs.commands;
    jumps.insert(rhs.jumps.begin(), rhs.jumps.end());
    auxliary.insert(rhs.auxliary.begin(), rhs.auxliary.end());
};

void Recipe::addIngredient (Ingredient i)
{
    ingredients[i.name] = i;
}

string Recipe::typeToString (IngredientType it)
{
    if (it == IngredientType::Dry)
        return "dry";
    else if (it == IngredientType::Liquid)
        return "liquid";
    else
        return "unspecified";
}


void Recipe::printInfo (bool printAux,  bool bowls_only)
{
    if (!bowls_only)
    {
        *os << " [ " << name << " ] "<< endl;
        for (size_t i = 0; i<name.size()+6; i++)
            *os << '-';
        *os << endl;

        *os << comments << endl;

        *os << endl << "Bowls" << endl;
    }
    for (auto  &mb : mixingBowls) mb.second.print(os);

    if (!bowls_only)
    {
        *os << endl << "Ingredients" << endl;
        for (auto & in : ingredients) *os << in.second.name <<  "#\t\t" << in.second.value << " : "  << typeToString(in.second.type)<< endl;

        *os << endl <<"Jumps" << endl;
        for (auto  &mb : jumps) *os << mb.first << ": " << mb.second.begin << " " << mb.second.end << endl;

        *os << endl <<"Commands" << endl;
        int i = 0;
        for (auto  &mb : commands) *os << i++ << '\t' << mb.cmd << " " << mb.arg1 << " " << mb.arg2<< endl;

        if (printAux)
            for (auto a: auxliary)
                a.second.printInfo(false);
    }
}

bool Recipe::toNum (const string & s, int & n)
{
    try
    {
        n= std::stoi( s );
        return true;
    }
    catch(...)
    {
        return false;
    }
}

void Recipe::addAuxliary (Recipe & aux)
{
    aux.isAuxliary = true;
    aux.parent = parent;
    auxliary [aux.name] = aux;
}

void Recipe::addCommand (string cmd = "", string arg1 = "", string arg2 = "")
{
    commands.push_back (Command(cmd, arg1, arg2));
}

void Recipe::processCommand (string cmd, string arg1 = "", string arg2 = "")
{
    int n, n1;
    bool isNumber = toNum(arg2, n);

    if (cmd == "refr")
    {
        currentCommand = 1000000;
        if (isAuxliary)
            return;
        else if (toNum(arg1, n1))
        {
            for (int i = 0; i< n1; i++)
                bakingDishes[i].print(os);
        }
    }
    else if  (cmd == "serve")
    {
        call (arg1);
    }
    else if (cmd == "jump")
    {
        doJump(jumps[arg1]); // pozn. pripisat na IDs miest neunikatnych mien
    }
    else if (cmd == "setaside")
    {
        setAside();
    }
    else if (cmd == "until")
    {
        doUntil(jumps[arg1]);
    }
    else if (cmd == "take")
    {
        takeFromFridge(arg1);
    }
    else if (cmd == "put")
    {
        if (isNumber) put (arg1, n);
        else put(arg1);
    }
    else if (cmd == "fold")
    {
        if (isNumber) fold (arg1, n);
        else fold(arg1);
    }
    else if (cmd == "add")
    {
        if (isNumber) add (arg1, n);
        else add(arg1);
    }
    else if (cmd == "remove")
    {
        if (isNumber) remove (arg1, n);
        else remove(arg1);
    }
    else if (cmd == "combine")
    {
        if (isNumber) combine (arg1, n);
        else combine(arg1);
    }
    else if (cmd == "divide")
    {
        if (isNumber) divide (arg1, n);
        else divide(arg1);
    }
    else if (cmd == "stir_ingred")
    {
        if (isNumber) stirIngredient (arg1, n);
        else stirIngredient(arg1);
    }
    else if (cmd == "addDry")
    {
        if (toNum(arg1, n))
        {
            addDry(n);
        }
        else
            addDry();
    }
    else if (cmd == "liquify")
    {
        liquify(arg1);
    }
    else if (cmd == "liquify_contents")
    {
        int n2 = 1;
        toNum(arg1, n2);
        mixingBowls[n2].liquify();
    }
    else if (cmd == "stir")
    {
        int n1;
        if (toNum(arg1, n1))
        {
            if (toNum(arg2, n))
                stir(n1,n);
            else
                stir(n1);
        }
        else return;
    }

    else if (cmd == "mix")
    {
        if (toNum(arg1, n))
        {
            mix(n);
        }
        else
            mix();
    }

    else if (cmd == "clean")
    {
        if (toNum(arg1, n))
        {
            clean(n);
        }
        else
            clean();
    }

    else if (cmd == "pour")
    {
        int mb = 1;
        int bd = 1;
        toNum(arg1, mb);
        toNum(arg2, bd);
        pour (mb, bd);
    }


    if (trace)
    {
        (*os) << "-------------" << endl;
        (*os) << "[" <<  currentCommand << "] " << name << "> " << cmd << "\t" << arg1 << "\t" << arg2 << endl;
        printInfo(false, true);

        //(*os) << "Press Enter to Continue";
        cin.ignore();
    }
}

int Recipe::run ()
{
    currentCommand = 0;
    while (currentCommand < commands.size())
    {
        processCommand(commands[currentCommand].cmd,
                       commands[currentCommand].arg1,
                       commands[currentCommand].arg2);
        currentCommand++;
    }

    // Output the baking dishes only for the main procedure
    if (!isAuxliary)
        for (int i = 1; i<= serves; i++)
            bakingDishes[i].print(os);
    return 0;
};

int Recipe::call (string aux)
{
    // make new recipe
    Recipe r (parent->auxliary[aux]);
    r.parent = parent;
    // copy contents of parent process's mixing bowl
    r.mixingBowls.clear();
    r.mixingBowls.insert(mixingBowls.begin(), mixingBowls.end());
    r.isAuxliary = true;
    // run it and udpate appropriate mixing bowls
    if (trace)
    {
        (*os) << "Call from " << name << endl;
        (*os) << "=======" << aux << "=======" << endl;
    }
    int i = r.run();

    if (trace)
    {
        (*os) << "Returning from " << aux << endl;
        (*os) << "=======" << name << "=======" << endl;
    }
    mixingBowls[1].append(r.mixingBowls[1]);

    return i;
}

void Recipe::addJump (const string & verb, const string & ingredient)
{
    // Register jump in jumps map
    Jump j;
    j.begin_ingredient = ingredient;
    j.verb = verb;
    j.begin = commands.size();
    jumps[verb] = j;

    // Add jump command to commands vector
    Command cm;
    cm.cmd = "jump";
    cm.arg1 = verb;
    commands.push_back(cm);
}

void Recipe::addUntil (const string & verb, string ingredient = "")
{
    // Register jump in jumps map
    jumps[verb].end_ingredient = ingredient;
    jumps[verb].end = commands.size();

    // Add jump command to commands vector
    Command cm;
    cm.cmd = "until";
    cm.arg1 = verb;
    commands.push_back(cm);
}

void Recipe::doJump (Jump & j)
{
    jumpsStack.push (j);

    if (ingredients[j.begin_ingredient].value== 0)
    {
        currentCommand = j.end;
        jumpsStack.pop();
    }
}

void Recipe::doUntil (Jump & j)
{
    if (j.end_ingredient != "")
        ingredients[j.end_ingredient].value--;


    if (ingredients[j.begin_ingredient].value== 0)
    {
        jumpsStack.pop();
    }
    else
        currentCommand = j.begin;
}

StackInfo Recipe::ingrToStack (const Ingredient & i)
{
    return StackInfo (i.value, i.type == IngredientType::Liquid);
}

void Recipe::setAside ()
{
    (*os) << "jsSize: " << jumpsStack.size() << endl;
    currentCommand = jumpsStack.top().end;
    jumpsStack.pop();
}

void Recipe::takeFromFridge (const string & ingredient)
{
    string s;
    (*os) << "Please enter value for [" << ingredient << "]: ";
    cin >> s;
    Ingredient i;
    toNum(s, i.value);
    i.name = ingredient;
    ingredients[ingredient] = i;
}

void Recipe::put (const string & ingredient, int bowlNo)
{
    mixingBowls[bowlNo].push(ingrToStack(ingredients[ingredient]));
}

void Recipe::fold (const string & ingredient, int bowlNo)
{
    StackInfo si;
    mixingBowls[bowlNo].popTop(si);
    ingredients[ingredient].value = si.value;
    ingredients[ingredient].type = (si.liquid ? IngredientType::Liquid : IngredientType::Dry);
}

void Recipe::add (const string & ingredient, int bowlNo)
{
    StackInfo i;
    if (mixingBowls[bowlNo].popTop(i))
        i.value+=ingredients[ingredient].value;
    mixingBowls[bowlNo].push(i);
}

void Recipe::remove (const string & ingredient, int bowlNo)
{
    StackInfo i;
    if (mixingBowls[bowlNo].popTop(i))
        i.value-=ingredients[ingredient].value;
    mixingBowls[bowlNo].push(i);
}

void Recipe::combine (const string & ingredient, int bowlNo)
{
    StackInfo i;
    if (mixingBowls[bowlNo].popTop(i))
        i.value*=ingredients[ingredient].value;
    mixingBowls[bowlNo].push(i);
}

void Recipe::divide (const string & ingredient, int bowlNo)
{
    StackInfo i;
    if (mixingBowls[bowlNo].popTop(i))
        i.value=ingredients[ingredient].value / i.value;
    mixingBowls[bowlNo].push(i);
}

void Recipe::addDry (int bowlNo)
{
    int sum = 0;
    for (auto it : ingredients)
    {
        if (it.second.type == IngredientType::Dry)
            sum+=it.second.value;
    }
    mixingBowls[bowlNo].push(sum);
}

void Recipe::liquify (string ingredient)
{
    ingredients[ingredient].type = IngredientType::Liquid;
}

void Recipe::stir (int times, int bowlNo)
{
    mixingBowls[bowlNo].stir(times);
}

void Recipe::stirIngredient (string ingredient, int bowlNo)
{
    mixingBowls[bowlNo].stir(ingredients[ingredient].value);
}

void Recipe::mix (int bowlNo)
{
    mixingBowls[bowlNo].randomize();
}

void Recipe::clean (int bowlNo)
{
    mixingBowls[bowlNo].clear();
}

void Recipe::pour (int bowlNo, int dishNo)
{
    bakingDishes[dishNo].append (mixingBowls[bowlNo]);
}
