#ifndef REPOSICAO_H
#define REPOSICAO_H

#include "VetorDinamico.h"

#include <string>

struct ItemReposicao
{
    int id_produto;
    int qtd;
};

class Reposicao
{
private:
    int _id;
    std::string _timestamp;
    VetorDinamico<ItemReposicao> _lote;
public:
    Reposicao(int id, const std::string& timestamp);
    void adicionarItem(int id_produto, int qtd);
    int getId() const;
    std::string getTimestamp() const;
    VetorDinamico<ItemReposicao>* getLote();
};

#endif // REPOSICAO_H