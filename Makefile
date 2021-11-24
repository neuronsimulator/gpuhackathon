all: bin/parallel_kernels_acc bin/parallel_kernels_omp profiles/parallel_kernels_acc.qdrep profiles/parallel_kernels_omp.qdrep

bin/parallel_kernels_omp: src/parallel_kernels.cpp
	mkdir -p bin/
	nvc++ -cuda -mp=multicore,gpu -Minfo=accel,mp -gpu=lineinfo -o $@ $^

bin/parallel_kernels_acc: src/parallel_kernels.cpp 
	mkdir -p bin/
	nvc++ -cuda -acc -Minfo=accel -gpu=lineinfo -o $@ $^

profiles/%.qdrep: bin/%
	mkdir -p profiles/
	nsys profile -o $@ -c cudaProfilerApi --kill=none $^
