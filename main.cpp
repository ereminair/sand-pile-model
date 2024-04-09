#include "lib/Arguments.h"
#include "lib/Sandpile.h"

int main(int argc, char* argv[]) {
  Arguments Input = ArgumentsInput(argc, argv);
  SandPile pile;
  pile.width = Input.width;
  pile.length = Input.length;
  pile.path = Input.input;
  pile.GetSandPile(Input.length, Input.width);
  pile.Topling(Input.freq, Input.output, Input.max_iter);

  return 0;
}
