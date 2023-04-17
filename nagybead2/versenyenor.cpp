#include "versenyenor.h"
#include <ctype.h>
#include <string>

versenyEnor::versenyEnor(const std::string &filename) {
    x.open(filename);
    if (x.fail())
        throw OPEN_ERROR;
}

std::istream& operator>>(std::istream& is, Horgasz_x &s) {
    std::string line;
    getline(is, line);
    std::istringstream ss(line);
    
    ss >> s.nev >> s.versenyid;

    s.halak.clear(); /// Nagyon fontos.
    Haladat_x a;
    while (ss >> a.nev >> a.suly) {
        s.halak.push_back(a);
    }
    
    return is;
}


void versenyEnor::next() {
    end_ = (sx == abnorm);

    if(!end_) {
        elem.id = dx.versenyid;
        elem.induloCount = 0;
        while(sx == norm && elem.id == dx.versenyid) {
            elem.induloCount++;
            read();
        }
    }
}

void versenyEnor::read() {
    x >> dx;
    sx = x.fail() ? abnorm : norm;
}