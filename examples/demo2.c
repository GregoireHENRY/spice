#include <stdio.h>
#include "SpiceUsr.h"
#include "tools_spice.h"

void main() {
    #define AU     149597870.7
    #define ABCORR "NONE"
    #define FRAME  "J2000"
    #define MK     "/home/greg/proj/hera-pmi/kernels/mk/hera_study.tm"
    #define UTC0   "2019-OCT-16 00:00:00"
    #define STEP   86400*31;
    #define MAXITR 0
    #define OBS    "SUN"
    #define TARGET "EARTH"
    SpiceInt i;
    SpiceDouble et0, et, det0, lt, d;
    SpiceDouble r[3];
    furnsh_c( MK );
    str2et_c( UTC0, &et0);

    printf("EARTH wrt SUN\n"
           "UTC: %s\n", UTC0);
    for (i = 0; i <= MAXITR; i++) {
        et = et0 + i*STEP;
        det0 = (et - et0) / 60;
        spkpos_c( TARGET, et, FRAME, ABCORR, OBS, r, &lt );
        d = distance(r) / AU;
        printf("\nT0+%.0fmn\n"
               "distance in AU: %10.10f (km)\n",
               det0, d);
    }
}
