#include <string>
#include <vector>

#define WHITE 		255,255,255
#define BLACK 		0,0,0
#define GREEN 		25,255,25
#define RED	  		255,25,25
#define BLUE  		25,25,255
#define GREY  		125,125,125
#define LIGHT_GREY 	200,200,200



// muda a cor na variavel
void setColor(unsigned char* color, unsigned char R, unsigned char G, unsigned char B);

// Funções para desenhar polígonos
void retangle(float x, float y, float w, float h, unsigned char*color);
void triangle(float x, float y, float h, float b, unsigned char*color);
void circle(float x, float y, float radius, unsigned char*color);
void strangePolygon(float x, float y, unsigned char*color);
void anotherStrangePolygon(float x, float y, unsigned char*color);


// textos
void RenderString(float x, float y, std::string string);

void draw_basic_menu(std::string title);

void nro_individuos(float x, float y, int Nro_ind);
void tipo_de_gene(float x, float y, int tipoGene, bool geneMenu);
void draw_Selecao(float x, float y, int tipoGene, int Nro_selecao, bool Nro_selecao_2);
void draw_Reproducao(float x, float y, bool blue_crossover);
void draw_Mutacao(float x, float y, bool blue_mutacao);


