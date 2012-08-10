//
//  main.c
//  peaksearch
//
//  Created by Paolo Bosetti on 8/7/12.
//  Copyright (c) 2012 Paolo Bosetti. All rights reserved.
//
#include "peaksearch.h"

int main(int argc, const char * argv[])
{
  // data array:
  data_t d[] = {
    1,1,2,1,2,30,32,8,2,1,
    1,1,2,1,2, 2, 1,3,1,1,
    1,1,2,1,2,33,32,8,2,1,
    1,1,2,1,2, 2, 1,3,1,1};

  // PeakSearch structure:
  PeakSearch ps;
  ps.sigmas = 1.0;
  ps.win_size = 5;
  ps.data_s = sizeof(d) / sizeof(data_t);
  ps.data_v = (data_t*) malloc(ps.data_s * sizeof(data_t));
  ps.data_v = d;

  // Result array, initialized to minimum length (will expand automatically)
  index_t *peaks = (index_t*) malloc(sizeof(index_t));

  // Run the search on ps and put results in peaks
  index_t count = search_peaks(&ps, &peaks);

  // Printout:
  printf("Overall st.dev: %f. Found %d peaks\n", ps.stdev, count);
  index_t i;
  for (i=0; i<count; i++) {
    printf("peak %d: point %d, value %f\n", i, peaks[i], ps.data_v[peaks[i]]);
  }

  // Cleanup:
  free(peaks);
  return 0;
}

