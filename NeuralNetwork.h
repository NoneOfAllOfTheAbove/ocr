void Start(size_t inputNodes, size_t hiddenNodes, size_t outputNodes);

double** ConstructMatrix(size_t line, size_t column);

double* ConstructArray(size_t size);

void PrintGlobalValues();

double* Predict(double input[]);

//double* MultArrayMatrix(double arrayInput[], double matrixWeight[][]);
