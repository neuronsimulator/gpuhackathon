| example | OpenACC | OpenMP |
| --- | --- | --- |
| https://github.com/BlueBrain/CoreNeuron/blob/d565f3512c8f70d11bf64b04f06bccada1473fda/coreneuron/nrnconf.h#L36 | `#pragma acc declare create(var)` |  |
| https://github.com/BlueBrain/CoreNeuron/blob/d565f3512c8f70d11bf64b04f06bccada1473fda/coreneuron/mechanism/register_mech.cpp#L24 | `#pragma acc declare copyin(secondorder)` |  |
| https://github.com/BlueBrain/CoreNeuron/blob/d565f3512c8f70d11bf64b04f06bccada1473fda/coreneuron/gpu/nrn_acc_manager.cpp#L915 | `#pragma acc wait(nt->stream_id)` | `#pragma omp taskwait` (?) |
| https://github.com/BlueBrain/CoreNeuron/blob/d565f3512c8f70d11bf64b04f06bccada1473fda/coreneuron/network/netcvode.cpp#L597 | `#pragma acc update host(nsbuffer[0:nt->_net_send_buffer_cnt]) if (nt->compute_gpu) async(stream_id)` |  |
| https://github.com/BlueBrain/CoreNeuron/blob/d565f3512c8f70d11bf64b04f06bccada1473fda/coreneuron/apps/main1.cpp#L563 | `#pragma acc update device(var) if (compute_gpu)` |  |
| https://github.com/BlueBrain/CoreNeuron/blob/d565f3512c8f70d11bf64b04f06bccada1473fda/coreneuron/mechanism/membfunc.hpp#L112 | `#pragma acc routine seq` |  |
| https://github.com/BlueBrain/CoreNeuron/blob/d565f3512c8f70d11bf64b04f06bccada1473fda/coreneuron/network/netcvode.cpp#L550-L554 | `#pragma acc parallel loop present(var) copy(var) if (var) async(var)` |  |
| https://github.com/BlueBrain/CoreNeuron/blob/d565f3512c8f70d11bf64b04f06bccada1473fda/coreneuron/network/netcvode.cpp#L577 | `#pragma acc atomic capture` |  |
| https://github.com/BlueBrain/CoreNeuron/blob/d565f3512c8f70d11bf64b04f06bccada1473fda/coreneuron/network/partrans.cpp#L162 | `#pragma acc enter data create(src_gather[0 : n_src_gather]) if (nt->compute_gpu)` |  |
| https://github.com/BlueBrain/CoreNeuron/blob/d565f3512c8f70d11bf64b04f06bccada1473fda/coreneuron/permute/cellorder.cpp#L503 | `#pragma acc atomic update` |  |
| https://github.com/BlueBrain/CoreNeuron/blob/d565f3512c8f70d11bf64b04f06bccada1473fda/coreneuron/permute/cellorder.cpp#L540 | `#pragma acc loop seq` |  |
| https://github.com/BlueBrain/CoreNeuron/blob/d565f3512c8f70d11bf64b04f06bccada1473fda/coreneuron/permute/cellorder.cpp#L607-L611 | `#pragma acc parallel loop gang vector vector_length(warpsize) present(var) if (var) async(stream_id)` |  |
| https://github.com/BlueBrain/CoreNeuron/blob/d565f3512c8f70d11bf64b04f06bccada1473fda/coreneuron/sim/fadvance_core.cpp#L331 | `#pragma acc update self(gather_i[0:1]) if(nth->compute_gpu) async(nth->stream_id)` |  |
| https://github.com/BlueBrain/CoreNeuron/blob/d565f3512c8f70d11bf64b04f06bccada1473fda/coreneuron/sim/solve_core.cpp#L75-L77 | `#pragma acc parallel loop seq present(var) async(stream_id) if (var)` |  |
| https://github.com/BlueBrain/CoreNeuron/blob/d565f3512c8f70d11bf64b04f06bccada1473fda/coreneuron/utils/vrecord.cpp#L108 | `#pragma acc kernels present(this) if(var)` |  |
