# Projeto T1

Este é o README do projeto **Nome do Projeto**. Este projeto é desenvolvido em C++ e utiliza o CMake como sistema de build. As instruções a seguir guiarão você para configurar, compilar e rodar o projeto em ambientes Windows e Linux.

---

## Pré-requisitos

Antes de compilar o projeto, certifique-se de ter as seguintes ferramentas instaladas:

- **CMake**: https://cmake.org/download/
- **Compilador C++**:
  - Windows: [Visual Studio](https://visualstudio.microsoft.com/) (com suporte a C++) ou [MinGW](http://www.mingw.org/)
  - Linux: `g++` ou `clang`

### Instalando as Ferramentas

#### Windows

1. **CMake**: Baixe e instale o executável do CMake a partir do link acima e adicione-o ao PATH.
2. **Compilador**: Instale o Visual Studio com as workloads para C++ ou MinGW e adicione-o ao PATH.

#### Linux

1. Instale o CMake e um compilador compatível (como `g++` ou `clang`) usando o gerenciador de pacotes:
    ```bash
    sudo apt update
    sudo apt install cmake g++
    ```
    ou, para usar o `clang` como compilador:
    ```bash
    sudo apt install cmake clang
    ```

---

## Compilando o Projeto

Uma vez que as ferramentas estejam instaladas, siga as instruções abaixo para compilar o projeto.

### Passo 1: Clone o Repositório

Primeiro, clone este repositório para sua máquina:
```bash
git clone https://github.com/usuario/nome-do-repositorio.git
cd nome-do-repositorio
```

### Passo 2: Crie o Diretório de Build

No diretório do projeto, crie um diretório para armazenar os arquivos de build:
```bash
mkdir build
cd build
```

### Passo 3: Configure o Build com o CMake

#### Windows

Para compilar no Windows, use o CMake para gerar o sistema de build para Visual Studio ou MinGW. No diretório `build`, execute:

**Visual Studio**:
```bash
cmake .. -G "Visual Studio 16 2019"  # ou substitua pela versão instalada
```

**MinGW**:
```bash
cmake .. -G "MinGW Makefiles"
```

#### Linux

No Linux, configure o CMake com o seguinte comando:
```bash
cmake ..
```

### Passo 4: Compile o Projeto

Após configurar o CMake, compile o projeto.

#### Windows

**Visual Studio**:
Abra o arquivo `.sln` gerado no Visual Studio e selecione "Build Solution" (Compilar Solução).

**MinGW**:
Se estiver usando o MinGW, compile com:
```bash
mingw32-make
```

#### Linux

No Linux, use o `make` para compilar o projeto:
```bash
make
```

---

## Executando o Projeto

Após a compilação, o executável será gerado no diretório `build`. Para executar o projeto, use:

```bash
./nome-do-executavel  # Linux
nome-do-executavel.exe  # Windows
```

---

## Dicas para Resolução de Problemas

- Certifique-se de que todas as ferramentas (CMake, compilador) estejam no PATH do sistema.
- Verifique se as versões do CMake e do compilador são compatíveis com o projeto.
- No Windows, se você estiver usando o Visual Studio, lembre-se de abrir o terminal "Developer Command Prompt" para garantir que os comandos do compilador estejam disponíveis.
