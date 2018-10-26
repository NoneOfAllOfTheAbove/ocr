#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

double* CreateArray(size_t);
void PrintGlobalValues();

void Start(size_t, size_t, size_t);
double* Predict(double[]);
void Train(double[], double[]);

void Save(char*);
void Load(char*);

#endif