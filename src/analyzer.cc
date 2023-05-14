#include "analyzer.hh"

double Analyzer::randomNumber(float max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.5, max);

    return dis(gen);
}

char Analyzer::randomOperator() {
    int num = randomNumber(2);
    if (num == 1)
        return '+';
    return '-';
}

std::string Analyzer::expressionGenerator(unsigned int lenght) {
    std::string expression;

    for (unsigned int i = 0; i < lenght / 2; i++)
        expression += " " + std::to_string(randomNumber(10)) + " " + randomOperator();

    expression += " " + std::to_string(randomNumber(100));
    return expression;
}

void Analyzer::dummyTime() {
    volatile int __attribute__((unused)) dummy;
    for (int i = 0; i < SIN_CICLES; i++)
        dummy = sin(1);
}

void Analyzer::expressionTreeCalculator_analysis() {
    std::cout << "Iniciando testes da classe expressionTreeCalculator... take a coffee :)" << std::endl;
    ExpressionTreeCalculator calc;
    for (int i = 0; i <= EXPRESSIONS_AMOUNT; i++) {
        // Expressões com i * 50 tokens.
        std::string expression = this->expressionGenerator((i + 1) * EXPRESSIONS_TEST_AMOUNT);

        for (int j = 0; j < ROUNDS; j++) {
            auto start = std::chrono::high_resolution_clock::now();

            this->dummyTime();
            calc.storeExpression(expression);
            this->dummyTime();
            calc.infix();
            this->dummyTime();
            calc.postfix();
            this->dummyTime();
            calc.evaluation();
            this->dummyTime();

            auto end = std::chrono::high_resolution_clock::now();
            auto time = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
            this->_time[i][j] = time.count(); // Tempo em segundos
        }
    }
    this->plotAnalysis();
}

void Analyzer::timeAverage() {
    std::cout << "Calculando tempos médios de execução..." << std::endl;
    for (int i = 0; i < EXPRESSIONS_AMOUNT; i++) {
        double average = 0;
        for (int j = 0; j < ROUNDS; j++) {
            average += this->_time[i][j];
        }
        this->_timeAverage[i][0] = (i + 1) * EXPRESSIONS_TEST_AMOUNT;
        this->_timeAverage[i][1] = average / ROUNDS;
    }
}

void Analyzer::plotAnalysis() {
    this->timeAverage();
    std::ofstream data("data.dat");
    std::cout << "Organizando dados..." << std::endl;
    for (int i = 0; i < EXPRESSIONS_AMOUNT; i++) {
        for (int j = 0; j < 2; j++) {
            data << this->_timeAverage[i][j] << " ";
        }
        data << std::endl;
    }
    data.close();

    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
    if (gnuplotPipe) {
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
    else {
        std::cerr << "ERRO ao executar o gnuplot" << std::endl;
    }
}
