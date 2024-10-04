#include "pipex.h"

int main()
{
  // argv[1] = infile.txt
  // argv[2] = command 1
  // argv[3] = command 2
  // argv[4] = outfile.txt

  // Parent will create 2 childs with 2 pipes
  // Parent opens the infile, and pipes the output to child one
  // child one executes the first command and pipes the outpue to child two
  // child two executes the second command


   //PARENT
  // int file = open("infile.txt")
  // dup2(fd[READ_START], file) -> dup takes the output of file descriptor from infile and puts it into read end of the pipe

  //CHILD 1
  // child 1 reads from READ START of pipe and executes first command exec(argv[2]) 
  // dup2(fd[], fd[])

  //CHILD 2
  // child 2 reads from READ START of pipe and executes second command exec(argv[3])
  // dup2(fd[], fd[])

  int pipe_fds[2];
  int pid;

  if (pipe(pipe_fds) == - 1)
    exit(-1);
  pid = fork();
  if (pid < 0)
    exit(-1);
  if (pid == 0)
    child_process();
  else
    parent_process();
  return 0;
}
