#!/bin/bash

# Executa o comando make
echo "Executando o comando make..."
make
echo "Rodando..."
time ./eqd.out

# Acessa a pasta 'plt'
echo "Entrando na pasta 'plt'..."
cd plt 

# Executa o script gnuplot
echo "Executando o script gnuplot 'sir.plt'..."
gnuplot sir.plt

echo "Script executado com sucesso!"
