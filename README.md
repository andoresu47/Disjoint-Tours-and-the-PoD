# Disjoint Tours and the Price of Diversity
This repository contains the code with the exhaustive search analysis required to prove Claims 3.1 and 4.1 of the *Disjoint Tours and the Price of Diversity* paper. 

## Overview
The programs here implement exhaustive enumeration of Hamiltonian paths and tours under specific disjointness and cost constraints. These experiments are used to confirm structural properties and exact bounds that underpin the theoretical results in the paper.  

## Contents
- `app/` – main executable containing the necessary tests to verify the stated claims. 
- `src/` – C++ source code for the exhaustive search algorithms.  
- `headers/` – header files.  
- `test/` – test executable with unit tests for the various functions defined in src/**.cpp.  

## Usage
To compile the main code, run:
```bash
g++ -O2 -std=c++17 /app/main.cpp /src/*.cpp -o main -I/headers
```

To compile the tests, run:
```bash
g++ -O2 -std=c++17 /test/testmain.cpp /src/*.cpp -o testmain -I/headers
```
