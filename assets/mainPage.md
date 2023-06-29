
# Project Review and Documentation

## Overview

The project at hand is a text-based calculator application developed in C++. The main purpose of this application is to provide the functionality of a  calculator as well as support for variables and import/export of calculator state. The application allows users to perform mathematical operations including addition, subtraction, multiplication, division, modulo operation, and power operation. It also supports factorial and round operations, as well as assignment of expressions to variables for later use. Users can interact with the calculator through a simple command-line interface.

## Description

The application is based on a modular design, encapsulating different functionalities within separate classes. The major classes of the project are:

- `Number`: This is an abstract base class representing a numerical value. This class has two derived classes, `IntegerNumber` and `FloatNumber`, which provide specific implementation for integer and floating-point numbers respectively.

- `Calculator`: This class encapsulates the logic of the calculator. It maintains a map of variables and their values, and provides functions for parsing and evaluating expressions, executing commands, and importing/exporting the calculator state.

- `UserInterface`: This class provides an interactive command-line interface for the user to input commands and expressions, and displays the results or error messages.

## Polymorphism Application

Polymorphism is extensively used in this project through the `Number` abstract base class and its two derived classes, `IntegerNumber` and `FloatNumber`. The `Number` class declares a set of pure virtual functions for performing mathematical operations, and these functions are implemented differently in `IntegerNumber` and `FloatNumber` based on the specific requirements of integer and floating-point arithmetic. This application of polymorphism allows us to write code that operates on `Number` pointers or references, and the correct function will be called based on the actual type of the object.

## Architecture Design

The project architecture is designed with modularity and separation of concerns in mind. The `Number` class hierarchy encapsulates the representation and operations of numbers. The `Calculator` class encapsulates the logic of parsing and evaluating expressions, and managing the state of variables. The `UserInterface` class encapsulates the interaction with the user, taking user input and displaying output or error messages.

## Parsing, Reverse Polish Notation (RPN) and Exception Handling

### Parsing

The parsing of the user input is handled in the `Calculator` class. It takes a string of mathematical expression as input and returns a sequence of tokens. The tokenization process involves splitting the input string by spaces and then determining the type of each token - it can be a number, a variable name, or an operator. For numbers and variable names, the parser also checks if the format is valid, i.e., a number should only contain digits and at most one decimal point, a variable name should start with a letter and contain only letters and digits.

### Exception Handling

The project employs robust exception handling to ensure the application's stability and user-friendliness. Each class is designed with a defensive programming approach, meaning it checks for potential errors and throws exceptions when something goes wrong.
