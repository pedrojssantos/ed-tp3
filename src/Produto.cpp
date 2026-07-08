#include "Produto.h"

#include <string>

// Cria um novo produto guardando todas as suas características básicas
Produto::Produto(
    int id,
    const std::string& nome,
    double preco,
    int qtd,
    const std::string& categoria,
    const std::string& marca,
    const std::string& condicao) :
    _id(id),
    _nome(nome),
    _preco(preco),
    _qtd(qtd),
    _categoria(categoria),
    _marca(marca),
    _condicao(condicao) {}

// Retorna o código de identificação único do produto
int Produto::getId() const
{
    return _id;
}

// Retorna o nome do produto
std::string Produto::getNome() const
{
    return _nome;
}

// Retorna o preço de venda do produto
double Produto::getPreco() const
{
    return _preco;
}

// Retorna a quantidade atual disponível no estoque
int Produto::getQtd() const
{
    return _qtd;
}

// Retorna a categoria (ex: Informatica, Livros)
std::string Produto::getCategoria() const
{
    return _categoria;
}

// Retorna a marca fabricante do produto
std::string Produto::getMarca() const
{
    return _marca;
}

// Retorna o estado físico do produto (ex: Novo, Usado)
std::string Produto::getCondicao() const
{
    return _condicao;
}

// Atualiza o estoque (valores positivos para reposição, negativos para compras)
void Produto::alterarQtd(int valor)
{
    _qtd += valor;
}