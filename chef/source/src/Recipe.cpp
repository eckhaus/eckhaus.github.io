#include "../include/Recipe.h"

using namespace std;
Recipe::Recipe() {};

Recipe::Recipe(const Recipe& rhs)
{
	os = rhs.os;
	trace = rhs.trace;
	parent = rhs.parent;
	name = rhs.name;
	comments = rhs.comments;
	ingredients.insert(rhs.ingredients.begin(), rhs.ingredients.end());
	commands.clear();
	commands = rhs.commands;
	jumps.insert(rhs.jumps.begin(), rhs.jumps.end());
	auxliary.insert(rhs.auxliary.begin(), rhs.auxliary.end());
};

void Recipe::addIngredient(Ingredient i)
{
	ingredients[i.name] = i;
}

string Recipe::typeToString(IngredientType & it)
{
	if (it == IngredientType::Dry)
		return "dry";
	else if (it == IngredientType::Liquid)
		return "liquid";
	else
		return "unspecified";
}


void Recipe::printInfo(bool printAux, bool bowls_only)
{
	if (!bowls_only)
	{
		*os << " [ " << name << " ] " << endl;
		for (size_t i = 0; i<name.size() + 6; i++)
			*os << '-';
		*os << endl;

		*os << comments << endl;

		*os << endl << "Bowls" << endl;
	}
	for (auto &mb : mixingBowls) mb.second.print(os);

	if (!bowls_only)
	{
		*os << endl << "Ingredients" << endl;
		for (auto & in : ingredients) *os << in.second.name << "#\t\t" << in.second.value << " : " << typeToString(in.second.type) << endl;

		*os << endl << "Jumps" << endl;
		for (auto &mb : jumps) *os << mb.first << ": " << mb.second.begin << " " << mb.second.end << endl;

		*os << endl << "Commands" << endl;
		int i = 0;
		for (auto &mb : commands) *os << i++ << '\t' << mb.cmd << " " << mb.arg1 << " " << mb.arg2 << endl;

		if (printAux)
			for (auto a : auxliary)
				a.second.printInfo(false);
	}
}

bool Recipe::toNum(const string & s, int & n)
{
	try
	{
		n = std::stoi(s);
		return true;
	}
	catch (...)
	{
		return false;
	}
}

void Recipe::addAuxliary(Recipe & aux)
{
	aux.isAuxliary = true;
	aux.parent = parent;
	auxliary[aux.name] = aux;
}

void Recipe::addCommand(const string & cmd = "", const string & arg1 = "", const string & arg2 = "")
{
	commands.push_back(Command(cmd, arg1, arg2));
}

void Recipe::processCommand(const string & cmd, const string & arg1 = "", const string & arg2 = "")
{
	int arg2_val = 1, arg1_val = 1;
	bool isArg2Numeric = toNum(arg2, arg2_val);
	bool isArg1Numeric = toNum(arg1, arg1_val);


	if (cmd == "refr") {
		currentCommand = commands.size() + 1;
		if (isAuxliary)
			return;
		else if (isArg1Numeric)
			for (int i = 1; i <= arg1_val; i++)
				bakingDishes[i].print(os);
	}
	else if (cmd == "serve")
		call(arg1);
	else if (cmd == "jump")
		doJump(jumps[arg1]);
	else if (cmd == "set aside")
		setAside();
	else if (cmd == "until")
		doUntil(jumps[arg1]);
	else if (cmd == "take")
		takeFromFridge(arg1);
	else if (cmd == "liquify")
		liquify(arg1);
	else if (cmd == "put") {
		if (isArg2Numeric) put(arg1, arg2_val);
		else put(arg1);
	}
	else if (cmd == "fold") {
		if (isArg2Numeric) fold(arg1, arg2_val);
		else fold(arg1);
	}
	else if (cmd == "add") {
		if (isArg2Numeric) add(arg1, arg2_val);
		else add(arg1);
	}
	else if (cmd == "remove") {
		if (isArg2Numeric) remove(arg1, arg2_val);
		else remove(arg1);
	}
	else if (cmd == "combine") {
		if (isArg2Numeric) combine(arg1, arg2_val);
		else combine(arg1);
	}
	else if (cmd == "divide") {
		if (isArg2Numeric) divide(arg1, arg2_val);
		else divide(arg1);
	}
	else if (cmd == "stir into") {
		if (isArg2Numeric) stirIngredient(arg1, arg2_val);
		else stirIngredient(arg1);
	}
	else if (cmd == "add dry") {
		if (isArg1Numeric) addDry(arg1_val);
		else addDry();
	}
	else if (cmd == "liquify_contents")
		mixingBowls[arg1_val].liquify();
	else if (cmd == "stir") {
		if (isArg1Numeric && isArg2Numeric)
			stir(arg2_val, arg1_val);
		else if (isArg1Numeric)
			stir(arg1_val);
		else if (isArg2Numeric)
			stir(arg2_val, 1);
		else return;
	}
	else if (cmd == "mix") {
		if (isArg1Numeric) mix(arg1_val);
		else mix();
	}
	else if (cmd == "clean") {
		if (isArg1Numeric) clean(arg1_val);
		else clean();
	}
	else if (cmd == "pour") {
		pour(arg1_val, arg2_val);
	}
	else
		err("Unrecognized command.");

	if (trace)
	{
		(*os) << "-------------" << endl;
		(*os) << "[" << currentCommand << "] " << name << "> " << cmd << "\t" << arg1 << "\t" << arg2 << endl;
		printInfo(false, true);
		cin.ignore();
	}
}

int Recipe::run()
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
		for (int i = 1; i <= serves; i++)
			if (bakingDishes.count(i)!=0)
				bakingDishes[i].print(os);
	return 0;
};

int Recipe::call(const string & aux)
{
	// make new recipe
	Recipe r(parent->auxliary[aux]);
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

	// r.printInfo();

	mixingBowls[1].append(r.mixingBowls[1]);

	return i;
}

void Recipe::addJump(const string & verb, const string & ingredient)
{
	// Register jump in jumps map
	if (jumps.count(verb) == 0) {
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
	else err("Conflicting jump identifiers: " + verb);
}

void Recipe::addUntil(const string & verb, const string & ingredient = "")
{
	// Register jump in jumps map
	if (jumps.count(verb) != 0) {
		jumps[verb].end_ingredient = ingredient;
		jumps[verb].end = commands.size();

		// Add jump command to commands vector
		Command cm;
		cm.cmd = "until";
		cm.arg1 = verb;
		commands.push_back(cm);
	}
	else err("Unmatched jump: " + verb);
}

void Recipe::doJump(Jump & j)
{
	jumpsStack.push(j);
	if (ingredients.count(j.begin_ingredient) == 0)
		err("Testing nonexisting ingredient \"" + j.begin_ingredient + "\"");
	if (ingredients[j.begin_ingredient].value == 0)
	{
		currentCommand = j.end;
		jumpsStack.pop();
	}
}

void Recipe::doUntil(Jump & j)
{

	if (j.end_ingredient != "") {
		if (ingredients.count(j.end_ingredient) == 0)
			err("Decrementing nonexisting ingredient \"" + j.end_ingredient + "\"");
		ingredients[j.end_ingredient].value--;
	}

	if (ingredients[j.begin_ingredient].value == 0)
		jumpsStack.pop();
	else
		currentCommand = j.begin;
}

StackInfo Recipe::ingrToStack(const Ingredient & i)
{
	return StackInfo(i.value, i.type == IngredientType::Liquid);
}

void Recipe::setAside()
{
	currentCommand = jumpsStack.top().end;
	jumpsStack.pop();
}

void Recipe::takeFromFridge(const string & ingredient)
{
	string s;
	(*os) << "Please enter value for [" << ingredient << "]: ";
	cin >> s;
	Ingredient i;
	toNum(s, i.value);
	i.name = ingredient;
	i.type = IngredientType::Dry;
	ingredients[ingredient] = i;
	//printInfo();
}

void Recipe::put(const string & ingredient, int bowlNo)
{
	if (ingredients.count(ingredient) == 0)
		err("Putting nonexisting ingredient +\"" + ingredient + "\"");
	mixingBowls[bowlNo].push_back(ingrToStack(ingredients[ingredient]));
}

void Recipe::fold(const string & ingredient, int bowlNo)
{
	StackInfo si;
	if (ingredients.count(ingredient) == 0)
		err("Folding nonexisting ingredient \"" + ingredient + "\"");
	if (mixingBowls[bowlNo].popTop(si)) {
		ingredients[ingredient].value = si.value;
		ingredients[ingredient].type = (si.liquid ? IngredientType::Liquid : IngredientType::Dry);
	}
	else err("Folding ingredient \"" + ingredient + "\" " + "into an empty stack.");

}

void Recipe::add(const string & ingredient, int bowlNo)
{
	if (ingredients.count(ingredient) == 0)
		err("Adding nonexisting ingredient +\"" + ingredient + "\"");
	StackInfo i;
	if (mixingBowls[bowlNo].popTop(i))
		i.value += ingredients[ingredient].value;
	mixingBowls[bowlNo].push_back(i);
}

void Recipe::remove(const string & ingredient, int bowlNo)
{
	if (ingredients.count(ingredient) == 0)
		err("Removing nonexisting ingredient +\"" + ingredient + "\"");
	StackInfo i;
	if (mixingBowls[bowlNo].popTop(i))
		i.value -= ingredients[ingredient].value;
	mixingBowls[bowlNo].push_back(i);
}

void Recipe::combine(const string & ingredient, int bowlNo)
{
	if (ingredients.count(ingredient) == 0)
		err("Combining nonexisting ingredient +\"" + ingredient + "\"");
	StackInfo i;
	if (mixingBowls[bowlNo].popTop(i))
		i.value *= ingredients[ingredient].value;
	mixingBowls[bowlNo].push_back(i);
}

void Recipe::divide(const string & ingredient, int bowlNo)
{
	if (ingredients.count(ingredient) == 0)
		err("Dividing nonexisting ingredient +\"" + ingredient + "\"");
	StackInfo i;
	if (mixingBowls[bowlNo].popTop(i))
		i.value = i.value / ingredients[ingredient].value;
	mixingBowls[bowlNo].push_back(i);
}

void Recipe::addDry(int bowlNo)
{
	int sum = 0;
	for (auto it : ingredients)
	{
		if (it.second.type == IngredientType::Dry)
			sum += it.second.value;
	}
	mixingBowls[bowlNo].push_back(sum);
}

void Recipe::liquify(const string & ingredient)
{
	if (ingredients.count(ingredient) == 0)
		err("Liquefying nonexisting ingredient +\"" + ingredient + "\"");
	ingredients[ingredient].type = IngredientType::Liquid;
}

void Recipe::stir(int times, int bowlNo)
{
	mixingBowls[bowlNo].stir(times);
}

void Recipe::stirIngredient(const string & ingredient, int bowlNo)
{
	if (ingredients.count(ingredient) == 0)
		err("Stirring nonexisting ingredient +\"" + ingredient + "\"");
	mixingBowls[bowlNo].stir(ingredients[ingredient].value);
}

void Recipe::mix(int bowlNo)
{
	mixingBowls[bowlNo].randomize();
}

void Recipe::clean(int bowlNo)
{
	mixingBowls[bowlNo].clear();
}

void Recipe::pour(int bowlNo, int dishNo)
{
	bakingDishes[dishNo].append(mixingBowls[bowlNo]);
}