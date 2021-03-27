#include <stdio.h>
#include "SpiceUsr.h"

void main() {
    #define ABCORR "NONE"
    #define FRAME  "J2000"
    #define LSK    "rsc/NAIF0010.TLS"
    #define DE     "rsc/DE418.BSP"
    #define SPK    "rsc/ORES_______________00125.BSP"
    #define UTC0   "2003-SEP-28 00:00:00"
    #define STEP   3600
    #define MAXITR 24
    #define OBS    "EARTH"
    #define TARGET "SMART-1"

    SpiceInt i;
    SpiceDouble et0, et, dt, lt, d;
    SpiceDouble r[6];

    furnsh_c(LSK);
    furnsh_c(DE);
    furnsh_c(SPK);

    str2et_c(UTC0, &et0);

    printf("%s state vector of %s wrt %s at %s\n", FRAME, TARGET, OBS, UTC0);
    printf("%20s %20s %20s %20s %20s %20s %20s \n", "elapsed time (h)", "x (km)", "y (km)", "z (km)", "vx (km/s)", "vy (km/s)", "vz (km/s)");
    for (i = 0; i <= MAXITR; i++) {
        et = et0 + i*STEP;
        dt = (et - et0) / STEP;
        spkezr_c(TARGET, et, FRAME, ABCORR, OBS, r, &lt);
        printf("%20.0f %20.10f %20.10f %20.10f %20.10f %20.10f %20.10f\n", dt, r[0], r[1], r[2], r[3], r[4], r[5]);
    }
}
