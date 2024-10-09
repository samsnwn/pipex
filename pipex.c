#include "pipex.h"

void  first_child_process(char *file, int pipe_fds[], char *cmd)
{
    // int bytes_read;
    // char *read_buf;
    // size_t str_len;
    int infile;

    close(pipe_fds[READ_START]);
    infile = open(file, O_RDONLY);
    if (infile < 0)
      return (perror("Open file Error"));
    dup2(infile, STDIN_FILENO);
    close(infile);
    dup2(pipe_fds[WRITE_END], STDOUT_FILENO);
    close(pipe_fds[WRITE_END]);
    if (execv("/usr/bin/ls", &cmd) < 0)
      return perror("LS EXEC Error");
    // read_buf = malloc(sizeof(char) * 1024);
    // if (!read_buf)
    //   return (perror("Malloc error"));
    // bytes_read = 1;
    // while ((bytes_read = read(infile, read_buf, 1024)) > 0)
    // {
    //   read_buf[bytes_read] = '\0';
    //   printf("First child buffer -> %s\n", read_buf);
    // }
    // close(infile);
    // str_len = ft_strlen(read_buf) + 1;
    // execve("/usr/bin/ls", &argv, env);
    // if (write(1, &str_len, sizeof(int)) < 0)
    //   return perror("Write Error");
    // if (write(1, read_buf, (sizeof(char) * str_len)) < 0)
    //   return perror("Write Error");
    // free(read_buf);
    // close(pipe_fds[WRITE_END]);


}

void  second_child_process(char *cmd, int pipe_fds[], char *file)
{
  // second child reads the input from the pipe read end, executes cmd2 and outputs to outfile
  // char *read_buf;
  // size_t str_len; 

  // close(pipe_fds[WRITE_END]);
  // read_buf = malloc(sizeof(char) * 1024);
  // if (!read_buf)
  //   return (perror("Malloc error"));
  // if (read(pipe_fds[READ_START], &str_len, sizeof(int)) < 0)
  //   return (perror("Read Error"));
  // printf("strlen -> %zu\n", str_len);
  // if (read(pipe_fds[READ_START], read_buf, sizeof(char) * str_len) < 0)
  //   return (perror("Read Error"));
  // printf("Second child buffer -> %s\n", read_buf);
  // close(pipe_fds[READ_START]);
  // execve("/usr/bin/grep", &argv, env);
  // dup2(outfile, STDOUT_FILENO);
  // if (write(1, read_buf, str_len) < 0)
  //   return (perror("Write error"));
  // free(read_buf);
  // close(pipe_fds[READ_START]);
  int outfile;

  close(pipe_fds[WRITE_END]);
  outfile = open(file, O_CREAT | O_RDWR | O_TRUNC);
  if (outfile < 0)
    return (perror("Open file error"));
  dup2(outfile, STDOUT_FILENO);
  close(outfile);
  dup2(pipe_fds[READ_START], STDIN_FILENO);
  close(pipe_fds[READ_START]);
  if (execv("/usr/bin/wc", &cmd) < 0)
    return perror("WC EXEC Error");
}

void  pipex(char **argv)
{
  int pipe_fds[2];
  int pid1;
  int pid2;


  if (pipe(pipe_fds) == -1)
    return (perror("Pipe error"));
  pid1 = fork();
  if (pid1 == -1)
    return (perror("Fork error"));
  if (pid1 == 0)
  {
    // child 1 process
    // child must read from infile into a read buffer. This buffer will be written into the input of the first command and execute it
    first_child_process(argv[1], pipe_fds, argv[2]);
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
      second_child_process(argv[3], pipe_fds, argv[4]);
    }
    close(pipe_fds[READ_START]);
    wait(NULL);
  }
}

int main(int argc, char **argv)
{
  if (argc != 5)
    return -1;
  pipex(argv);
  return (0);
}
