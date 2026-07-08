#include "Usuario.h"
#include "Produto.h"
#include "TabelaHash.h"
#include "Compra.h"
#include "Reposicao.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

int main()
{
    std::string linha;
    std::string comando;

    // Contadores para atribuir IDs únicos automaticamente
    int contadorUsuarios = 0;
    int contadorProdutos = 0;
    int contadorCompras = 0;
    int contadorReposicoes = 0;

    // Bancos de dados e Índices Invertidos
    VetorDinamico<Usuario*> usuarios;
    VetorDinamico<Produto*> produtos;
    TabelaHash hashUsuarios;
    TabelaHash hashProdutos;

    VetorDinamico<Compra*> compras;
    VetorDinamico<Reposicao*> reposicoes;
    TabelaHash hashCompras;
    TabelaHash hashReposicoes;

    // Loop principal
    while (std::getline(std::cin, linha))
    {
        if (!linha.empty() && linha.back() == '\r')
        {
            linha.pop_back();
        }

        std::stringstream token(linha);
        if (!(token >> comando)) continue;

        // Cadastro de Usuário: salva o dado e indexa todos os atributos na Hash
        if (comando == "U")
        {
            std::string nome, cidade, estado, nacionalidade;
            int idade;
            token >> nome >> idade >> cidade >> estado >> nacionalidade;

            Usuario* novoUser = new Usuario(contadorUsuarios, nome, idade, cidade, estado, nacionalidade);
            usuarios.inserir(novoUser);

            hashUsuarios.inserir("id:" + std::to_string(contadorUsuarios), contadorUsuarios);
            hashUsuarios.inserir("nome:" + nome, contadorUsuarios);
            hashUsuarios.inserir("idade:" + std::to_string(idade), contadorUsuarios);
            hashUsuarios.inserir("cidade:" + cidade, contadorUsuarios);
            hashUsuarios.inserir("estado:" + estado, contadorUsuarios);
            hashUsuarios.inserir("nacionalidade:" + nacionalidade, contadorUsuarios);

            std::cout << "U " << contadorUsuarios << "\n";
            contadorUsuarios++;
        }
        // Cadastro de Produto: salva o dado e indexa todos os atributos na Hash
        else if (comando == "P")
        {
            std::string nome, precoStr, qtdStr, categoria, marca, condicao;
            token >> nome >> precoStr >> qtdStr >> categoria >> marca >> condicao;

            Produto* novoProd = new Produto(contadorProdutos, nome, std::stod(precoStr), std::stoi(qtdStr), categoria, marca, condicao);
            produtos.inserir(novoProd);

            hashProdutos.inserir("id:" + std::to_string(contadorProdutos), contadorProdutos);
            hashProdutos.inserir("nome:" + nome, contadorProdutos);
            hashProdutos.inserir("categoria:" + categoria, contadorProdutos);
            hashProdutos.inserir("marca:" + marca, contadorProdutos);
            hashProdutos.inserir("condicao:" + condicao, contadorProdutos);

            std::cout << "P " << contadorProdutos << "\n";
            contadorProdutos++;
        }
        // Reposição: adiciona itens ao estoque e atualiza índices de reposição
        else if (comando == "R")
        {
            std::string timestamp;
            token >> timestamp;

            Reposicao* novaRep = new Reposicao(contadorReposicoes, timestamp);
            int id_prod, qtd;

            while (token >> id_prod >> qtd)
            {
                novaRep->adicionarItem(id_prod, qtd);
                produtos.get(id_prod)->alterarQtd(qtd);

                hashReposicoes.inserir("id_produto:" + std::to_string(id_prod), contadorReposicoes);
            }

            reposicoes.inserir(novaRep);

            hashReposicoes.inserir("id:" + std::to_string(contadorReposicoes), contadorReposicoes);
            hashReposicoes.inserir("timestamp:" + timestamp, contadorReposicoes);

            std::cout << "R " << contadorReposicoes << "\n";
            contadorReposicoes++;
        }
        // Compra: verifica disponibilidade, desconta estoque e registra a transação
        else if (comando == "C")
        {
            std::string timestamp;
            int id_usuario;
            token >> timestamp >> id_usuario;

            VetorDinamico<ItemTransacao> itensTemp;
            int id_p, qtd;
            bool compraValida = true;

            // Validação de estoque antes de efetivar a compra
            while (token >> id_p >> qtd)
            {
                ItemTransacao item = {id_p, qtd};
                itensTemp.inserir(item);
                if (id_p >= contadorProdutos || produtos.get(id_p)->getQtd() < qtd) compraValida = false;
            }

            if (compraValida)
            {
                Compra* novaCompra = new Compra(contadorCompras, timestamp, id_usuario);
                for (int i = 0; i < itensTemp.getTamanho(); ++i)
                {
                    ItemTransacao item = itensTemp.get(i);
                    novaCompra->adicionarItem(item.id_produto, item.qtd);
                    produtos.get(item.id_produto)->alterarQtd(-item.qtd);

                    hashCompras.inserir("id_produto:" + std::to_string(item.id_produto), contadorCompras);
                }

                compras.inserir(novaCompra);

                hashCompras.inserir("id:" + std::to_string(contadorCompras), contadorCompras);
                hashCompras.inserir("timestamp:" + timestamp, contadorCompras);
                hashCompras.inserir("id_usuario:" + std::to_string(id_usuario), contadorCompras);

                std::cout << "C " << contadorCompras << "\n";
                contadorCompras++;
            }
            else std::cout << "C INV\n";
        }
        // Consultas (LU, LP, LC, LR): utilizam a técnica de Dois Ponteiros para interseção linear
        else if (comando == "LU")
        {
            std::string atributo, valor;

            if (!(token >> atributo >> valor)) continue;

            std::string chaveBusca = atributo + ":" + valor;
            VetorDinamico<int>* resultado = hashUsuarios.buscar(chaveBusca);
            VetorDinamico<int>* intersecao = nullptr;

            while (token >> atributo >> valor)
            {
                chaveBusca = atributo + ":" + valor;
                VetorDinamico<int>* prox = hashUsuarios.buscar(chaveBusca);
                VetorDinamico<int>* nova = new VetorDinamico<int>();

                if (resultado && prox)
                {
                    int i = 0, j = 0;
                    while (i < resultado->getTamanho() && j < prox->getTamanho())
                    {
                        if (resultado->get(i) == prox->get(j))
                        {
                            nova->inserir(resultado->get(i));
                            i++; j++;
                        }
                        else if (resultado->get(i) < prox->get(j)) i++;
                        else j++;
                    }
                }

                if (intersecao) delete intersecao;
                intersecao = nova;
                resultado = intersecao;
            }

            if (!resultado || resultado->getTamanho() == 0)
            {
                std::cout << "LU VAZIO\n";
            }
            else
            {
                for (int i = 0; i < resultado->getTamanho(); ++i)
                {
                    int idFinal = resultado->get(i);
                    Usuario* u = usuarios.get(idFinal);

                    std::cout << "LU resultado_" << (i + 1) << " usuario " << u->getId() << " "
                              << u->getNome() << " " << u->getIdade() << " "
                              << u->getCidade() << " " << u->getEstado() << " "
                              << u->getNacionalidade() << "\n";

                    int* prodComprados = new int[contadorProdutos]();
                    bool comprouAlgo = false;

                    for (int c = 0; c < compras.getTamanho(); ++c)
                    {
                        Compra* compra = compras.get(c);
                        if (compra->getIdUsuario() == idFinal)
                        {
                            VetorDinamico<ItemTransacao>* carrinho = compra->getCarrinho();
                            for (int itemIdx = 0; itemIdx < carrinho->getTamanho(); ++itemIdx)
                            {
                                prodComprados[carrinho->get(itemIdx).id_produto] += carrinho->get(itemIdx).qtd;
                                comprouAlgo = true;
                            }
                        }
                    }

                    if (comprouAlgo)
                    {
                        int pCount = 1;
                        bool primeiro = true;
                        for (int p = 0; p < contadorProdutos; ++p)
                        {
                            if (prodComprados[p] > 0)
                            {
                                if (!primeiro) std::cout << " ";
                                std::cout << "produto_" << pCount << " " << p << " " << prodComprados[p];
                                pCount++;
                                primeiro = false;
                            }
                        }
                        std::cout << "\n";
                    }

                    delete[] prodComprados;
                }
            }
        }
        else if (comando == "LP")
        {
            std::string atributo, valor;

            if (!(token >> atributo >> valor)) continue;

            std::string chaveBusca = atributo + ":" + valor;
            VetorDinamico<int>* resultado = hashProdutos.buscar(chaveBusca);
            VetorDinamico<int>* intersecao = nullptr;

            while (token >> atributo >> valor)
            {
                std::string novaChave = atributo + ":" + valor;
                VetorDinamico<int>* prox = hashProdutos.buscar(novaChave);
                VetorDinamico<int>* nova = new VetorDinamico<int>();

                if (resultado && prox)
                {
                    int i = 0, j = 0;
                    while (i < resultado->getTamanho() && j < prox->getTamanho())
                    {
                        if (resultado->get(i) == prox->get(j))
                        {
                            nova->inserir(resultado->get(i));
                            i++; j++;
                        }
                        else if (resultado->get(i) < prox->get(j)) i++;
                        else j++;
                    }
                }

                intersecao = nova;
                resultado = intersecao;
            }

            if (!resultado || resultado->getTamanho() == 0)
            {
                std::cout << "LP VAZIO\n";
            }
            else
            {
                for (int i = 0; i < resultado->getTamanho(); ++i)
                {
                    int idFinal = resultado->get(i);
                    Produto* p = produtos.get(idFinal);

                    std::cout << "LP resultado_" << (i + 1) << " produto " << p->getId() << " "
                              << p->getNome() << " "
                              << std::fixed << std::setprecision(2) << p->getPreco() << " "
                              << p->getQtd() << " " << p->getCategoria() << " "
                              << p->getMarca() << " " << p->getCondicao() << "\n";

                    int* usersCompradores = new int[contadorUsuarios]();
                    bool foiComprado = false;

                    for (int c = 0; c < compras.getTamanho(); ++c)
                    {
                        Compra* compra = compras.get(c);
                        VetorDinamico<ItemTransacao>* carrinho = compra->getCarrinho();

                        for (int itemIdx = 0; itemIdx < carrinho->getTamanho(); ++itemIdx)
                        {
                            if (carrinho->get(itemIdx).id_produto == idFinal)
                            {
                                usersCompradores[compra->getIdUsuario()] += carrinho->get(itemIdx).qtd;
                                foiComprado = true;
                            }
                        }
                    }

                    if (foiComprado)
                    {
                        int uCount = 1;
                        bool primeiro = true;

                        for (int u = 0; u < contadorUsuarios; ++u)
                        {
                            if (usersCompradores[u] > 0)
                            {
                                if (!primeiro) std::cout << " ";
                                std::cout << "usuario_" << uCount << " " << u << " " << usersCompradores[u];
                                uCount++;
                                primeiro = false;
                            }
                        }
                        std::cout << "\n";
                    }

                    delete[] usersCompradores;
                }
            }

            if (intersecao) delete intersecao;
        }
        else if (comando == "LC")
        {
            std::string atributo, valor;

            if (!(token >> atributo >> valor)) continue;

            std::string chaveBusca = atributo + ":" + valor;
            VetorDinamico<int>* resultado = hashCompras.buscar(chaveBusca);
            VetorDinamico<int>* intersecao = nullptr;

            while (token >> atributo >> valor)
            {
                std::string novaChave = atributo + ":" + valor;
                VetorDinamico<int>* prox = hashCompras.buscar(novaChave);
                VetorDinamico<int>* nova = new VetorDinamico<int>();

                if (resultado && prox)
                {
                    int i = 0, j = 0;
                    while (i < resultado->getTamanho() && j < prox->getTamanho())
                    {
                        if (resultado->get(i) == prox->get(j))
                        {
                            nova->inserir(resultado->get(i));
                            i++; j++;
                        }
                        else if (resultado->get(i) < prox->get(j)) i++;
                        else j++;
                    }
                }

                intersecao = nova;
                resultado = intersecao;
            }

            if (!resultado || resultado->getTamanho() == 0)
            {
                std::cout << "LC VAZIO\n";
            }
            else
            {
                for (int i = 0; i < resultado->getTamanho(); ++i)
                {
                    int idFinal = resultado->get(i);
                    Compra* c = compras.get(idFinal);

                    std::cout << "LC resultado_" << (i + 1) << " compra " << c->getId()
                              << " timestamp " << c->getTimestamp()
                              << " usuario " << c->getIdUsuario() << "\n";

                    int* prodNaCompra = new int[contadorProdutos]();
                    VetorDinamico<ItemTransacao>* carrinho = c->getCarrinho();

                    for (int itemIdx = 0; itemIdx < carrinho->getTamanho(); ++itemIdx)
                    {
                        prodNaCompra[carrinho->get(itemIdx).id_produto] += carrinho->get(itemIdx).qtd;
                    }

                    int pCount = 1;
                    bool primeiro = true;
                    for (int p = 0; p < contadorProdutos; ++p)
                    {
                        if (prodNaCompra[p] > 0)
                        {
                            if (!primeiro) std::cout << " ";
                            std::cout << "produto_" << pCount << " " << p << " " << prodNaCompra[p];
                            pCount++;
                            primeiro = false;
                        }
                    }
                    std::cout << "\n";
                    delete[] prodNaCompra;
                }
            }
        }
        else if (comando == "LR")
        {
            std::string atributo, valor;

            if (!(token >> atributo >> valor)) continue;

            std::string chaveBusca = atributo + ":" + valor;
            VetorDinamico<int>* resultado = hashReposicoes.buscar(chaveBusca);
            VetorDinamico<int>* intersecao = nullptr;

            while (token >> atributo >> valor)
            {
                std::string novaChave = atributo + ":" + valor;
                VetorDinamico<int>* prox = hashReposicoes.buscar(novaChave);
                VetorDinamico<int>* nova = new VetorDinamico<int>();

                if (resultado && prox)
                {
                    int i = 0, j = 0;
                    while (i < resultado->getTamanho() && j < prox->getTamanho())
                    {
                        if (resultado->get(i) == prox->get(j))
                        {
                            nova->inserir(resultado->get(i));
                            i++; j++;
                        }
                        else if (resultado->get(i) < prox->get(j)) i++;
                        else j++;
                    }
                }

                intersecao = nova;
                resultado = intersecao;
            }

            if (!resultado || resultado->getTamanho() == 0)
            {
                std::cout << "LR VAZIO\n";
            }
            else
            {
                for (int i = 0; i < resultado->getTamanho(); ++i)
                {
                    int idFinal = resultado->get(i);
                    Reposicao* r = reposicoes.get(idFinal);

                    std::cout << "LR resultado_" << (i + 1) << " reposicao " << r->getId()
                              << " timestamp " << r->getTimestamp() << "\n";

                    int* prodNaRep = new int[contadorProdutos]();
                    VetorDinamico<ItemReposicao>* lote = r->getLote();

                    for (int itemIdx = 0; itemIdx < lote->getTamanho(); ++itemIdx)
                    {
                        prodNaRep[lote->get(itemIdx).id_produto] += lote->get(itemIdx).qtd;
                    }

                    int pCount = 1;
                    bool primeiro = true;
                    for (int p = 0; p < contadorProdutos; ++p)
                    {
                        if (prodNaRep[p] > 0)
                        {
                            if (!primeiro) std::cout << " ";
                            std::cout << "produto_" << pCount << " " << p << " " << prodNaRep[p];
                            pCount++;
                            primeiro = false;
                        }
                    }
                    std::cout << "\n";
                    delete[] prodNaRep;
                }
            }
        }
    }

    return 0;
}