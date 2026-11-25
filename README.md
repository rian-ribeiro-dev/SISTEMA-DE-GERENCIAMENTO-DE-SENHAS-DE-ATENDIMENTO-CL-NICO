# Sistema de Gerenciamento de Senhas de Atendimento Clínico

Trabalho em linguagem C que simula a triagem de uma clínica: cadastra pacientes, classifica a prioridade, emite senhas e controla a ordem de atendimento.

## Arquivos

- `main.c`: menu principal
- `operacoes.h`: struct `Senha` e declaração das funções
- `funcoes.c`: implementação das funções (cadastro, classificação, filas, atendimento e painel)
- `exemplos/entrada.txt` e `exemplos/saida.txt`: teste usado no exemplo abaixo

## Como compilar e executar

```
gcc main.c funcoes.c -o main
./main
```

No Windows o executável fica como `main.exe`.

Para rodar o exemplo pronto sem digitar tudo:

```
./main < exemplos/entrada.txt
```

## Categorias

| Código | Categoria | Quem entra |
|---|---|---|
| U001 | Urgente | Idade superior a 80 anos |
| P001 | Preferencial | Gestantes, lactantes, necessidades especiais, obesos, mulheres com 60+ e homens com 65+ |
| N001 | Normal | Pacientes sem nenhuma das condições acima |

Obs.: a classificação por idade não substitui avaliação clínica, é só uma regra de programação para este trabalho.

## Como o programa funciona

- Existem 3 filas (urgente, preferencial e normal), guardadas em uma matriz de `Senha`.
- Cada categoria tem seu próprio contador (N001, N002... / P001, P002... / U001, U002...).
- Na hora de chamar, o programa procura primeiro na fila de urgentes, depois nas preferenciais e por último nas normais. Dentro de cada fila vale a ordem de chegada (FIFO).
- Ao chamar um paciente, ele sai da fila e os demais andam uma posição.
- Só é possível chamar o próximo depois de finalizar o atendimento atual. Ao finalizar, o programa já mostra qual é a próxima senha.
- Quem já foi atendido não volta para a fila.
- Cada fila aceita até 100 senhas esperando ao mesmo tempo (`MAX` no `operacoes.h`).

## Funções

| Módulo | Funções |
|---|---|
| Registro de senhas | `cadastrarPaciente`, `gerarSenha` |
| Classificação | `classificar` |
| Atendimento | `consultarProxima`, `chamarPaciente`, `mostrarAtendimento`, `finalizarAtendimento` |
| Painel | `mostrarPainel` |

## Exemplo de execução

Pacientes cadastrados (opção 1):

| Ordem | Paciente | Senha gerada |
|---|---|---|
| 1 | Homem, 30 anos | N001 |
| 2 | Mulher, 28 anos, gestante | P001 |
| 3 | Homem, 85 anos | U001 |
| 4 | Mulher, 62 anos | P002 |
| 5 | Homem, 63 anos (ainda não é preferencial) | N002 |
| 6 | Mulher, 90 anos | U002 |

Painel logo após os cadastros (opção 6):

```
=============== PAINEL ===============
Senha chamada: ---

Proximas senhas:
  1) U001 (Urgente)
  2) U002 (Urgente)
  3) P001 (Preferencial)
  4) P002 (Preferencial)
  5) N001 (Normal)

Aguardando por categoria:
  Urgente: 2
  Preferencial: 2
  Normal: 2

Emitidas: 6 | Atendidas: 0
======================================
```

Chamando pacientes (opção 3) e finalizando (opção 5):

```
Chamando senha U001 - Urgente

Ja existe um atendimento em andamento (U001). Finalize antes de chamar outro.

Atendimento da senha U001 finalizado.
Proxima senha: U002 (Urgente)

Chamando senha U002 - Urgente

Atendimento da senha U002 finalizado.
Proxima senha: P001 (Preferencial)

Chamando senha P001 - Preferencial
```

Painel depois dessas chamadas:

```
=============== PAINEL ===============
Senha chamada: P001 (Preferencial)

Proximas senhas:
  1) P002 (Preferencial)
  2) N001 (Normal)
  3) N002 (Normal)

Aguardando por categoria:
  Urgente: 0
  Preferencial: 1
  Normal: 2

Emitidas: 6 | Atendidas: 2
======================================
```

Ordem completa de chamada: U001, U002, P001, P002, N001, N002.

A saída completa do teste está em `exemplos/saida.txt`.
