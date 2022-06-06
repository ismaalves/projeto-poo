#include <stdio.h>
#include <stdlib.h>
#include "classes.cpp"
#include <fstream>

int main(){
    std::string NomeJogador;
    int qtdletras;
    
    std::cout <<NC"Nome do jogador: "<< std::endl;
    std::cin >> NomeJogador;
    std::cout <<NC"Com quantas letras você quer jogar? (5,6,7) " << std::endl;
    std::cin >> qtdletras;
    
    std::string palavra;
    Jogo jogo1(NomeJogador, qtdletras);
    
    while(jogo1.getFimdejogo() && jogo1.player->getTentativas() > 0){
        std::cout <<NC"\nDigite sua palavra de "<< jogo1.palavra_resposta->getTamanho() << " letras: "<< std::endl;
        std::cin >> palavra;
        jogo1.palavra_player->setPalavra(palavra);
        jogo1.comparaLetras(); jogo1.testaPalavras();
    }
    jogo1.mensagemFinal();
    
}