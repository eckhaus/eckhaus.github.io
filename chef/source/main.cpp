// Author: Róbert Eckhaus
// Date: 17 May 2016
// Chef language interpreter

/*! \mainpage Chef interpreter
    ## Chef language
    Chef is stack-based esoteric programming language designed by David Morgan-Mar in 2002. Programs in Chef look like recipes,
    where variables are represented by ingredients and program's stacks are referred to as mixing bowls and baking dishes.

    Full specification of the language can be found on [David Morgan-Mar's webpage](http://www.dangermouse.net/esoteric/chef.html) or
    on [Steffan Mueller's interpreter pages](http://search.cpan.org/~smueller/Acme-Chef/lib/Acme/Chef.pm).
    ## Usage of the interpreter
    ### %Command line arguments

     * -i <file> input file

     * -o <file> output file

     * -v show also information about recipe

     * -t trace mode
    ### Example
    chef -i myInput.chef -o output.txt -v

    ## Download
    http://eckhaus.github.io/chef/

    <i>Róbert Eckhaus, MFF UK, 2016</i>
 */

#include "include/Program.h"

using namespace std;



void parseArgs (int argc, char ** argv, string & inFile, string & outFile, bool & trace, bool & verbose)
{
    vector<string> args (argv+1, argv + argc);

    if (argc > 1)
    {
        int field = 0;
        while (field < args.size() && ((args[field] == "-v" || args[field] == "-t") || ((field + 1 < argc) && (args[field][0] == '-') && (string(args[field]).size() == 2))))
        {
            if (args[field] == "-v")
            {
                verbose = true;
                field++;
            }
            else if  (args[field] == "-t")
            {
                trace = true;
                field++;
            }
            else if (args[field][1] == 'i')
            {
                if (field+1 < args.size()){
                inFile = args[field+1];
                field +=2;}
                else err("Missing filename.");
            }
            else if (args[field][1] == 'o')
            {
                if (field+1 < args.size()){
                outFile = args[field+1];
                field +=2;}
                else err("Missing filename.");
            }
            else
            {
                cout << "Error: Unknown option" << endl;
                std::exit(-1);
            }
        }
        if (field < args.size())
            err("Unknown option2.");
    }
}

int main(int argc, char ** argv)
{
    string inFile = "";
    string outFile = "";
    bool trace = false;
    bool verbose = false;

    parseArgs(argc, argv, inFile, outFile, trace, verbose);
    Program p (inFile, outFile, trace, verbose);
    p.parse();

    return 0;
}
