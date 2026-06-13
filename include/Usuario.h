#ifndef USUARIO_H
#define USUARIO_H

#include <string>

class Usuario
{
private:
    std::string _nome;
    int _idade;
    std::string _cidade;
    std::string _estado;
    std::string _nacionalidade;
public:
    Usuario(
        std::string& nome,
        int idade,
        std::string& cidade,
        std::string& estado,
        std::string& nacionalidade);
    std::string getNome() const;
    int getIdade() const;
    std::string getCidade() const;
    std::string getEstado() const;
    std::string getNacionalidade() const;
};

#endif //USUARIO_H
