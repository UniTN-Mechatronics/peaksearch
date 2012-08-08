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
    float d[20] = {1,1,2,1,2,30,32,8,2,1,1,1,2,1,2,2,1,3,1,1};
    ps.data_v = d;

Initialize a result vector (it will contain the peaks indexes); it will be
resized as needed:

    u_int16_t *peaks = (u_int16_t*) malloc(1 * sizeof(u_int16_t));

Perform the search:

    u_int16_t count = search_peaks(&ps, &peaks);



To Do
=====

- Dynamic allocation and resizing of the `peaks_v` vector.