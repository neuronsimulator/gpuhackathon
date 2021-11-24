#include <cuda_profiler_api.h>

#include <memory>

#define stringify(x) #x
#ifdef _OPENMP
#define omp_pragma(x) _Pragma(stringify(omp x))
#define acc_pragma(x)
#elif defined(_OPENACC)
#define omp_pragma(x)
#define acc_pragma(x) _Pragma(stringify(acc x))
#else
#error "Expected OpenMP or OpenACC to be enabled."
#endif

void init(int* data, std::size_t data_size) {
  acc_pragma(parallel loop present(data[0:data_size]))
  omp_pragma(target teams distribute parallel for simd depend(out: data[0:data_size]) nowait)
  for(auto i = 0; i < data_size; ++i) {
    data[i] = i;
  }
}

void compute(int* data, std::size_t data_start, std::size_t data_size, int queue) {
  acc_pragma(parallel loop present(data[data_start:data_size]) async(queue))
  omp_pragma(target teams distribute parallel for simd depend(inout: data[data_start:data_size]) nowait)
  for(auto i = data_start; i < data_start + data_size; ++i) {
    for(auto j = 0; j < i*i; ++j) {
      data[i] += j;
    }
  }
}

int main() {
  cudaProfilerStart();
  // Choose a size small enough for there to be space for the two compute kernels on the device at the same time.
  auto const data_size = 10000;
  auto* data = new int[data_size];
  acc_pragma(data create(data[0:data_size]))
  omp_pragma(target data map(alloc: data[0:data_size]))
  {
    init(data, data_size);
    // Launch 2 kernels that can be run in parallel
    compute(data, 0, data_size/2, 0);
    compute(data, data_size/2, data_size/2, 1);
    acc_pragma(wait async(0))
    acc_pragma(wait async(1))
    omp_pragma(taskwait)
  }
  cudaProfilerStop();
  return 0;
}
