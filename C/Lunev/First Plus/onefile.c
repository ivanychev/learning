int is_one_file(int fd1, int fd2) {
  struct stat f1_stat = {};
  struct stat f2_stat = {};

  int stat_cond = fstat(fd1, &f1_stat);
  CHECK(stat_cond == 0, "Failed to get stats on first file");
  stat_cond = fstat(fd2, &f2_stat);
  CHECK(stat_cond == 0, "Failed to get stats on second file");

  return (f1_stat.st_ino == f2_stat.st_ino && f1_stat.st_dev == f2_stat.st_dev);
}