#ifndef VERSENYENOR_H
#define VERSENYENOR_H

#include "horgaszenor.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

struct Haladat_x {
    std::string nev;
    int suly;
};

struct Horgasz_x {
    std::string nev;
    std::string versenyid;
    std::vector<Haladat_x> halak;
    friend std::istream& operator>>(std::istream& is, Horgasz_x& h);
};

struct Verseny {
    std::string id;
    int induloCount;
};

class versenyEnor {
public:
    enum Exception {OPEN_ERROR};
    versenyEnor(const std::string& filename);
    ~versenyEnor(){ x.close(); }
    void first() { read(); next(); }
    void next();
    Verseny current() const { return elem; }
    bool end() const { return end_; }
private:
    enum Status { abnorm, norm };
    std::ifstream x;
    Horgasz_x dx;
    Verseny elem;
    Status sx;
    bool end_;
    
    void read();
};

#endif