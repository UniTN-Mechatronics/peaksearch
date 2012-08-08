//
//  main.c
//  peaksearch
//
//  Created by Paolo Bosetti on 8/7/12.
//  Copyright (c) 2012 Paolo Bosetti. All rights reserved.
//
#include "peaksearch.h"
#define LENGTH 40

int main(int argc, const char * argv[])
{
  struct PeakSearch ps;
  ps.sigmas = 1.0;
  ps.win_size = 5;
  ps.data_s = LENGTH;
  ps.data_v = (data_t*) malloc(ps.data_s * sizeof(data_t));
  data_t d[LENGTH] = {
    1,1,2,1,2,30,32,8,2,1,
    1,1,2,1,2, 2, 1,3,1,1,
    1,1,2,1,2,33,32,8,2,1,
    1,1,2,1,2, 2, 1,3,1,1};
  ps.data_v = d;

  index_t *peaks = (index_t*) malloc(1 * sizeof(index_t));
  index_t count = search_peaks(&ps, &peaks);

  printf("Overall st.dev: %f. Found %d peaks\n", ps.stdev, count);
  index_t i;
  for (i=0; i<count; i++) {
    printf("peak %d: point %d, value %f\n", i, peaks[i], ps.data_v[peaks[i]]);
  }
  free(peaks);
  return 0;
}

