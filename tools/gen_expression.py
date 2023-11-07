#!/usr/bin/env python3

# Filename: gen_expression.py
# Created on: May  9, 2023
# Author: Lucas Araújo <araujolucas@dcc.ufmg.br>

import random
import argparse

# Usage: python3 gen_expression.py -n <size> 
# <size> é a quantidade de tokens que a expressão gerada deve ter

parser = argparse.ArgumentParser(description='Gera uma expressão matemática com soma e subtração.')
parser.add_argument('-n', type=int, help='Tamanho da expressão')
args = parser.parse_args()

expr_size = args.n

expr = ""
count = 0

while count < expr_size:
    num = random.randint(-99, 99)

    if count == 0:
        expr += str(num)

    else:
        op = random.choice(['+', '-'])
        expr += f" {op} {num}"

    count += 1;

print(expr)
