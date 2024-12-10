#include <cstdio>

inline void putUI(unsigned int N) {
    if (N == 0) {
        putc_unlocked(48, stdout);
        return;
    }

    char tab[12];
    int p = 0;
    while (N != 0) {
        tab[p++] = (N % 10) + 48;
        N /= 10;
    }
    while (p--) 
        putc_unlocked(tab[p], stdout);
}

inline void readINT(int *N) {
    register char c = 0, znak_liczby = 1;
    while (c < 33) c = getc_unlocked(stdin);
    
    if (c == 45) { 
        znak_liczby = -1;  
        c = getc_unlocked(stdin);
    }
    
    (*N) = 0;
    
    while (c > 32) {
        (*N) = (*N) * 10 + c - 48;
        c = getc_unlocked(stdin);
    }

    (*N) *= znak_liczby;
}

void hanoiAlgorithm(int N, char fromCharacter, char toCharacter, char helperCharacter) {
    if (N == 1) {
        putc_unlocked(fromCharacter, stdout); 
        putc_unlocked(' ', stdout);
        putc_unlocked(toCharacter, stdout); 
        putc_unlocked('\n', stdout);
        return;
    }
    hanoiAlgorithm(N - 1, fromCharacter, helperCharacter, toCharacter);
    putc_unlocked(fromCharacter, stdout); 
    putc_unlocked(' ', stdout);
    putc_unlocked(toCharacter, stdout); 
    putc_unlocked('\n', stdout);
    hanoiAlgorithm(N - 1, helperCharacter, toCharacter, fromCharacter);
}

int main() {
    int N;
    readINT(&N);
    
    hanoiAlgorithm(N, 'A', 'B', 'C');
    
    return 0;
}
