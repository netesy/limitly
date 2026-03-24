#include "ir/Use.h"
#include "ir/Value.h"

namespace ir {

Use::Use(User* u, Value* v) : user(u), v(nullptr) {
    set(v);
}

Use::~Use() {
    // Break the link to the currently used value.
    if (v) {
        v->removeUse(*this);
        v = nullptr;
    }
}

void Use::set(Value* new_v) {
    if (v == new_v) return;

    // Remove from the old value's use list.
    if (v) {
        v->removeUse(*this);
    }

    v = new_v;

    // Add to the new value's use list.
    if (v) {
        v->addUse(*this);
    }
}

} // namespace ir
