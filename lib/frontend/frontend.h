namespace fe {

class Ir;

class Frontend {
public:
  Frontend();
  virtual ~Frontend();

  virtual Ir* CreateIr();
private:
};

}
