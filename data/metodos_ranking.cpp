#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <list>
#include <vector>

#include <fstream>
#include <string>
#include <sstream>

#include "objetos.h"

using namespace std;

//-----------MÉTODOS DE RANKING-------------

void OrdenaVetor(vector <Player> &jogadores){

    string stringAux;
    int menor, aux;

    for(int i=0; i < jogadores.size()-1; i++){
            menor = i;
        for(int j = i+1; j< jogadores.size(); j++){
            if(jogadores[j].pontos > jogadores[menor].pontos){
                menor = j;
            }
        }
        if(i!=menor){
            aux = jogadores[i].pontos;
            stringAux = jogadores[i].nome;

            jogadores[i].pontos = jogadores[menor].pontos;
            jogadores[i].nome = jogadores[menor].nome;

            jogadores[menor].pontos = aux;
            jogadores[menor].nome = stringAux;
        }
    }

}

void CarregaVetor(vector <Player> &jogadores){

    ifstream ARQUIVO;
    ARQUIVO.open("saves.imd");

    string nome;
    string linha;
    int pontos;
    int contaPonto = 0;
    int contaNome = 0;
    int pontosTemp;
    int contaLinha =0;

    if(ARQUIVO.is_open() && ARQUIVO.good()){

            while(!ARQUIVO.fail())
            {
                getline(ARQUIVO,linha);
                if(contaLinha % 2 == 0 )
                {
                    stringstream numero(linha);
                    numero >> pontosTemp;
                    jogadores.at(contaPonto).pontos = pontosTemp;
                    contaPonto++;
                }
                else
                {
                   jogadores.at(contaNome).nome = linha;
                   contaNome++;
                }

                if(contaPonto==jogadores.size() && contaNome == jogadores.size()){break;}
                contaLinha++;

            }

    }
    ARQUIVO.close();
}

int ContaJogadores()
{
    ifstream ARQUIVO;
    ARQUIVO.open("saves.imd");
    string linha;
    int cont=0;
    int contaLinha = 0;

    if(ARQUIVO.is_open() && ARQUIVO.good()){
        while(!ARQUIVO.fail()){
            getline(ARQUIVO,linha);
            if(contaLinha % 2 == 0){
                cont++;
            }
            contaLinha++;
        }
    }
    cont=cont-1;
    return cont;
}

void Recordistas(vector <Player> &jogadores)
{
    vector <Player> recordes(ContaJogadores());
    CarregaVetor(recordes);
    OrdenaVetor(recordes);
    jogadores = recordes;
}
