#ifndef PRODUTO_H
#define PRODUTO_H

#include <string>

class Produto
{
private:
    std::string _nome;
    double _preco;
    int _qtdInicial;
    std::string _categoria;
    std::string _marca;
    std::string _condicao;
public:
    Produto(
    std::string& nome,
    double preco,
    int qtdInicial,
    std::string& categoria,
    std::string& marca,
    std::string& condicao);
    std::string getNome() const;
    double getPreco() const;
    int getQtdInicial() const;
    std::string getCategoria() const;
    std::string getMarca() const;
    std::string getCondicao() const;
};

#endif //PRODUTO_H
