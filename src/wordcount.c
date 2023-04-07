/*
Rewrite this to C

#include <string>
#include <iostream>
#include <unordered_map>

int main() {
    using namespace std;
    unordered_map<string,int> m;  // asociativní pole
                    // mapuje klíč/string na hodnotu/int
    string word;
    while (cin >> word) // čtení slova (jako scanf "%s", ale bezpečné)
        m[word]++;      // počítání výskytů slova (zvýší hodnotu pro
                        // zadaný klíč/slovo pokud záznam existuje,
                        // jinak vytvoří nový záznam s hodnotou 0 a
                        // tu operace ++ zvýší na 1)

    for (auto &mi: m)   // pro všechny prvky kontejneru m
        cout << mi.first << "\t" << mi.second << "\n";
        //      klíč/slovo          hodnota/počet
        // prvky kontejneru typu "map" jsou dvojice (klíč,hodnota)
}
*/

#include <stdlib.h>
#include "io.h"
#include "htab.h"

void print(htab_pair_t* pair) {
    printf("%s\t%d\n", pair->key, pair->value);
}

int main() {
    char* s = malloc(255);
    if (!s)
        return 1;

    htab_t* t = htab_init(100);
    while (read_word(s, 255, stdin)) {
        htab_lookup_add(t, s);
    }

    htab_for_each(t, print);

    htab_erase(t, "se");

    printf("\n");
    htab_for_each(t, print);

    free(s);
    htab_free(t);
    return 0;
}
