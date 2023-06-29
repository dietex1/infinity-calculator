
#include "UserInterface.h"
#include <iostream>
using namespace std;


UserInterface::UserInterface(Calculator& calculator) : calculator_(calculator) {}


// Run the user interface
void UserInterface::run() {
    cout << "Welcome to the Calculator! Type 'help' for a list of commands." << endl;
    string input;
    // Enter a loop to receive user input and process commands
    while (getline(cin, input)) {
        cout << "> ";
        if (input == "quit" || input == "q") {
            break;
        } else if (input == "help") {
            printHelp();
        }else {
            try {
                // Handle various commands such as executing expressions, assigning variables, importing/exporting state, etc.
                calculator_.executeCommand(input);
            } catch (const exception& e) {
                // Print the result or any error messages to the console
                cerr << "Error: " << e.what() << endl;
            }
        }
    }
}

// Display a list of  commands and their descriptions to the user
void UserInterface::printHelp() {
    cout << "Available commands:" << endl
         << "  quit | q -- Exits the application." << endl
         << "  help -- Displays this help message." << endl
         << "  IMPORT <filename> -- Imports calculator state from a file." << endl
         << "  EXPORT <filename> -- Exports calculator state to a file." << endl
         << "  <variable> = <expression> -- Assigns the result of the expression to the variable." << endl
         << "  var < + - * / > var -- Evaluates the expression and prints the result." << endl
         << "  var < % > var -- Evaluates modulo and prints the result." << endl
         << "  var < ^ > var -- Evaluates power and prints the result." << endl
         << "  < ! > var -- Evaluates the factorial and prints the result." << endl
         << "  < ~ > var -- Round and prints the result." << endl;
}



