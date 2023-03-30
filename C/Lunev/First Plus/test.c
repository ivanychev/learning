#include "onefile.c"
#include "pipe.h"

const char *F1_NAME = "try.txt";
const char *F2_NAME = "try_linked.txt";
const char *F3_NAME = "test.c";

int main(int argc, char const *argv[]) {
  /*
          int f1 = open(F1_NAME, O_RDONLY);
          int f2 = open(F2_NAME, O_RDONLY);
          int f3 = open(F3_NAME, O_RDONLY);

          printf("First and second are %s\n",
                  (is_one_file(f1, f2))? "SAME" : "DIFFERENT");
          printf("Second and third are %s\n",
                  (is_one_file(f3, f2))? "SAME" : "DIFFERENT");
          printf("First and third are %s\n",
                  (is_one_file(f1, f3))? "SAME" : "DIFFERENT");

          close(f1);
          close(f2);
          close(f3);
          return 0;
  */

  unsigned a = 666;
  printf("%o\n", a);

  int buf[10] = {};
  int mk_cond = mkfifo("fifo_temp", 666);
  OUT1("Making fifo condition = %d\n", mk_cond);
  if (mk_cond == -1)
    perror("");

  int fifo_id = open("fifo_temp", O_RDWR);
  OUT1("fifo_id = %d\n", fifo_id);

  int written = write(fifo_id, "aaa", 3);
  OUT1("written = %d\n", written);

  int fifo2_id = open("fifo_temp", O_RDONLY, O_NDELAY);
  OUT1("fifo2_id = %d\n", fifo2_id);

  int cond = read(fifo2_id, buf, 3);
  OUT1("Read = %d\n", cond);

  int written_out = write(1, buf, cond);
  OUT1("Written to console = %d", written_out);

  close(fifo_id);
  close(fifo2_id);
  unlink("fifo_temp");
  return 0;
}