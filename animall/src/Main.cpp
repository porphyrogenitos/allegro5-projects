#include "Frame.hpp"

int main() {
  Frame frame {20, 20};
  frame.set(5, 2, true);
  frame.print();
}
