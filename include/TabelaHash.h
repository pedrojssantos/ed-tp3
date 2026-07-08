#ifndef TABELAHASH_H
#define TABELAHASH_H

#include "VetorDinamico.h"

#include <string>

struct NoHash
{
    std::string _chave;
    VetorDinamico<int> _ids;
    NoHash* _prox;

    NoHash(std::string chave) : _chave(chave), _prox(nullptr) {}
};

class TabelaHash
{
private:
    NoHash** _tabela;
    int _capacidade;
    int calcularHash(const std::string& chave);
public:
    TabelaHash();
    ~TabelaHash();
    void inserir(const std::string& chave, int id);
    VetorDinamico<int>* buscar(std::string& chave);
};

#endif // TABELAHASH_H
