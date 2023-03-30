#include "cpu.h"

#define RELOAD_FILE_(file, stream, param)                                      \
  fclose(stream);                                                              \
  stream = fopen(file, param);

int plot(char *input_stream, char *output_stream, char *error_stream,
         cpu *my_cpu, double x_begin, double x_end, double dx, double ymin,
         double ymax, int display_width, int display_height) {
  ASSERT(my_cpu);
  ASSERT(cpu_check(my_cpu) == CPU_CHECK_OK);
  ASSERT(display_width > 0);
  ASSERT(display_height > 0);

  FILE *fi = fopen(input_stream, "r");
  FILE *fo = fopen(output_stream, "w");
  FILE *strerr = fopen(error_stream, "w");
  txCreateWindow(display_width, display_height);

  double x = x_begin;
  double y = 0;
  int ret = 0;
  bool mistakes = false;
  int x1 = 0;
  int x2 = 0;
  int y1 = 0;
  int y2 = 0;
  double xlast = x_begin;
  double ylast = 0;

  cpu_mov_ax(my_cpu, xlast);
  ret = calculator(fi, fo, strerr, my_cpu, &ylast, cpu_catch_error);

  RELOAD_FILE_(input_stream, fi, "r");

  bool draw_mistakes = false;

  while (x <= x_end + dx / 4) // DBL_EPSILON fucks up
  {
    cpu_mov_ax(my_cpu, x);
    ret = calculator(fi, fo, strerr, my_cpu, &y, cpu_catch_error);
    if (ret != CALC_OK) {
      mistakes = true;
      x += dx;
      RELOAD_FILE_(input_stream, fi, "r");
      continue;
    }
    x1 = (int)((xlast - x_begin) / (x_end - x_begin) * display_width);
    y1 = (int)((1 - (ylast - ymin) / (ymax - ymin)) * display_height);
    x2 = (int)((x - x_begin) / (x_end - x_begin) * display_width);
    y2 = (int)((1 - (y - ymin) / (ymax - ymin)) * display_height);

    if (mistakes == true) {
      x2 = x1;
      y2 = y1;
      mistakes = false;
    }
    // DEBUG_OUT fprintf(fo, "PRINT %d %d %d %d\n", x1, y1, x2, y2);

    draw_mistakes = txLine(x1, y1, x2, y2);
    if (draw_mistakes == false)
      return DRAW_BAD;
    ylast = y;
    xlast = x;
    x += dx;
    RELOAD_FILE_(input_stream, fi, "r");
  }

  fclose(fi);
  fclose(fo);
  fclose(strerr);
  return DRAW_OK;
}