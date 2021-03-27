/* Position of TARGET wrt to OBS at UTC0 for MAXITR iterations of STEPS
 * STEP_ABRV steps.
 */

#include <stdio.h>

#include "SpiceUsr.h"
#include "spicetools.h"
#include "tools.h"

int main() {
  System system =
      new_system("rsc/data/hera_PO_EMA_2024.tm", "J2000", "HERA", "DIMORPHOS",
                 "2027-MAR-23 16:00:00", 14.0 * DAY, "NONE");

  SpiceDouble *pos = get_position_start(&system);
  printf("%f %f %f\n", pos[0], pos[1], pos[2]);

  unload_kernel(&system);
  return 0;
}
