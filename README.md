# cs429-mastery-assignment
## [IMPORTANT] After you SSH into a lab machine: Note that
- **ALL git commands must be in the command line.**
- **ALL gdb debugging must be in the command line.**
- **ALL file system actions (eg. creating a file, navigating a file, etc) must be in the command line**

You are allowed to utilize the terminal of your choice for these actions, but they must be accomplished in-terminal. 

*Note: SSHing via VS Code or another GUI is acceptable provided that the above actions are then accomplished via a terminal therein.*

# What this repo contains:
- `main.c`, `reader.c`, `calculator.c` and their corresponding header files.
- A Makefile
- Some testcases in the `testcases` folder
- a reference executable called `mini_ci_reference`

# What this code does:
The given code reads in a string representing a postfix operation, evaluates the value of the operation,
and prints the result, notifying the user if the operation was invalid.
A postfix operation is defined by `<operand1> <operand2> <binary operator>` eg. `1 2 +` which evaluates to 3.
These operations can be chained together `8 1 - 2 +` = `7 2 +` = `9`;
Similarly `8 1 2 - +` = `8 -1 +` = `7`
If at any point the Reader encounters an error, the final result should be set to -1 and the Reader's had_error field
should be set to true. If no error occurs, the Reader's had_error field should be false.
The given program uses a greedy stack based approach to evaluate valid operations as soon as they appear.
Unfortunately, this program may be wrong!

To run an individual testcase use 
`mini_ci <file>`. Use `mini_ci_reference <file>` for the reference output.

# Instructions:
1. ssh into your favorite UTCS lab machine
2. Create a file `~/.gdbinit`
3. Add the line `set history save on` to `~/.gdbinit`
4. Clone this repository
5. Read then use the Makefile
6. Debug the test cases using gdb; you must use gdb to pass this mastery assessment.
7. Ensure your output matches the reference exactly.
8. Write the outputs of the `history` command to a file in this repo called `shell_logs.txt`
9. While in gdb, use the command `show commands` to display your most recently used commands. Write this output to a file in this repo called `gdb_logs.txt`
10. Commit and push your changes. Do not forget to add `shell_logs.txt` and `gdb_logs.txt` to git.
11. Delete your local copy of this repository (you will need to use the r and f flags). If this results in any errors, please notify your proctor before leaving the room.
12. Please do not leave before your proctors tell you to do so. 
