//
//  peaksearch.c
//  peaksearch
//
//  Created by Paolo Bosetti on 8/8/12.
//  Copyright (c) 2012 Paolo Bosetti. All rights reserved.
//

#include "peaksearch.h"
#define FULL    0
#define PARTIAL 1

typedef struct {
  data_t  mean;
  data_t  sd;
  data_t  max;
  index_t max_idx;
} Statistics;

data_t
mean(PeakSearch       * ps,
     index_t    const   start,
     index_t    const   end)
{
  data_t sum = 0.;
  index_t i, c;
  for (i = start, c = 0; i < end; i++, c++) {
    sum += ps->data_v[i];
  }
  return (sum / c );
}

void
statistics(PeakSearch       * ps,
           index_t    const   start,
           char       const   type,
           Statistics       * stat)
{
  data_t acc = 0.;
  index_t i, c, end;
  switch (type) {
    case FULL:
      end = ps->data_s;
      break;
    case PARTIAL:
      end = start + ps->win_size <= ps->data_s ? start + ps->win_size : ps->data_s;
      break;
  }
  stat->mean = mean(ps, start, end);
  stat->max  = 0.;
  for (i = start, c = 0; i < end; i++, c++) {
    acc += pow((ps->data_v[i] - stat->mean), 2);
    if (ps->data_v[i] > stat->max) {
      stat->max     = ps->data_v[i];
      stat->max_idx = i;
    }
  }
  stat->sd = sqrt(acc / (c - 1));
}

index_t
search_peaks(PeakSearch  * ps,
             index_t    ** peaks_v)
{
  index_t count   = 0;
  index_t peaks_s = CHUNK_SIZE;
  Statistics stat;
  free(*peaks_v);
  *peaks_v = (index_t*) malloc(peaks_s * sizeof(index_t));
  
  statistics(ps, 0, FULL, &stat);
  ps->stdev = stat.sd;

  index_t i;
  char in_cluster = 0;

  data_t max = 0.;
  for(i = 0; i < (ps->data_s - ps->win_size); i++) {
    statistics(ps, i, PARTIAL, &stat);
    if (stat.sd > ps->sigmas * ps->stdev) {
      if (stat.max > max) {
        (*peaks_v)[count] = stat.max_idx;
        max = stat.max;
      }
      in_cluster = 1;
    }
    else {
      if(in_cluster == 1) count++;
      if(count > peaks_s) {
        peaks_s += CHUNK_SIZE;
        *peaks_v = (index_t*) realloc(*peaks_v, peaks_s * sizeof(index_t));
      }
      max = 0.;
      in_cluster = 0;
    }
  }
  return count;
}

