#include <omp.h>
#include <openacc.h>
#include <iostream>

#define N 10

struct Data {
    int a;
    int *b;
};

void acc_version() {
    Data *t = new Data;
    t->a = 0;
    t->b = new int[N];
    for (unsigned i = 0; i < N; ++i) {
        t->b[i] = i;
    }

    void* d_t = acc_copyin(t, sizeof(Data));
    void* d_b = acc_copyin(t->b, sizeof(int) * N);
    acc_memcpy_to_device((void*)&(((Data*)d_t)->b), &d_b, sizeof(int*));

    #pragma acc parallel loop present(t[0:1])
    for (unsigned i = 0; i < N; ++i) {
        #pragma acc atomic update
        t->a++;
        t->b[i] *= 2;
    }

    acc_update_self(&(t->a), sizeof(int));
    acc_update_self(t->b, sizeof(int) * N);

    std::cout << "OpenACC : " <<  t->a << std::endl;
    for (unsigned i = 0; i < N; ++i) {
        std::cout << t->b[i] << std::endl;
    }

    acc_delete((void*)t->b, sizeof(int)*N);
    acc_delete((void*)t, sizeof(Data));

    delete [] t->b;
    delete t;
}

void omp_version() {
    Data *t = new Data;
    t->a = 0;
    t->b = new int[N];
    for (unsigned i = 0; i < N; ++i) {
        t->b[i] = i;
    }

    auto host_id = omp_get_initial_device();
    auto device_id = omp_get_default_device();

    Data* d_t = (Data*)omp_target_alloc(sizeof(Data), device_id);
    omp_target_memcpy(d_t, t, sizeof(Data), 0, 0, omp_get_default_device(), omp_get_initial_device());

    int* d_b = (int*)omp_target_alloc(sizeof(int) * N, device_id);
    omp_target_memcpy(d_b, t->b, sizeof(int)*N, 0, 0, omp_get_default_device(), omp_get_initial_device());
    omp_target_memcpy(&(d_t->b), &d_b, sizeof(int*), 0, 0, omp_get_default_device(), omp_get_initial_device());

    omp_target_associate_ptr(t->b, d_b, sizeof(int) * N, 0, device_id);
    omp_target_associate_ptr(t, d_t, sizeof(Data), 0, device_id);

    #pragma omp target loop map(to:t[:0])
    for (unsigned i = 0; i < N; ++i) {
        #pragma omp atomic update
        t->a++;
        t->b[i] *= 2;
    }

    omp_target_memcpy(&(t->a), &(d_t->a), sizeof(int), 0, 0, omp_get_initial_device(), omp_get_default_device());
    omp_target_memcpy(t->b, d_b, sizeof(int)*N, 0, 0, omp_get_initial_device(), omp_get_default_device());

    std::cout << "OpenMP : " <<  t->a << std::endl;
    for (unsigned i = 0; i < N; ++i) {
        std::cout << t->b[i] << std::endl;
    }

    delete [] t->b;
    delete t;
}

int main() {
    acc_version();
    omp_version();
    return 0;
}
