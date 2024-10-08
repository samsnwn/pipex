#include "pipex.h"

void  child_process(int infile, char *cmd, char **env)
{
  read(infile)
}

void  parent_process(int outfile, char *cmd, char **env);

void  pipex(int infile, int outfile, char **argv, char **env)
{
  int pipe_fds[2];
  int pid;
  int status;

  if (pipe(pipe_fds) == -1)
    return (perror("Pipe error"));
  pid = fork();
  if (pid == -1)
    return (perror("Fork error"));
  if (pid == 0)
  {
    // child 1 process
    // child_process(infile, argv[2], env);
    // child must read from infile into the input of the first command

    read(infile, pipe_fds[READ_START]);
    // close(pipe_fds[READ_START]);
    dup2(pipe_fds[WRITE_END], STDOUT_FILENO);
    close(pipe_fds[WRITE_END]);

    execve("");



  }
  else
  {
    // parent process
    // parent_process(outfile, argv[3], env);
    close(pipe_fds[WRITE_END]);

    pid = fork();

    if (pid == 0)
    {
      // Child 2 process
      dup2(pipe_fds[READ_START], STDIN_FILENO);
      close(pipe_fds[READ_START]);
      dup2(outfile, STDOUT_FILENO);
      execve();
    }
    else 
    {
      close(pipe_fds[READ_START]);
    }
    wait(&status);
    wait(&status);
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
