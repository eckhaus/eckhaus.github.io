#include "../include/Program.h"
#include <sstream>

using namespace std;

Program::Program(string input, string output, bool t, bool v) : fileName(input), outputName(output), trace(t), printProgramInfo(v) {}

void Program::parse()
{
	main_recipe.parent = &main_recipe;

	// open input and output streams
	ifstream ifs;
	if (fileName != "") {
		ifs.open(fileName, ios::in);
		if (!ifs.good()) err("Could not open input stream.");
		fs = &ifs;
	}
	else
		fs = &cin;

	ofstream ofs;
	if (outputName != "") {
		ofs.open(outputName, ios::out);
		if (!ofs.good()) err("Could not open output stream.");
		os = &ofs;
	}
	else
		os = &cout;

	if (!fs->good()) return;
	// load regexps for command matching
	setUpRegex();

	// Load main recipe
	LoadRecipe(main_recipe);
	main_recipe.trace = trace;
	main_recipe.os = os;
	// Load auxliary recipes
	while (true)
	{
		Recipe aux;
		aux.trace = trace;
		aux.os = os;
		if (!LoadRecipe(aux))
			break;
		main_recipe.addAuxliary(aux);
	}
	if (printProgramInfo)
		main_recipe.printInfo(printAuxiliaryPrograms);
	ifs.close();
	main_recipe.run();
};

void Program::setUpRegex()
{
	// Common subexpressions for matching arguments
	string str = "([a-zA-Z0-9 -]+?)";
	string num = "( ([0-9]*)(th|st|nd|rd)){0,1}";
	string banCmd = "(?!take|fold|put|add|remove|combine|divide|add dry|liqu[ie]fy|stir|mix|clean|pour|set aside|serve|refrigerate)";

	regexp_string["put"] = ("put (?:the ){0,1}" + str + " (?:in){0,1}to(?: the){0,1}" + num + " (?:the ){0,1}mixing bowl.");
	regexp_string["fold"] = ("fold (?:the ){0,1}" + str + " (?:in){0,1}to(?: the){0,1}" + num + " (?:the ){0,1}mixing bowl.");
	regexp_string["add"] = ("add (?!dry)(?:the ){0,1}" + str + "( (?:in){0,1}to(?: the){0,1}" + num + " (?:the ){0,1}mixing bowl){0,1}.");
	regexp_string["remove"] = ("remove (?:the ){0,1}" + str + "( from(?: the){0,1}" + num + " (?:the ){0,1}mixing bowl){0,1}.");
	regexp_string["combine"] = ("combine (?:the ){0,1}" + str + "( (?:in){0,1}to(?: the){0,1}" + num + " (?:the ){0,1}mixing bowl){0,1}.");
	regexp_string["divide"] = ("divide (?:the ){0,1}" + str + "( (?:in){0,1}to(?: the){0,1}" + num + " (?:the ){0,1}mixing bowl){0,1}.");
	regexp_string["add dry"] = ("add dry ingredients( to(?: the){0,1}(?: the){0,1}" + num + " (?:the ){0,1}mixing bowl){0,1}.");
	regexp_string["liquify"] = ("liqu[ie]fy(?! contents| the contents) (?:the ){0,1}" + str + ".");
	regexp_string["stir"] = ("stir((?: the){0,1}" + num + " (?:the ){0,1}mixing bowl){0,1} for ([0-9]+) minute(?:s){0,1}.");
	regexp_string["stir into"] = ("stir (?:the ){0,1}" + str + " (?:in){0,1}to( the){0,1}" + num + " (?:the ){0,1}mixing bowl.");
	regexp_string["mix"] = ("mix((?: the){0,1}" + num + " (?:the ){0,1}mixing bowl){0,1} well.");
	regexp_string["clean"] = ("clean((?: the){0,1}" + num + " (?:the ){0,1}mixing bowl){0,1}.");
	regexp_string["pour"] = ("pour contents of(?: the){0,1}" + num + " mixing bowl (?:in){0,1}to( the){0,1}" + num + " (?:the ){0,1}baking dish.");
	regexp_string["take"] = ("take (?:the ){0,1}" + str + " from (?:the ){0,1}refrigerator.");
	regexp_string["verb"] = (banCmd + "([a-zA-Z0-9-]+?)(?:e){0,1} (the ){0,1}((?!.*until)[a-zA-Z0-9 ]*?).");
	regexp_string["verbed"] = ("([a-zA-Z0-9-]+?) (the ){0,1}([a-zA-Z0-9 ]*){0,1} *until " + str + "e[nd].");
	regexp_string["set aside"] = ("set aside.");
	regexp_string["serve"] = ("serve with (?:the ){0,1}" + str + ".");
	regexp_string["serves"] = ("serves ([0-9]+).");
	regexp_string["refr"] = ("refrigerate( for ([0-9]+) hour(?:s){0,1}){0,1}.");
	regexp_string["liquify_contents"] = ("liqu[ie]fy(?: the){0,1} contents of(?: the){0,1}" + num + " mixing bowl.");

	// Positions on which the arguments in regexp occur

	parameter_positions["take"] = { 1,0 };
	parameter_positions["put"] = { 1,3 };
	parameter_positions["fold"] = { 1,3 };
	parameter_positions["add"] = { 1,4 };
	parameter_positions["remove"] = { 1,4 };
	parameter_positions["divide"] = { 1,4 };
	parameter_positions["combine"] = { 1,4 };
	parameter_positions["add dry"] = { 3,0 };
	parameter_positions["liquify"] = { 1,0 };
	parameter_positions["stir"] = { 3,5 };
	parameter_positions["stir into"] = { 1, 4 };
	parameter_positions["mix"] = { 3,0 };
	parameter_positions["clean"] = { 3,0 };
	parameter_positions["pour"] = { 2,6 };
	parameter_positions["liquify_contents"] = { 2,0 };
	parameter_positions["verb"] = { 1,3 };
	parameter_positions["verbed"] = { 3,4 };
	parameter_positions["set aside"] = { 0,0 };
	parameter_positions["serve"] = { 1,0 };
	parameter_positions["refr"] = { 2,0 };
	parameter_positions["serves"] = { 1,0 };

}

void Program::normalize(string & s)
{
	// case insensitive
	for (char& c : s) c = tolower(c);
	// remove all superfluous whitespace
	s = regex_replace(s, regex("\t"), " ");
	s = regex_replace(s, regex("^(?:[\t ])+|(?:[\t ])+$|( ) +"), "$1");

}

IngredientType Program::typeFromString(const string & s)
{
	string ss = s;
	normalize(ss);
	if (s.substr(0, 5) == "level" || s.substr(0, 6) == "heaped")
		return IngredientType::Dry;
	if (s == "g" || s == "kg" || s == "pinch" || s == "pinches" || s == "heaped" || s == "")
		return IngredientType::Dry;
	if (s == "ml" || s == "l" || s == "dash" || s == "dashes")
		return IngredientType::Liquid;
	return IngredientType::Unspecified;
}

bool Program::LoadHeader(Recipe & r)
{
	bool success = false; // did we load at least name of the method?
	string line;
	while (getline(*fs, line))
	{
		if (fs->eof()) err("Recipe name not found.");
		normalize(line);
		if (line.size() == 0) continue;
		if (line[line.size() - 1] == '.') // Name ends with period
		{
			r.name = line;
			normalize(r.name);
			r.name.pop_back(); // delete the final period
			success = true;
			if (printParserOutput)
				*os << "Recipe: " << r.name << endl << endl;
			break;
		}
		else if (line.size() != 0)
			err("Recipe name expected, instead got \"" + line + "\"");
	}

	// Read the comments until "ingredients" section is found
	while (getline(*fs, line))
	{
		if (fs->eof()) err("Methods block not found.");
		normalize(line);
		if ((line == "method.") || (line == "methods."))
			break;
		if (line == "ingredients.")
		{
			LoadIngredients(r);
			break;
		}
		else if (line != "")
			r.comments += '\n' + line;
	}
	return success;
}


void Program::LoadIngredients(Recipe & r)
{
	string ingredient_regexp = "([0-9]*) *(g|kg|pinch(?:es){0,1}|ml|(?!level)l|dash(?:es){0,1}|(?:heaped |level ){0,1}cup(?:s){0,1}|(?:heaped |level ){0,1}teaspoon(?:s){0,1}|(?:heaped |level ){0,1}tablespoon(?:s){0,1}){0,1} +([a-zA-Z0-9 -]+?)";
	string heaped_or_level_regexp = "(?:heaped |level ){0,1}([a-zA-Z0-9 -]+?)";
	string line;
	while (getline(*fs, line))
	{
		if (fs->eof()) break;
		normalize(line);
		if ((line == "method.") || (line == "methods.")) // ingredients block ends with method line
			break;
		// try to match one ingredient
		smatch match;
		std::regex expr(ingredient_regexp);
		regex_match(line, match, expr);
		if (match.size() != 0) {
			// remove heaped/level specifiers
			smatch match2;
			std::regex expr2(heaped_or_level_regexp);
			string tmp = match[3];
			regex_match(tmp, match2, expr2);
			r.addIngredient(Ingredient(match2[1], stoi(match[1]), typeFromString(match[2])));
		}
		// cooking time and pre-heat oven are not used anywhere
		else if (line.substr(0, 13) == "cooking time:" || line.substr(0, 13) == "pre-heat oven")
			continue;
		else if (line != "")
			r.addIngredient(Ingredient(line, 0, IngredientType::Unspecified)); // no value specified
	}
}

// returns true if next commands should be parsed
bool Program::parseCommand(Recipe & r, string & line) {

	std::smatch match;
	int wasMatched = 0; // how many commands does this expression match?
	for (auto & x : regexp_string)
	{
		std::regex expr(x.second);
		regex_match(line, match, expr);
		if (match.size() != 0)
		{
			wasMatched++;
			string command, arg1, arg2;
			command = x.first;
			// some of the arguments may be empty
			if (parameter_positions[x.first][0] == 0 || match[parameter_positions[x.first][0]] == "")
				arg1 = "";
			else
				arg1 = match[parameter_positions[x.first][0]];
			if (parameter_positions[x.first][1] == 0 || match[parameter_positions[x.first][1]] == "")
				arg2 = "";
			else
				arg2 = match[parameter_positions[x.first][1]];

			// remove extra whitespace
			normalize(command);
			normalize(arg1);
			normalize(arg2);

			// Parser output
			if (printParserOutput)
				(*os) << command << "\t\t" << arg1 << "\t\t" << arg2 << endl;
			if (x.first == "serves")
			{
				r.serves = stoi(arg1);
				if (printParserOutput)
					(*os) << endl;
				return false;
			}

			// Loops
			if (command == "verb")
				r.addJump(arg1, arg2);
			else if (command == "verbed")
				r.addUntil(arg2, arg1);
			else
				r.addCommand(command, arg1, arg2);
		}
	}
	if (wasMatched > 1)
		err("Ambiguous command\"" + line + "\"");
	if ((wasMatched == 0) && (line != ""))
		err("No match for command\"" + line + "\"");
	return true;
}

void split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
}

bool Program::LoadRecipe(Recipe & r)
{
	if (!LoadHeader(r))
		return false;
	string line;
	string line2;
	while (getline(*fs, line))
	{
		normalize(line);
		if (line == "") continue;
		// join lines if they are not terminated by a period
		while (line.substr(line.size() - 1, 1) != "." && getline(*fs, line2)) {
			if (fs->eof()) return false;
			line += " " + line2;
			normalize(line);
		}
		// split line into commands, period is delimiter
		vector<string> lines;
		split(line, '.', lines);
		for (string & s : lines) {
			normalize(s);
			if (s == "") continue;
			s += '.';
			if (!parseCommand(r, s))
				return true;
		}
		if (fs->eof()) return false;
	}
	if (printParserOutput)
		*os << endl;
	return true;
}