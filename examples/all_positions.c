/* Position of TARGET wrt to OBS at UTC0 for MAXITR iterations of STEPS
 * STEP_ABRV steps.
 */

#include <stdio.h>

#include "SpiceUsr.h"
#include "spicetools.h"
#include "tools.h"

int main() {
  System system =
      system_new("rsc/data/hera_PO_EMA_2024.tm", "J2000", "HERA", "DIMORPHOS",
                 "2027-MAR-23 16:00:00", 129.0 * DAY, "NONE");

  double time_step = 1.0 * DAY;

  SpiceDouble *positions = system_get_positions(&system, time_step);
  unsigned int size = system_get_number_points(&system, time_step);

  SpiceDouble *distances = compute_distances(positions, size);
  char **times = system_get_times_formatted(&system, time_step);

  for (unsigned int i = 0; i < size; i++) {
    printf("%s -> %.2f km\n", times[i], distances[i]);
  }

  system_unload_kernel(&system);
  return 0;
}
