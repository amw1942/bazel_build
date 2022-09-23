#include <vector>

namespace ir {

enum InstType {
  NOP,
  ADD,
  MULT,
  LOAD,
  STORE,
  DIV,
  INVALID_INST
};

class Inst {
public:
  Inst(InstType it);
  ~Inst();

  unsigned Id();
  InstType GetType();

private:
  static unsigned uid_;
  unsigned id_;
  InstType it_;
};

class Vliw {
public:
  Vliw(unsigned num_packets);
  ~Vliw();

  unsigned Id();

  void Set(unsigned idx, Inst* inst);
  Inst* Get(unsigned idx);

private:
  static unsigned uid_;
  unsigned id_;
  std::vector<Inst*> lane_;
};

}
