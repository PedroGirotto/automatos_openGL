#include <iostream>
#include <string>

class EstadoAutomato
{
    private:
        std::string nome;
        EstadoAutomato* simboloA;
        EstadoAutomato* simboloB;
        bool estadoFinal;

    public:
        EstadoAutomato()
        {
            nome = "";
            simboloA = NULL;
            simboloB = NULL;
            estadoFinal = false;
        }

        EstadoAutomato(std::string _Nome, EstadoAutomato* _A, EstadoAutomato* _B, bool _Final)
        {
            nome = _Nome;
            simboloA = _A;
            simboloB = _B;
            estadoFinal = _Final;
        }

        void setNome(std::string _Nome)
        {
            nome = _Nome;
        }
        std::string getNome()
        {
            return nome;
        }

        void setSimboloA(EstadoAutomato* _Estado)
        {
            simboloA = _Estado;
        }
        EstadoAutomato* getSimboloA()
        {
            return simboloA;
        }

        void setSimboloB(EstadoAutomato* _Estado)
        {
            simboloB = _Estado;
        }
        EstadoAutomato* getSimboloB()
        {
            return simboloB;
        }

        void setEstadoFinal(bool _Valor)
        {
            estadoFinal = _Valor;
        }
        bool getEstadoFinal()
        {
            return estadoFinal;
        }

};

EstadoAutomato* FuncaoTransicao(char simbolo, EstadoAutomato* estadoAtual)
{
    if(simbolo == 'a')
    {
        return estadoAtual->getSimboloA();
    }
    else if(simbolo == 'b')
    {
        return estadoAtual->getSimboloB();
    }
    else
    {
        return NULL;
    }
}

void IniciarPrograma(EstadoAutomato& EstadoInicial)
{
    void* EstadoAtual = &EstadoInicial;

    std::string textoEntrada;

    int posicao = 0;
    char simboloLido;

    std::cout << "Digite uma palavra {a, b}: ";
    std::cin >> textoEntrada;

    std::cout << "\nEstado Atual: " << EstadoAtual << "\n";
    std::cout << "Palavra de entrada: " << textoEntrada << "\n\n";

    while(posicao < textoEntrada.length())
    {
        simboloLido = (char) textoEntrada[posicao];
        
        EstadoAtual = FuncaoTransicao(simboloLido, (EstadoAutomato*) EstadoAtual);
        std::cout << "Estado Atual: " << EstadoAtual << "\n";

        if(EstadoAtual == NULL)
        {
            break;
        }

        textoEntrada.replace(posicao, 1, ((EstadoAutomato*) EstadoAtual)->getNome());
        std::cout << textoEntrada << "\n\n";

        textoEntrada[posicao] = simboloLido;
        posicao++;
    }

    if(EstadoAtual != NULL && ((EstadoAutomato*) EstadoAtual)->getEstadoFinal())
    {
        std::cout << "Palavra aceita!\n";
    }
    else
    {
        std::cout << "Palavra rejeitada!\n";
    }
}

std::ostream& operator<<(std::ostream& os, EstadoAutomato& Estado)
{
    os << "Estado: " << Estado.getNome() << " >>> " << &Estado;
    os << " Apontando: " << Estado.getSimboloA() << " | " << Estado.getSimboloB() << "\n";
    return os;
}

int main()
{
    // Criando e Configurando os estados
    EstadoAutomato Q1;
    EstadoAutomato Q2;
    EstadoAutomato Q3;
    EstadoAutomato Q4;

    Q1.setNome("1");
    Q1.setSimboloA(&Q2);
    Q1.setSimboloB(&Q3);
    
    Q2.setNome("2");
    Q2.setSimboloA(&Q1);
    Q2.setSimboloB(&Q4);

    Q3.setNome("3");
    Q3.setSimboloA(&Q4);
    Q3.setSimboloB(&Q1);

    Q4.setNome("4");
    Q4.setSimboloA(&Q3);
    Q4.setSimboloB(&Q2);
    Q4.setEstadoFinal(true);

    // Analisando as alocações de memória
    std::cout << "-----------------------------------------------------------------------\n";
    std::cout << "Estado: x >>> 0xMemoEndereço Apontando: SimboloLidoA   | SimboloLidoB  \n\n";
    std::cout << Q1;
    std::cout << Q2;
    std::cout << Q3;
    std::cout << Q4;
    std::cout << "-----------------------------------------------------------------------\n\n";

    // Iniciando o automato
    IniciarPrograma(Q1);
    
    return 0;
}