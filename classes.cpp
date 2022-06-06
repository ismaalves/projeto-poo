#include <ctime>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <stdexcept>
#include <string.h>
#include <fstream>

#define NC "\e[0m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"

class Jogador{
    private:
        std::string nome;
        int pontuacao;
        int tentativas;
    public:
        Jogador(){}
        Jogador(std::string nome){
            this->setNome(nome);
            this->setPontuacao(1000);
            this->setTentativas(5);
        };
        
        void setNome(std::string name){
            std::string padrao = "Jogador 1";
            try{
                if(name.size() > 20){
                    throw std::overflow_error("Nome muito grande");
                }
                else{
                    this->nome = name;
                }  
            }
            catch (std::overflow_error& e) {
                //std::cout << "exception capturada::" << e.what() << '\n';
                this->nome = padrao;
            }
            
        }
        std::string getNome(){
            return this->nome;
        }

        void diminuiPontuacao(){
            this->pontuacao -= 200;
        }
        void setPontuacao(int pont){
            this->pontuacao = pont;
        }
        int getPontuacao(){
            return this->pontuacao;
        }

        void diminuiTentativas(){
            this->tentativas -= 1;
        }
        void setTentativas(int tent){
            this->tentativas = tent;
        }
        int getTentativas(){
            return this->tentativas;
        }
        virtual ~Jogador(){};
};

class Palavra{
    private:
        std::string palavra;
    public:
        Palavra(){};
        Palavra(std::string text){
            this->setPalavra(text);
        };

        std::string capitalizeString(std::string s){
            transform(s.begin(), s.end(), s.begin(),[](unsigned char c){return toupper(c);});
            return s;
        }
        
        void setPalavra(std::string palavra){
            this->palavra = capitalizeString(palavra);
        }
        std::string getPalavra(){
            return palavra;
        }

        virtual ~Palavra(){};
};

class PalavraSort: public Palavra{
    private:
        int tamanho;
    public:
        void setTamanho(int tam){
            if(tam >= 5 && tam <=7){
                this->tamanho = tam;
            }
            else{
                this->tamanho = 5;
            }
        }
        int getTamanho(){
            return this->tamanho;
        }

        PalavraSort(int tam):Palavra(sorteiaPalavra(tam)){
            setTamanho(tam);
        }

        int aleatorio(){
            unsigned seed = time(0);
            srand(seed);
            int pos = rand()%19;
            return pos;
        }
        
        std::string sorteiaPalavra(int tam){
            std::string arq;
            std::string sort;
            int pos = aleatorio();
            if(tam == 5){
                arq = "letras5.txt";
            }
            else if(tam == 6){
                arq = "letras6.txt";
            }
            else if(tam == 7){
                arq = "letras6.txt";
            }
            else{
                std::cout << "Fora dos limites. Tamanho definido como 5" << std::endl;
                arq = "letras5.txt";
            }
            std::ifstream objarq = std::ifstream(arq,std::ios::in);
            objarq.seekg(((tam+1)*pos));
            char ch;
            for(int i = 0; i < tam; i++){
                objarq.get(ch);
                sort = sort+ch;
            }
            objarq.close();
            return sort;
        }
};

class Jogo{
    private:
        int fimdejogo;
    public:
        Jogador *player;
        Palavra *palavra_player;
        PalavraSort *palavra_resposta;

        Jogo(){};
        Jogo(std::string nome, int tam){
            player = new Jogador(nome);
            palavra_resposta = new PalavraSort(tam);
            palavra_player = new Palavra();
            fimdejogo = 1;
        };

        int getFimdejogo(){
            return this->fimdejogo;
        }
        void setFimdejogo(int fim){
            this->fimdejogo = fim;
        }
        //Função que compara letra a letra, para colorir
        void comparaLetras(){
            for(int j = 0; j < palavra_resposta->getTamanho(); j++){
                size_t found = palavra_resposta->getPalavra().find(palavra_player->getPalavra()[j]);
                if (found != std::string::npos){
                    if(found == j){
                        std::cout << GRN << palavra_player->getPalavra()[j];
                    }
                    else{
                        found = palavra_resposta->getPalavra().find(palavra_player->getPalavra()[j], found+1);
                        if(found == j){std::cout << GRN << palavra_player->getPalavra()[j];}
                        else{std::cout << YEL << palavra_player->getPalavra()[j];}
                    }
                }
                else{
                    std::cout << RED << palavra_player->getPalavra()[j];
                }
            }
        }
        
        //Função que compara se as duas palavras são iguais
        void testaPalavras(){
            size_t found = palavra_player->getPalavra().find(palavra_resposta->getPalavra(), 0);
            if (found != std::string::npos){
                setFimdejogo(0);
            }else{
                player->diminuiTentativas();
                player->diminuiPontuacao();
            }
        }

        void mensagemFinal(){
            std::cout << NC"\nFim de jogo" << std::endl;
            if(player->getTentativas() > 0){
                std::cout <<NC"\nPARABÉNS " << player->getNome()<< " VOCÊ ACERTOU A PALAVRA: " GRN <<palavra_resposta->getPalavra()<< std::endl;
                std::cout << NC "Pontuação: " << player->getPontuacao()<< std::endl;
            }
            else{
                std::cout <<NC"\nA PALAVRA ERA: " << palavra_resposta->getPalavra()<< std::endl;
                std::cout << NC "Jogador: " << player->getNome() << std::endl;
                std::cout << NC "Pontuação: " << player->getPontuacao()<< std::endl;
            }
        }
        virtual ~Jogo(){};
};