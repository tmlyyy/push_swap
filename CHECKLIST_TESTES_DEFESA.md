# Checklist de Testes para a Defesa — push_swap

> Baseado integralmente na grade de avaliação oficial
> (`Projetos Intra push_swap Editar.pdf`). Rode cada bloco antes da
> defesa e marque o `[ ]` como `[x]` quando passar. Sempre que uma
> seção pedir "rode 2-3 vezes com entradas diferentes", troque os
> valores de exemplo por outros gerados aleatoriamente.

**Preparação:**
```bash
make re
ls -la push_swap checker_linux
```
Confirme que os dois binários existem antes de começar.

---

## 1. Preliminares (o avaliador precisa disso, não é nota)

- [ ] Confirmar que exatamente **2 alunos** (`thamoliv`, `gproenca`) aparecem como colaboradores no repositório Git.
- [ ] Ambos conseguem explicar e defender qualquer parte do código (não só a que cada um escreveu).
- [ ] `README.md` documenta claramente a contribuição de cada aluno.

Se qualquer um desses 3 falhar, a avaliação é reprovada automaticamente — não é sobre código.

---

## 2. Checklist de conformidade do README.md

O repositório precisa ter um `README.md` na raiz contendo:

- [ ] Primeira linha em **itálico**, exatamente: *This project has been created as part of the 42 curriculum by thamoliv, gproenca.*
- [ ] Seção **"Descrição"** explicando o objetivo do projeto.
- [ ] Seção **"Instruções"** com compilação, instalação e/ou execução.
- [ ] Seção **"Recursos"** com referências (documentação, tutoriais etc.) e explicação de para que parte do projeto cada uma foi usada (incluindo uso de IA, se houver).
- [ ] Explicação detalhada e justificativa dos algoritmos: **Simple O(n²)**, **Medium O(n√n)**, **Complex O(n log n)** e a estratégia **adaptativa**.
- [ ] Documentação clara das contribuições de cada aluno.

*(Já coberto pelo `README.md` do projeto — confira antes da defesa.)*

---

## 3. Norma e compilação

```bash
norminette
```
- [ ] Nenhum erro de norma (se houver 1 erro, a avaliação **para** — pode continuar discutindo o código, mas essa parte não é pontuada).

```bash
make fclean
make
ls -la push_swap
```
- [ ] `Makefile` contém `NAME`, `all`, `clean`, `fclean`, `re`.
- [ ] Compila com `-Wall -Wextra -Werror`, sem warnings.
- [ ] Gera o executável `push_swap`.
- [ ] Não relinka desnecessariamente (rodar `make` de novo sem alterar nada não deve recompilar nada).

```bash
make clean && ls        # objetos somem, binário continua
make fclean && ls       # objetos e binário somem
make re && ls           # tudo recompilado do zero
```
- [ ] `make clean`, `make fclean` e `make re` funcionam corretamente.

---

## 4. Vazamentos de memória

Durante toda a defesa, rodar com uma ferramenta de leak check (o corretor pode usar `leaks`, `valgrind` ou `e_fence`; no Linux, use `valgrind`):

```bash
valgrind --leak-check=full --show-leak-kinds=all ./push_swap 5 4 3 2 1
```
- [ ] `definitely lost` e `indirectly lost` = **0 bytes**.
- [ ] Nenhum vazamento significativo (pequenos "still reachable" residuais do sistema costumam ser aceitáveis; vazamentos reais de heap não são).

---

## 5. Gestão de erros (push_swap)

> Nota: pelo menos 3 dos 4 testes abaixo precisam passar, senão a seção inteira vale 0.

```bash
./push_swap 1 2 a
```
- [ ] Parâmetro não numérico → imprime `Error` + `\n` em stderr.

```bash
./push_swap 1 2 2
```
- [ ] Parâmetro numérico duplicado → imprime `Error` + `\n` em stderr.

```bash
./push_swap 1 2 99999999999
```
- [ ] Número maior que `INT_MAX` → imprime `Error` + `\n` em stderr.

```bash
./push_swap
```
- [ ] Sem parâmetros → não imprime nada, apenas retorna o prompt.

---

## 6. Seleção de estratégia — testes básicos

> Nota: pelo menos 3 dos 5 testes abaixo precisam passar.

```bash
./push_swap --simple 5 4 3 2 1
```
- [ ] Produz saída válida que ordena os números.

```bash
./push_swap --medium 5 4 3 2 1
```
- [ ] Produz saída válida que ordena os números.

```bash
./push_swap --complex 5 4 3 2 1
```
- [ ] Produz saída válida que ordena os números.

```bash
./push_swap --adaptive 5 4 3 2 1
```
- [ ] Produz saída válida que ordena os números.

```bash
./push_swap 5 4 3 2 1
```
- [ ] Executar **sem nenhuma flag** produz o mesmo comportamento de `--adaptive`.

---

## 7. Teste de identidade — entradas já ordenadas

> Nota: pelo menos 3 dos 4 testes abaixo precisam funcionar.

```bash
./push_swap 42
```
- [ ] Não imprime nada.

```bash
./push_swap 2 3
```
- [ ] Não imprime nada.

```bash
./push_swap 0 1 2 3
```
- [ ] Não imprime nada.

```bash
./push_swap 0 1 2 3 4 5 6 7 8 9
```
- [ ] Não imprime nada.

---

## 8. Entradas pequenas (3 números)

```bash
ARG="2 1 0"; ./push_swap $ARG | ./checker_linux $ARG
```
- [ ] `checker_linux` responde `OK`.
- [ ] Número de operações ≤ 5 (aceitável), ≤ 3 (bom).

Repetir com outras combinações:
```bash
ARG="0 2 1"; ./push_swap $ARG | ./checker_linux $ARG
ARG="1 0 2"; ./push_swap $ARG | ./checker_linux $ARG
```
- [ ] `OK` em todas, com contagem de operações razoável.

---

## 9. Entradas médias (5 números)

```bash
ARG="1 5 2 4 3"; ./push_swap $ARG | ./checker_linux $ARG
```
- [ ] `checker_linux` responde `OK`.
- [ ] Número de operações ≤ 15 (aceitável), ≤ 12 (bom).

Repetir com 2-3 combinações extras:
```bash
ARG="5 1 4 2 3"; ./push_swap $ARG | ./checker_linux $ARG
ARG="3 5 1 4 2"; ./push_swap $ARG | ./checker_linux $ARG
```
- [ ] `OK` em todas, com contagem razoável (algoritmos diferentes podem variar — corretude importa mais que otimização perfeita aqui).

---

## 10. Modo benchmark e cálculo de desordem

```bash
./push_swap --bench --simple 5 4 3 2 1 2>/dev/null
```
- [ ] Ainda produz normalmente as instruções de ordenação em stdout (o `--bench` não deve interferir na saída principal).

```bash
./push_swap --bench --simple 5 4 3 2 1 2>bench.txt >/dev/null && cat bench.txt
```
- [ ] Saída do benchmark contém: percentual de desordem, nome da estratégia + classe de complexidade, contagem total de operações, contagens individuais por tipo de operação.

```bash
./push_swap --bench --simple 1 2 3 4 5 2>&1 >/dev/null | grep -i disorder
```
- [ ] Entrada já ordenada (`1 2 3 4 5`) → desordem próxima de **0,00%**.

```bash
./push_swap --bench --simple 5 4 3 2 1 2>&1 >/dev/null | grep -i disorder
```
- [ ] Entrada invertida (`5 4 3 2 1`) → desordem próxima de **100,00%**.

---

## 11. Entradas grandes (100 números)

```bash
for i in 1 2 3; do
  ARG=$(shuf -i 1-500 -n 100 | tr '\n' ' ')
  echo "Rodada $i:"
  ./push_swap $ARG | ./checker_linux $ARG
  ./push_swap $ARG | wc -l
done
```
- [ ] `OK` em todas as rodadas.
- [ ] Menos de **2000** operações para passar.
- [ ] Menos de **1500** = bom.
- [ ] Menos de **700** = excelente. *(Nos nossos testes: ~644–664 → excelente.)*

---

## 12. Revisão de código e explicação do algoritmo (perguntas orais)

Preparar resposta curta e objetiva para cada uma (ver `GUIA_DE_ESTUDO_DEFESA.md` para o detalhe completo):

- [ ] **Como funciona a estratégia `--simple`?** (deve ser O(n²) — selection sort adaptado: acha o menor, leva ao topo pelo caminho mais curto, empurra para `b`; repete e depois devolve tudo para `a`).
- [ ] **Como funciona a estratégia `--medium`?** (deve ser O(n√n) — divide em blocos de tamanho `n/5` ou `n/11`, empurra por faixas de valor, depois devolve do maior para o menor).
- [ ] **Como funciona a estratégia `--complex`?** (deve ser O(n log n) — quicksort adaptado com pivô de mediana, particiona recursivamente entre `a` e `b`).
- [ ] **Como a estratégia `--adaptive` escolhe qual método usar?** — resposta honesta: por **tamanho da pilha** (`size_a == 2`/`3` → casos triviais; `size_a <= 5` → selection; `size_a > 5` → chunk), e explicar a decisão consciente de não usar quicksort automaticamente em pilhas grandes por causa do bug de sub-blocos identificado nos testes de 500 números.

---

## 13. Teste de sinalizadores de estratégia (comparação)

```bash
ARG=$(shuf -i 1-200 -n 50 | tr '\n' ' ')
echo "Entrada: $ARG"
echo "--simple:";  ./push_swap --simple  $ARG | ./checker_linux $ARG; ./push_swap --simple  $ARG | wc -l
echo "--medium:";  ./push_swap --medium  $ARG | ./checker_linux $ARG; ./push_swap --medium  $ARG | wc -l
echo "--complex:"; ./push_swap --complex $ARG | ./checker_linux $ARG; ./push_swap --complex $ARG | wc -l
echo "--adaptive:"; ./push_swap --adaptive $ARG | ./checker_linux $ARG; ./push_swap --adaptive $ARG | wc -l
```
- [ ] A maioria das estratégias produz resultados válidos (`OK`) e corretamente classificados.
- [ ] Em geral, `--complex` usa **menos** operações que `--simple`.
- [ ] `--adaptive` (ou nenhuma flag) funciona e escolhe automaticamente.

---

## 14. Entradas muito grandes (500 números)

```bash
for i in 1 2; do
  ARG=$(shuf -i 1-1000 -n 500 | tr '\n' ' ')
  echo "Rodada $i:"
  ./push_swap $ARG | ./checker_linux $ARG
  ./push_swap $ARG | wc -l
done
```
- [ ] `OK` nas duas rodadas.
- [ ] Menos de **12000** operações para passar.
- [ ] Menos de **8000** = bom.
- [ ] Menos de **5500** = excelente. *(Nos nossos testes: ~4300 → excelente.)*

---

## 15. Modificação rápida de código ao vivo (`--count-only`)

O avaliador vai pedir para adicionar, **ao vivo, em até 10 minutos**, uma flag nova:

```bash
./push_swap --count-only 3 2 1
```
Deve imprimir **apenas** o número total de operações (ex.: `3`), sem listar as operações em si.

**Onde mexer (praticar antes):**
- [ ] Adicionar `--count-only` ao parsing de flags (`argument_parser.c` / `main.c`, junto com `--simple`/`--medium`/`--complex`/`--bench`).
- [ ] Localizar onde as operações são impressas (provavelmente em `print_operation`, dentro de `utils.c`, chamado por cada `op_*` em `operations_push.c`, `operations_swap.c`, `operations_rotate.c`, `operations_reverse_rotate.c`).
- [ ] Adicionar uma flag/contador em `t_data` ou `t_config` (ex.: `int count_only`) que, quando ativa, faz `print_operation` **incrementar um contador global** em vez de imprimir a operação.
- [ ] Ao final da execução, se `count_only` estiver ativo, imprimir só o valor do contador com `\n`.
- [ ] Testar com pelo menos 2 entradas diferentes antes de mostrar ao avaliador.

- [ ] Task concluída dentro de 10 minutos, com demonstração funcionando.

---

## 16. Bônus — checker (só avaliado se a parte obrigatória for EXCELENTE)

### 16.1 Gestão de erros do checker

> Se pelo menos 1 desses falhar, a seção inteira vale 0.

```bash
./checker_linux 1 2 a
```
- [ ] Parâmetro não numérico → `Error` + `\n` em stderr.

```bash
./checker_linux 1 2 2
```
- [ ] Parâmetro duplicado → `Error` + `\n` em stderr.

```bash
./checker_linux 1 2 99999999999
```
- [ ] Maior que `MAXINT` → `Error` + `\n` em stderr.

```bash
./checker_linux
```
- [ ] Sem parâmetros → não imprime nada, retorna o prompt.

```bash
./checker_linux 1 2 3
xyz
```
(digitar uma ação inexistente e Enter)
- [ ] Ação inválida durante a fase de instruções → `Error` + `\n` em stderr.

```bash
./checker_linux 1 2 3
 sa 
```
(ação com espaços antes/depois)
- [ ] Ação com espaço extra → `Error` + `\n` em stderr.

### 16.2 Testes falsos (o checker precisa detectar erro de ordenação)

> Se pelo menos 1 falhar, a seção vale 0.

```bash
./checker_linux 0 9 1 8 2 7 3 6 4 5
```
Digitar: `sa`, `pb`, `rrr`, depois `Ctrl+D`.
- [ ] Deve responder `KO` (lista não ordena a pilha).

```bash
./checker_linux <lista válida>
```
Escrever uma lista de instruções válida, mas que **não** ordena — repetir com 2-3 permutações diferentes.
- [ ] Deve responder `KO` em todas.

### 16.3 Testes corretos (o checker precisa confirmar ordenação certa)

> Se pelo menos 1 falhar, a seção vale 0.

```bash
./checker_linux 0 1 2
```
`Ctrl+D` sem digitar nada.
- [ ] Deve responder `OK` (já está ordenado, nenhuma instrução necessária).

```bash
./checker_linux 0 9 1 8 2
```
Digitar: `pb`, `ra`, `pb`, `ra`, `sa`, `ra`, `pa`, `pa`, depois `Ctrl+D`.
- [ ] Deve responder `OK`.

```bash
./checker_linux <lista válida>
```
Gerar uma lista de instruções válida usando o próprio `push_swap` (`./push_swap $ARG`) e alimentar no `checker`, com 2-3 permutações diferentes.
- [ ] Deve responder `OK` em todas.

---

## 17. Lembretes finais (regra que zera a nota se violada)

- [ ] **Nenhum segfault, crash ou saída abrupta/descontrolada durante toda a defesa** (parte obrigatória e bônus). Se acontecer, a nota final é **0**.
- [ ] Confirmar antecipadamente que `push_swap` e `checker_linux` tratam entradas extremas sem crashar: strings vazias, só espaços, `INT_MIN`/`INT_MAX`, milhares de argumentos.

```bash
./push_swap ""
./push_swap "   "
./push_swap -2147483648 2147483647
```
- [ ] Nenhum desses trava ou dá segfault.

---

## Resumo rápido — comandos para rodar tudo em sequência antes da defesa

```bash
make re
norminette
valgrind --leak-check=full ./push_swap 5 4 3 2 1

./push_swap 1 2 a; echo "---"
./push_swap 1 2 2; echo "---"
./push_swap; echo "---"

ARG="2 1 0"; ./push_swap $ARG | ./checker_linux $ARG
ARG="1 5 2 4 3"; ./push_swap $ARG | ./checker_linux $ARG

for i in 1 2 3; do
  ARG=$(shuf -i 1-500 -n 100 | tr '\n' ' ')
  ./push_swap $ARG | ./checker_linux $ARG
  ./push_swap $ARG | wc -l
done

for i in 1 2; do
  ARG=$(shuf -i 1-1000 -n 500 | tr '\n' ' ')
  ./push_swap $ARG | ./checker_linux $ARG
  ./push_swap $ARG | wc -l
done
```
