/**
 * @mainpage
 *
 * @author              Sergey Ivanychev, DCAM MIPT, 376 group
 * @brief               Patching .elf file
 */
#include "assert.h"
#include "stdio.h"
#include "stdlib.h"

#define OFFSET 0x3c1
#define BUFSIZE 1024

/**
 * @brief               obtaining size of opened file
 *
 *
 * @param stream        current file stream
 * @return              -1 if error occured
 *                      otherwise size is returned
 */
ssize_t file_size(FILE *stream) {
  assert(stream);
  ssize_t size = 0;
  if (fseek(stream, 0, SEEK_END) == -1) {
    perror("Failed to seek to the end");
    return -1;
  }
  if ((size = ftell(stream)) == -1) {
    perror("Failed to obtain stream offset");
    return -1;
  }
  rewind(stream);
  return size;
}

/**
 * @brief               get a copy of file in dynamic memory
 * @details             gets file size, allocates memory and copies file into it
 *
 * @param stream        current file
 * @param buf_tosave    pointer to buffer pointer, where allocated memory adress
 *                      will be saved
 *
 * @return              -1 if error occured
 *                      otherwise the size of file (buffer) is returned
 */
ssize_t alloc_copy(FILE *stream, char **buf_tosave) {
  ssize_t fsize = 0;
  ssize_t written = 0;
  char *buf = NULL;
  assert(stream);
  assert(buf_tosave);

  fsize = file_size(stream);
  if (fsize == -1) {
    perror("Failed to get file size");
    goto fail;
  }

  buf = malloc(fsize);
  if (buf == NULL) {
    perror("Failed to allocate buffer");
    goto fail;
  }

  written = fread(buf, fsize, 1, stream);
  if (written != 1) {
    printf("fsize = %zd, written = %zd", fsize, written);
    perror("Failed to read file to buffer");
    goto fail;
  }

  *buf_tosave = buf;
exit:
  return fsize;
fail:
  if (buf) {
    free(buf);
    buf = NULL;
  }
  fsize = -1;
  goto exit;
}

int main(int argc, char const *argv[]) {
  const char *path = argv[1];
  char *buf = NULL;
  FILE *elf = fopen("arm.elf", "r");
  FILE *patch = fopen("patched", "w");
  ssize_t fsize = 0;

  if (argc != 1) {
    fprintf(stderr, "Invalid number of arguments\n"
                    "Specify only the input file\n");
    return -1;
  }
  if (elf == NULL || patch == NULL) {
    perror("Failed to open executable or create copy");
    goto fail;
  }

  fsize = alloc_copy(elf, &buf);
  if (fsize == -1) {
    perror("Failed to get file to buffer");
    goto fail;
  }

  ((unsigned char *)buf)[OFFSET] = (unsigned char)0xd0;
  if (fwrite(buf, fsize, 1, patch) != 1) {
    perror("Failed to save patched copy");
    goto fail;
  }

  fclose(elf);
  fclose(patch);
  free(buf);
  return 0;

fail:
  if (elf) {
    fclose(elf);
    elf = NULL;
  }
  if (patch) {
    fclose(patch);
    patch = NULL;
  }
  if (buf) {
    free(buf);
    buf = NULL;
  }
  return -1;
}
