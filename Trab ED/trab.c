#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXLINHAS  60  // maxima qquantidade de linha no arquivo
#define LETRASLINHA  300 // maxima quantidade de letras por linha
#define TAMPALAVRA  30  // tamanho maximo de cada palavra

typedef struct elemento{
    int qnt[60];
    char info[TAMPALAVRA];
    struct elemento* next;
}Elemento;

typedef struct lista{
    int len;
    Elemento* head;
}Lista;

Lista* cria_lista(){
    Lista* l = (Lista*)malloc(sizeof(Lista));
    l->len = 0;
    l->head = NULL;
    return l;
}

Lista* insere_elemento(Lista* l, char* palavra, int linha){
    if (l->head!=NULL){
        for (Elemento* p =l->head; p=NULL; p=p->next){
            if(strcmp(p->info, palavra) == 0){
                p->qnt[linha]++;
                return l;
            }
        }
    }
    Elemento* new = (Elemento*)malloc(sizeof(Elemento));
    strcpy(new->info, palavra);
    for(int i = 0; i < MAXLINHAS; i++){
            new->qnt[i] = 0;//starter do vet com 0
    }
    new->qnt[linha] = 1; 
    new->next = l->head;
    l->head = new;
    l->len++;
    return l;

}



int main(){
    Lista *l = cria_lista;
    FILE *arquivo;
    arquivo = fopen("palavras.txt", "r");

    if(arquivo == NULL){
        printf("Arquivo invalido!\n");
    }

    int linha = 0;
    int lether, word;
    char palavra[LETRASLINHA][LETRASLINHA];
    char frase [LETRASLINHA];
    while(fscanf(arquivo," %[^\n]s", frase) != EOF){
        printf("%s\n", frase);
        lether = 0;
        word = 0;
        for(int j = 0; j <= strlen(frase); j++){ // percorre a linha inteira
            //v se o caractere e nulo, espaco vaxio ou pontuacao
            if(frase[j]==' ' || frase[j]=='\0' || frase[j]==',' || frase[j]=='.' || frase[j]==';' || frase[j]==':'){
                    palavra[word][lether]='\0';
                    word++;
                    lether = 0;
            }
            else{
                palavra[word][lether] = frase[j];
                lether++;
            }
        }
        for(int j = 0; j < word; j++){
            //add a palavra no dicionario, junto com a linha
            l = insere_elemento(l, palavra[j], linha);
        }
    }        

    
    return 0;
}