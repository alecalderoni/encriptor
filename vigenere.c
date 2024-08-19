#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LEN 100
#define KEYLEN 5

int ReadString(char* msg);
void CreateKey(char* key);
void ReplicaKey(char* repkey, char* key, int n);
void Cypher(char* cmsg, char* msg, char* repkey, int n);

int main() {
    srand48(time(NULL));

    char msg[LEN + 1], cmsg[LEN + 1], key[KEYLEN + 1], repkey[LEN + 1];

    int len = ReadString(msg);

    CreateKey(key);

    ReplicaKey(repkey, key, len);

    Cypher(cmsg, msg, repkey, len);

    fprintf(stdout, "Messaggio chiaro:\t%s\nchiave:\t%s\nmessaggio cifrato:\t%s\n", msg, key, cmsg);

    return 0;
}

int ReadString(char* msg) {
    int N = 0;
    char ch;
    
    fprintf(stdout, "Inserire la frase da criptare (solo maiuscole e spazi, lunghezza massima: %d):\n", LEN);
    
    while((ch = getchar()) != '\n') {
        if(N == LEN) {
            fprintf(stderr, "...THE MESSAGE EXCEEDS THE MAXIMUM LENGHT...\n");
            exit(1);
        }
        if((ch < 'A' || ch > 'Z') && ch !=' ') {
            fprintf(stderr, "...INVALID INPUT...\n");
            exit(1);
        }

        msg[N++] = ch;
    }

    msg[N] = '\0';

    return N;
}

void CreateKey(char* key) {
    for(int i = 0; i < KEYLEN; i++) {
        key[i] = 'A' + lrand48() % 26;
    }

    key[KEYLEN] = '\0';
}

void ReplicaKey(char* repkey, char* key, int n) {
    for(int i = 0; i < n; i++) {
        repkey[i] = key[i % KEYLEN];
    }

    repkey[KEYLEN] = '\0';
}

void Cypher(char* cmsg, char* msg, char* repkey, int n) {
    for(int i = 0; i < n; i++) {
        if(msg[i] != ' ' && msg[i] != '\0') {
            cmsg[i] = 'A' + (msg[i] + repkey[i]) % 26;  
        }
        else {
            cmsg[i] = msg[i];
        }
    }
}