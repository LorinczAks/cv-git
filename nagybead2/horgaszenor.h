#ifndef PAPERCOLLECTOR_H
#define PAPERCOLLECTOR_H

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

struct Haladat {
    std::string nev;
    int suly;
};

struct Horgasz {
    std::string nev;
    std::string versenyid;
    std::vector<Haladat> halak;
    friend std::istream& operator>>(std::istream& is, Horgasz& h);
    bool harcsa() const;
};

struct HarcsaHorgasz {
    std::string nev;
    bool haromHarcsa;
};

class horgaszEnor {
public:
    enum Exception {OPEN_ERROR};
    horgaszEnor(const std::string& filename);
    ~horgaszEnor(){ x.close(); }
    void first() { read(); next(); }
    void next();
    HarcsaHorgasz current() const { return elem; }
    bool end() const { return end_; }
private:
    enum Status { abnorm, norm };
    std::ifstream x;
    Horgasz dx;
    HarcsaHorgasz elem;
    Status sx;
    bool end_;
    
    void read();
};

#endif