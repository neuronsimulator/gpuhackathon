# openacc2openmp
CoreNEURON openacc to openmp offloading explorations

A repo to collect all coreneuron openacc code and how it could be translated into openmp offloading
code.

Check overview.md for the list of collected pragmas.

# Code examples
There is a basic Makefile for compiling code snippets in the `src/` directory.

## parallel kernels
The `parallel_kernels` example probes how we can launch two independent kernels that should be able to execute simultaneously on a single GPU.
With OpenACC this is done by launching them in independent asynchronous streams.
With OpenMP this is attempted using task dependencies, but it doesn't seem to work.
