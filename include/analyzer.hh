#ifndef ANALYZER_H_
#define ANALYZER_H_

#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <random>

#include "expression_tree_calculator.hh"

#define ROUNDS 5 // Número de testes com uma mesma expressão
#define EXPRESSIONS_AMOUNT 100 // Quantidade de expressões que são analisadas
#define TOKENS_MAX_AMOUNT 1000 // Tamanho máximo de uma expressão
#define EXPRESSIONS_TEST_AMOUNT TOKENS_MAX_AMOUNT/EXPRESSIONS_AMOUNT // Define a quantidade de testes
#define SIN_CICLES 10000000 // Quantidade de senos calculados para que o tempo das analises fique em segundos

class Analyzer {
    private:
        double _time[EXPRESSIONS_AMOUNT][ROUNDS];
        double _timeAverage[EXPRESSIONS_AMOUNT][2];

    public:
        /**
        @brief Função de carga, ou seja, ela é utilizada para aumentar o tempo de execução de outras
        funções, de forma que esse tempo esteja próximo de segundos
        */
        void dummyTime();

        /**
        @brief Responsável pela avaliação do tempo de execução da classe expressionTreeCalculator
        com relação ao tamanho da expressão
        */
        void expressionTreeCalculator_analysis();

        /**
        @brief Gera um número pseudo-aleatório do tipo double
        @param max O número gerado deve estar no intervalo que vai de 0 até max
        */
        double randomNumber(float max);

        /**
        @brief Gera um dos quatro operadores aritméticos
        */
        char randomOperator();

        /**
        @brief Calcula a média dos tempos armazenados no atributo _time
        */
        void timeAverage();

        /**
        @brief Gera um gráfico de linha com os dados de avaliação armazenados nos atributos desta
        classe
        */
        void plotAnalysis();

        /**
        @brief Gera uma expressão infixa
        @param lenght Tamanho da expressão dado pela quantidade de operadores + operandos
        */
        std::string expressionGenerator(unsigned int lenght);
};

#endif // ANALYZER_H_
