#include "lymar.hh"
#include "dap_server.hh"

namespace LM {

void DapRunner::run(int port) {
    LM::DAP::DapServer server;
    if (port > 0) {
        server.runSocket(port);
    } else {
        server.runStdio();
    }
}

} // namespace LM
