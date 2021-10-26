#include <stdio.h>
#include <stdlib.h>

struct item{
    int dado;
    int altura;
};
typedef struct item Item;

struct node{
    Item item;
    struct node *left;
    struct node *right;
};
typedef struct node node;

int FB (node* pRaiz);
int Altura(node* pRaiz);
void RSE(node** ppRaiz);
void RSD(node** ppRaiz);
int BalancaEsquerda(node** ppRaiz);
int BalancaDireita(node** ppRaiz);
int Balanceamento(node** ppRaiz);
int Insere(node** ppRaiz,int x);
int verificaAVL(node* pRaiz);
void imprime(node *raiz);


int main(){
    int nNos=0, dado=0, verif=0;
    node *start = NULL;

    printf("\nDeseja inserir quantos nos? ");
    scanf("%d", &nNos);

    for(int i = 1; i <= nNos; i++){
        printf("\nNo %d: ", i);
        scanf("%d", &dado);
        Insere(&start, dado);
    }

    imprime(start);

    verif = verificaAVL(start);
    if(verif == 1){
        printf("\nArvore Verificada!\n");
    } else{
        printf("\nErro na Arvore!\n");
    }

    return 0;
}

int Altura(node* pRaiz){
    int iEsq,iDir;

    if (pRaiz == NULL){
        return 0;
    }

    iEsq = Altura(pRaiz->left);
    iDir = Altura(pRaiz->right);

    if ( iEsq > iDir )
        return iEsq + 1;
    else
        return iDir + 1;
}

int FB (node* pRaiz){
    if (pRaiz == NULL)
        return 0;
    return Altura(pRaiz->left) - Altura(pRaiz->right);
}

void RSE(node** ppRaiz){
    node *pAux;
    pAux = (*ppRaiz)->right;
    (*ppRaiz)->right = pAux->left;
    pAux->left = (*ppRaiz);
    (*ppRaiz) = pAux;
}

void RSD(node** ppRaiz){
    node *pAux;
    pAux = (*ppRaiz)->left;
    (*ppRaiz)->left = pAux->right;
    pAux->right = (*ppRaiz);
    (*ppRaiz) = pAux;
}

int BalancaEsquerda(node** ppRaiz){
    int fbe = FB ( (*ppRaiz)->left );
    
    if ( fbe > 0 ){
        RSD(ppRaiz);
        return 1;
    }
    else if (fbe < 0 ){ 
        /* Rotação Dupla Direita */
        RSE( &((*ppRaiz)->left) );
        RSD( ppRaiz ); /* &(*ppRaiz) */
        return 1;
    }
    return 0;
}

int BalancaDireita(node** ppRaiz){
    int fbd = FB( (*ppRaiz)->right);
    if ( fbd < 0 )
    {
    RSE (ppRaiz);
    return 1;
    }
    else if (fbd > 0 )
    { /* Rotação Dupla Esquerda */
    RSD( &((*ppRaiz)->right) );
    RSE( ppRaiz ); /* &(*ppRaiz) */
    return 1;
    }
    return 0;
}

int Balanceamento(node** ppRaiz){
    int fb = FB(*ppRaiz);
    if ( fb > 1)
        return BalancaEsquerda(ppRaiz);
    else if (fb < -1 )
        return BalancaDireita(ppRaiz);
    else
        return 0;
}

int Insere(node** ppRaiz,int x){
    if (*ppRaiz == NULL){
        *ppRaiz = (node*)malloc(sizeof(node));
        (*ppRaiz)->item.dado = x;
        (*ppRaiz)->left = NULL;
        (*ppRaiz)->right = NULL;
        return 1;
    }

    else if ((*ppRaiz)->item.dado > x)
    {
        if ( Insere(&(*ppRaiz)->left, x) )
        {
            if (Balanceamento(ppRaiz))
                return 0;
            else
                return 1;
        }
    }

    else if ((*ppRaiz)->item.dado < x)
    {
        if ( Insere(&(*ppRaiz)->right, x) )
        {
            if (Balanceamento(ppRaiz))
                return 0;
            else
                return 1;
        }
        else
            return 0;
        }

    
    return 0;
}

int verificaAVL(node* pRaiz){
    int fb;
    if (pRaiz == NULL)
        return 1;
    if (!verificaAVL(pRaiz->left))
        return 0;
    if (!verificaAVL(pRaiz->right))
        return 0;
    fb = FB(pRaiz);
    if ( ( fb > 1 ) || ( fb < -1) )
        return 0;
    else
        return 1;
}

void imprime(node *raiz){
    if (raiz != NULL)    {
        printf("\n%d", raiz->item.dado);           
        imprime(raiz->left);
        imprime(raiz->right);
    }
}