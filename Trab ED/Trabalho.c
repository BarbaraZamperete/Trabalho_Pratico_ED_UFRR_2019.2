#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma region Estruturas
typedef struct nodo{
    int num_linha;
    int num_repete;
}Nodo;

typedef struct palavras{
    char palavra[50];
    int aparicoes;
    Nodo *detalhes[50];
    Nodo *next;
}Palavra;


typedef struct lista{
    Nodo *head;
    int len;
}Lista;
#pragma endregion

#pragma region Comandos
Lista *cria_lista(){
    Lista *lista = (Lista*) malloc(sizeof(Lista));
    lista->head = NULL;
    lista->len = 0;
    return lista;
}

Nodo *cria_nodo(int numero_linha){
    Nodo *new = (Nodo*) malloc(sizeof(Nodo));
    new->num_linha = numero_linha;
    new->num_repete=1;
    return new;
}

void cria_palavra(Lista *f,int numero_linha,char palavra[50]){
    Palavra *new = (Palavra*) malloc(sizeof(Palavra));
    new->palavra = palavra;
    new->detalhes[0]=cria_nodo(numero_linha); // aqui tb
    new->aparicoes=1;
    new->next = f->head;
    f->head = new; // f-head aponta para um Nodo e vc ta igualando ele a um tipo Palavra
    //f->head = new->next (?)
    f->len++;
}

void incrementer_detalhes(Palavra *f,int linha){
    if(f->aparicoes>0){
        int aux = f->aparicoes;
        while(aux>0){
            if(f->detalhes[aux-1]->num_linha == linha){
                f->detalhes[aux-1]->num_repete+1;
            }else{
                Nodo *new = (Nodo*) malloc(sizeof(Nodo));
                f->detalhes[0] = new;
                f->detalhes[0]->num_linha = linha;
                f->detalhes[0]->num_repeticoes=1;
            }
            aux--;
        }
    }else{
        Nodo *new = (Nodo*) malloc(sizeof(Nodo));
        f->detalhes[0] = new;
        f->detalhes[0]->num_linha = linha;
        f->detalhes[0]->num_repeticoes=1;
    }
    f->aparicoes++;
}
#pragma endregion

int main(){
    char texto[500];
    int aux=0;
    int i=0;
    FILE *arquivo;
    arquivo = fopen("palavras.txt", "r");
    Lista* dicionario = cria_lista();
     *p;
    if (arquivo == NULL)
        return 0;

    while(fscanf("%s",texto[i]) != EOF){
        aux = dicionario->len;
        p = dicionario->head;
        if(aux>0){
            while(p->palavra!=texto[i]){
                if(p->palavra==texto[i]){
                    incrementa_detalhes(p->head,i);
                }else{
                    if(p->next == NULL){
                        p = dicionario->head;
                        break;
                    }else{
                        p = p->next;
                    }
                }            
            }
        }
        cria_palavra(dicionario,i,palavra[i]);
        incrementa_detalhes(p->head,i);
        i++;
    }
   
    for(Palavra *z = dicionario->head; z!=NULL; z=z->next){ //Dicionario head é um Nodo*
        printf("Palavra: %s\n",z->palavra);
        for(int j=z->aparicoes,j<=0;j--){
            printf("Linha: %d ",z->detalhes[j]->num_linha);
            printf("Numero de repetições: %d ",z->detalhes[j]->num_repete);
        }
    }
    return 0;
}