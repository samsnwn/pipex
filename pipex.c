#include "pipex.h"

int ft_strlen(char *str)
{
    int count;

    count = 0;
    while (*str)
    {
        count++;
        str++;
    }
    return count;
}

void  first_child_process(int infile, char *argv, int pipe_fds[], char **env)
{
    int bytes_read;
    char *read_buf;
    int str_len;

    close(pipe_fds[READ_START]);
    read_buf = malloc(sizeof(char) * 1024);
    if (!read_buf)
      return (perror("Malloc error"));
    bytes_read = 1;
    while ((bytes_read = read(infile, read_buf, 1024)) > 0)
    {
      read_buf[bytes_read] = '\0';
      printf("First child buffer -> %s\n", read_buf);
    }
    close(infile);
    str_len = ft_strlen(read_buf) + 1;
    dup2(pipe_fds[WRITE_END], STDOUT_FILENO);
    execve("/usr/bin/ls", &argv, env);
    if (write(1, &str_len, sizeof(int)) < 0)
      return perror("Write Error");
    if (write(1, read_buf, (sizeof(char) * str_len)) < 0)
      return perror("Write Error");
    free(read_buf);
    close(pipe_fds[WRITE_END]);
}

void  second_child_process(int outfile, char *argv, int pipe_fds[], char **env)
{
  // second child reads the input from the pipe read end, executes cmd2 and outputs to outfile
  int bytes_read;
  char *read_buf;
  int str_len; 

  close(pipe_fds[WRITE_END]);
  read_buf = malloc(sizeof(char) * 1024);
  if (!read_buf)
    return (perror("Malloc error"));
  bytes_read = 1;
  if (read(pipe_fds[READ_START], &str_len, sizeof(int)) < 0)
    return (perror("Read Error"));
  if (read(pipe_fds[READ_START], read_buf, sizeof(char) * str_len) < 0)
    return (perror("Read Error"));
  printf("Second child buffer -> %s\n", read_buf);
  close(pipe_fds[READ_START]);
  execve("/usr/bin/grep", &argv, env);
  dup2(outfile, STDOUT_FILENO);
  if (write(1, read_buf, str_len) < 0)
    return (perror("Write error"));
  free(read_buf);
  close(pipe_fds[READ_START]);
}

void  pipex(int infile, int outfile, char **argv, char **env)
{
  int pipe_fds[2];
  int pid1;
  int pid2;
  int status;


  if (pipe(pipe_fds) == -1)
    return (perror("Pipe error"));
  pid1 = fork();
  if (pid1 == -1)
    return (perror("Fork error"));
  if (pid1 == 0)
  {
    // child 1 process
    // child must read from infile into a read buffer. This buffer will be written into the input of the first command and execute it
    first_child_process(infile, argv[2], pipe_fds, env);
  }
  else
  {
    // parent process
    close(pipe_fds[WRITE_END]);
    pid2 = fork();

    if (pid2 == 0)
    {
      // Child 2 process
      // child 2 will read the output of cmd1, execute cmd2 and redirect the putput of cmd2 to outfile
      second_child_process(outfile, argv[3], pipe_fds, env);
    }
    else 
      close(pipe_fds[READ_START]);
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
  close(infile);
  close(outfile);
  return (0);
}
