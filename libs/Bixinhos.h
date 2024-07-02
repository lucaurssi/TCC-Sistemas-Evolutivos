
#include <vector>

#ifndef BIXINHO
#define BIXINHO
typedef struct _bixinho{
  float radius;
  float x;
  float y;
  float theta;
  unsigned char r,g,b;
  float vel;
  int shape;
}Bixinho; // Bixinho e menu
#endif

// this struct is here only for convenience
#ifndef SIM_VAR
#define SIM_VAR
typedef struct simulation_variables{
    std::vector<Bixinho> Bixinhos;
    char N; // number of bixinhos being simulated
    char N_menu; // number of bixinhos selected on menu (10, 25, 50, 100)

    char Gene; // gene type: form, color or (form and color)
    char Gene_menu; // (0, 1, 2)
    bool geneMenu;

    char Shape; //  circle, square, triangle
    char Shape_menu; // (0,1,2)
    bool Cor; // black, white
    bool Cor_menu; // false, true

    bool Breed; // asexual, sexual
    bool Breed_menu;  

    bool Mutation; // fixed, variable
    bool Mutation_menu;

    bool Change; // menu redraw flag
    bool Run; // Run button flag
    
} Sim_Var;
#endif


Bixinho CreateBixinho(float x, float y, unsigned char *color);

void drawBixinho(Bixinho bixinho, int gene);

void moveBixinho(Bixinho *bixinho, float distance);

void Repopulate(Sim_Var *SV, bool mutation);



