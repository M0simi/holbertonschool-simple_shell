# simple_shell

## 🧠 Description
**simple_shell** is a basic UNIX command-line interpreter built as part of the Holberton School curriculum.  
It replicates the behavior of the standard shell (`/bin/sh`) and allows users to execute commands both interactively and non-interactively.

This project offers hands-on experience with system-level programming in C, focusing on:
- Process creation (`fork`)
- Program execution (`execve`)
- Environment handling
- Memory management
- Input/output operations

---

## ✨ Features

- ✅ Execute commands using absolute paths or via the `$PATH` environment.
- 🔄 Supports built-in commands:
  - `exit`: exits the shell.
  - `env`: prints current environment variables.
- 💬 Modes:
  - **Interactive**: wait for user input.
  - **Non-interactive**: read input from piped or redirected data.
- ⚠️ Graceful error handling for invalid or unknown commands.
- 📖 Manual page: `man_1_simple_shell` included.

---

## 🛠️ Compilation

To compile the shell, run:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh



Interactive mode:
bash
./hsh
$ ls -l
$ pwd
$ exit



Non-interactive mode:
bash
echo "ls -l" | ./hsh




File 
File | Description
main.c | Entry point of the shell
shell.c | Core shell loop and execution
builtins.c | Implementation of built-in commands
utils.c | Utility functions (e.g. string parsing)
man_1_simple_shell | Manual page


written by Abdulaziz Almotairi and Meshari Alosimi
