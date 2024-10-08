#include "pipex.h"

void  pipex(int a, int b, char **argv, char **env)
{
  int pipe_fds[2];
  int pid;

  if (pipe(pipe_fds) == -1)
    exit(-1);
  pid = fork();
  if (pid == -1)
    return (perror("Fork error"));
  if (pid == 0)
  {
    // child process
    child_process(a, argv[1], argv[2], env);
  }
  else
  {
    // parent process
    parent_process(b, argv[3], argv[4], env);
  }
}

int main(int argc, char **argv, char **env)
{
  int infile;
  int outfile;

  if (argc != 5)
    return 1;
  infile = open(argv[1], O_RDONLY);
  outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC);
  if (infile < 0 || outfile < 0)
    return (-1);
  pipex(infile, outfile, argv, env);
  return (0);
}
