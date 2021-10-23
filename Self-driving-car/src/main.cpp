// AUTHOR: Juan García Santos
// DATE: 04/10/2021
// EMAIL: alu0101325583@ull.edu.es
// VERSION: 4.0
// SUBJECT: AI
// PRACTICE Nº: 1
// Compilation: make
// Execution: ./simulation
// Este programa simula el comportamiento del taxi autonomo en un formto de texto.
// chcp.com 65001 arregla el encoding

#include "include/world.h"

int main( void ) {
    int row, col, vehicle_row, vehicle_col, menu, vehicle_type;
    int destination_row, destination_col, obstacle_percentage, obstacle_type = -1, heuristic_type = -1;
    long t0,t1;

    std::cout << "¿Desea el comportamiento personalizado(0), o evaluación expermiental (1)?\n";
    std::cout << "Introduzca 0 o 1: ";
    std::cin >> menu;
    while ((menu != 0) && (menu != 1)) {
        std::cout << "¡Eso no era un 1 o un 0! Ojito cuidado. " << std::endl << "Introduzca 0 o 1: ";
        std::cin >> menu;
    }

    std::cout << "Introduzca el Ancho: ";
    std::cin >> row;
    while (row <= 0) {
        std::cout << "Eso era menor que 0. Ojito Cuidado" << std::endl;
        std::cout << "Introduzca el Ancho: " << std:: endl;
        std::cin >> row;
    }

    std::cout << "Introduzca el Largo: ";
    std::cin >> col;
    while (col <= 0) {
        std::cout << "Eso era menor que 0. Ojito Cuidado" << std::endl;
        std::cout << "Introduzca el Largo: " << std:: endl;
        std::cin >> col;
    }

    World world(row, col);

    std::cout << "¿Desea generacion automatica de obstaculos (0), introducirlos manualmente(1) o por fichero(2)?\n";
    std::cout << "Introduzca 0, 1 o 2: ";
    std::cin >> obstacle_type;
    while ((obstacle_type != 0) && (obstacle_type != 1) && (obstacle_type != 2)) {
        std::cout << "¡Eso no era un 1 o un 0! Ojito cuidado. " << std::endl << "Introduzca 0, 1 o 2: ";
        std::cin >> obstacle_type;
    }

    world.Obstacle(obstacle_percentage, obstacle_type);


    std::cout << "Introduzca la coordenada X del taxi: ";
    std::cin >> vehicle_row;
    while ((vehicle_row < 0) || (vehicle_row > row-1)) {
        std::cout << "Esa coordenada X no está dentro del mundo previamente definido. Ojito Cuidado" << std::endl;
        std::cout << "Introduzca una coordenada entre " << 0 << " y " << row-1 << std:: endl;
        std::cin >> vehicle_row;
    }

    std::cout << "Introduzca la coordenada Y del taxi: ";
    std::cin >> vehicle_col;
    while ((vehicle_col < 0) || (vehicle_col > col-1)) {
        std::cout << "Esa coordenada Y no está dentro del mundo previamente definido. Ojito Cuidado" << std::endl;
        std::cout << "Introduzca una coordenada entre " << 0 << " y " << col-1 << std:: endl;
        std::cin >> vehicle_col;
    }

    do {
        std::cout << "Introduzca la coordenada X de destino: ";
        std::cin >> destination_row;
        while ((destination_row < 0) || (destination_row >= row)) {
            std::cout << "Esa coordenada X no está dentro del mundo previamente definido. Ojito Cuidado" << std::endl;
            std::cout << "Introduzca una coordenada entre " << 0 << " y " << row << std:: endl;
        std::cin >> destination_row;
        }

        std::cout << "Introduzca la coordenada Y de destino: ";
        std::cin >> destination_col;
        while ((destination_col < 0) || (destination_col >=  col)) {
            std::cout << "Esa coordenada Y no está dentro del mundo previamente definido. Ojito Cuidado" << std::endl;
            std::cout << "Introduzca una coordenada entre " << 0 << " y " << col-1 << std:: endl;
            std::cin >> destination_col;
        }
        
    } while ((world.GetWorldState(destination_row, destination_col)) == 1);
    

    world.SetVehicle(vehicle_row, vehicle_col, destination_row, destination_col);

    std::cout << "¿Desea emplear una función heurística Manhattan (0), Euclídea (1) o  tchebysev(2)?\n";
    std::cout << "Introduzca 0, 1 o 2: ";
    std::cin >> heuristic_type;
    while ((heuristic_type != 0) && (heuristic_type != 1) && (heuristic_type != 2)) {
        std::cout << "¡Eso no era un 1 o un 0! Ojito cuidado. " << std::endl << "Introduzca 0, 1 o 2: ";
        std::cin >> heuristic_type;
    }

/*     switch(heuristic_type) {
        case 0:
            f_heuristica* h = new d_manhattan;
        break;
        case 1:
            f_heuristica* h = new d_euclidea;
        break;
        case 2:
            f_heuristica* h = new d_tchebysev;
        break;
    } */
    
    world.PrintWorld(); //Mundo inicial

    f_heuristica* h1 = new d_euclidea;
    t0 = clock();
    if(world.Astar(h1, true))std::cout<<"Solucion"<<std::endl; //true hace 8 false 4 direcciones
    t1 = clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    std::cout<<"Tiempo de ejecución = "<< time <<std::endl;
    world.PrintWorld();

    f_heuristica* h2 = new d_manhattan;
    if(world.Astar(h2, false)) std::cout<<"Solucion"<<std::endl;
    world.PrintWorld();


    f_heuristica* h3 = new d_tchebysev;
    if(world.Astar(h3, false)) std::cout<<"Solucion"<<std::endl;
    world.PrintWorld();

return 0;
}
