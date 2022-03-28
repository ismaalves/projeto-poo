#include <iostream>
#include <string> // Necessário para usar strings
#include <ctime>
#include <algorithm>

using namespace std;

#define NC "\e[0m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"

int tamanho_palavra(){
    int tam;
    cout << "Quantidade de letras na palavra (5,6 ou 7): " << endl;
    cin >> tam;
    return tam;
}

int aleatorio(){
    unsigned seed = time(0);
    srand(seed);
    int pos = rand()%19;
    return pos;
}

string palavra_5l(int pos){
    string a[20] = {"SAGAZ","AMAGO","EXITO","MEXER","TERMO",
                    "SENSO","NOBRE","ALGOZ","AFETO","PLENA",
                    "ETICA","MUTUA","SUTIL","TENUE","VIGOR",
                    "AMIGO","AUDAZ","FAZER","SANAR","TEMPO"};
    return a[pos];
}

string palavra_6l(int pos){
    string a[20] = {"MERITO","ALUSAO","CASUAL","ANSEIO","PRESSA",
                    "ALHEIO","IDIOTA","HOSTIL","NOCIVO","LEGADO",
                    "INFAME","CETICO","GENTIL","EXIMIO","AFAVEL",
                    "CLICHE","ADORNO","PAIXAO","DADIVA","ADESAO"};
    return a[pos];
}

string palavra_7l(int pos){
    string a[20] = {"EMPATIA","EMBUSTE","VERBETE","SUBLIME","SUCINTO",
                    "RECESSO","REDIMIR","ESTIGMA","CINISMO","CULTURA",
                    "VIRTUDE","SOBERBA","ASPECTO","IMPUTAR","MITIGAR",
                    "DEBOCHE","CANDURA","ALMEJAR","SUCESSO","ALEGRIA"};
    return a[pos];
}

string capitalizeString(string s){
    transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return toupper(c); });
    return s;
}

int main(){
  int tam_palavra = tamanho_palavra();
  string palavra_mister;
  string palavra_player;
  
  if(tam_palavra == 5){
    palavra_mister = palavra_5l(aleatorio());
  }
  else if(tam_palavra == 6){
    palavra_mister = palavra_6l(aleatorio());
  }
  else if(tam_palavra == 7){
    palavra_mister = palavra_7l(aleatorio());
  }
  else{
    return 0;
  }
  
	for(int i = 0; i < 7; i++){
    cout << NC "\nDigite uma palavra com "<< tam_palavra <<" letras: ";
    getline(cin, palavra_player);
    palavra_player = capitalizeString(palavra_player);

    for(int j = 0; j < tam_palavra; j++){
      size_t found = palavra_mister.find(palavra_player[j]);
      if (found!=string::npos){
        if(found == j){
          cout << GRN << palavra_player[j];
        }else{
          cout << YEL << palavra_player[j];
        }
      }
      else{
        cout << RED << palavra_player[j];
      }
    }

    size_t found2 = palavra_player.find(palavra_mister);
    if (found2 != string::npos){
      cout << NC "\nPARABÉNS VOCÊ ACERTOU A PALAVRA: " <<palavra_mister<< endl;
      return 0;
    }
    
  }
  cout << NC "\nA PALAVRA ERA: " << palavra_mister << endl;
}

/*
Strings: https://www.inf.pucrs.br/~flash/lapro2ec/aulas/aula_strings.html
Strings: https://pt.wikibooks.org/wiki/Programar_em_C%2B%2B/Manipulando_strings
Array de Strings: https://www.geeksforgeeks.org/array-strings-c-3-different-ways-create/
String colorida: https://www.delftstack.com/pt/howto/cpp/how-to-colorize-output-in-console-cpp/
String maiuscula: https://www.delftstack.com/pt/howto/cpp/how-to-convert-string-to-uppercase-cpp/#utilize-stdtransform-e-stdtoupper-para-converter-uma-string-em-mai%25C3%25BAsculas
Gerar numeros aleatórios: https://www.cmmprogressivo.net/2019/12/Como-Gerar-Numeros-Aleatorios-Randomicos-rand-srand.html
*/
