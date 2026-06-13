*This project was created as part of the 42 curriculum by wsilveir, <login2>.*

## Description

**minishell** is a minimal Unix shell written in C, inspired by `bash`. It reads
command lines interactively, interprets them, and executes the corresponding
programs — giving hands-on experience with **processes**, **file descriptors**,
**pipes**, **signals**, and **environment management**.

The shell supports:

- An interactive prompt with command **history** (via `readline`).
- Execution of binaries found through `$PATH`, or via absolute/relative paths.
- **Quotes**: single quotes (`'...'`, fully literal) and double quotes
  (`"..."`, expands only `$`).
- **Redirections**: `<` (input), `>` (output), `>>` (append) and `<<` (heredoc).
- **Pipes** (`|`) connecting an arbitrary number of commands.
- **Environment variable expansion** (`$VAR`) and exit-status expansion (`$?`),
  including word splitting of unquoted values.
- **Signals** matching bash: `Ctrl-C`, `Ctrl-\` and `Ctrl-D` in interactive,
  execution and heredoc contexts.
- **Built-in commands**: `echo` (with `-n`), `cd`, `pwd`, `export`, `unset`,
  `env`, `exit`.

A single global variable is used, and only to store the number of a received
signal, as required by the subject.

## Instructions

**Compile**

```sh
make
```

The `Makefile` first builds the bundled `libft`, then the shell, with the
mandatory flags `-Wall -Wextra -Werror`. Other rules: `make clean`,
`make fclean`, `make re`.

**Execution**

```sh
./minishell
```

**Example**

```sh
minishell$ echo "hello $USER" | cat -e
hello wini$
minishell$ ls -la > out.txt
minishell$ cat < out.txt | wc -l
12
minishell$ export GREETING="hi there"
minishell$ echo $GREETING
hi there
minishell$ exit
exit
```

### Important Rules

- No memory leaks in our own code (only `readline`'s internal, tolerated, leaks
  remain). Tested with:
  ```sh
  valgrind --leak-check=full --show-leak-kinds=all \
           --suppressions=readline.supp ./minishell
  ```
- No unexpected crashes (segfault, double free, etc.).
- Every `.c`/`.h` complies with the 42 Norm.

## Resources

Classic references used while studying the topic:

- **GNU Bash Reference Manual** — quoting, expansion, redirection and signal
  behavior used as the reference for matching bash.
- **The Linux Programming Interface** (M. Kerrisk) — processes, `fork`/`execve`,
  pipes, file descriptors and signal handling.
- **GNU Readline documentation** — `readline`, history and the
  `rl_*` redisplay functions used for signal handling at the prompt.
- `man` pages: `execve(2)`, `pipe(2)`, `dup2(2)`, `wait(2)`, `sigaction(2)`,
  `open(2)`.

### Use of Artificial Intelligence

AI tools (Claude) were used as a support during development, specifically for:

- Helping **design the architecture** of the pipeline (lexer → parser →
  expansion → execution) and discussing trade-offs.
- Generating and reviewing **boilerplate** and helper functions, then adapting
  them to the project's conventions and the 42 Norm.
- Discussing **edge cases** (quote handling, `$?`, word splitting, heredoc
  signal handling) and how bash behaves in each one.
- Explaining concepts (file descriptor management in pipelines, signal contexts)
  to deepen understanding.

All generated content was reviewed, tested, and is fully understood by the
authors, who take responsibility for every line of the final code.
