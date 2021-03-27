#include <stdio.h>
#include "SpiceUsr.h"
#include "tools_spice.h"

void main() {
    #define ABCORR "NONE"
    #define FRAME  "J2000"
    #define MK     "/home/greg/rob/hera/kernels/mk/hera_study_PO_EA_2026.tm"
    #define UTC0   "2027-JUN-05 00:00:00"
    #define STEP   60*60
    #define MAXITR 9
    #define OBS    "HERA"
    #define TARGET "DIDYMOON"
    SpiceInt i;
    SpiceDouble et0, et, det0, lt, d;
    SpiceDouble r[3];

    furnsh_c( MK );
    str2et_c( UTC0, &et0);

    printf("DIDYMOON wrt HERA\n"
           "UTC: %s\n", UTC0);
    for (i = 0; i <= MAXITR; i++) {
        et = et0 + i*STEP;
        det0 = (et - et0) / 60;
        spkpos_c( TARGET, et, FRAME, ABCORR, OBS, r, &lt );
        d = distance(r);
        printf("\nT0+%.0fmn\n"
               "distance: %.1f (km)\n",
               det0, d);
    }
}
