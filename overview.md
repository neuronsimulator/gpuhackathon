| example | OpenACC | OpenMP |
| --- | --- | --- |
| http://bbpcf011.bbp.epfl.ch/source/xref/github/BlueBrain/CoreNeuron/coreneuron/nrnconf.h#36 | #pragmaaccdeclare create(var) |  |
| http://bbpcf011.bbp.epfl.ch/source/xref/github/BlueBrain/CoreNeuron/coreneuron/apps/main1.cpp#563 | #pragmaaccupdate device(var) if (compute_gpu) |  |
| http://bbpcf011.bbp.epfl.ch/source/xref/github/BlueBrain/CoreNeuron/coreneuron/gpu/nrn_acc_manager.cpp#109 | #pragma accenter data copyin(var) async(nt->stream_id) |  |
| http://bbpcf011.bbp.epfl.ch/source/xref/github/BlueBrain/CoreNeuron/coreneuron/gpu/nrn_acc_manager.cpp#110 | #pragma accwait(nt->stream_id) |  |
| http://bbpcf011.bbp.epfl.ch/source/xref/github/BlueBrain/CoreNeuron/coreneuron/mechanism/capac.cpp#22 | #pragma acc update host(var) |  |
| http://bbpcf011.bbp.epfl.ch/source/xref/github/BlueBrain/CoreNeuron/coreneuron/mechanism/membfunc.hpp#112 | #pragma acc routine seq |  |
| http://bbpcf011.bbp.epfl.ch/source/xref/github/BlueBrain/CoreNeuron/coreneuron/mechanism/register_mech.cpp#24 | #pragma acc declare copyin(secondorder) |  |
| http://bbpcf011.bbp.epfl.ch/source/xref/github/BlueBrain/CoreNeuron/coreneuron/network/netcvode.cpp?r=846b3a63#550 | #pragma acc parallel loop present(var) copy(var) if (var) async(var) |  |
| http://bbpcf011.bbp.epfl.ch/source/xref/github/BlueBrain/CoreNeuron/coreneuron/network/netcvode.cpp#577 | #pragma acc atomic capture |  |
| http://bbpcf011.bbp.epfl.ch/source/xref/github/BlueBrain/CoreNeuron/coreneuron/network/netcvode.cpp#587 | #pragma acc wait(stream_id) |  |
| http://bbpcf011.bbp.epfl.ch/source/xref/github/BlueBrain/CoreNeuron/coreneuron/gpu/nrn_acc_manager.cpp#899 | #pragma acc update host(nsbuffer[0:nt->_net_send_buffer_cnt]) if (nt->compute_gpu) async(stream_id) |  |
| http://bbpcf011.bbp.epfl.ch/source/s?defs=enter&project=github | #pragmaacc enter data create (var) if (var) |  |
| http://bbpcf011.bbp.epfl.ch/source/xref/github/BlueBrain/CoreNeuron/coreneuron/permute/cellorder.cpp#503 | #pragma acc atomic update |  |
| http://bbpcf011.bbp.epfl.ch/source/xref/github/BlueBrain/CoreNeuron/coreneuron/permute/cellorder.cpp#540 | #pragma acc loop seq |  |
| http://bbpcf011.bbp.epfl.ch/source/xref/github/BlueBrain/CoreNeuron/coreneuron/permute/cellorder.cpp#607 | #pragma acc parallel loop gang vector vector_length(warpsize) present(var) if (var) async(stream_id) |  |
| http://bbpcf011.bbp.epfl.ch/source/xref/github/BlueBrain/CoreNeuron/coreneuron/sim/fadvance_core.cpp?r=846b3a63#212 | #pragma acc parallel loop present(var) if (var) async(stream_id) |  |
| http://bbpcf011.bbp.epfl.ch/source/xref/github/BlueBrain/CoreNeuron/coreneuron/sim/fadvance_core.cpp#331 | #pragma acc update self(gather_i[0:1]) if(nth->compute_gpu) async(nth->stream_id) |  |
| http://bbpcf011.bbp.epfl.ch/source/xref/github/BlueBrain/CoreNeuron/coreneuron/sim/solve_core.cpp?r=c7a186bf#46 | #pragma acc parallel loop seq present(var) async(stream_id) if (var) |  |
| http://bbpcf011.bbp.epfl.ch/source/s?defs=kernels&project=github | #pragma acc kernels present(this) if(var) |  |
```