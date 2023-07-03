# XtremeShell

<img src="https://img.icons8.com/?size=128&id=UtFWXwkWreTY&format=png" />

XtremeShell is a simple command-line shell implemented in C. It allows users to execute commands and provides basic functionality such as parsing input, executing commands, and displaying the output.

## Features

- Command parsing: The shell splits user input into individual commands and arguments.
- Command execution: The shell uses the `fork()` and `execvp()` functions to create a child process and execute the specified commands.
- Multiple commands: Users can enter multiple commands separated by semicolons.
- Output display: The shell displays the output of executed commands.
- Custom prompt: The shell displays its own prompt, "&xtremeshell& -> ", to differentiate it from the regular terminal prompt.

## Usage

1. Clone the repository and navigate to the project directory.
2. Compile the code using `gcc`:
   

   gcc -o xtremeshell xtremeshell.c
   
3. Run the shell:
   

   ./xtremeshell
   
4. Enter commands at the prompt, and the shell will execute them.

## Contributions

Contributions to XtremeShell are welcome! If you find any bugs or want to add new features, feel free to open an issue or submit a pull request.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more information.


Feel free to modify this description to fit your project and add any additional sections or details that you would like to include.
