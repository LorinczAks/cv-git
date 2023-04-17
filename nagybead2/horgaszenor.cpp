#include "horgaszenor.h"
#include <ctype.h>
#include <string>


horgaszEnor::horgaszEnor(const std::string& filename) {
    x.open(filename);
    if (x.fail())
        throw OPEN_ERROR;
}

std::istream& operator>>(std::istream& is, Horgasz &s) {
    std::string line;
    getline(is, line);
    std::istringstream ss(line);
    
    ss >> s.nev >> s.versenyid;

    s.halak.clear(); /// Nagyon fontos.
    Haladat a;
    while (ss >> a.nev >> a.suly) {
        s.halak.push_back(a);
    }
    return is;
}

bool Horgasz::harcsa() const {
    int count;
    bool csakharcsa = true;
    for (Haladat a : halak) {
        if (a.nev == "Harcsa"){
            count++;
        }
        else {
            csakharcsa = false;
        }
    }
    if(count >= 3 && csakharcsa) {
        return true;
    }
    return false;
}

void horgaszEnor::next() {
    end_ = (sx == abnorm);

    if(!end_) {
        elem.nev = dx.nev;
        elem.haromHarcsa = dx.harcsa();
        read();
    }
}


void horgaszEnor::read() {
    x >> dx;
    sx = x.fail() ? abnorm : norm;
}