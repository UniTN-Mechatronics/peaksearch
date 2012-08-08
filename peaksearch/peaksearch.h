//
//  peaksearch.h
//  peaksearch
//
//  Created by Paolo Bosetti on 8/8/12.
//  Copyright (c) 2012 Paolo Bosetti. All rights reserved.
//

#ifndef peaksearch_peaksearch_h
#define peaksearch_peaksearch_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define FULL    0
#define PARTIAL 1

// Types for data and indexes:
typedef float     data_t;
typedef u_int16_t index_t;

// Structure holding algorithm data and parameters:
struct PeakSearch {
  data_t  *data_v;   // vector of data
  index_t  data_s;   // number of data points
  data_t   sigmas;   // number of sigmas defining the threshold
  index_t  win_size; // moving windows size
  data_t   stdev;    // search_peaks() will put here the overal st.dev.
};


// FOR INTERNAL USE
struct Statistics {
  data_t  mean;
  data_t  sd;
  data_t  max;
  index_t max_idx;
};

// FOR INTERNAL USE
data_t
mean(struct PeakSearch *ps, const index_t start, const index_t end);

// FOR INTERNAL USE
void
statistics(struct PeakSearch *ps, const index_t start, char const type, struct Statistics *stat);

// Performs the peak search on the data and according to the parameters in ps.
// The indexes of found peaks are returned in peaks_v.
// ps.stdev will be loaded with the overall standard deviation.
index_t
search_peaks(struct PeakSearch *ps, index_t **peaks_v);


#endif
