#include "horgaszenor.h"
#include "versenyenor.h"
#include <iostream>
#include <cstdlib>

#define NORMAL_MODE
#ifdef NORMAL_MODE

bool first(const std::string &name, HarcsaHorgasz& e)
{
    
    horgaszEnor t(name);
    /// Pesszimista lineáris keresés programozási tétel.
    
    bool l = false;
    for (t.first(); !t.end(); t.next()) {
            if (t.current().haromHarcsa) {
                l = true;
                e = t.current();
            }
        }
    return l;
}

bool second(const std::string &name, Verseny& e)
{
    versenyEnor g(name);
    /// Maximumkeresés programozási tétel.
    g.first();
    int max = g.current().induloCount;
    Verseny maxVerseny = g.current();

    g.next();

    while(!g.end()) {
        if(g.current().induloCount > max) {
            max = g.current().induloCount;
            maxVerseny = g.current();
        }
        g.next();
    }
    e = maxVerseny;
    return true;
}


int main() {
    //Adjunk meg egy olyan horgászt, aki csak harcsát fogott, de abból legalább hármat!
    try {
        std::cout << "\"A\" problem solution:\n\n";
        HarcsaHorgasz e;

        if(first("input.txt", e)) {
            std::cout << "First fisherman who only caught catfish, but at least 3 of them: " << e.nev << "\n";
        }
        else {
            std::cout << "No fishermen caught only catfish, but at least 3 of them :(\n";
        }
    } catch (horgaszEnor::Exception e) {
        std::cerr << "File open error!\n";
        return 1;
    }

    //Melyik versenyen indult a legtöbb horgász?
    try {
        std::cout << "\"B\" problem solution:\n\n";
        Verseny f;

        if(second("input.txt", f))
        std::cout << "Event with the most fishermen: " << f.id << "\n";
        
    } catch (versenyEnor::Exception e) {
        std::cerr << "File open error!\n";
        return 1;
    }

    return 0;
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"


// first task

TEST_CASE("no catfisherman", "input.txt") {
    HarcsaHorgasz q;
    CHECK(!first("input.txt", q));
}

TEST_CASE("first fisherman is the catfisherman", "input2.txt") {
    HarcsaHorgasz w;
    first("input.txt", w)
    CHECK(w.nev=="JANIBA");
}

TEST_CASE("last fisherman is the catfisherman", "input3.txt") {
    HarcsaHorgasz e;
    first("input.txt", e)
    CHECK(e.nev=="FERIBA");
}

// second task

TEST_CASE("empty file", "input7.txt") {
    Verseny verseny;
    CHECK_FALSE(second_search("input7.txt", verseny));
}

TEST_CASE("first contest has most fishermen", "input4.txt") {
    Verseny q;
    first("input4.txt", q)
    CHECK(q.id=="Kiliti0512");
}

TEST_CASE("last contest has most fishermen", "input5.txt") {
    Verseny w;
    first("input5.txt", w)
    CHECK(w.id=="Lamatu2511");
}

TEST_CASE("two contests have most fishermen", "input6.txt") {
    Verseny e;
    first("input6.txt", e)
    CHECK(e.id=="Kiliti0512");
}

#endif