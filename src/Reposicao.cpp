#include "Reposicao.h"

#include <string>

// Inicia a reposição guardando seu ID e o momento em que ocorreu
Reposicao::Reposicao(int id, const std::string& timestamp)
    : _id(id), _timestamp(timestamp) {}

// Adiciona um produto e a quantidade que chegou no lote de reposição
void Reposicao::adicionarItem(int id_produto, int qtd)
{
    ItemReposicao item = {id_produto, qtd};
    _lote.inserir(item);
}

// Retorna o código de identificação da reposição
int Reposicao::getId() const
{
    return _id;
}

// Retorna o momento em que a reposição foi feita
std::string Reposicao::getTimestamp() const
{
    return _timestamp;
}

// Retorna o ponteiro do lote para evitar cópias desnecessárias na memória
VetorDinamico<ItemReposicao>* Reposicao::getLote()
{
    return &_lote;
}