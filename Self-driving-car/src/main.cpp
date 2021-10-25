// AUTHOR: Joseph Gabino Rodríguez
// DATE: 24/10/2021
// EMAIL: alu0101329161@ull.edu.es
// VERSION: 1.0
// SUBJECT: AI
// PRACTICE Nº: 1
// Compilation: make
// Execution: ./simulation
// Este programa simula el comportamiento del taxi autonomo en un formto de texto.
// chcp.com 65001 arregla el encoding

#include "include/world.h"
#include <chrono>

int main( void ) {
    int row, col, vehicle_row, vehicle_col, menu, vehicle_type;
    int destination_row, destination_col, obstacle_percentage = 0, obstacle_type = -1, heuristic_type = -1;
    bool direction = true; //false = 4 true = 8
    using Time = std::chrono::high_resolution_clock;

    std::cout << "¿Desea el comportamiento personalizado(0), o evaluacion expermiental (1)?\n";
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

    if(obstacle_type == 0 || obstacle_type == 1) {
        std::cout << "Introduzca el porcentaje de obstaculos (entre 0 y 100): " << std:: endl;
        std::cin >> obstacle_percentage;
        while ((obstacle_percentage < 0) || (obstacle_percentage > 100)) {
            std::cout << "Eso no estaba entre 0 y 100. Ojito Cuidado" << std::endl;
            std::cout << "Introduzca el numero de obstaculos (entre 0 y 100): " << std:: endl;
            std::cin >> obstacle_percentage;
        }
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
            std::cout << "Introduzca una coordenada entre " << 0 << " y " << col << std:: endl;
            std::cin >> destination_col;
        }
        
    } while ((world.GetWorldState(destination_row, destination_col)) == 1);
    

    world.SetVehicle(vehicle_row, vehicle_col, destination_row, destination_col);

    if(menu == 0){

        std::cout << "¿Coche de 8 o 4 direcciones?: ";
        std::cin >> vehicle_type;
        while ((vehicle_type != 8) && (vehicle_type != 4)) {
            std::cout << "Elige entre 8 y 4:" << std::endl;
            std::cin >> vehicle_type;
        }
        if (vehicle_type == 4) direction = false; // se establece si el coche emplea 4 u 8 direcciones

        std::cout << "¿Desea emplear una funcion heuristica Manhattan (0), Euclidea (1) o  tchebysev(2)?\n";
        std::cout << "Introduzca 0, 1 o 2: ";
        std::cin >> heuristic_type;
        while ((heuristic_type != 0) && (heuristic_type != 1) && (heuristic_type != 2)) {
            std::cout << "¡Eso no era un 1 o un 0! Ojito cuidado. " << std::endl << "Introduzca 0, 1 o 2: ";
            std::cin >> heuristic_type;
        }
        f_heuristica* h;

        if(heuristic_type == 0) 
            h = new d_manhattan;
        else if (heuristic_type == 1) 
            h = new d_euclidea;
        else
            h = new d_tchebysev;

        std::cout << "\nMundo inicial: \n";
        world.PrintWorld(); //Mundo inicial

        auto start_time = Time::now(); //inicia el crono
        if(world.Astar(h , direction))std::cout<<"\n!!Solucion Encontrada||\n"<<std::endl; //true hace 8 false 4 direcciones
        else std::cout << "!!Solucion No Encontrada||" << std::endl;
        
        auto elapsed = Time::now() - start_time;
        long long end_time = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count(); // acaba el chrono

        world.PrintWorld();
        std::cout<<"Tiempo de ejecucion en nanosegundos = "<< end_time << std::endl;        
    }

    else if( menu == 1) {
        std::cout << "\nMundo inicial: \n";
        world.PrintWorld(); //Mundo inicial
        // algoritmo usando 4 direcciones
        std::string minimo;
        
        f_heuristica* h1 = new d_manhattan;
            std::cout << "\nMundo resuelto con heuristica Manhattan y 4 direcciones: \n";

            auto start_time_manhattan_4 = Time::now(); //inicia el crono
            if(world.Astar(h1 , false))std::cout << "!!Solucion Encontrada||" << std::endl; //true hace 8 false 4 direcciones
            else std::cout << "!!Solucion No Encontrada||" << std::endl;

            auto elapsed_manhattan_4 = Time::now()- start_time_manhattan_4;
            long long end_time_manhattan_4 = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_manhattan_4).count(); // acaba el chrono

            world.PrintWorld();
            std::cout<<"Tiempo de ejecucion en ms = "<< end_time_manhattan_4 << std::endl;  
            

        f_heuristica* h2 = new d_euclidea;
            std::cout << "\nMundo resuelto con heuristica Euclidea y 4 direcciones: \n";

            auto start_time_euclidea_4 = Time::now(); //inicia el crono
            if(world.Astar(h2, false)) std::cout << "!!Solucion Encontrada||" << std::endl;
            else std::cout << "!!Solucion No Encontrada||" << std::endl;

            auto elapsed_euclidea_4 = Time::now()- start_time_euclidea_4;
            long long end_time_euclidea_4 = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_euclidea_4).count(); // acaba el chrono

            world.PrintWorld();
            std::cout<<"Tiempo de ejecucion en ms = "<< end_time_euclidea_4 << std::endl;

        f_heuristica* h3 = new d_tchebysev;
            std::cout << "\nMundo resuelto con heuristica Tchebysev y 4 direcciones: \n";

            auto start_time_tchebysev_4 = Time::now(); //inicia el crono
            if(world.Astar(h3, false)) std::cout << "!!Solucion Encontrada||" << std::endl;
            else std::cout << "!!Solucion No Encontrada||" << std::endl;

            auto elapsed_tchebysev_4 = Time::now()- start_time_tchebysev_4;
            long long end_time_tchebysev_4 = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_tchebysev_4).count(); // acaba el chrono

            world.PrintWorld();
            std::cout<<"Tiempo de ejecucion en ms = "<< end_time_tchebysev_4 << std::endl;
    

            //algoritmo usando 8 direcciones

            f_heuristica* h4 = new d_manhattan;
            std::cout << "\nMundo resuelto con heuristica Manhattan y 8 direcciones: \n";

            auto start_time_manhattan_8 = Time::now(); //inicia el crono
            if(world.Astar(h4 , true))std::cout << "!!Solucion Encontrada||" << std::endl; //true hace 8 false 4 direcciones
            else std::cout << "!!Solucion No Encontrada||" << std::endl;

            auto elapsed_manhattan_8 = Time::now()- start_time_manhattan_8;
            long long end_time_manhattan_8 = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_manhattan_8).count(); // acaba el chrono

            world.PrintWorld();
            std::cout<<"Tiempo de ejecucion en ms = "<< end_time_manhattan_8 << std::endl;  
            

        f_heuristica* h5 = new d_euclidea;
            std::cout << "\nMundo resuelto con heuristica Euclidea y 8 direcciones: \n";

            auto start_time_euclidea_8 = Time::now(); //inicia el crono
            if(world.Astar(h5, true)) std::cout << "!!Solucion Encontrada||" << std::endl;
            else std::cout << "!!Solucion No Encontrada||" << std::endl;

            auto elapsed_euclidea_8 = Time::now()- start_time_euclidea_8;
            long long end_time_euclidea_8 = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_euclidea_8).count(); // acaba el chrono

            world.PrintWorld();
            std::cout<<"Tiempo de ejecucion en ms = "<< end_time_euclidea_8 << std::endl;

        f_heuristica* h6 = new d_tchebysev;
            std::cout << "\nMundo resuelto con heuristica Tchebysev y 8 direcciones: \n";

            auto start_time_tchebysev_8 = Time::now(); //inicia el crono
            if(world.Astar(h6, true)) std::cout << "!!Solucion Encontrada||" << std::endl;
            else std::cout << "!!Solucion No Encontrada||" << std::endl;

            auto elapsed_tchebysev_8 = Time::now()- start_time_tchebysev_8;
            long long end_time_tchebysev_8 = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_tchebysev_8).count(); // acaba el chrono

            world.PrintWorld();
            std::cout<<"Tiempo de ejecucion en ms = "<< end_time_tchebysev_8 << std::endl;
    }

return 0;
}
