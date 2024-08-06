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

## Compilation

- From the root of the package, run
    1. <tt>mkdir build && cd build</tt>
	2. <tt>../configure [options | --help for help]</tt>
	3. <tt>make</tt><br>

    By default, <tt>configure</tt> searches for <tt>gccgo</tt>. To override this
    default, see sec. Configure Options below.

## Configure Options

Features:

- <p><tt>--disable-go</tt>: By default, <tt>configure</tt> searches for a Golang
  compiler to compile the source <tt>src/ordered_check_sums.go</tt>. This can be
  disabled at configuration via <tt>../configure --disable-go</tt>
  The user will then be required to provide their own substitue for
  <tt>src/ordered_check_sums.go</tt></p>
  <p>To manually choose a compiler, run
  <tt>../configure GOC=<compiler> GOFLAGS=<compiler flags></tt> from inside the
  <tt>build</tt> directory.</p>

- <p><tt>--disable-doxygen-doc</tt>: By default, running <tt>make</tt>
  will run <tt>doxygen</tt> to generate detailed documentation of the source code.
  If you do not have <tt>doxygen</tt> installed, then this step will simply fail
  and <tt>make</tt> will happily continue. Alternatively, at configuration, the
  user may run <tt>../configure --disable-doxygen-doc</tt> in order to disable
  this feature.</p>

  <p>If you have the freely available doxygen installed, detailed html
  documentation will be generated at <tt>build/docs/index.html</tt> when you
  execute <tt>make</tt>. If you do not have doxygen installed, you can download it
  [here](https://www.doxygen.nl/). Otherwise, the detailed descriptions are found
  in the source code comments.</p>

- <tt>--disable-async-exec</tt>: By default, POSIX pthreads are used to employ
  asynchronous execution. To disable this feature, run
  <tt>../configure --disable-async-exec</tt> If the pthreads utilities cannot be
  accessed, then this feature will be automatically disabled.

- <p>For a detailed description of all the options available to the user, simply
  run <tt>../configure --help</tt> to display them.</p>

## Usage

- <tt>src/A</tt>:
    <tt>./src/A \<length\> 1\> \<A_out_file\></tt>
- <tt>src/B</tt>:
    <tt>./src/B \<length\> 1\> \<B_out_file\></tt>
- <tt>src/ordered_check_sums</tt>:
    <tt>./src/ordered_check_sums \<A_out_file\> \<B_out_file\> 1\>
    \<legendre_pairs\></tt>

