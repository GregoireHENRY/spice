#ifndef SPICETOOLS_H
#define SPICETOOLS_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "SpiceUsr.h"
#include "tools.h"

/* Duration of day, in seconds. */
extern const double DAY;

/* String that specifies how the ephemeris time should be represented. */
const char *TIME_FORMAT;

/* Size of TIME_FORMAT. */
const unsigned int TIME_FORMAT_SIZE;

typedef struct {
  /* Path of the meta-kernel. */
  char *KERNEL;
  /* Name of the reference frame. */
  char *FRAME;
  /* Name of the observer. */
  char *OBSERVER;
  /* Name of the target. */
  char *TARGET;
  /* Date of the start of the window to get the data. */
  char *START_DATE;
  /* Duration of the window to get the data, in seconds. */
  double DURATION;
  /* Abberation correction. */
  char *ABCORR;
} System;

/* System constructor. */
System system_new(char *, char *, char *, char *, char *, double, char *);

/* Load the kernel. */
void system_load_kernel(System *);

/* Unload the kernel. This function MUST be called at the end of your program to
 * avoir conflicts. */
void system_unload_kernel(System *);

/* Get the ephemeris time of the start date, in seconds. */
SpiceDouble system_get_time_start(System *);

/* Get the ephemeris time of the end date, in seconds. */
SpiceDouble system_get_time_end(System *);

/* Get the position of the target with respect to the observer in the reference
 * frame at the start date, in kilometers. */
SpiceDouble *system_get_position_start(System *);

/* Get the position of the target with respect to the observer in the reference
 * frame at the end date, in kilometers. */
SpiceDouble *system_get_position_end(System *);

unsigned int system_get_number_points(System *, double);

/* Get all ephemeris times in the date range with given time step. */
SpiceDouble *system_get_times(System *, double);

/* Get all ephemeris times formatted to string in the date range with given time
 * step. */
char **system_get_times_formatted(System *, double);

/* Get all positions of the target with respect to the observer in the
 * reference frame, in kilometers. */
SpiceDouble *system_get_positions(System *, double);

/* Compute euclidian distance from cartesian position array. */
SpiceDouble *compute_distances(SpiceDouble *, unsigned int);

#endif
