/*
* Filename: analyzer.h
* Created on: May  9, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*
* Analyzer é responsável por realizar uma bateria de testes a fim de avaliar o desempenho
* do resolvedor de expressão numérica
*/

#ifndef ANALYZER_H_
#define ANALYZER_H_

#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <random>

#include "expression_tree_calculator.h"

#define ROUNDS 5 // Número de testes com uma mesma expressão
#define EXPRESSIONS_AMOUNT 100 // Quantidade de expressões que são analisadas
#define TOKENS_MAX_AMOUNT 100000 // Tamanho máximo de uma expressão
#define EXPRESSIONS_TEST_AMOUNT TOKENS_MAX_AMOUNT/EXPRESSIONS_AMOUNT // Define o quanto a quantidade de tokens em uma expressão varia em cada teste
#define SIN_CICLES 1000000 // Quantidade de senos calculados para que o tempo das análises fique em segundos

class Analyzer
{
    private:
        double _time[EXPRESSIONS_AMOUNT][ROUNDS];
        double _timeAverage[EXPRESSIONS_AMOUNT][2];

    public:
        /**
         * @brief Função de carga, ou seja, ela é utilizada para aumentar o tempo de execução de outras
         *        funções, de forma que esse tempo esteja próximo de segundos
         */
        void DummyTime();

        /**
         * @brief Responsável pela avaliação do tempo de execução da classe ExpressionTreeCalculator
         *        com relação ao tamanho da expressão
         */
        void ExpressionTreeCalculatorAnalysis();

        /**
         * @brief Gera um número pseudo-aleatório do tipo double
         * @param max O número gerado deve estar no intervalo que vai de 0 até max
         */
        double_t RandomNumber(double_t max);

        /**
         * @brief Gera um dos quatro operadores aritméticos
         */
        char RandomOperator();

        /**
         * @brief Calcula a média dos tempos armazenados no atributo _time
         */
        void TimeAverage();

        /**
         * @brief Gera um gráfico de linha com os dados de avaliação armazenados nos atributos desta
         *        classe
         */
        void PlotAnalysis();

        /**
         * @brief Gera uma expressão infixa
         * @param lenght Tamanho da expressão dado pela quantidade de operadores + operandos
         */
        std::string ExpressionGenerator(uint32_t lenght);
};

#endif // ANALYZER_H_
