# include "rtklib.h"


int main(void){
    obsd_t *obs = malloc(sizeof(obsd_t));
    int n = 1;
    nav_t *nav = malloc(sizeof(nav_t));
    prcopt_t *opt = malloc(sizeof(prcopt_t));
    sol_t *sol = malloc(sizeof(sol_t));
    double az[2] = {1, 3};
    double *azel = az;
    ssat_t *ssat = malloc(sizeof(ssat_t));
    // pntpos();
}