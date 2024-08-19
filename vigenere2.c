#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LEN 100
#define KEYLEN 5

int ReadString(char* cmsg);
void ReadKey(char* key);
void ReplicaKey(char* repkey, char* key, int n);
void DeCypher(char* cmsg, char* msg, char* repkey, int n);

int main() {
    srand48(time(NULL));

    char cmsg[LEN + 1], msg[LEN + 1], key[KEYLEN + 1], repkey[LEN + 1];

    int len = ReadString(cmsg);

    ReadKey(key);

    ReplicaKey(repkey, key, len);

    DeCypher(cmsg, msg, repkey, len);

    fprintf(stdout, "Messaggio cifrato:\t%s\nchiave:\t%s\nmessaggio chiaro:\t%s\n", cmsg, key, msg);

    return 0;
}

int ReadString(char* cmsg) {
    int N = 0;
    char ch;
    
    fprintf(stdout, "Inserire la frase da decifrare (solo maiuscole e spazi, lunghezza massima: %d):\n", LEN);
    
    while((ch = getchar()) != '\n') {
        if(N == LEN) {
            fprintf(stderr, "...THE MESSAGE EXCEEDS THE MAXIMUM LENGHT...\n");
            exit(1);
        }
        if((ch < 'A' || ch > 'Z') && ch !=' ') {
            fprintf(stderr, "...INVALID INPUT...\n");
            exit(1);
        }

        cmsg[N++] = ch;
    }

    cmsg[N] = '\0';

    return N;
}

void ReadKey(char* key) {
    int N = 0;
    char ch;

    fprintf(stdout, "Inserire la chiave (solo maiuscole e spazi, lunghezza: %d):\n", KEYLEN);
    
    while((ch = getchar()) != '\n') {
        if(N == KEYLEN) {
            fprintf(stderr, "...THE KEY EXCEEDS THE MAXIMUM LENGHT...\n");
            exit(1);
        }
        if(ch < 'A' || ch > 'Z') {
            fprintf(stderr, "...INVALID INPUT...\n");
            exit(1);
        }

        key[N++] = ch;
    }
    key[KEYLEN] = '\0';
}

void ReplicaKey(char* repkey, char* key, int n) {
    for(int i = 0; i < n; i++) {
        repkey[i] = key[i % KEYLEN];
    }

    repkey[KEYLEN] = '\0';
}

void DeCypher(char* cmsg, char* msg, char* repkey, int n) {
    for(int i = 0; i < n; i++) {
        if(cmsg[i] != ' ' && cmsg[i] != '\0') {
            msg[i] = (cmsg[i] - repkey[i] + 26) % 26 + 'A'; 
        }
        else {
            msg[i] = cmsg[i];
        }
    }
}