#ifndef USUARIO_H
#define USUARIO_H

#include <string>

class Usuario
{
private:
    int _id;
    std::string _nome;
    int _idade;
    std::string _cidade;
    std::string _estado;
    std::string _nacionalidade;
public:
    Usuario(
        int id,
        const std::string& nome,
        int idade,
        const std::string& cidade,
        const std::string& estado,
        const std::string& nacionalidade);

    int getId() const;
    std::string getNome() const;
    int getIdade() const;
    std::string getCidade() const;
    std::string getEstado() const;
    std::string getNacionalidade() const;
};

#endif // USUARIO_H