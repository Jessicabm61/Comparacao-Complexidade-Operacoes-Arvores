#include <stdlib.h>
#include <string.h>

long int avlCount = 0;

typedef struct no {
    struct no* pai;
    struct no* esquerda;
    struct no* direita;
    int valor;
} No;

typedef struct arvoreAVL {
    struct no* raiz;
} ArvoreAVL;

ArvoreAVL* criarArvoreAVL() {
    ArvoreAVL *arvoreAVL = malloc(sizeof(ArvoreAVL));
    arvoreAVL->raiz = NULL;

    return arvoreAVL;
}

int vaziaAVL(ArvoreAVL* arvoreAVL) {
    return arvoreAVL->raiz == NULL;
}

int altura(No *no) {
    int esquerda = 0, direita = 0;

    if (no->esquerda != NULL) {
        esquerda = altura(no->esquerda) + 1;
    }

    if (no->direita != NULL) {
        direita = altura(no->direita) + 1;
    }

    return esquerda > direita ? esquerda : direita;
}

int fb(No *no) {
    avlCount++;
    int esquerda = 0, direita = 0;

    if (no->esquerda != NULL) {
        esquerda = altura(no->esquerda) + 1;
    }

    if (no->direita != NULL) {
        direita = altura(no->direita) + 1;
    }

    return esquerda - direita;
}

No *rse(ArvoreAVL *arvoreAVL, No *no) {
    avlCount++;
    No *pai = no->pai;
    No *direita = no->direita;

    if (direita->esquerda != NULL) {
        direita->esquerda->pai = no;
    }

    no->direita = direita->esquerda;
    no->pai = direita;

    direita->esquerda = no;
    direita->pai = pai;

    if (pai == NULL) {
        arvoreAVL->raiz = direita;
    } else {
        if (pai->esquerda == no) {
            pai->esquerda = direita;
        } else {
            pai->direita = direita;
        }
    }

    return direita;
}

No *rsd(ArvoreAVL *arvoreAVL, No *no) {
    avlCount++;
    No *pai = no->pai;
    No *esquerda = no->esquerda;

    if (esquerda->direita != NULL) {
        esquerda->direita->pai = no;
    }

    no->esquerda = esquerda->direita;
    no->pai = esquerda;

    esquerda->direita = no;
    esquerda->pai = pai;

    if (pai == NULL) {
        arvoreAVL->raiz = esquerda;
    } else {
        if (pai->esquerda == no) {
            pai->esquerda = esquerda;
        } else {
            pai->direita = esquerda;
        }
    }

    return esquerda;
}

No *rde(ArvoreAVL *arvoreAVL, No *no) {
    no->direita = rsd(arvoreAVL, no->direita);
    return rse(arvoreAVL, no);
}

No *rdd(ArvoreAVL *arvoreAVL, No *no) {
    no->esquerda = rse(arvoreAVL, no->esquerda);
    return rsd(arvoreAVL, no);
}

void balanceamento(ArvoreAVL *a, No *no) {
    while (no != NULL) {
        avlCount++;
        int fator = fb(no);

        if (fator > 1) {
            if (fb(no->esquerda) > 0) {
                rsd(a, no);
            } else {
                rdd(a, no);
            }
        } else if (fator < -1) {
            if (fb(no->direita) < 0) {
                rse(a, no);
            } else {
                rde(a, no);
            }
        }

        no = no->pai;
    }
}

No* criarNo(int valor) {
    No* no = malloc(sizeof(No));
    no->valor = valor;
    no->pai = NULL;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

No* adicionarNo(No* no, int valor) {
    avlCount++;
    if (valor > no->valor) {
        if (no->direita == NULL) {
            No* novo = criarNo(valor);
            novo->pai = no;
            no->direita = novo;

            return novo;
        } else {
            return adicionarNo(no->direita, valor);
        }
    } else {
        if (no->esquerda == NULL) {
            No* novo = criarNo(valor);
            novo->pai = no;
            no->esquerda = novo;

            return novo;
        } else {
            return adicionarNo(no->esquerda, valor);
        }
    }
}

No* adicionarValorAVL(ArvoreAVL* arvoreAVL, int valor) {
    avlCount++;
    if (arvoreAVL->raiz == NULL) {
        No* novo = criarNo(valor);
        arvoreAVL->raiz = novo;

        return novo;
    } else {
        avlCount++;
        No* no = adicionarNo(arvoreAVL->raiz, valor);
        balanceamento(arvoreAVL, no);
        return no;
    }
}

void removerNoAVL(ArvoreAVL *arvoreAVL, No *no) {
    avlCount++;
    if (no->esquerda != NULL) removerNoAVL(arvoreAVL, no->esquerda);

    if (no->direita != NULL) removerNoAVL(arvoreAVL, no->direita);

    if (no->pai == NULL) {
        arvoreAVL->raiz = NULL;
    } else {
        if (no->pai->esquerda == no)
            no->pai->esquerda = NULL;
        else
            no->pai->direita = NULL;
    }
    free(no);
}

No* localizar(No* no, int valor) {
    avlCount++;
    if (no->valor == valor) {
        return no;
    } else {
        if (valor < no->valor) {
            if (no->esquerda != NULL) {
                return localizar(no->esquerda, valor);
            }
        } else {
            if (no->direita != NULL) {
                return localizar(no->direita, valor);
            }
        }
    }

    return NULL;
}

void removerValorAVL(ArvoreAVL* arvoreAVL, int valor) {
    avlCount++;
    No* no = localizar(arvoreAVL->raiz, valor);

    while (no != NULL) {
        if (no->esquerda == NULL && no->direita == NULL) {
            avlCount++;
            if (no->pai == NULL) {
                avlCount++;
                arvoreAVL->raiz = NULL;
            } else {
                avlCount++;
                if (no->pai->esquerda == no)
                    no->pai->esquerda = NULL;
                else
                    no->pai->direita = NULL;
            }
            free(no);
            break;
        } else if (no->esquerda != NULL && no->direita != NULL) {
            No* sucessor = no->direita;
            while (sucessor->esquerda != NULL) {
                avlCount++;
                sucessor = sucessor->esquerda;
            }

            no->valor = sucessor->valor;
            no = sucessor;
        } else {
            No* filho = (no->esquerda != NULL) ? no->esquerda : no->direita;
            filho->pai = no->pai;

            if (no->pai == NULL) {
                arvoreAVL->raiz = filho;
            } else {
                if (no->pai->esquerda == no)
                    no->pai->esquerda = filho;
                else
                    no->pai->direita = filho;
            }

            free(no);
            break;
        }
    }

    if (no != NULL) {
        balanceamento(arvoreAVL, arvoreAVL->raiz);
    }
}
