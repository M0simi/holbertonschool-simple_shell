# simple_shell

## Description
**simple_shell** is a basic UNIX command line interpreter, created as part of the Holberton School curriculum. It aims to replicate the behavior of the standard shell (`/bin/sh`) by executing commands entered by the user, whether interactively or through input redirection (non-interactive mode).

This project provided deep understanding of system calls in C, process creation (`fork`), program execution (`execve`), memory management, and more.

---

## Features
- Executes commands, both with absolute path or found in the `$PATH` environment variable.
- Supports built-in commands:
  - `exit`: exits the shell.
  - `env`: displays the current environment variables.
- Works in both:
  - **Interactive mode**: user types commands manually.
  - **Non-interactive mode**: commands are piped into the shell.
- Graceful error handling for unknown commands or execution issues.
- Manual page included (`man_1_simple_shell`).

---

## How to Use

### 🛠️ Compilation

Compile all the `.c` files using:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
written by Abdulaziz Almotairi and Meshari Alosimi
