#include "calculator.h"
#include "stdlib.h"
#include "stdio.h"

int main(int argc, char* argv[]) {
  // Ensure a filename is provided as an argument
  if (argc < 2) {
    printf("Usage: %s <filename>\n", argv[0]);
    return 1; // Exit with an error code
  }

  // Use the first argument as the filename
  char* filename = argv[1];
  struct Reader reader; //declare space on the stack. We don't need to malloc.
  reader.had_error = false;
  char* line = init_reader(&reader, filename); // reader->token now has the first token
  int ans = calculate_result(&reader); // this is the bulk of the work and the logic
  printf("Final Answer: %d\n", ans);

  if (reader.had_error) {
    printf("Had Error\n");
  }

  free(line); //free the single line read from file
  return 0; // Exit successfully
}
