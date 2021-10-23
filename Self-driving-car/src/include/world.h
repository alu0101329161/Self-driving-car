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
#include <time.h>


// O libre, 1 obstaculos, 2 camino, 3 start, 4 end
#pragma once

class World {

private:

    int row;
    int col;
    std::vector<std::vector<Cell>> world;
    std::pair<int, int> star_;
    std::pair<int, int> end_;

public:

    World(int, int); //Constructor por tamaño

    int GetRow() {
        return row;
    } 

    int GetColumn() {
        return col;
    } 

    Cell& GetCell(int i, int j) {
        return world[i][j];   
    }

    void Obstacle(int, int);
    void SetVehicle(int, int, int , int);
    int GetWorldState(int, int); //devuelve el "color" de una celda
    void SetWorldState(int, int, int); //establecer el color de una celda
    void SetWorld(std::vector<std::vector<Cell>>&);

    void PrintWorld(void); //imprime la malla sola

    bool Astar(f_heuristica*, bool direction);
    void ReconstruirCamino();
    void CreateSons(int, int, bool);

};
