#include "disjointsets.h"

void DisjointSets::addelements(int num) {
    for (int i = 0; i < num; i++) {
        sets.push_back(-1);
    }
}

int DisjointSets::find(int elem) {
    if (sets[elem] < 0) { //if elem is its own parent
        return elem;
    } else { //elem is not the representative of its set, call find recursively
        int num = find(sets[elem]);
        sets[elem] = num;
        return num;
    }
}

void DisjointSets::setunion(int a, int b) {
    int aroot = find(a);
    int broot = find(b);

    if (aroot == broot) {
        return;
    }

    if (aroot > broot) { // a smaller set -> put it in b
        sets[broot] = sets[aroot] + sets[broot];
        sets[aroot] = broot;
    } else {
        sets[aroot] = sets[aroot] + sets[broot];
        sets[broot] = aroot;
    }
}

int DisjointSets::size(int elem) {
    return (sets[find(elem)] * -1);
}