// Do not modify this file. It will be replaced by the grading scripts
// when checking your project.

#include "types.h"
#include "stat.h"
#include "user.h"

void
worker(void *a)
{
  printf(1, "worker thread value %d\n", (int) a);
  exit();
}
int
main(int argc, char *argv[])
{
  int a, b, c, d, f, g, h, i = 1;
  int pid, pid2;
  char *e;
  g = (int)malloc(1);
  a = (int)malloc(1);
  b = (int)malloc(2);
  c = (int)malloc(40);
  f = (int)malloc(17);
  h = (int)malloc(16);
  e = (char *)c;
  e+=20;
  d = (int)e;

  printf(1, "%s", "** Placeholder program for grading scripts **\n");
  printf(1, "** g %d, a %d, b %d, c %d, d %d, f %d, h %d**\n", g, a, b, c, d, f, h);
  pid = thread_create(worker,(void *)i);
  pid2 = thread_join();
  printf(1, "create pid = %d, join pid = %d\n", pid, pid2);
  exit();
}
