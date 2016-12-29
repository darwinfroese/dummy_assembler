# dummy_assembler
A dummy assembler for pseudo-assembly written to teach a friend how to (inefficiently?) write an assembler. Strict rules are used with input code to keep parsing simple for now.

Goal: Write an assembler as practice to create a better one for my [DLX-Simulator](https://github.com/darwinfroese/dlx-simulator.git).

## Features
- Unsophisticated code
- Stupid parsing
- Handles all if conditionals
 - ==, !=, <=, >=, <, >
 - Handles constant values and variable values on either side of conditional statement
 
## Changelog
#### 0.0.1
- If statements translated to "assembly"
- Other statement types print they're type
