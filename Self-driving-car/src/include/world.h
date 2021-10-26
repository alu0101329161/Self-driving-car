// AUTHOR: Juan García Santos
// DATE: 04/10/2021
// EMAIL: alu0101325583@ull.edu.es
// VERSION: 4.0
// SUBJECT: AI
// PRACTICE Nº: 1
// Compilation: make
// Execution: ./simulation
// Clase "mundo" para definir el comportamiento y características del entorno del vehiculo

#include  "f_heuristicas.h"
#include  "termcolor.h"

#include <vector>
#include <list>
#include <fstream>
#include <iostream>
#include <random>


// O libre, 1 obstaculos, 2 camino, 3 start, 4 end
#pragma once

class World {

private:

    int row; // Filas del mundo
    int col; // Columnas de mundo
    std::vector<std::vector<Cell>> world; // Vector donde se almacena el mundo
    std::pair<int, int> star_; // Posicion de inicio
    std::pair<int, int> end_; // Posicion de fin

public:

    World(int, int); //Constructor del mundo

    void Obstacle(int, int);
    void SetVehicle(int, int, int , int);
    int  GetWorldState(int, int);
    void SetWorldState(int, int, int);
    void SetWorld(std::vector<std::vector<Cell>>&);

    void PrintWorld(void);
    bool Astar(f_heuristica*, bool direction);
    void RebuildPath();
    void CreateSons(int, int, bool);

    int GetRow() {
        return row;
    } 

    int GetColumn() {
        return col;
    } 

};
