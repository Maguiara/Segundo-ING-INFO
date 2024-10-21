// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 6: Diseño e implementación de un simulador de autómatas finitos
// Autor: Daniel Martínez Sopo
// Correo: alu0101675893@ull.edu.es
// Fecha: 19/10/2024
// Archivo tools.h: Contiene declaraciones de funciones utilizadas en el programa.
// Historial de revisiones
// 19/10/2024 - Creación (primera versión) del código
#include <iostream>
#include <fstream>

void Usage(int argc, char* argv[]);
void CheckHelp(char* argv[]);
void CheckFiles(char* argv[]);
void ArgFail(char* argv[]);
void Help();
