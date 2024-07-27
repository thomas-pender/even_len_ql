# Project: Search for Even Length Quaternary Legendre Pairs

## Sources

-src/A.c
	-search for quaternary bracelets passing the PSD test, with real periodic
	 autocorrelations, sum of elements 0.
-src/B.c
	-search for quaternary bracelets passing the PSD test, with real periodic
   autocorrelations, sum of elements 1+i.
-src/ordered_check_sums.go
	- search the outputs of src/A and src/B for quaternary Legendre pairs.

## Installation

    - Run:
        1. ./configure
        2. make install
    - If you do not have a Go compiler, you will need to provide your own
      program to replace src/ordered_check_sums.go.
    - If you have the freely available 'doxygen' installed, detailed html
      documentation will be generated at docs/index.html.
    - If you do not have doxygen installed, you can download it at
         https://www.doxygen.nl/
      Otherwise, the detailed descriptions are found in the source code comments.
    - By default, POSIX pthreads are used to employ asynchronous execution. To
      disable this feature, run
         ./configure --disable-async-exec
      If the pthreads utilities cannot be accessed, then this feature will be
      automatically disabled.
    - To change the compiler flags from the default, run, for example,
         ./configure CFLAGS="-O3"
      to set the compiler flags to -O3.
    - If you downloaded the github repo, you are required to first use autotools
      to generate the configure script. This is accomplished by running
      'autoreconf -i'.
    - For more details, see INSTALL.

## Usage

    - src/A:
        ./src/A <length> 1> <A_out_file>
    - src/B:
        ./src/B <length> 1> <B_out_file>
    - src/ordered_check_sums:
        ./src/ordered_check_sums <A_out_file> <B_out_file> 1> <Legendre_pairs>

