#include "TabelaHash.h"

#include <string>

// Inicia a tabela com 97 posições (um número primo ajuda a espalhar melhor os dados)
TabelaHash::TabelaHash() : _capacidade(97)
{
    // Cria o array de ponteiros e já zera todos eles
    _tabela = new NoHash*[_capacidade]();
}

// Limpa toda a memória alocada para evitar vazamentos (memory leaks)
TabelaHash::~TabelaHash()
{
    for (int i = 0; i < _capacidade; ++i)
    {
        NoHash* atual = _tabela[i];
        // Percorre a lista encadeada de cada posição deletando os nós
        while (atual)
        {
            NoHash* proximo = atual->_prox;
            delete atual;
            atual = proximo;
        }
    }
    delete[] _tabela;
}

// Calcula em qual posição do array a chave deve ser guardada
int TabelaHash::calcularHash(const std::string& chave)
{
    long long hash = 0;

    // Usa um número primo (31) para multiplicar o valor das letras e evitar colisões
    for (char letra : chave)
    {
        hash = (hash * 31 + letra) % _capacidade;
    }

    return hash;
}

// Associa um ID a uma palavra-chave (ex: ID 5 associado a "cidade:Bh")
void TabelaHash::inserir(const std::string& chave, int id)
{
    int indice = calcularHash(chave);
    NoHash* atual = _tabela[indice];

    // Se a posição estiver vazia, cria o primeiro nó
    if (!atual)
    {
        _tabela[indice] = new NoHash(chave);
        _tabela[indice]->_ids.inserir(id);
        return;
    }

    NoHash* anterior = nullptr;

    // Se a posição já estiver ocupada (colisão), percorre a lista encadeada
    while (atual)
    {
        // Se a palavra-chave já existe, apenas adiciona o novo ID no vetor dela
        if (atual->_chave == chave)
        {
            atual->_ids.inserir(id);
            return;
        }

        anterior = atual;
        atual = atual->_prox;
    }

    // Se percorreu tudo e não achou a chave, cria um nó novo no final da lista
    anterior->_prox = new NoHash(chave);
    anterior->_prox->_ids.inserir(id);
}

// Retorna o vetor com todos os IDs que possuem a palavra-chave buscada
VetorDinamico<int>* TabelaHash::buscar(std::string& chave)
{
    int indice = calcularHash(chave);

    VetorDinamico<int>* aux = nullptr;
    NoHash* atual = _tabela[indice];

    // Percorre a lista encadeada daquela posição procurando a chave exata
    while (atual)
    {
        if (atual->_chave == chave)
        {
            aux = &atual->_ids; // Pega o ponteiro do vetor de IDs
            break;
        }

        atual = atual->_prox;
    }

    return aux; // Retorna o vetor (ou nulo se não encontrar nada)
}