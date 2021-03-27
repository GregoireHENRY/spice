#include "tools.h"

unsigned int size_range_with_step(double start, double end, double step) {
  unsigned int size = (end - start) / step;
  if (start + step * size < end) {
    size++;
  }
  return size;
}
