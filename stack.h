#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

//Rokas Rickus, 4 grupe; studento pazymejimo nr.: 1712219

/* Norint steke laikyti kito tipo duomenis, int reikia pakeisti i:
   typedef double/float/char Type*/
typedef int Type;
typedef struct Stekas_t Stekas;

/* Sukuriamas tuscias stekas. Funkcija grazina
 nuoroda i Stekas tipo objekta (struktura) jei pavyko sukurti steka.
 Jei nepavyko, grazina NULL.
 Pvz:
 Stekas* s1 = createStack();
 @return nuoroda i Stekas tipo struktura (klaidos atveju - NULL).*/
Stekas* createStack();

/* Tikrina ar stekas tuscias.
 @param steko nuoroda i Stekas tipo struktura.
 @return 1 - jei stekas tuscias, 0 - jei nera tuscias.*/
int isStackEmpty(Stekas* stekas);

/* Funkcija ipushina elementa i steka.
 Funkcijai turi buti perduota jau
 sukurto steko nuoroda bei elementas, kuri norima ipushinti.
 Pvz: norint ipushinti skaiciu 2:
 push(s1, 2);
 @param stekas nuoroda i Stekas tipo struktura;
 @param i steka idedami duomenys;
 @return 1 - jei pavyko ipushinti (stekas nera pilnas), 0 - jei nepavyko.*/
int push(Stekas* stekas, Type data);

/* Funkcija ispopina elementa is steko.
 @param stekas nuoroda i Stekas tipo struktura.
 @param data adresas i kintamaji, kuriame bus issaugota popinama reiksme.
 Perdavus NULL, reiksme neissaugoma ir elementas
 istrinamas (atlaisvinama elemento naudojama atmintis).
 @return 0 - jei stekas buvo tuscias, 1 - kitu atveju (elementas ispopintas).*/
int pop(Stekas* stekas, Type* data);

/* @param stekas nuoroda i Stekas tipo struktura.
   @return 1 - jei stekas pilnas, 0 - jei nepilnas.*/
int isStackFull(Stekas* stekas);

/*Sunaikina steka (atlaisvina atminti).
  @param stekas nuoroda i Stekas tipo struktura.*/
void destroyStack(Stekas* stekas);

#endif // STACK_H_INCLUDED
