// AUTHOR: Juan García Santos
// DATE: 04/10/2021
// EMAIL: alu0101325583@ull.edu.es
// VERSION: 4.0
// SUBJECT: AI
// PRACTICE Nº: 1
// Compilation: make
// Execution: ./simulation
// Pequeño struct para representar las celdas

#pragma once
#include <vector>

class Cell {
    
    private:

    int state;
    bool open = false, close = false;

    int x; //coordenada x
    int y; //cordenada y

    double f_; // Coste estimado desde nodo inicial a nodo objetivo (g(n) + h(n))
    double h_; // Coste estimado desde este nodo al nodo objetivo
    double g_; // Coste desde el nodo inicial a este nodo

    std::pair<int, int> dad_{-1, -1};
    std::vector<std::pair<int,int>> sons_;

    public:

    std::pair<int, int>& GetDad(){
        return dad_;
    }

    std::pair<int, int>& GetSons(int i){
        return sons_[i];
    }

    int GetSonsSize() {
        return sons_.size();
    }

    void SetDad(int i, int j) {
        dad_.first = i;
        dad_.second = j;
    }

    void SetSons(int i, int j) {
        sons_.push_back(std::make_pair(i, j));
    }

    void CleanSons() {
        sons_.clear();
    }

    int GetState() const {
        return state;
    }

    int GetState() {
        return state;
    }

    int GetX() const {
        return x;
    }

    int GetY() const {
        return y;
    }

    int GetX() {
        return x;
    }

    int GetY() {
        return y;
    }

    void SetState(int new_state) {
        state = new_state;
    }

    void SetX(int x_) {
        x = x_;
    }
    void SetY(int y_) {
        y = y_;
    }
    
    void SetG(double i) {
        g_ = i;
    }

    void SetH(double i) {
        h_ = i;
    }

    void SetF(double i) {
        f_ = i;
    }

    double GetG() {
        return g_;
    }

    double GetH() {
        return h_;
    }

    double GetF() {
        return f_;
    }

    void SetOpen(bool i) {
        open = i;
    }

    void SetClose(bool i) {
        close = i;
    }

    bool GetOpen() {
        return open;
    }

    bool GetClose() {
        return close;
    }
};