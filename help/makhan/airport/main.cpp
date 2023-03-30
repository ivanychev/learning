#include <assert.h>
#include <errno.h>
#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <string.h>

using namespace std;

int strip[4], t_now[4] = {};

struct Plan {
  int time;
  int takeoff;
};

#define PLANE_CASES 5

struct Plan plans[PLANE_CASES];
int plans_in[PLANE_CASES], plans_out[PLANE_CASES];
int in = 0, out = 0;

void *f_in(void *data) {
  int bash = (long)data;
  int k = bash % 2;
  int time = plans_in[bash];
  if (time - t_now[k] > 0)
    printf("Полоса %d для взлета: запрошенное время : %d, время ожидания: %d "
           "мин, вылет в %d  \n",
           k + 1, time, time - t_now[k], max(t_now[k], time));
  else
    printf("Полоса %d для взлета: запрошенное время %d, время задержки: %d "
           "мин, вылет в %d \n",
           k + 1, time, t_now[k] - time, max(t_now[k], time));
  t_now[k] = max(t_now[k], time) + 3;
  return NULL;
}

void *f_out(void *data) {
  int bash = (long)data;
  int k = bash % 2 + 2;
  int time = plans_out[bash];
  if (time - t_now[k] > 0)
    printf("Полоса %d для посадки: запрошенное время %d, время ожидания: %d "
           "мин, вылет в %d  \n",
           k + 1, time, time - t_now[k], max(t_now[k], time));
  else
    printf("Полоса %d для посадки: запрошенное время %d, время задержки: %d "
           "мин, вылет в %d \n",
           k + 1, time, t_now[k] - time, max(t_now[k], time));
  t_now[k] = max(t_now[k], time) + 3;
  return NULL;
}

void launch(int in, int out) {
  // a = plans_in;
  // b = plans_out;

  int ret = 0;
  int count_in = 0;
  int count_out = 0;

  pthread_t first_in, second_in;
  pthread_t first_out, second_out;
  // printf("%d %d\n",in, out);

  while ((count_in < in) || (count_out < out)) {
    if (count_in < in) {

      if (count_in < 2 || !(ret = pthread_tryjoin_np(first_in, NULL))) {
        if (count_in >= 1)
          first_in = second_in;

        // передать k % 2 - ромер полосы
        assert(!pthread_create(&second_in, 0, f_in, (void *)(long)count_in));
        count_in++;

        if (count_in == 0)
          first_in = second_in;
      } else if (count_in >= 2) {
        assert(ret == EBUSY);
      };
    }

    if (count_out < out) {

      if (count_out < 2 || !(ret = pthread_tryjoin_np(first_out, NULL))) {
        if (count_out >= 1)
          first_out = second_out;

        // передать k % 2 - ромер полосы
        assert(!pthread_create(&second_out, 0, f_out, (void *)(long)count_out));
        count_out++;

        if (count_out == 0)
          first_out = second_out;
      } else if (count_out >= 2) {
        assert(ret == EBUSY);
      };
    }
  }
}

void save_time(struct Plan *this, int hour, int min) {
  assert(this);
  this->time = (60 * hour) + min;
}

int main()

{
  int min, hour;
  printf("Please type data in format\n"
         "\"0 12:42\" --- takeoff at 12:42\n"
         "\"1 13:44\" --- arrival at 13:44\n"
         "First %d cases will be analysed",
         PLANE_CASES);

  for (int i = 0; i < PLANE_CASES; i++) {
    scanf("%d %d:%d \n", &plans[i].takeoff, &hour, &min);
    save_time(&plans[i], hour, min);

    if (plans[i].takeoff == 0) {
      plans_in[in] = plans[i].time;
      in++;
    } else {
      plans_out[out] = plans[i].time;
      out++;
    }
  }
  launch(in, out);
  return 0;
}
