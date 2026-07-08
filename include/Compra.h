#ifndef COMPRA_H
#define COMPRA_H

#include "VetorDinamico.h"

#include <string>

struct ItemTransacao
{
    int id_produto;
    int qtd;
};

class Compra
{
private:
    int _id;
    std::string _timestamp;
    int _id_usuario;
    VetorDinamico<ItemTransacao> _carrinho;
public:
    Compra(int id, const std::string& timestamp, int id_usuario);
    void adicionarItem(int id_produto, int qtd);
    int getId() const;
    std::string getTimestamp() const;
    int getIdUsuario() const;
    VetorDinamico<ItemTransacao>* getCarrinho();
};

#endif // COMPRA_H