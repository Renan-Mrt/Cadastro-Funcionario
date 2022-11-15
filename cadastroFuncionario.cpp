#include <stdio.h>
#include <stdlib.h>

#define U 12

typedef struct{
    int cr;// credencial
    char nome[50];
}User;

	User tabelaHash[U];


void inicializarTabela(){
    int i;
    for(i = 0; i < U; i++)
        tabelaHash[i].cr = -1;
}

int gerarCodigoHash(int chave){
    return chave % U;
}

User lerUser(){
    User u;
    printf("Digite a credencial de acesso: ");
    scanf("%d", &u.cr);
    scanf("%*c");
    printf("Digite o nome: ");
    fgets(u.nome, 50, stdin);
    return u;
}

void inserir(){
    User us = lerUser();
    int indice = gerarCodigoHash(us.cr);
    while(tabelaHash[indice].cr != -1)
        indice = gerarCodigoHash(indice + 1);
    tabelaHash[indice] = us;
}

User* buscar(int chave){
    int indice = gerarCodigoHash(chave);
    while(tabelaHash[indice].cr != -1){
        if(tabelaHash[indice].cr == chave)
            return &tabelaHash[indice];
        else
            indice = gerarCodigoHash(indice + 1);
    }
    return NULL;
}

void imprimir(){
    int i;
    printf("\n------------------------TABELA---------------------------\n");
    for(i = 0; i < U; i++){
        if(tabelaHash[i].cr != -1)
            printf("%2d = %3d \t %s", i, tabelaHash[i].cr, tabelaHash[i].nome);
        else
            printf("%2d =\n", i);
    }
    printf("\n----------------------------------------------------------\n");
}

int main() {
    int op, chave;
    User *u;

    inicializarTabela();

    do{
        printf("1 - Inserir\n2 - Buscar\n3 - Imprimir\n0 - Sair\n");
        scanf("%d", &op);

        switch(op){
        case 0:
            printf("Saindo...\n");
            break;
        case 1:
            inserir();
            break;
        case 2:
            printf("Digite a credencial a ser buscada: ");
            scanf("%d", &chave);
            u = buscar(chave);

            if(u)
                printf("\n\tCredencial: %d \tNome: %s\n", u->cr, u->nome);
            else
                printf("\nCredencial nao encontrada!\n");
            break;
        case 3:
            imprimir();
            break;
        default:
            printf("Opcao invalida!\n");
        }

    }while(op != 0);

    return 0;
}
