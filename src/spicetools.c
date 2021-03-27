#include "spicetools.h"

const double DAY = 86400.0;

const char *TIME_FORMAT = "YYYY-MON-DD HR:MN::SC ::RND";
const unsigned int TIME_FORMAT_SIZE = 21;

System system_new(char *KERNEL, char *FRAME, char *OBSERVER, char *TARGET,
                  char *START_DATE, double DURATION, char *ABCORR) {
  System system;
  system.KERNEL = KERNEL;
  system.FRAME = FRAME;
  system.OBSERVER = OBSERVER;
  system.TARGET = TARGET;
  system.START_DATE = START_DATE;
  system.DURATION = DURATION;
  system.ABCORR = ABCORR;
  system_load_kernel(&system);
  return system;
}

void system_load_kernel(System *system) { furnsh_c(system->KERNEL); }

void system_unload_kernel(System *system) { unload_c(system->KERNEL); }

SpiceDouble system_get_time_start(System *system) {
  SpiceDouble ephemeris_time;
  str2et_c(system->START_DATE, &ephemeris_time);
  return ephemeris_time;
}

SpiceDouble system_get_time_end(System *system) {
  SpiceDouble ephemeris_time;
  str2et_c(system->START_DATE, &ephemeris_time);
  return ephemeris_time + system->DURATION;
}

SpiceDouble *system_get_position_start(System *system) {
  SpiceDouble *position = malloc(sizeof(SpiceDouble) * 3);
  SpiceDouble light_time;
  SpiceDouble ephemeris_time = system_get_time_start(system);
  spkpos_c(system->TARGET, ephemeris_time, system->FRAME, system->ABCORR,
           system->OBSERVER, position, &light_time);
  return position;
}

SpiceDouble *system_get_position_end(System *system) {
  SpiceDouble *position = malloc(sizeof(SpiceDouble) * 3);
  SpiceDouble light_time;
  SpiceDouble ephemeris_time = system_get_time_end(system);
  spkpos_c(system->TARGET, ephemeris_time, system->FRAME, system->ABCORR,
           system->OBSERVER, position, &light_time);
  return position;
}

unsigned int system_get_number_points(System *system, double time_step) {
  SpiceDouble time_start = system_get_time_start(system);
  SpiceDouble time_end = system_get_time_end(system);
  return size_range_with_step(time_start, time_end, time_step);
}

SpiceDouble *system_get_times(System *system, double time_step) {
  SpiceDouble time_start = system_get_time_start(system);
  SpiceDouble time_end = system_get_time_end(system);
  unsigned int size = system_get_number_points(system, time_step);
  SpiceDouble *times = malloc(sizeof(SpiceDouble) * size);
  for (unsigned int i = 0; i < size; i++) {
    SpiceDouble time = time_start + i * time_step;
    if (time > time_end) {
      time = time_end;
    }
    times[i] = time;
  }
  return times;
}

char **system_get_times_formatted(System *system, double time_step) {
  SpiceDouble time_start = system_get_time_start(system);
  SpiceDouble time_end = system_get_time_end(system);
  unsigned int size = system_get_number_points(system, time_step);
  char **times = malloc(sizeof(char[TIME_FORMAT_SIZE]) * size);
  for (unsigned int i = 0; i < size; i++) {
    SpiceDouble time = time_start + i * time_step;
    if (time > time_end) {
      time = time_end;
    }
    char *time_formatted = malloc(sizeof(TIME_FORMAT_SIZE));
    timout_c(time, TIME_FORMAT, TIME_FORMAT_SIZE + 1, time_formatted);
    times[i] = time_formatted;
  }
  return times;
}

SpiceDouble *system_get_positions(System *system, double time_step) {
  SpiceDouble time_start = system_get_time_start(system);
  SpiceDouble time_end = system_get_time_end(system);
  unsigned int size = system_get_number_points(system, time_step);
  SpiceDouble *positions = malloc(sizeof(SpiceDouble) * size * 3);
  for (unsigned int i = 0; i < size; i++) {
    SpiceDouble *position = malloc(sizeof(SpiceDouble) * 3);
    SpiceDouble light_time;
    SpiceDouble time = time_start + i * time_step;
    if (time > time_end) {
      time = time_end;
    }
    spkpos_c(system->TARGET, time, system->FRAME, system->ABCORR,
             system->OBSERVER, position, &light_time);
    positions[i * 3 + 0] = position[0];
    positions[i * 3 + 1] = position[1];
    positions[i * 3 + 2] = position[2];
  }
  return positions;
}

SpiceDouble *compute_distances(SpiceDouble *positions, unsigned int size) {
  SpiceDouble *distances = malloc(sizeof(SpiceDouble) * size);
  for (unsigned int i = 0; i < size; i++) {
    distances[i] = sqrt(positions[i * 3 + 0] * positions[i * 3 + 0] +
                        positions[i * 3 + 1] * positions[i * 3 + 1] +
                        positions[i * 3 + 2] * positions[i * 3 + 2]);
  }
  return distances;
}
