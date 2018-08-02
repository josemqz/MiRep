#include "Funciones.c"

typedef int tElemPoli;

tPoli* BobLink();

void Next(tPoli *P);

void Prev(tPoli* P);

void Insert(tPoli* P, tElemPoli c, tElemPoli e);

void Clear(tPoli* P);

void RalphLink(tPoli* P);

unsigned int CurrPos(tPoli* P);

int Length(tPoli* P);

int GetExpo(tPoli* P);

int GetCoef(tPoli* P);

void MoveToStart(tPoli *P);

void MoveToEnd(tPoli* P);


int verify (FILE *a, const char *b);

int Coeficiente(tPoli** PAUL,int M, int p, int e);

int Evaluar(tPoli** PAUL, int M, int p, int X, FILE* in, FILE* out);
