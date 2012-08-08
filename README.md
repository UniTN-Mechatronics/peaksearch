Peak Search Algorithm
=====================

This is a rather simple algorithm for finding the peaks in a set of points 
(think at a FFT spectrum), given as an array of value assumed to be regularly
spaced along the abscissa. The result is the array of indexes of the peaks maxima.


Usage
=====

Initialize a PeakSearch structure with the algorithm parameters:

    struct PeakSearch ps;
    ps.sigmas = 1.0;
    ps.win_size = 4;
    ps.data_s = 20;
    ps.data_v = (float*) malloc(ps.data_s * sizeof(float));
    data_t d[20] = {1,1,2,1,2,30,32,8,2,1,1,1,2,1,2,2,1,3,1,1};
    ps.data_v = d;

Initialize a result vector (it will contain the peaks indexes); it will be
resized as needed:

    index_t *peaks = (index_t*) malloc(1 * sizeof(index_t));

Perform the search:

    index_t count = search_peaks(&ps, &peaks);

Remember to `free()` the `peaks` array at the end:

    free(peaks);


Rationale
=========

The algorithm is based on a moving window (holding `ps.win_size` points) over the 
`ps.data_v` array, one element at a time. 

At each iteration, the standard deviation of the moving window is compared to the 
overall standard deviation. If their ratio exceeds `ps.sigmas`, then it is assumed 
that the current window contains a peak.

For each consecutive set of windows containing a peak, the index of the maximum 
of the values is saved in the `peaks` array, which starts of size `CHUNK_SIZE`
and then grows by multiples of this size when needed.

