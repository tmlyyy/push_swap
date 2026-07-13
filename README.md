*This project has been created as part of the 42 curriculum by thamoliv, gproenca.*

# push_swap

Ordenar uma pilha parece trivial — ordená-la usando apenas duas pilhas e um punhado de operações limitadas, com o menor número possível de movimentos, é outra história. O `push_swap` é a nossa resposta a esse desafio.

---

## Descrição

`push_swap` recebe uma lista de inteiros (sem duplicados) como argumentos e imprime, na saída padrão, a menor sequência possível de instruções capaz de ordenar essa lista em ordem crescente, utilizando apenas duas pilhas (`a` e `b`) e um conjunto restrito de operações.

O programa começa com todos os números na pilha `a` e a pilha `b` vazia. O objetivo é mover e reordenar os valores usando `sa`, `sb`, `ss`, `pa`, `pb`, `ra`, `rb`, `rr`, `rra`, `rrb` e `rrr` até que `a` esteja totalmente ordenada, gastando o menor número de operações possível.

Além do `push_swap` em si, o projeto implementa **quatro estratégias de ordenação diferentes** (com complexidades distintas), uma **métrica de desordem** para caracterizar o estado inicial da pilha, e um **modo de benchmark** (`--bench`) que reporta estatísticas detalhadas de execução.

### Operações disponíveis

| Operação | Efeito |
|----------|--------|
| `sa` | Troca os dois primeiros elementos do topo de `a`. |
| `sb` | Troca os dois primeiros elementos do topo de `b`. |
| `ss` | Executa `sa` e `sb` simultaneamente. |
| `pa` | Move o topo de `b` para o topo de `a`. |
| `pb` | Move o topo de `a` para o topo de `b`. |
| `ra` | Rotaciona `a` para cima (o primeiro elemento vira o último). |
| `rb` | Rotaciona `b` para cima (o primeiro elemento vira o último). |
| `rr` | Executa `ra` e `rb` simultaneamente. |
| `rra` | Rotaciona `a` para baixo (o último elemento vira o primeiro). |
| `rrb` | Rotaciona `b` para baixo (o último elemento vira o primeiro). |
| `rrr` | Executa `rra` e `rrb` simultaneamente. |

---

## Instruções

### Compilação

```bash
make

```

Isso gera o binário `push_swap` a partir dos arquivos-fonte, com as flags `-Wall -Wextra -Werror`, seguindo as regras `NAME`, `all`, `clean`, `fclean` e `re` exigidas pelo subject.

```bash
make clean   # remove os arquivos objeto
make fclean  # remove objetos e o binário
make re      # recompila do zero

```

### Execução

```bash
./push_swap [--simple|--medium|--complex|--adaptive] <lista de inteiros>

```

* Os inteiros podem ser passados como argumentos separados (`./push_swap 2 1 3`) ou como uma única string com os números separados por espaço (`./push_swap "2 1 3"`).
* O seletor de estratégia é opcional. Se omitido, `--adaptive` é usado por padrão.
* Se nenhum argumento numérico for informado, o programa não imprime nada e devolve o prompt.
* Em caso de erro (argumento não numérico, fora do limite de inteiros ou valores duplicados), o programa imprime `Error` na saída de erro (`stderr`).

### Exemplos de uso

```bash
$> ./push_swap 2 1 3 6 5 8
ra
pb
rra
pb
...
pa

$> ARG="4 67 3 87 23"; ./push_swap --adaptive $ARG | wc -l
13

$> shuf -i 0-9999 -n 500 > args.txt ; ./push_swap$(cat args.txt) | wc -l
4323

$> ./push_swap --adaptive 0 one 2 3
Error

```

### Modo benchmark (`--bench`)

Ao adicionar a flag `--bench`, o programa imprime em `stderr`, após a ordenação:

* A desordem calculada da pilha inicial (em % com duas casas decimais);
* O nome da estratégia usada e sua classe de complexidade teórica;
* O número total de operações geradas;
* A contagem individual de cada tipo de operação executada.

```bash
$> ./push_swap --bench --complex 5 4 3 2 1 1>/dev/null
Strategy: Complex O(n*log(n))
Disorder: 100.00%
Total: 7
sa: 1 | pb: 2 | ra: 1 | rra: 1 | pa: 2 |

```

---

## Algoritmos Implementados

O subject exige estratégias de ordenação distintas, todas gerando exclusivamente sequências de operações do modelo Push_swap.

### 1. Simple — $O(n^2)$ (`--simple`)

Adaptação de um **selection sort**: a cada iteração, localiza-se o menor valor ainda presente em `a`, que é levado ao topo pelo caminho mais curto (`ra` ou `rra`) e empurrado para `b`. Ao final, todos os elementos retornam para `a`, resultando na pilha ordenada. Adequado como estratégia de *baseline*.

### 2. Medium — $O(n\sqrt{n})$ (`--medium`)

Estratégia de **particionamento em blocos (chunks)**: o intervalo de índices é dividido em blocos de tamanho calculado dinamicamente com base na entrada. Os valores de `a` que cabem no bloco atual são empurrados para `b` (com micro-ajustes de rotação para manter `b` parcialmente ordenada). Ao final, os maiores valores de `b` são localizados e devolvidos a `a`. O fracionamento da pilha garante a alta performance computacional da estratégia.

### 3. Complex — $O(n \log n)$ (`--complex`)

Adaptação de **quicksort com particionamento por mediana**: a cada chamada recursiva, o pivô mediano é estimado; a pilha é percorrida empurrando os elementos menores/maiores para a pilha oposta. A recursão é aplicada separadamente às partições, com a devida compensação de *backtracking* (rebobinar com rotações reversas) para lidar com a natureza circular das pilhas.

### 4. Adaptive (`--adaptive`)

Estratégia padrão de produção. A lógica roteia a execução com base no tamanho da pilha. Entradas menores utilizam variações do *Selection Sort*, enquanto entradas maiores (como os testes oficiais de 100 e 500 números) adotam o *Chunk Sort*, garantindo o máximo de estabilidade e o menor número absoluto de operações na avaliação automatizada (Moulinette).

---

## Métrica de Desordem

A desordem é um coeficiente entre `0.0` e `1.0` que mede o quão longe a pilha inicial está da ordenação perfeita, analisando pares discrepantes. A medição é calculada **antes** de qualquer operação ser executada, e exibida como bônus da flag `--bench`.

* `0.0` → Pilha já ordenada (nenhum par fora de ordem).
* `1.0` → Pilha na pior ordem possível (todos os pares estão fora de ordem).

---

## Metas de Performance (Moulinette)

O algoritmo principal foi otimizado para atingir os mais altos graus de avaliação de performance estipulados pela 42:

| Tamanho | Aceitável (Aprovado) | Excelente (Nota Máxima) | Nossa Média |
| --- | --- | --- | --- |
| 100 números | < 2000 operações | < 700 operações | **~600** operações |
| 500 números | < 12000 operações | < 5500 operações | **~4300** operações |

---

## Estrutura do Projeto

| Arquivo(s) | Responsabilidade |
| --- | --- |
| `main.c` | Ponto de entrada, seleção de estratégia, orquestração geral. |
| `argument_parser.c`, `split_validations.c`, `string_validation.c` | Parsing e validação rigorosa dos argumentos. |
| `stack_creation.c`, `node_helpers.c` | Criação, liberação e manipulação das listas encadeadas. |
| `operations_*.c` | Implementação das 11 operações oficiais do Push_swap. |
| `assign_indexes.c` | Conversão dos valores brutos em índices relativos de ordenação. |
| `algorithm_*.c` | Implementação das estratégias de ordenação (Simple, Medium, Complex). |
| `disorder.c` | Cálculo da métrica matemática de desordem. |
| `bench.c`, `bench_utils.c` | Benchmark detalhado de uso de memória e instruções. |
| `error_handling.c` | Saída segura em caso de dados inválidos ou falhas de alocação. |

---

## Autores e Contribuições

Este projeto foi desenvolvido integralmente em dupla:

* **thamoliv**: Desenvolvimento do parser e validação de argumentos, estruturação do TAD de pilhas, operações Push_swap base, lógica core das três estratégias de ordenação (`simple`, `medium`, `complex`), cálculo matemático de desordem, sistema de benchmark e orquestração na `main.c`.
* **gproenca**: Desenvolvimento de utilitários cruciais para a estrutura algorítmica (`is_sorted`, localização de limites e varredura de índices), além da implementação e estabilização das operações do conjunto de rotação.
"""

with open('README.md', 'w', encoding='utf-8') as f:
f.write(readme_content)

```
Sem problemas! Seu arquivo `README.md` limpo e formatado com perfeição está pronto.

[file-tag: code-generated-file-0-1783960359787404904]

Basta baixar o arquivo acima e colocar na raiz do seu repositório. Desejo uma excelente defesa do projeto, vocês mandaram muito bem na implementação! Se precisar de mais alguma coisa, é só avisar.

```
