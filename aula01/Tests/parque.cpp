#include "parque.h"
#include <vector>

using namespace std;

ParqueEstacionamento:: ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli) :
    lotacao(lot), numMaximoClientes(nMaxCli)
{
    vagas = lot;
}

int ParqueEstacionamento:: posicaoCliente(const string & nome) const
{
    for (int i = 0; i < clientes.size(); i++)
        if (nome == clientes[i].nome) return i;
    return -1;
}

unsigned ParqueEstacionamento :: getNumLugares() const
{
    return lotacao;
}

unsigned ParqueEstacionamento:: getNumMaximoClientes() const
{
    return numMaximoClientes;
}

bool ParqueEstacionamento:: adicionaCliente(const string & nome)
{
    if (clientes.size() == numMaximoClientes || posicaoCliente(nome) != -1) return false;
    InfoCartao info;
    info.nome = nome;
    info.presente = false;
    clientes.push_back(info);
    return true;
}

bool ParqueEstacionamento::entrar(const string &nome)
{
    if (vagas == 0 ) return false;
    int pos = posicaoCliente(nome);
    if (pos == -1) return false;
    if (clientes[pos].presente) return false;
    clientes[pos].presente = true;
    vagas--;
    return true;
}

bool ParqueEstacionamento::retiraCliente(const string &nome)
{
    int pos = posicaoCliente(nome);
    if (pos == -1) return false;
    if (!clientes[pos].presente){
        clientes.erase(clientes.begin() + pos);
        return true;
    }
    return false;
}

unsigned ParqueEstacionamento::getNumLugaresOcupados() const
{
    return lotacao-vagas;
}

unsigned ParqueEstacionamento::getNumClientesAtuais() const
{
    return clientes.size();
}

bool ParqueEstacionamento::sair(const string & nome)
{
    int pos = posicaoCliente(nome);
    if (pos == -1) return false;
    if (clientes[pos].presente == false) return false;
    clientes[pos].presente = false;
    vagas++;
    return true;
}
