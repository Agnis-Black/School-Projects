/* $begin shellmain */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <spawn.h>
#include <fcntl.h>

#define MAXARGS 128
#define MAXLINE 8192 /* Max text line length */

typedef enum { 
    IS_SIMPLE,
    IS_PIPE,
    IS_INPUT_REDIR,
    IS_OUTPUT_REDIR,
    IS_INPUT_OUTPUT_REDIR,
    IS_SEQ,
    IS_ANDIF,
    IS_ORIF
} Mode; /* simple command, |, >, <, ;, && */

typedef struct { 
    char *argv[MAXARGS]; /* Argument list */
    int argc; /* Number of args */
    int bg; /* Background job? */
    Mode mode; /* Handle special cases | > < ; */
} parsed_args; 

extern char **environ; /* Defined by libc */

/* Function prototypes */
void unix_error(char *msg);
void eval(char *cmdline);
parsed_args parseline(char *buf);
int builtin_command(char **argv, pid_t pid, int status);
void signal_handler(int sig);
int exec_cmd(char **argv, posix_spawn_file_actions_t *actions, pid_t *pid, int *status, int bg);
int find_index(char **argv, char *target); 

int main(int argc, char *argv[])
{
    char cmdline[MAXLINE]; /* Command line */

    /* TODO: register signal handlers */
    signal(SIGINT, signal_handler);
    signal(SIGTSTP, signal_handler);
    signal(SIGCHLD,signal_handler);

    while (1) {
        char *result;
        /* Read */
        printf("CS361 >"); /* TODO: correct the prompt */
        result = fgets(cmdline, MAXLINE, stdin);
        if (result == NULL && ferror(stdin)) {
            fprintf(stderr, "fatal fgets error\n");
            exit(EXIT_FAILURE);
        }

        if (feof(stdin))
            exit(EXIT_SUCCESS);

        /* Evaluate */
        eval(cmdline);
    }
}

void unix_error(char *msg) /* Unix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(EXIT_FAILURE);
}
/* $end shellmain */

/* $begin eval */
/* eval - Evaluate a command line */
void eval(char *cmdline)
{
    char buf[MAXLINE];   /* Holds modified command line */
    pid_t pid;           /* Process id */
    int status;          /* Process status */
    int child_status;
    int pipe_fds[2];
    int pid1, pid2;
    int pos;
    posix_spawn_file_actions_t actions; /* used in performing spawn operations */
    posix_spawn_file_actions_t actions1, actions2;
    posix_spawn_file_actions_init(&actions); //Initialize spawn file actions object for the processes
    posix_spawn_file_actions_init(&actions1);
    posix_spawn_file_actions_init(&actions2);

    strcpy(buf, cmdline);
    parsed_args parsed_line = parseline(buf);
    if (parsed_line.argv[0] == NULL) /* Ignore empty lines */
        return; 

    /* Not a bultin command */
    if (!builtin_command(parsed_line.argv, pid, status)) {
        switch (parsed_line.mode) {
        case IS_SIMPLE: /* cmd argv1 argv2 ... */ 
            if (!exec_cmd(parsed_line.argv, &actions, &pid, &status, parsed_line.bg)) 
                return;
            break;
        case IS_PIPE: /* command1 args | command2 args */
            // TODO: handle pipe
          
            //Create a unidirectional pipe for interprocess communication with a 
            // read and write end.
            pipe(pipe_fds);

            // Add duplication action of copying the write end of the pipe to the 
            // standard out file descriptor
            posix_spawn_file_actions_adddup2(&actions1, pipe_fds[1], STDOUT_FILENO);

  	    // Add action of closing the read end of the pipe
            posix_spawn_file_actions_addclose(&actions1, pipe_fds[0]);

            // Add duplication action of copying the read end of the pipe to the 
            // standard in file descriptor
            posix_spawn_file_actions_adddup2(&actions2, pipe_fds[0], STDIN_FILENO);

            // Add the action of closing the write end of the pipe
            posix_spawn_file_actions_addclose(&actions2, pipe_fds[1]);

            pos = find_index(parsed_line.argv,"|");
            parsed_line.argv[pos] = NULL;
            // Create the first child process 
            if (0 != posix_spawnp(&pid1, parsed_line.argv[0], &actions1, NULL, &parsed_line.argv[0], environ)) {
                perror("spawn failed");
                exit(1);
            }

            //Create the second child process
            if (0 != posix_spawnp(&pid2, parsed_line.argv[pos+1], &actions2, NULL, parsed_line.argv+pos+1, environ)) {
                perror("spawn failed");
                exit(1);
            }

            // Close the read end in the parent process
            close(pipe_fds[0]);

            // Close the write end in the parent process
            close(pipe_fds[1]);

            // Wait for the first child to complete
            waitpid(pid1, &child_status, 0);

            // Wait for the second child to complete
            waitpid(pid2, &child_status, 0);
 
            break;
        case IS_OUTPUT_REDIR: /* command args > output_redirection */
            // TODO: handle output redirection 
		
	    pos = find_index(parsed_line.argv,">");
            parsed_line.argv[pos] = NULL;

            //Create a unidirectional pipe for interprocess communication with a 
            // read and write end.
            pipe(pipe_fds);

            int file = posix_spawn_file_actions_addopen(&actions, STDOUT_FILENO, parsed_line.argv[pos+1], O_WRONLY |O_CREAT| O_TRUNC, 0700);

  	    // Add action of closing the read end of the pipe
            posix_spawn_file_actions_addclose(&actions1, pipe_fds[0]);

            // Add the action of closing the write end of the pipe
            posix_spawn_file_actions_addclose(&actions2, pipe_fds[1]);

            exec_cmd(parsed_line.argv, &actions, &pid, &status, parsed_line.bg);

            // Close the read end in the parent process
            close(pipe_fds[0]);

            // Close the write end in the parent process
            close(pipe_fds[1]);

            break;
        case IS_INPUT_REDIR: /* command args < input_redirection */
            // TODO: handle input redirection 
            printf("input redirection not yet implemented :(\n");
            break;
        case IS_INPUT_OUTPUT_REDIR: /* command args < input_redirection > output_redirection */
            // TODO: handle input output redirection 
            printf("input output redirection not yet implemented :(\n");
            break;
        case IS_SEQ: /* command1 args ; command2 args */
            // TODO: handle sequential 

            // TODO: handle pipe
           
            //Create a unidirectional pipe for interprocess communication with a 
            // read and write end.
            pipe(pipe_fds);

            pos = find_index(parsed_line.argv,";");
            parsed_line.argv[pos] = NULL;
            // Create the first child process 
            if (0 != posix_spawnp(&pid1, parsed_line.argv[0], &actions1, NULL, &parsed_line.argv[0], environ)) {
                perror("spawn failed");
                exit(1);
            }

            //Create the second child process
            if (0 != posix_spawnp(&pid2, parsed_line.argv[pos+1], &actions2, NULL, parsed_line.argv+pos+1, environ)) {
                perror("spawn failed");
                exit(1);
            }

            // Close the read end in the parent process
            close(pipe_fds[0]);

            // Close the write end in the parent process
            close(pipe_fds[1]);

            // Wait for the first child to complete
            waitpid(pid1, &child_status, 0);

            // Wait for the second child to complete
            waitpid(pid2, &child_status, 0);

            break;

        case IS_ANDIF: /* command1 args && command2 args */
            // TODO: handle "and if"
            
            //Create a unidirectional pipe for interprocess communication with a 
            // read and write end.
            pipe(pipe_fds);

            pos = find_index(parsed_line.argv,"&&");
            parsed_line.argv[pos] = NULL;
            // Create the first child process 
            if ((0 != posix_spawnp(&pid1, parsed_line.argv[0], &actions1, NULL, &parsed_line.argv[0], environ)) && (0 != posix_spawnp(&pid2, parsed_line.argv[pos+1], &actions2, NULL, parsed_line.argv+pos+1, environ))){
                perror("spawn failed");
                exit(1);
            }

            // Close the read end in the parent process
            close(pipe_fds[0]);

            // Close the write end in the parent process
            close(pipe_fds[1]);

            // Wait for the first child to complete
            waitpid(pid1, &child_status, 0);

            // Wait for the second child to complete
            waitpid(pid2, &child_status, 0);
            break;

        case IS_ORIF: /* command1 args || command2 args */
            // TODO: handle "or if"
            
            //Create a unidirectional pipe for interprocess communication with a 
            // read and write end.
            pipe(pipe_fds);

            pos = find_index(parsed_line.argv,"||");
            parsed_line.argv[pos] = NULL;
            // Create the first child process 
            if (0 == posix_spawnp(&pid1, parsed_line.argv[0], &actions1, NULL, &parsed_line.argv[0], environ)) {
                // Wait for the first child to complete
            	waitpid(pid1, &child_status, 0);
            }else 
            {
 	        //Create the second child process
                if (0 == posix_spawnp(&pid2, parsed_line.argv[pos+1], &actions2, NULL, parsed_line.argv+pos+1, environ)) {
                    // Wait for the second child to complete
            	    waitpid(pid2, &child_status, 0);
                }
      
            }

            
            // Close the read end in the parent process
            close(pipe_fds[0]);

            // Close the write end in the parent process
            close(pipe_fds[1]);

            break;
        }

        if (parsed_line.bg)
            printf("%d %s", pid, cmdline);
    }

    posix_spawn_file_actions_destroy(&actions);
    return;
}

/* If first arg is a builtin command, run it and return true */
int builtin_command(char **argv, pid_t pid, int status)
{
    if (!strcmp(argv[0], "exit")) /* exit command */
        exit(EXIT_SUCCESS);
    if (!strcmp(argv[0], "&")) /* Ignore singleton & */
        return 1;

    // TODO: implement special command "?"
    if (!strcmp(argv[0], "?")){ 
        printf("\npid:\%d status:\%d\n", pid,status);
        return 1;
    }

    return 0; /* Not a builtin command */
}
/* $end eval */

/* Run commands using posix_spawnp */
int exec_cmd(char **argv, posix_spawn_file_actions_t *actions, pid_t *pid, int *status, int bg)
{
    //printf("simple command not yet implemented :(\n");

    // Lab 5 TODO: use posix_spawnp to execute commands and when it fails,
    // print an error, "spawn failed", using the perror function
	if(posix_spawnp(pid,argv[0],actions,NULL,argv,environ) != 0){
        perror("spawn failed");
     }

    // Lab 5 TODO: when posix_spawnp is ready, uncomment me
     if (!bg) {
         if (waitpid(*pid, status, 0) < 0) 
             unix_error("waitfg: waitpid error");
     }

    return 1;
}
/* $end exec_cmd */

/* signal handler */
void signal_handler(int sig)
{
    // TODO: handle SIGINT and SIGTSTP and SIGCHLD signals here
    if(sig == SIGINT){
        char line[] = "\ncaught sigint\nCS361 >";
        write(1, line, sizeof(line));
    }
    if(sig == SIGTSTP){
        char line[] = "\ncaught sigstp\nCS361 >";
        write(1,line, sizeof(line));
    }
    if(sig == SIGCHLD){
        int olderrno = errno;
        waitpid(-1, NULL, 0);
        errno = olderrno;
    }   
    
}

/* finds index of the matching target in the arguments */
int find_index(char **argv, char *target)
{
    for (int i = 0; argv[i] != NULL; i++) {
        if (!strcmp(argv[i], target))
            return i;
    }
    
    return 0;
}

/* $begin parseline */
/* parseline - Parse the command line and build the argv array */
parsed_args parseline(char *buf)
{
    char *delim; /* Points to first space delimiter */
    parsed_args pa;

    buf[strlen(buf) - 1] = ' ';   /* Replace trailing '\n' with space */
    while (*buf && (*buf == ' ')) { /* Ignore leading spaces */
        buf++;
    } 

    /* Build the argv list */
    pa.argc = 0;
    while ((delim = strchr(buf, ' '))) {
        pa.argv[pa.argc++] = buf;
        *delim = '\0';
        buf = delim + 1;

        while (*buf && (*buf == ' ')) { /* Ignore spaces */
            buf++;
        }
    }
    pa.argv[pa.argc] = NULL;

    if (pa.argc == 0) /* Ignore blank line */
        return pa;

    /* Should the job run in the background? */
    if ((pa.bg = (*pa.argv[pa.argc - 1] == '&')) != 0)
        pa.argv[--pa.argc] = NULL;

    /* Detect various command modes */
    pa.mode = IS_SIMPLE;
    if (find_index(pa.argv, "|"))
        pa.mode = IS_PIPE;
    else if (find_index(pa.argv, ";")) 
        pa.mode = IS_SEQ; 
    else if (find_index(pa.argv, "&&"))
        pa.mode = IS_ANDIF;
    else if (find_index(pa.argv, "||"))
        pa.mode = IS_ORIF;
    else {
        if (find_index(pa.argv, "<")) 
            pa.mode = IS_INPUT_REDIR;
        if (find_index(pa.argv, ">")) {
            if (pa.mode == IS_INPUT_REDIR)
                pa.mode = IS_INPUT_OUTPUT_REDIR;
            else
                pa.mode = IS_OUTPUT_REDIR; 
        }
    }

    return pa;
}
/* $end parseline */
