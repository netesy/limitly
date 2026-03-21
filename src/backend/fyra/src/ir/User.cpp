#include "ir/User.h"
#include "ir/Use.h"
#include <memory>

namespace ir {

User::User(Type* ty) : Value(ty) {}

User::~User() {
    // operands are unique_ptrs, so they will be automatically destroyed.
    // Use's destructor will call v->removeUse(*this).
    operands.clear();
}

void User::addOperand(Value* v) {
    operands.push_back(std::make_unique<Use>(this, v));
}

} // namespace ir
