#include <cuda_profiler_api.h>

#include <omp.h>
#include <openacc.h>
#include <iostream>

#define N 10

struct T {
    int a;
    int *b;
};

void device_to_host(void* dst, void* src, size_t len) {
    int r = omp_target_memcpy(dst, src, len, 0, 0, omp_get_initial_device(), omp_get_default_device());
    if (r != 0) {
        std::cout << "memcpy fail" << std::endl;
    }
}

void host_to_device(void* dst, void* src, size_t len) {
    int r = omp_target_memcpy(dst, src, len, 0, 0, omp_get_default_device(), omp_get_initial_device());
    if (r != 0) {
        std::cout << "memcpy fail" << std::endl;
    }
}

int main() {
    cudaProfilerStart();
    T *t = new T;
    t->a = 0;
    t->b = new int[N];
    for (unsigned i = 0; i < N; ++i) {
        t->b[i] = 0x41;
    }

    // void* d_t = acc_copyin(t, sizeof(T));
    // void* d_b = acc_copyin(t->b, sizeof(int) * N);
    // acc_memcpy_to_device((void*)&(((T*)d_t)->b), &d_b, sizeof(int*));
    auto host_id = omp_get_initial_device();
    auto device_id = omp_get_default_device();
    std::cout << "host_id: " << host_id << ", device_id: " << device_id << std::endl;
    T* d_t = (T*)omp_target_alloc(sizeof(T), device_id);
    host_to_device(d_t, t, sizeof(T));
    int* d_b = (int*)omp_target_alloc(sizeof(int) * N, device_id);
    host_to_device(d_b, t->b, sizeof(int) * N);
    host_to_device(&(((T*)d_t)->b), &d_b, sizeof(int*));
    omp_target_associate_ptr(t->b, d_b, sizeof(int) * N, 0, device_id);
    omp_target_associate_ptr(t, d_t, sizeof(T), 0, device_id);

    //#pragma acc parallel loop present(t[0:1])
#pragma omp target loop map(to:t[:0])
    for (unsigned i = 0; i < N; ++i) {
#pragma omp atomic update
        t->a++;
        t->b[i] = i;
    }

    device_to_host(&(t->a), &(d_t->a), sizeof(int));
    device_to_host(t->b, d_b, sizeof(int) * N);

    std::cout << t->a << std::endl;
    for (unsigned i = 0; i < N; ++i) {
        std::cout << t->b[i] << std::endl;
    }

    cudaProfilerStop();
    return 0;
}
