//
//  main.c
//  peaksearch
//
//  Created by Paolo Bosetti on 8/7/12.
//  Copyright (c) 2012 Paolo Bosetti. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define FULL 0
#define PARTIAL 1

struct PeakSearch {
  float *data_v;
  u_int16_t data_s;
  float sigmas;
  u_int16_t win_size;
  float stdev;
};

struct Statistics {
  float mean;
  float sd;
  float max;
  u_int16_t max_idx;
};

float
mean(struct PeakSearch *ps, u_int16_t start, u_int16_t end)
{
  float sum = 0.;
  u_int16_t i, c;
  for (i=start,c=0; i<end; i++,c++) {
    sum += ps->data_v[i];
  }
  return (sum / c );
}

void
statistics(struct PeakSearch *ps, u_int16_t start, char type, struct Statistics *stat)
{
  float acc = 0.;
  u_int16_t i, c, end;
  switch (type) {
    case FULL:
      end = ps->data_s;
      break;
    case PARTIAL:
      end = start + ps->win_size <= ps->data_s ? start + ps->win_size : ps->data_s;
      break;
  }
  stat->mean = mean(ps, start, end);
  stat->max = 0.;
  for (i=start,c=0; i<end; i++,c++) {
    acc += pow((ps->data_v[i] - stat->mean), 2);
    if (ps->data_v[i] > stat->max) {
      stat->max = ps->data_v[i];
      stat->max_idx = i;
    }
  }
  stat->sd = sqrt(acc / (c - 1));
}

u_int16_t
search_peaks(struct PeakSearch *ps, u_int16_t **peaks_v)
{
  u_int16_t count = 0;
  struct Statistics stat;
  free(*peaks_v);
  *peaks_v = (u_int16_t*) malloc(ps->data_s * sizeof(u_int16_t));

  statistics(ps, 0, FULL, &stat);
  ps->stdev = stat.sd;

  u_int16_t i;
  char in_cluster = 0;

  for(i=0; i<ps->data_s-ps->win_size; i++) {
    statistics(ps, i, PARTIAL, &stat);
    float max = 0.;
    if (stat.sd > ps->sigmas * ps->stdev) {
      if (stat.max > max) {
        (*peaks_v)[count] = stat.max_idx;
        max = stat.max;
      }
      in_cluster = 1;
    }
    else {
      if(in_cluster == 1) count++;
      max = 0.;
      in_cluster = 0;
    }
  }
  return count;
}


int main(int argc, const char * argv[])
{
  struct PeakSearch ps;
  ps.sigmas = 1.0;
  ps.win_size = 4;
  ps.data_s = 20;
  ps.data_v = (float*) malloc(ps.data_s * sizeof(float));
  float d[20] = {1,1,2,1,2,30,32,8,2,1,1,1,2,1,2,2,1,3,1,1};
  ps.data_v = d;
  u_int16_t i;

  u_int16_t *peaks = (u_int16_t*) malloc(1 * sizeof(u_int16_t));
  u_int16_t count = search_peaks(&ps, &peaks);

  printf("Overall st.dev: %f. Found %d peaks\n", ps.stdev, count);
  for (i=0; i<count; i++) {
    printf("peak %d: point %d, value %f\n", i, peaks[i], ps.data_v[peaks[i]]);
  }
  return 0;
}

