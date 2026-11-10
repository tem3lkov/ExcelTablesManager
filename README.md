# Console Spreadsheet Editor

A lightweight, console-based spreadsheet application developed in C++. This project demonstrates advanced Object-Oriented Programming (OOP) principles, dynamic memory management, and the implementation of classic software design patterns to parse, evaluate, and manage tabular data.

<div align="center">
  <img width="800" alt="UML Architecture Diagram" src="https://github.com/user-attachments/assets/83f2abae-8e3c-409d-9641-2ae30811d09c" />
  <br>
  <i><b>Fig 1. UML Class Diagram:</b> Architectural overview demonstrating the decoupling of Cell parsing and instantiation via the Factory and Creator design patterns.</i>
  <br><br>
  <img width="400" alt="CLI Initial State" src="https://github.com/user-attachments/assets/1c718869-187c-4a4c-846a-8eb3a6cca9f9" />
  <img width="375" alt="CLI Modified State" src="https://github.com/user-attachments/assets/7ec0700a-74d5-4972-9256-030bafc42e52" />
  <br>
  <i><b>Fig 2. Interactive CLI in Action:</b> (Left) Initial table loaded from a text file and modified with a formula (`R1C1 * R1C2`). (Right) The table successfully dynamically re-evaluates the formula output after the modification.</i>
</div>

## 🚀 Key Features

- **Heterogeneous Cell Types:** Supports integers, floating-point numbers (doubles), strings (with escape character support), and dynamic formulas.
- **Formula Evaluation:** Evaluates mathematical expressions (`+`, `-`, `*`, `/`, comparison operators) and supports direct cell referencing (e.g., `R1C1 * R1C2`).
- **Circular Reference Detection:** Safely identifies and handles cyclic dependencies between formula cells to prevent infinite loops.
- **Dynamic Memory Management:** Utilizes a custom heterogeneous container for table rows, ensuring safe memory handling via RAII and STL vectors.
- **File I/O Operations:** Load tables from properly formatted text files and save modifications back to the disk.
- **Interactive CLI:** A built-in command handler to seamlessly interact with the spreadsheet grid.

## 🏗️ Architecture & Design Patterns

The core engine is heavily decoupled to allow easy extensibility (e.g., adding new cell types) using several design patterns:

- **Factory Method & Creator:** Used to instantiate specific cell types (`IntCell`, `DoubleCell`, `StringCell`, `FormulaCell`) dynamically at runtime without hardcoding class dependencies.
- **Singleton:** Applied to the main `Table` and `App` classes to restrict instantiation and provide a global point of access, which is crucial for resolving formula references across the grid.
- **Command (Simplified):** Encapsulates CLI inputs into distinct executable methods, separating the user interface from the underlying business logic.
- **Polymorphism:** A pure abstract `Cell` base class forces implementations of `eval()`, `clone()`, and `print()` across all derived cell types.

## 💻 Supported Commands

Once the application is running, the following commands are available in the terminal:

- `open <file_path>` - Loads a table from the specified file.
- `close` - Closes the currently opened table.
- `edit <row> <col> <value>` - Modifies a specific cell. Values can be numbers, strings, or formulas (e.g., `= R1C1 + 10`).
- `print` - Displays the current state of the table in a formatted grid.
- `save` - Saves modifications to the currently opened file.
- `save as <file_path>` - Saves the current table to a new file location.
- `exit` - Terminates the application.

## 🛠️ Technical Stack

- **Language:** C++ (Standard Library: `<string>`, `<vector>`, `<cmath>`, etc.)
- **Concepts:** Polymorphism, Abstract Classes, Exception Handling, File Parsing, String Tokenization, Cycle Detection.

## 🔮 Future Improvements

- Implement the Shunting Yard algorithm and Reverse Polish Notation (RPN) for complex nested mathematical operations (e.g., `3 + (8 + 5) * 4`).
- Integrate a Graphical User Interface (GUI) to replace the CLI[cite: 16, 17, 18, 19].
