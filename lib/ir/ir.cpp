#include "ir.h"

namespace ir {

unsigned Inst::uid_ = 0;

Inst::Inst(InstType it)
: id_(uid_++), it_(it) {
}

Inst::~Inst() {
}

unsigned Inst::Id() {
  return id_;
}

InstType Inst::GetType() {
  return it_;
}

unsigned Vliw::uid_ = 0;

Vliw::Vliw(unsigned lane_size)
: id_(uid_++), lane_(std::vector<Inst*>(lane_size)) {
}

Vliw::~Vliw() {
}

unsigned Vliw::Id() {
  return id_;
}

void Vliw::Set(unsigned idx, Inst* inst) {
  lane_[idx] = inst;
}

Inst* Vliw::Get(unsigned idx) {
  return lane_[idx];
}

}
