#ifndef VETOR_DINAMICO_H
#define VETOR_DINAMICO_H

// Estrutura de array dinâmico que cresce automaticamente
template <typename T>
class VetorDinamico
{
private:
    T* _dados;
    int _capacidade;
    int _tamanho;

    // Dobra o tamanho do vetor quando ele fica cheio
    void redimensionar()
    {
        int novaCap = _capacidade * 2;
        T* temp = new T[novaCap];

        // Copia os elementos antigos para o novo espaço
        for (int i = 0; i < _tamanho; ++i)
        {
            temp[i] = _dados[i];
        }

        delete[] _dados;
        _dados = temp;
        _capacidade = novaCap;
    }

public:
    // Inicia o vetor com espaço para apenas 1 elemento
    VetorDinamico() : _capacidade(1), _tamanho(0)
    {
        _dados = new T[_capacidade];
    }

    // Destrutor limpa a memória alocada quando o vetor é destruído
    ~VetorDinamico()
    {
        delete[] _dados;
    }

    // Adiciona um novo elemento ao final da estrutura
    void inserir(T elemento)
    {
        // Se não tiver mais espaço, pede mais memória
        if (_tamanho >= _capacidade)
        {
            redimensionar();
        }

        _dados[_tamanho] = elemento;
        _tamanho++;
    }

    // Retorna o elemento salvo na posição solicitada
    T get(int pos) const
    {
        return _dados[pos];
    }

    // Retorna a quantidade atual de itens no vetor
    int getTamanho() const
    {
        return _tamanho;
    }
};

#endif // VETOR_DINAMICO_H