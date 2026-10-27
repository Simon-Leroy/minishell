# minishell

A small Unix shell written in C, built as part of the 42 curriculum. It reproduces the core behavior of bash.

Developed by sleroy and roguille.

## Features

- Interactive prompt with command history (GNU readline)
- Execution of commands found in `PATH`, or given by relative/absolute path
- Pipes: `cmd1 | cmd2 | cmd3`
- Redirections: `<`, `>`, `>>`, and heredoc `<<`
- Single and double quotes
- Environment variable expansion (`$VAR`) and exit status (`$?`)
- Signal handling: `Ctrl-C`, `Ctrl-D`, `Ctrl-\`
- Built-ins: `echo` (with `-n`), `cd`, `pwd`, `export`, `unset`, `env`, `exit`

## Build and run

Requires a C compiler, `make` and the readline library (`libreadline-dev` on Debian/Ubuntu).

```bash
make
./minishell
```

Other targets: `make clean`, `make fclean`, `make re`.

## Project structure

```
main.c          Entry point and main loop
includes/       Headers
libft/          Custom C standard library functions
src/
  lexer/        Splits the input line into tokens
  parser/       Builds command blocks and redirections, validates quotes
  expander/     Expands variables and handles quotes
  executor/     Runs commands: pipes, redirections, heredoc, PATH lookup
  built_ins/    Built-in commands
  utils/        Errors, memory cleanup, signals
```

## How it works

Each input line goes through a pipeline: **lexer** (tokens) → **parser** (commands and redirections) → **expander** (variables and quotes) → **executor** (fork, pipes, execve, or built-in).
