#pragma once


#include <string>
#include "Calculator.h"

class Calculator;
/**
 * @brief Represents a import and export logic.
 */
class ImportExport {
public:
    Calculator* calc;
    /**
      * @brief  Constructs a new ImportExport object.
      */
    ImportExport(Calculator* calculator);

    /**
     * @brief Imports memory from a file.
     * @param filename The name of the file from which to import memory.
     */
    void importMemory(const std::string &filename) ;
    /**
     * @brief Exports memory to a file.
     * @param filename The name of the file to which to export memory.
     */
    void exportMemory(const std::string &filename) ;

};


