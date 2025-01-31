#ifndef KEYBOARDELM_H
#define KEYBOARDELM_H

//Funções de configuração do teclado matricial
void InitKeyboard(const int*, const int*);
const char (*KeyMap())[];
char ReadMap(const char (*)[], const int*, const int*);

#endif