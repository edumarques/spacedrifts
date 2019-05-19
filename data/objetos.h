
//---------OBJETOS-----------

enum IDS {JOGADOR,BOLAS,BONUS,INIMIGO,ESTRELA,BOTAO};


struct Player
{
    std::string nome;
    int pontos;
};

struct CursorBola
{
    ALLEGRO_BITMAP *imagem;

    int ID;
    int x;
    int y;
    unsigned int vidas;
    unsigned int pontos;
    unsigned int nivel;
};

struct Bolas
{
    ALLEGRO_BITMAP *imagem;

    int ID;
    float x;
    float y;
    float velocidade;
    bool ativo;
};

struct Estrelas
{
    int ID;
    int x;
    int y;
    int velocidade;
};

struct Botao
{
    int ID;
    int x;
    int y;
    int largura;
    int altura;

};

