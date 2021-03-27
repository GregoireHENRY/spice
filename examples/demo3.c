/* Position of TARGET wrt to OBS at UTC0 for MAXITR iterations of STEPS
 * STEP_ABRV steps.
 */

#include <stdio.h>
#include "SpiceUsr.h"
#include "spicetools.h"

int main() {
    #define ABCORR "NONE"
    #define FRAME  "J2000"
    #define MK     "rsc/data/hera_PO_EMA_2024.tm"
    #define UTC0   "2027-03-23 16:00:00"
    #define STEP   86400
    #define MAXITR 42
    #define OBS    "HERA"
    #define TARGET "DIDYMOS"
    char STEP_ABRV[1] = "j";
    SpiceInt i;
    SpiceDouble et0, et, det0, lt, d;
    SpiceDouble r[3];

    furnsh_c( MK );
    str2et_c( UTC0, &et0);

    printf("%s wrt %s\n"
           "UTC: %s\n", TARGET, OBS, UTC0);
    for (i = 0; i <= MAXITR; i++) {
        et = et0 + i * STEP;
        det0 = (et - et0) / STEP;
        spkpos_c( TARGET, et, FRAME, ABCORR, OBS, r, &lt );
        d = distance(r);
        printf("\nT0+%.0f%s\n"
               "distance: %.1f (km)\n",
               det0, STEP_ABRV, d);
    }

    return 0;
}
