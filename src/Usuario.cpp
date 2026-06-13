#include "Usuario.h"

#include <string>

Usuario::Usuario(
    std::string& nome,
    int idade,
    std::string& cidade,
    std::string& estado,
    std::string& nacionalidade) :
    _nome(nome),
    _idade(idade),
    _cidade(cidade),
    _estado(estado),
    _nacionalidade(nacionalidade)
{
}

std::string Usuario::getNome() const
{
    return _nome;
}

int Usuario::getIdade() const
{
    return _idade;
}

std::string Usuario::getCidade() const
{
    return _cidade;
}

std::string Usuario::getEstado() const
{
    return _estado;
}

std::string Usuario::getNacionalidade() const
{
    return _nacionalidade;
}
