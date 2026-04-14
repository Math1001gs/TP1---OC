# 🖥️ Montador RISC-V Simplificado

> Trabalho Prático 01 — CCF 252 · Organização de Computadores I  
> Ciência da Computação — UFV Florestal  
> Prof. José Augusto Miranda Nacif

Implementação em **C** de um montador (assembler) para um subconjunto da arquitetura **RISC-V**, capaz de traduzir instruções Assembly para código de máquina binário de 32 bits.

---

## 📋 Instruções Suportadas

O montador suporta os quatro formatos de instrução do RISC-V: **R**, **I**, **S** e **B**.

| Tipo | Instruções |
|------|-----------|
| **R** | `add`, `sub`, `and`, `or`, `xor`, `sll`, `srl` |
| **I** | `lb`, `lh`, `lw`, `addi`, `andi`, `ori` |
| **S** | `sb`, `sh`, `sw` |
| **B** | `bne`, `beq` |

### Pseudo-instruções suportadas

| Pseudo-instrução | Traduzida para |
|-----------------|---------------|
| `li rd, imm`    | `addi rd, x0, imm` |
| `mv rd, rs`     | `addi rd, rs, 0`   |

---

## 📁 Estrutura do Projeto

```
.
├── main.c          # Ponto de entrada: leitura, decodificação e saída
├── func/
│   ├── func.h      # Definição da struct instrucao e protótipos
│   └── func.c      # Funções auxiliares de conversão binária
├── makefile        # Automação de compilação e execução
└── teste.asm       # Arquivo de exemplo para teste
```

---

## ⚙️ Compilação

### Pré-requisitos

- GCC (GNU Compiler Collection)
- Make
- Linux

### Compilar manualmente

```bash
gcc main.c func/func.c -o assembler
```

### Compilar com Make

```bash
make
```

> O `make` compila o projeto e executa automaticamente o arquivo `teste.asm`, gerando `saida.bin`.

---

## 🚀 Como Usar

O montador aceita duas formas de execução:

### 1. Saída no terminal

Passa apenas o arquivo `.asm` como argumento — o resultado é impresso diretamente no terminal.

```bash
./assembler entrada.asm
```

### 2. Saída em arquivo

Usa o parâmetro `-o` para salvar o código binário em um arquivo de saída.

```bash
./assembler entrada.asm -o saida.bin
```

---

## 📄 Exemplo

**Entrada** (`teste.asm`):
```asm
add  x2, x0, x1
sll  x1, x2, x2
or   x2, x2, x1
andi x2, x1, 16
addi x3, x2, -243
```

**Saída** (terminal ou arquivo):
```
00000000000100000000000100110011
00000000001000010001000010110011
00000000000100010110000100110011
00000001000000001111000100010011
11110000110100010000000110010011
```

---

## 🧠 Funcionamento Interno

### Tabela de instruções

Em `main.c`, todas as instruções são armazenadas em um vetor de structs do tipo `instrucao`, contendo nome, `funct7`, `funct3`, `opcode` e tipo (`R`, `I`, `S` ou `B`).

### Codificação por tipo

Ao identificar a instrução, o programa realiza a leitura dos operandos e monta a palavra de 32 bits seguindo o formato do ISA RISC-V:

- **Tipo R:** `funct7 | rs2 | rs1 | funct3 | rd | opcode`
- **Tipo I:** `imm[11:0] | rs1 | funct3 | rd | opcode`
- **Tipo S:** `imm[11:5] | rs2 | rs1 | funct3 | imm[4:0] | opcode`
- **Tipo B:** `imm[12|10:5] | rs2 | rs1 | funct3 | imm[4:1|11] | opcode`

### Funções auxiliares (`func.c`)

| Função | Descrição |
|--------|-----------|
| `printBin(n, bits)` | Imprime `n` em binário com `bits` dígitos, preservando os zeros à esquerda |
| `xNparaBin(str, out)` | Converte registradores (`x0`–`x31`) para binário de 5 bits |
| `NumparaBin(str, out)` | Converte imediatos inteiros (incluindo negativos) para binário de 12 bits em complemento de dois |

---

## 📚 Referência

- [RISC-V ISA Specification v2.2](https://riscv.org/wp-content/uploads/2017/05/riscv-spec-v2.2.pdf)

---

## 🎓 Informações Acadêmicas

| Campo | Info |
|-------|------|
| Disciplina | CCF 252 — Organização de Computadores I |
| Instituição | Universidade Federal de Viçosa — Campus Florestal |
| Professor | José Augusto Miranda Nacif |
| Linguagem | C |
