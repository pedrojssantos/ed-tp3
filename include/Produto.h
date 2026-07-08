#ifndef PRODUTO_H
#define PRODUTO_H

#include <string>

class Produto
{
private:
    int _id;
    std::string _nome;
    double _preco;
    int _qtd;
    std::string _categoria;
    std::string _marca;
    std::string _condicao;
public:
    Produto(
        int id,
        const std::string& nome,
        double preco,
        int qtd,
        const std::string& categoria,
        const std::string& marca,
        const std::string& condicao);
    int getId() const;
    std::string getNome() const;
    double getPreco() const;
    int getQtd() const;
    std::string getCategoria() const;
    std::string getMarca() const;
    std::string getCondicao() const;
    void alterarQtd(int valor);
};

#endif // PRODUTO_H