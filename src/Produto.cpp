#include "Produto.h"

#include <string>

Produto::Produto(
    std::string& nome,
    double preco,
    int qtdInicial,
    std::string& categoria,
    std::string& marca,
    std::string& condicao) :
    _nome(nome),
    _preco(preco),
    _qtdInicial(qtdInicial),
    _categoria(categoria),
    _marca(marca),
    _condicao(condicao)
{
}

std::string Produto::getNome() const
{
    return _nome;
}

double Produto::getPreco() const
{
    return _preco;
}

int Produto::getQtdInicial() const
{
    return _qtdInicial;
}

std::string Produto::getCategoria() const
{
    return _categoria;
}

std::string Produto::getMarca() const
{
    return _marca;
}

std::string Produto::getCondicao() const
{
    return _condicao;
}
