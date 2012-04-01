#include <cstdio>
#include "symbol.h"
#include "source.h"

int main(int argc, char* argv[])
{
  FILE *input;
  Source source;

  if (argc != 2)
  {
    printf("Uso: ./<programa> <fichero_entrada>\n");
    return(-1);
  }

  input = fopen(argv[1], "r");

  if (input == NULL)
  {
    printf("Fichero de entrada no encontrado.\n");
    return(-1);
  }

  source.getProperties(input);
  source.showProperties();

  return 0;
}
