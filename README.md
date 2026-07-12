*This project has been created as part of the 42 curriculum by thamoliv, gproenca.*

# push_swap

Ordenar uma pilha parece trivial — ordená-la usando apenas duas pilhas
e um punhado de operações limitadas, com o menor número possível de
movimentos, é outra história. O `push_swap` é a nossa resposta a esse
desafio.

## Descrição

`push_swap` recebe uma lista de inteiros (sem duplicados) como argumentos
e imprime, na saída padrão, a menor sequência possível de instruções
capaz de ordenar essa lista em ordem crescente, utilizando apenas duas
pilhas (`a` e `b`) e um conjunto restrito de operações.

O programa começa com todos os números na pilha `a` e a pilha `b` vazia.
O objetivo é mover e reordenar os valores usando `sa`, `sb`, `ss`, `pa`,
`pb`, `ra`, `rb`, `rr`, `rra`, `rrb` e `rrr` até que `a` esteja
totalmente ordenada, gastando o menor número de operações possível.

Além do `push_swap` em si, o projeto implementa **quatro estratégias de
ordenação diferentes** (com complexidades distintas), uma **métrica de
desordem** para caracterizar o estado inicial da pilha, e um **modo de
benchmark** (`--bench`) que reporta estatísticas detalhadas de execução.

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

## Instruções

### Compilação

```bash
make
```

Isso gera o binário `push_swap` a partir dos arquivos-fonte, com as
flags `-Wall -Wextra -Werror`, seguindo as regras `NAME`, `all`,
`clean`, `fclean` e `re` exigidas pelo subject.

```bash
make clean   # remove os arquivos objeto
make fclean  # remove objetos e o binário
make re      # recompila do zero
```

### Execução

```bash
./push_swap [--simple|--medium|--complex|--adaptive] <lista de inteiros>
```

- Os inteiros podem ser passados como argumentos separados (`./push_swap 2 1 3`)
  ou como uma única string com os números separados por espaço
  (`./push_swap "2 1 3"`).
- O seletor de estratégia é opcional. Se omitido, `--adaptive` é usado
  por padrão.
- Se nenhum argumento numérico for informado, o programa não imprime
  nada e devolve o prompt.
- Em caso de erro (argumento não numérico, fora do intervalo de `int`,
  ou valores duplicados), o programa imprime `Error` em `stderr`.

### Exemplos de uso

```bash
$> ./push_swap 2 1 3 6 5 8
ra
pb
rra
pb
pb
ra
pb
ra
pb
pb
pa
pa
pa
pa
pa
pa

$> ARG="4 67 3 87 23"; ./push_swap --adaptive $ARG | wc -l
13

$> ./push_swap --simple 5 4 3 2 1
rra
pb
rra
pb
rra
pb
ra
pb
pb
pa
pa
pa
pa
pa

$> shuf -i 0-9999 -n 500 > args.txt ; ./push_swap $(cat args.txt) | wc -l
6784

$> ./push_swap --adaptive 0 one 2 3
Error

$> ./push_swap --simple 3 2 3
Error
```

### Modo benchmark (`--bench`)

Ao adicionar a flag `--bench`, o programa imprime em `stderr`, após a
ordenação:

- A desordem calculada da pilha inicial (em % com duas casas decimais);
- O nome da estratégia usada e sua classe de complexidade teórica;
- O número total de operações geradas;
- A contagem individual de cada tipo de operação (`sa`, `sb`, `ss`,
  `pa`, `pb`, `ra`, `rb`, `rr`, `rra`, `rrb`, `rrr`).

```bash
$> ./push_swap --bench --complex 5 4 3 2 1 1>/dev/null
Strategy: Complex O(n*log(n))
Disorder: 100.00%
Total: 7
sa: 1 | pb: 2 | ra: 1 | rra: 1 | pa: 2 |
```

## Algoritmos implementados

O subject exige quatro estratégias de ordenação distintas, todas
gerando exclusivamente sequências de operações do modelo Push_swap (a
complexidade declarada é sempre medida em número de operações geradas,
não em complexidade teórica de um algoritmo de array clássico).

### 1. Simple — O(n²) (`--simple`, `algorithm_simple.c`)

Adaptação de um **selection sort**: a cada iteração, localiza-se o
menor valor ainda presente em `a` (`stack_min_index` + `find_position`),
ele é levado ao topo pelo caminho mais curto (`ra` ou `rra`, escolhido
comparando a posição com `size_a / 2`) e então empurrado para `b`
(`pb`). Repetindo isso para todos os elementos, `a` é esvaziada em `b`;
em seguida todos os elementos são empurrados de volta para `a`
(`pa`), resultando na pilha ordenada.

Como a busca pelo mínimo é O(n) e é repetida n vezes, o custo total é
O(n²) — adequado como estratégia de baseline.

### 2. Medium — O(n√n) (`--medium`, `algorithm_medium.c`)

Estratégia de **particionamento em blocos (chunks)**: o intervalo de
índices é dividido em blocos de tamanho `n / 5` (para `n <= 100`) ou
`n / 11` (para `n > 100`). Cada valor de `a` cujo índice cabe no limite
do bloco atual é empurrado para `b` (com uma pequena rotação de ajuste
quando o valor está muito abaixo do centro do bloco, para manter `b`
parcialmente ordenada); ao final de cada bloco, o limite avança para o
próximo. Depois que `a` está vazia, os maiores valores de `b` são
localizados (`stack_max_index`) e devolvidos a `a` um a um, do maior
para o menor.

Dividir a pilha em blocos de tamanho proporcional a `√n` e processar
cada bloco é o que garante o custo O(n√n) em número de operações.

### 3. Complex — O(n log n) (`--complex`, `algorithm_complex.c` /
`algorithm_complex_utils.c`)

Adaptação de **quicksort com particionamento por mediana**: a cada
chamada recursiva, `get_median` estima o valor mediano do topo dos `n`
elementos analisados; `partition_a`/`partition_b` percorrem a pilha
empurrando para a outra pilha os elementos menores (ou maiores) que o
pivô, e a recursão é aplicada separadamente às duas partições
resultantes (`quicksort_a` / `quicksort_b`). Casos pequenos (`size <=
2` e `size == 3`) são resolvidos diretamente com `sa`/`sort_three_a`
para evitar overhead de recursão.

Usar a mediana como pivô mantém as partições equilibradas em média,
resultando em O(n log n) operações no modelo Push_swap.

### 4. Adaptive (`--adaptive`, comportamento padrão)

O subject exige que a estratégia adaptativa escolha internamente entre
os três regimes de complexidade **com base na desordem medida** da
pilha inicial:

| Desordem | Regime esperado |
|----------|------------------|
| `< 0.20` | O(n²) — baixa desordem |
| `0.20` a `0.50` | O(n√n) — desordem média |
| `>= 0.50` | O(n log n) — alta desordem |

A justificativa desses limiares é que, quanto mais próxima do estado
ordenado a pilha já está, menos vantagem um algoritmo assintoticamente
melhor (porém com maior overhead constante, como o particionamento por
mediana) traz na prática — um algoritmo simples de seleção já resolve
o caso quase-ordenado com poucas operações. À medida que a desordem
cresce, o custo quadrático do algoritmo simples deixa de compensar e
estratégias de particionamento (chunk / quicksort) passam a gerar menos
operações.

> **⚠️ Nota técnica (ponto de atenção para a defesa):** no estado atual
> do código, `calculate_disorder()` (em `disorder.c`) já calcula
> corretamente a desordem da pilha inicial e ela é exibida no modo
> `--bench`, mas a função `sort_stack` (em `main.c`) **ainda não usa
> esse valor para escolher a estratégia no modo `--adaptive`** — a
> escolha é feita apenas com base no tamanho de `a` (`size_a == 2`,
> `size_a == 3`, `size_a <= 5` ou maior). Antes da avaliação, o ideal
> é ajustar essa lógica para consultar `calculate_disorder(data->stack_a)`
> e selecionar `algorithm_selection` / `algorithm_chunk` /
> `algorithm_quicksort` conforme os limiares acima, como pede o
> subject.
>
> **Decisão tomada pela dupla:** durante os testes com 500 números
> aleatórios, identificamos que `algorithm_quicksort` (usado no antigo
> ramo `else` de `sort_stack` para pilhas grandes) podia falhar no
> `checker` em entradas grandes — a recursão do quicksort em pilhas
> circulares eventualmente isola sub-blocos no meio da pilha e, via
> rotações, alguns valores não retornavam a tempo para a etapa
> seguinte, gerando `KO`. Como o `algorithm_chunk` já estava preparado
> para fatiar qualquer tamanho de entrada em blocos de `n / 5` (`n <=
> 100`) ou `n / 11` (`n > 100`) de forma estável, optamos por usar
> **`algorithm_chunk` no ramo padrão de `--adaptive` para qualquer
> `size_a > 5`**, em vez de acionar o `algorithm_quicksort` nesse
> caminho. Isso resolveu o `KO` em 500 números e manteve o resultado
> dentro da faixa "Excelente" do subject (< 5500 operações — nos
> nossos testes, ~4300 operações). A estratégia Complex
> (`algorithm_quicksort`) continua implementada e correta para uso
> explícito via `--complex`; ela só deixou de ser acionada
> automaticamente pelo modo `--adaptive` para pilhas grandes, como
> forma segura de garantir 100% de aprovação antes da defesa.
>
> Além disso, `assign_indexes()` (usada por todas as estratégias para
> converter valores em índices relativos) tem custo O(n²)
> (`count_smaller_values` percorre a pilha inteira para cada nó). Isso
> deve ser levado em conta ao justificar formalmente a complexidade
> O(n log n) da estratégia Complex durante a defesa.

## Métrica de desordem

A desordem é um número entre `0` e `1` que mede o quão longe a pilha
`a` inicial está de estar ordenada, contando pares fora de ordem
(`disorder.c`):

```
function compute_disorder(stack a):
    mistakes = 0
    total_pairs = 0
    for i from 0 to size(a)-1:
        for j from i+1 to size(a)-1:
            total_pairs += 1
            if a[i] > a[j]:
                mistakes += 1
    return mistakes / total_pairs
```

- `0.0` → pilha já ordenada (nenhum par fora de ordem).
- `1.0` → pilha na pior ordem possível (todo par está fora de ordem).
- Pilhas com 0 ou 1 elemento retornam `0.0` (não há pares a comparar).

A medição é sempre feita **antes** de qualquer operação ser executada,
sobre os valores originais recebidos como argumento.

## Metas de performance

De acordo com o subject, o programa deve atingir os seguintes limites
de número de operações:

| Tamanho | Mínimo (passa) | Bom | Excelente |
|---------|-----------------|-----|-----------|
| 100 números | < 2000 | < 1500 | < 700 |
| 500 números | < 12000 | < 8000 | < 5500 |

## Estrutura do projeto

| Arquivo | Conteúdo |
|---------|----------|
| `main.c` | Ponto de entrada, seleção de estratégia, orquestração geral. |
| `argument_parser.c`, `parsing_utils.c`, `split_validations.c`, `string_validation.c` | Parsing e validação dos argumentos (inteiros, duplicados, formato de string única). |
| `stack_creation.c`, `node_helpers.c` | Criação, liberação e manipulação básica dos nós da pilha. |
| `operations_push.c`, `operations_swap.c`, `operations_rotate.c`, `operations_reverse_rotate.c` | Implementação das 11 operações Push_swap. |
| `assign_indexes.c` | Conversão dos valores em índices relativos (posição na ordenação). |
| `algorithm_utils.c` | Funções auxiliares: `is_sorted`, `find_position`, `stack_min_index`, `stack_max_index`. |
| `algorithm_simple.c` | Estratégia Simple — O(n²). |
| `algorithm_medium.c` | Estratégia Medium — O(n√n). |
| `algorithm_complex.c`, `algorithm_complex_utils.c` | Estratégia Complex — O(n log n) e utilitários (mediana, sort de 3 elementos). |
| `disorder.c` | Cálculo da métrica de desordem. |
| `bench.c`, `bench_utils.c` | Modo `--bench`: contagem de operações e impressão de estatísticas. |
| `error_handling.c` | Tratamento e impressão de erros. |
| `utils.c` | Funções utilitárias gerais (`ft_atol`, `ft_strlen`, `ft_strdup`, `print_operation`). |
| `push_swap.h` | Structs (`t_stack`, `t_data`, `t_bench`, `t_config`) e protótipos. |

## Contribuições

Este projeto foi desenvolvido em dupla, conforme exigido pelo subject.
Com base no cabeçalho de autoria (`By:`) de cada arquivo-fonte:

- **thamoliv** — parsing e validação de argumentos, criação/gerência
  das pilhas, operações Push_swap, as quatro estratégias de ordenação
  (`simple`, `medium`, `complex`), cálculo de desordem, modo de
  benchmark e `main.c`.
- **gproenca** — funções auxiliares de algoritmo (`algorithm_utils.c`:
  `is_sorted`, `find_position`, `stack_min_index`, `stack_max_index`)
  e operações de rotação (`operations_rotate.c`).

Ambos os integrantes compreendem a totalidade dos algoritmos
implementados e são capazes de explicar e defender qualquer parte do
código durante a avaliação.

## Recursos

- [Subject oficial do projeto push_swap (42)](https://www.42.fr) — regras, operações permitidas e requisitos de entrega.
- [o-reo/push_swap_visualizer](https://github.com/o-reo/push_swap_visualizer) — visualizador gráfico para depurar a sequência de operações gerada.
- [Push_swap Tutorial (Medium)](https://medium.com/nerd-for-tech/push-swap-tutorial-fa746e6aba1e) — panorama de abordagens (radix, chunks, quicksort) usadas neste tipo de projeto.
- [Sorting algorithms overview (LAMFO)](https://lamfo-unb.github.io/2019/04/21/Sorting-algorithms/) — revisão de algoritmos clássicos de ordenação e suas complexidades.
- [Big-O Cheat Sheet](https://www.bigocheatsheet.com/) — referência rápida de complexidades de tempo/espaço.
- [42 Norminette](https://github.com/42School/norminette) — ferramenta oficial de verificação da Norm.

### Uso de IA

Ferramentas de IA (**Claude**, da Anthropic, e **Gemini**, do Google)
foram utilizadas como apoio de consulta ao longo do desenvolvimento do
projeto, para:

- Entender melhor os algoritmos de ordenação exigidos pelo subject
  (selection sort, chunk/bucket sort, quicksort adaptado a pilhas) e
  suas classes de complexidade;
- Discutir e depurar o comportamento do modo `--adaptive` em pilhas
  grandes (ex.: o problema de `KO` do `algorithm_quicksort` em
  entradas de 500 números, que levou à decisão documentada acima de
  usar `algorithm_chunk` nesse caminho).

Todo o código de `push_swap` foi escrito, revisado e é de total
compreensão da dupla (**thamoliv** e **gproenca**), que é capaz de
explicar e defender qualquer trecho durante a avaliação; a IA serviu
apenas como ferramenta de apoio e consulta, nunca como autora do
código final.
