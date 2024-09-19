 // Universidad de La Laguna
 // Escuela Superior de Ingeniería y Tecnología
 // Grado en Ingeniería Informática
 // Asignatura: Computabilidad y Algoritmia
 // Curso: 2º
 // Práctica 2: Cadenas y lenguajes
 // Autor: Marco Aguiar Álvarez
 // Correo: alu0101620961@ull.edu.es
 // Fecha: 19/09/2024
 // Archivo tools.h: programa de herramientas.
 // Contiene la declaracion de las funciones herramienta contenidas en el programa
 // para indicar al usuario el correcto funcionamiento del codigo
 // Historial de revisiones
 // 17/09/2024- Creación (primera versión) del código


/** @Brief: Funcion que explica al usuario que funcionalidad tiene el programa, y en caso de recibir la cadena
    "--help" indicara por pantalla una breve descripcion sobre como usar el programa
    @Param argc: numero de argumentos pasados por linea de comandos
           argv: vector que contiene los argumentos pasados por linea de comando

 */
#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>
#include <fstream>
#include <string>

 void Usage(int argc, char* argv[]);
 void ErrorMesagge(char* argv[]);
 void CheckFiles(char* argv[]);
 void CheckHelp( char* argv[]);
 void CheckOpcode(char* argv[]);




#endif