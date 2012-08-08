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

#define FULL 0
#define PARTIAL 1

typedef float data_t;
typedef u_int16_t index_t;

struct PeakSearch {
  data_t *data_v;
  index_t data_s;
  data_t sigmas;
  index_t win_size;
  data_t stdev;
};

struct Statistics {
  data_t mean;
  data_t sd;
  data_t max;
  index_t max_idx;
};


data_t
mean(struct PeakSearch *ps, const index_t start, const index_t end);

void
statistics(struct PeakSearch *ps, const index_t start, char const type, struct Statistics *stat);

index_t
search_peaks(struct PeakSearch *ps, index_t **peaks_v);


#endif
