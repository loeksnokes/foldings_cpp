# Foldings C++ Project

This project implements a graph-based algorithm for generating and manipulating De Bruijn graphs and their foldings. The functionality is replicated from a Go implementation, providing similar capabilities in C++.

## Project Structure

- **include/**: Contains header files defining the main classes used in the project.
  - `graph.hpp`: Defines the `Vertex` class for representing sets of strings in the graph.
  - `digraph.hpp`: Defines the `Digraph` class for representing directed graphs with integer vertices.
  - `ggraph.hpp`: Defines the `GGraph` class for representing graphs with vertices as graphs.

- **src/**: Contains the implementation files for the project.
  - `graph.cpp`: Implements methods for managing the adjacency list and vertices of the graph.
  - `digraph.cpp`: Implements methods for the directed graph, including adding vertices and edges.
  - `ggraph.cpp`: Implements methods for managing the graph of graphs.
  - `foldings.cpp`: Contains the implementation of the folding functionality.
  - `main.cpp`: The entry point of the application, generating the De Bruijn graph and building the foldings graph.

- **test/**: Contains unit tests for the folding functionality.
  - `test_foldings.cpp`: Ensures that the implemented methods work as expected.

- **CMakeLists.txt**: Configuration file for CMake, specifying project details and source files.

## Building the Project

To build the project, follow these steps:

1. Ensure you have CMake installed on your system.
2. Open a terminal and navigate to the project directory.
3. Create a build directory:
   ```
   mkdir build
   cd build
   ```
4. Run CMake to configure the project:
   ```
   cmake ..
   ```
5. Compile the project:
   ```
   make
   ```

## Running the Application

After building the project, you can run the application using the following command in the build directory:
```
./foldings_cpp
```

## Testing

To run the unit tests, you can execute the following command in the build directory:
```
./test/test_foldings
```

## License

This project is licensed under the MIT License. See the LICENSE file for more details.