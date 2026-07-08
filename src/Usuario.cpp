#include "Usuario.h"

#include <string>

// Cria um novo usuário guardando todas as suas informações básicas de cadastro
Usuario::Usuario(
    int id,
    const std::string& nome,
    int idade,
    const std::string& cidade,
    const std::string& estado,
    const std::string& nacionalidade) :
    _id(id),
    _nome(nome),
    _idade(idade),
    _cidade(cidade),
    _estado(estado),
    _nacionalidade(nacionalidade) {}

// Retorna o código de identificação único gerado para o usuário
int Usuario::getId() const
{
    return _id;
}

// Retorna o nome cadastrado
std::string Usuario::getNome() const
{
    return _nome;
}

// Retorna a idade do usuário
int Usuario::getIdade() const
{
    return _idade;
}

// Retorna a cidade onde o usuário mora
std::string Usuario::getCidade() const
{
    return _cidade;
}

// Retorna o estado (UF) do usuário
std::string Usuario::getEstado() const
{
    return _estado;
}

// Retorna o país de origem (nacionalidade) do usuário
std::string Usuario::getNacionalidade() const
{
    return _nacionalidade;
}