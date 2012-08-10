//
//  peaksearch.h
//  peaksearch
//
//  Created by Paolo Bosetti on 8/8/12.
//  Copyright (c) 2012 Paolo Bosetti. All rights reserved.
//

#ifndef PEAKSEARCH_H
#define PEAKSEARCH_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Whenever the output array gets full, it is expanded by this quantity:
#define CHUNK_SIZE 10

#ifdef __cplusplus
extern "C"
{
#endif

// Types for data and indexes:
typedef float     data_t;
typedef u_int16_t index_t;

// Structure holding algorithm data and parameters:
typedef struct {
  data_t  * data_v;   // vector of data
  index_t   data_s;   // number of data points
  data_t    sigmas;   // number of sigmas defining the threshold
  index_t   win_size; // moving windows size
  data_t    stdev;    // search_peaks() will put here the overal st.dev.
} PeakSearch;

// Performs the peak search on the data and according to the parameters in ps.
// The indexes of found peaks are returned in peaks_v.
// ps.stdev will be loaded with the overall standard deviation.
index_t
search_peaks(PeakSearch  * ps,
             index_t    ** peaks_v);

#ifdef __cplusplus
}
#endif

#endif