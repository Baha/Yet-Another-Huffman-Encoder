#include <cstdio>
#include "symbol.h"
#include "source.h"

int main(int argc, char* argv[])
{
  FILE *input;
  Source source;

  if (argc != 3)
  {
    printf("Uso: ./<programa> <fichero_entrada> <fichero_salida>\n");
    return(-1);
  }

  input = fopen(argv[1], "r");

  if (input == NULL)
  {
    printf("Fichero de entrada no encontrado.\n");
    return(-1);
  }

  source.unserializeTree(input);
  source.writeUncodifiedFile(input, argv[2]);

  return 0;
}
