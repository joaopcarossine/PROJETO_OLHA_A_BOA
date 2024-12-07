# Projeto “Olha a Boa” - Jogo de Bingo em C++  

## Descrição  
O projeto **"Olha a Boa"** é uma implementação de um jogo de Bingo em C++ utilizando o compilador MinGW, proposto pelo professor [Orlando Saraiva Júnior](https://github.com/orlandosaraivajr/FATEC_2024_2SEM_ED), na matéria de Estrutura de Dados. O Bingo é um jogo tradicional onde os jogadores marcam números em uma cartela conforme são sorteados. O objetivo é preencher uma linha, coluna ou um padrão específico antes dos outros jogadores e anunciar "Bingo!" para sinalizar a vitória.  

## Funcionalidades  
- **Geração automática de cartelas**: As cartelas são geradas com números únicos e aleatórios.  
- **Sorteio aleatório de números**: Números entre 1 e 75 são sorteados sem repetições.  
- **Marcação de números**: Permite ao jogador marcar números na cartela.  
- **Verificação de vitória**: O sistema verifica automaticamente se houve vitória por linha, coluna ou cartela completa.  
- **Histórico de números chamados**: Exibe todos os números que já foram sorteados.  
- **Interface de menu interativo**: O usuário navega por opções de menu para jogar.


## Requisitos  
- **Compilador**: MinGW (GCC para Windows).  
- Acesse [https://osdn.net/projects/mingw/](https://osdn.net/projects/mingw/) e baixe o instalador (`mingw-get-setup.exe`)
- **Instale e selecione esses pacotes:** 
   - **mingw32-gcc-g++**
   - **mingw32-base** 
- **Editar variáveis de ambiente:**
   - Acesse Editar as variáveis de ambiente do sistema;
   - Encontre `Path` e clique em "Editar".
   - Adicione o caminho da pasta `bin` do MinGW à lista e clique em "OK", normalmente `C:\MinGW\bin`.

- **Testar MinGW:**
   - Acesse o terminal e utilize o comando g++ --version

- **Após a instalação do MinGW, fazer download dos arquivos do GitHub e rodar o arquivo .cpp.**
