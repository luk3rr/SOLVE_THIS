/*
* Filename: analyzer.cc
* Created on: May  9, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#include "analyzer.h"
#include <cmath>
#include <cstddef>
#include <cstdint>

double_t Analyzer::RandomNumber(double_t max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution dis(0.5, max);

    return dis(gen);
}

char Analyzer::RandomOperator()
{
    int num = RandomNumber(2);

    if (num == 1) return '+';
    return '-';
}

std::string Analyzer::ExpressionGenerator(uint32_t lenght) {
    std::string expression;

    for (std::size_t i = 0; i < lenght / 2; i++)
        expression += " " + std::to_string(RandomNumber(10)) + " " + RandomOperator();

    expression += " " + std::to_string(RandomNumber(100));
    return expression;
}

void Analyzer::DummyTime()
{
    volatile int __attribute__((unused)) dummy;
    for (uint32_t i = 0; i < SIN_CICLES; i++)
        dummy = sin(1);
}

void Analyzer::ExpressionTreeCalculatorAnalysis()
{
    std::cout << "Iniciando testes da classe expressionTreeCalculator... take a coffee :)" << std::endl;
    ExpressionTreeCalculator calc;

    for (std::size_t i = 0; i <= EXPRESSIONS_AMOUNT; i++)
    {
        // Expressões com i * 50 tokens.
        std::string expression = this->ExpressionGenerator((i + 1) * EXPRESSIONS_TEST_AMOUNT);

        for (std::size_t j = 0; j < ROUNDS; j++)
        {
            auto start = std::chrono::high_resolution_clock::now();

            this->DummyTime();
            calc.StoreExpression(expression);
            this->DummyTime();
            calc.Infix();
            this->DummyTime();
            calc.Postfix();
            this->DummyTime();
            calc.Evaluation();
            this->DummyTime();

            auto end = std::chrono::high_resolution_clock::now();
            auto time = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
            this->_time[i][j] = time.count(); // Tempo em segundos
        }
    }

    this->PlotAnalysis();
}

void Analyzer::TimeAverage()
{
    std::cout << "Calculando tempos médios de execução..." << std::endl;

    for (std::size_t i = 0; i < EXPRESSIONS_AMOUNT; i++)
    {
        double_t average = 0;
        for (std::size_t j = 0; j < ROUNDS; j++)
        {
            average += this->_time[i][j];
        }

        this->_timeAverage[i][0] = (i + 1) * EXPRESSIONS_TEST_AMOUNT;
        this->_timeAverage[i][1] = average / ROUNDS;
    }
}

void Analyzer::PlotAnalysis()
{
    this->TimeAverage();

    std::ofstream data("data.dat");
    std::cout << "Organizando dados..." << std::endl;

    for (std::size_t i = 0; i < EXPRESSIONS_AMOUNT; i++)
    {
        for (std::size_t j = 0; j < 2; j++)
        {
            data << this->_timeAverage[i][j] << " ";
        }

        data << std::endl;
    }

    data.close();

    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");

    if (gnuplotPipe)
    {
        fprintf(gnuplotPipe, "set title 'expressionTreeCalculator'\n");
        fprintf(gnuplotPipe, "set xlabel 'Tamanho da entrada'\n");
        fprintf(gnuplotPipe, "set ylabel 'Tempo de execução (s)'\n");
        fprintf(gnuplotPipe, "set terminal png\n");
        fprintf(gnuplotPipe, "set output 'grafico.png'\n");
        fprintf(gnuplotPipe, "plot 'data.dat' with lines\n");
        fflush(gnuplotPipe);
        pclose(gnuplotPipe);

        std::cout << "Gráfico gerado" << std::endl;
    }
    else
    {
        std::cerr << "ERRO ao executar o gnuplot" << std::endl;
    }
}
