# Minishell — Guia do Projeto

Implementação de um shell mínimo (estilo Bash) para o currículo da 42. Este arquivo descreve regras, restrições e convenções **obrigatórias** para qualquer trabalho neste repositório.

---

## 1. Restrições do Projeto (NÃO NEGOCIÁVEIS)

### Funções externas permitidas
Apenas as funções abaixo podem ser usadas no código (fora da `libft`):

```
readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay,
add_history, printf, malloc, free, write, access, open, read, close, fork,
wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset, sigaddset, kill,
exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe,
opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot,
ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr,
tgoto, tputs
```

**Qualquer outra função libc resulta em nota 0.** Antes de sugerir uma função, verifique se está nesta lista. Se faltar uma utilitária (ex.: `ft_split`, `ft_strjoin`), implemente-a na `libft` ou em `src/utils/`.

### Variável global
- Máximo **uma** variável global, e apenas para armazenar o **número do sinal recebido**.
- **Proibido** colocar structs, ponteiros, ou qualquer outra coisa em escopo global.
- O handler de sinal **não pode** acessar estruturas principais do shell — apenas escrever o número do sinal na global.

### Norminette
- Todo arquivo `.c`/`.h` precisa passar na norminette (incluindo bônus).
- Funções: máximo **25 linhas**, **5 parâmetros**, **4 variáveis**.
- Arquivos: máximo **5 funções por `.c`**.
- Linhas: máximo **80 colunas**.
- Sem `for`, sem `do-while`, sem operadores de atribuição compostos (`+=`, `++` permitido).
- Sem declarações múltiplas na mesma linha; sem `=` na mesma linha da declaração quando ocorrem várias variáveis.
- Variáveis declaradas no início do bloco.
- Header 42 obrigatório em todo arquivo (já presente nos arquivos atuais).

### Memória
- **Zero vazamentos no código do aluno.** Apenas vazamentos internos de `readline` são tolerados.
- Toda alocação na heap deve ter um caminho claro de `free`, inclusive em erros (heredoc interrompido, `execve` falhou, fork falhou, etc.).
- Validar com `valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp` (criar supressão para readline).

### Sem crashes
- Qualquer segfault, double free, bus error durante a avaliação = nota 0.
- Sempre checar retorno de `malloc`, `fork`, `pipe`, `open`, `dup2`, etc.

---

## 2. Estrutura Atual de Pastas

```
minishell/
├── Makefile
├── README.md
├── includes/
│   ├── minishell.h        # tipos principais, protótipos públicos
│   └── lexer.h            # tokens e protótipos do lexer
├── libs/libft/            # libft do aluno (copiada conforme exige o subject)
└── src/
    ├── main.c             # loop readline + add_history
    ├── process_input.c    # pipeline lexer → parser → executor
    ├── lexer/             # tokenização (T_WORD, T_PIPE, T_REDIR_*, T_HEREDOC, T_APPEND)
    ├── parser/            # (vazio) construção da AST/lista de comandos
    ├── expansion/         # (vazio) expansão de $VAR, $?, remoção de aspas
    ├── execution/         # (vazio) fork, execve, pipes
    ├── redirections/      # (vazio) <, >, <<, >>
    ├── builtins/          # (vazio) echo, cd, pwd, export, unset, env, exit
    ├── env/               # (vazio) cópia/manipulação do env
    ├── signals/           # SIGINT, SIGQUIT (interativo + execução)
    ├── utils/             # (vazio) helpers que não cabem na libft
    └── debug/             # (vazio) prints de tokens/AST — NÃO incluir no build final
```

**Regra:** cada subsistema fica isolado em sua pasta. Não amontoar lógica em `main.c` ou `process_input.c` — manter esses arquivos como orquestradores finos.

---

## 3. Pipeline de Execução (ordem mental)

1. **`readline`** lê uma linha (já implementado em [src/main.c](src/main.c)).
2. **Lexer** ([src/lexer/](src/lexer/)) transforma em lista de `t_token`. Já tokeniza palavras, `|`, `<`, `>`, `<<`, `>>` preservando o conteúdo dentro de aspas (sem ainda remover).
3. **Parser** (a implementar em [src/parser/](src/parser/)) agrupa tokens em uma lista de comandos conectados por pipes; cada comando carrega argv + redirecionamentos.
4. **Expansão** (a implementar em [src/expansion/](src/expansion/)) substitui `$VAR` e `$?`, respeitando regras de aspas duplas vs simples, e remove as aspas (quote removal — depois da expansão).
5. **Heredoc** é processado **antes** da execução do pipeline (cria pipe ou arquivo temporário com a entrada).
6. **Execução** ([src/execution/](src/execution/)): builtins em pipeline único rodam no processo pai apenas quando há um único comando sem fork; em pipeline, cada estágio é forkado. Aplicar redirecionamentos com `dup2`, fechar todos os fds, `execve` resolvendo `PATH`.
7. **Limpeza**: aguardar com `waitpid`, atualizar `$?` com o último status do pipeline, liberar tokens/AST.

---

## 4. Regras de Comportamento (referência: bash)

### Aspas
- `'...'` — nada é interpretado dentro (sem expansão de `$`, sem operadores).
- `"..."` — apenas `$VAR` e `$?` são expandidos; o resto é literal.
- Aspas **não fechadas** devem reportar erro de sintaxe (não tentar adivinhar fechamento).

### Redirecionamentos
- `<` entrada, `>` saída (truncate), `>>` append, `<<` heredoc (delimitador literal — não atualiza histórico).
- Múltiplos redirecionamentos: abrir todos, mas o último vence; falha em qualquer um aborta o comando com erro.
- Heredoc deve aceitar interrupção por `Ctrl-C`.

### `$?`
- Status do **último** pipeline foreground.
- `0` ao iniciar o shell.
- Comando não encontrado: `127`. Permissão negada: `126`. Morto por sinal `n`: `128 + n`.

### Sinais
| Contexto | Ctrl-C | Ctrl-\ | Ctrl-D |
|---|---|---|---|
| Prompt vazio | nova linha + novo prompt | nada | sai do shell |
| Comando em execução | interrompe filho | quit no filho | EOF para o filho (ex.: `cat`) |
| Heredoc | aborta heredoc, $?=130 | nada | termina heredoc |

- Usar `sigaction` (não `signal`) quando precisar de comportamento determinístico.
- Durante execução de filho: shell deve **ignorar** SIGINT/SIGQUIT e restaurar ao terminar.

### Builtins (sem opções, exceto `echo -n`)
- `echo [-n] args...`
- `cd <path>` (relativo ou absoluto; atualizar `PWD` e `OLDPWD`).
- `pwd`
- `export [VAR=value ...]` (sem args → lista no formato `declare -x`).
- `unset VAR...`
- `env` (apenas variáveis com valor atribuído).
- `exit [n]` (modulo 256; com argumento não-numérico → erro + `255`).

Detalhe importante: builtins que **alteram o estado do shell** (`cd`, `export`, `unset`, `exit`) precisam rodar no **processo pai** quando não há pipe. Em pipeline, rodam no filho (efeito local apenas, comportamento idêntico ao bash).

---

## 5. Convenções de Código

- Prefixos: estruturas com `s_`, tipos com `t_`, enums com `e_`/membros `T_`/`E_`.
- Funções de um subsistema começam pelo nome do subsistema (`lexer_*`, `token_*`, `exec_*`, `builtin_*`).
- Arquivos seguem `snake_case.c`. Bônus em `*_bonus.c`/`*_bonus.h`.
- Headers protegidos por `#ifndef NOME_H`.
- Comentários: **apenas quando o porquê não é óbvio**. Não comentar o que o código já diz. Não deixar `TODO` antigo apodrecer — ou implementa, ou remove.
- Erros do shell: imprimir em `stderr` no formato `minishell: <contexto>: <mensagem>\n`.

---

## 6. Makefile

- Flags obrigatórias: `-Wall -Wextra -Werror`.
- Regras: `all`, `clean`, `fclean`, `re`, `$(NAME)`. Para bônus: `bonus`.
- **Sem relink desnecessário** — usar dependências de header (atualmente faltam; adicionar `-MMD -MP` ou listar headers explicitamente como dependência das `.o`).
- Linkar `libft` antes do binário final.
- `-lreadline` no link.

Estado atual: o Makefile não rastreia dependências de `.h`; alterar `minishell.h` não força recompilação. **Corrigir antes da avaliação.**

---

## 7. Bônus

**Não serão implementados.** Foco total na parte obrigatória.

- Não criar arquivos `*_bonus.c` / `*_bonus.h`.
- Não adicionar regra `bonus` ao Makefile.
- Não implementar `&&`, `||`, parênteses ou wildcard `*`.
- Se aparecer sugestão de "já que estamos aqui, dá pra adicionar X do bônus" — recusar. Toda energia vai para deixar a obrigatória perfeita (sem leaks, sem crashes, bash-equivalente).

---

## 8. Pontos da Evalsheet a Validar Manualmente

Antes de declarar uma feature pronta, rodar mentalmente os testes da evalsheet correspondentes. Casos críticos onde projetos falham:

- `cat | cat | ls` — comportamento "normal" (ls executa, cats encerram com EOF).
- `expr $? + $?` — expansão de `$?` em argumentos.
- `echo "'$USER'"` deve imprimir `'wini'`; `echo '"$USER"'` deve imprimir `"$USER"`.
- `unset PATH` e depois rodar `ls` → erro de "command not found".
- `Ctrl-C` em prompt com texto digitado deve limpar o buffer (apertar Enter depois não pode executar o que estava lá).
- `<<` (heredoc) interrompido por `Ctrl-C` deve voltar ao prompt com `$? = 130`.
- `>` que falha (sem permissão) não pode deixar fds vazando nem corromper o próximo comando.

---

## 9. Diretrizes para Trabalho Assistido

1. **Sempre** rodar `make re` após mudanças não-triviais — não confiar em incremental enquanto o Makefile não rastrear headers.
2. **Sempre** rodar norminette no diretório alterado antes de declarar pronto: `norminette src/<dir> includes/`.
3. **Sempre** testar com valgrind quando mexer em alocação/execução.
4. Quando criar arquivo novo, copiar header 42 dos arquivos existentes (manter formato exato).
5. Quando adicionar `.c`, **atualizar o Makefile** (a variável `SRC`) — não há glob.
6. Não inventar funções que não estão na lista permitida; em caso de dúvida, perguntar antes de codar.
7. Preferir editar arquivos existentes a criar novos quando a responsabilidade já cabe em algum lugar.
