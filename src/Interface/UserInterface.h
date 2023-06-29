#pragma once



#include "../Logic/Calculator.h"


/**
 * @brief The UserInterface class provides an interface for users to interact with the Calculator.
 */
class UserInterface {
public:
    /**
   * @brief Constructs a new UserInterface object associated with a given Calculator.
   * @param calculator Reference to the Calculator object to be used.
   */
    UserInterface(Calculator& calculator);
/**
     * @brief Starts the main loop of the user interface, processing user input until the user chooses to exit.
     */
    void run();
    /**
     * @brief Displays a help message to the user, listing the available commands.
     */
    void printHelp();
private:
    /**
     * @brief Reference to the Calculator object used to perform calculations.
     */
    Calculator& calculator_;
};


