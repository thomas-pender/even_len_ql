# Project: Search for Even Length Quaternary Legendre Pairs

## Sources

- <tt>src/A.c</tt>:
	- search for quaternary bracelets passing the PSD test, with real periodic
	 autocorrelations, sum of elements 0.
- <tt>src/B.c</tt>:
	- search for quaternary bracelets passing the PSD test, with real periodic
   autocorrelations, sum of elements 1+i.
- <tt>src/ordered_check_sums.go</tt>:
	- search the outputs of <tt>src/A</tt> and <tt>src/B</tt> for quaternary 
      Legendre pairs.

## Installation

- Run
    1. <tt>mkdir build && cd build</tt>
	1. <tt>../configure [options | --help for help]</tt>
	2. <tt>make</tt><br>
- If you have a Go compiler, then <tt>build/src/ordered_check_sums</tt> will be 
  built from <tt>src/ordered_check_sums.go</tt>. The Go compiler can be set using 
  either <tt>./configuration</tt> or <tt>make</tt> by overriding the variable 
  <tt>GOC</tt>. If you do not have a Go compiler, you will need to provide your 
  own program to replace <tt>src/ordered_check_sums.go</tt>.
- If you have the freely available doxygen installed, detailed html
  documentation will be generated at <tt>build/docs/index.html</tt> when you 
  execute <tt>make</tt>. If you do not have doxygen installed, you can download it 
  [here](https://www.doxygen.nl/). Otherwise, the detailed descriptions are found 
  in the source code comments, and doxygen can be disabled at configuration by 
  <tt>../configure --disable-doxygen-doc</tt>.
- By default, POSIX pthreads are used to employ asynchronous execution. To disable 
  this feature, run <tt>../configure --disable-async-exec</tt>. If the pthreads 
  utilities cannot be accessed, then this feature will be automatically disabled.
- To change the compiler flags from the default, run, for example,
  <tt>../configure CFLAGS="-O3"</tt> to set the compiler flags to <tt>-O3</tt>.
- If you downloaded the github repo, you are required to first use autotools
  to generate the configure script. This is accomplished by running
  <tt>autoreconf -i</tt> in the project's root directory.
- For more details, see INSTALL.

## Usage

- <tt>build/src/A</tt>:
    <tt>./build/src/A \<length\> 1\> \<A_out_file\></tt>
- <tt>build/src/B</tt>: 
    <tt>./build/src/B \<length\> 1\> \<B_out_file\></tt>
- <tt>build/src/ordered_check_sums</tt>: 
    <tt>./build/src/ordered_check_sums \<A_out_file\> \<B_out_file\> 1\> 
    \<legendre_pairs\></tt>

