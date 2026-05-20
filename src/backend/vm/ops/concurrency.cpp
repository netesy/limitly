#include "../register.hh"
#include "../../../runtime/runtime.h"
#include "../../channel.hh"
#include "../../scheduler.hh"
#include "../../shared_cell.hh"

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

void RegisterVM::execute_concurrency(const LIR::LIR_Inst* pc) {
    switch (pc->op) {
        case LIR::LIR_Op::ChannelAlloc: {
            auto channel = std::make_unique<LM::Backend::Channel>(pc->a);
            channels.push_back(std::move(channel));
            registers[pc->dst] = BOX_PTR(channels.back().get());
            break;
        }
        case LIR::LIR_Op::ChannelSend: {
            if (IS_PTR(registers[pc->a])) {
                LM::Backend::Channel* channel = (LM::Backend::Channel*)UNBOX_PTR(registers[pc->a]);
                channel->send(registers[pc->b], get_current_fiber());
            }
            break;
        }
        case LIR::LIR_Op::ChannelRecv: {
            if (IS_PTR(registers[pc->a])) {
                LM::Backend::Channel* channel = (LM::Backend::Channel*)UNBOX_PTR(registers[pc->a]);
                registers[pc->dst] = channel->recv(get_current_fiber());
            }
            break;
        }
        case LIR::LIR_Op::ChannelClose: {
            if (IS_PTR(registers[pc->a])) {
                LM::Backend::Channel* channel = (LM::Backend::Channel*)UNBOX_PTR(registers[pc->a]);
                channel->close();
            }
            break;
        }
        case LIR::LIR_Op::ChannelHasData: {
            if (IS_PTR(registers[pc->a])) {
                LM::Backend::Channel* channel = (LM::Backend::Channel*)UNBOX_PTR(registers[pc->a]);
                registers[pc->dst] = channel->has_data() ? VAL_TRUE : VAL_FALSE;
            }
            break;
        }
        default:
            break;
    }
}

} // namespace Register
} // namespace VM
} // namespace Backend
} // namespace LM
