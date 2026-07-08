#include "Compra.h"

#include <string>

// Inicializa a compra com seus dados básicos
Compra::Compra(int id, const std::string& timestamp, int id_usuario)
    : _id(id), _timestamp(timestamp), _id_usuario(id_usuario) {}

// Cria um item e guarda no vetor do carrinho de compras
void Compra::adicionarItem(int id_produto, int qtd)
{
    ItemTransacao item = {id_produto, qtd};
    _carrinho.inserir(item);
}

// Retorna o número de identificação da compra
int Compra::getId() const
{
    return _id;
}

// Retorna o momento em que a compra ocorreu
std::string Compra::getTimestamp() const
{
    return _timestamp;
}

// Retorna qual usuário realizou esta compra
int Compra::getIdUsuario() const
{
    return _id_usuario;
}

// Retorna o ponteiro do carrinho para evitar cópias na memória e erros de double free
VetorDinamico<ItemTransacao>* Compra::getCarrinho()
{
    return &_carrinho;
}