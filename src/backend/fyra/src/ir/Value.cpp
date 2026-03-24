#include "ir/Value.h"
#include "ir/Use.h"
#include <iostream>
#include <algorithm>

namespace ir {

Value::~Value() {
    // Break connections to all users before this value is destroyed.
    // Use a while loop with front() to safely handle modifications to use_list
    // during iteration, as u->set(nullptr) will call removeUse on this value.
    while (!use_list.empty()) {
        Use* u = use_list.front();
        u->set(nullptr);
    }
}

void Value::addUse(Use& u) {
    use_list.push_back(&u);
}

void Value::removeUse(Use& u) {
    use_list.remove(&u);
}

void Value::replaceAllUsesWith(Value* newVal) {
    auto copy = use_list;
    for (Use* u : copy) {
        u->set(newVal);
    }
}

void Value::print(std::ostream& os) const {
    if (!name.empty()) {
        os << "%" << name;
    } else {
        os << "<unnamed:" << (void*)this << ">";
    }
}

} // namespace ir
