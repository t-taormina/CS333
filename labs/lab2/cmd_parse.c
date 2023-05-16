/* Tyler Taormina - taormina@pdx.edu */
/* CS333 PSUsh program - Lab 2*/
/* Credits: rchaney@pdx.edu*/


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/param.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>

#include "cmd_parse.h"

#define PROMPT_LEN 100
#define MAX_HISTORY 15

// I have this a global so that I don't have to pass it to every
// function where I might want to use it. Yes, I know global variables
// are frowned upon, but there are a couple useful uses for them.
// This is one.
unsigned short is_verbose = 0;

int 
process_user_input_simple(void)
{
    char str[MAX_STR_LEN] = {'\0'};
    char prompt[PROMPT_LEN] = {'\0'};
    char cwd[60] = {'\0'};
    char host_name[20] = {'\0'};
    char *ret_val = NULL;
    char *raw_cmd = NULL;
    cmd_list_t *cmd_list = NULL;
    hist_list_t *hist_list = NULL;
    int *count_ptr = NULL;
    int cmd_count;
    
    signal(SIGINT, sigint_handler);
    cmd_count = 0;
    count_ptr = &cmd_count;
    hist_list = (hist_list_t *) calloc(1, sizeof(hist_list_t));
    hist_list->count = 0;

    for ( ; ; ) {
        hist_t *hist = NULL;
        // Set up a cool user prompt.
        // test to see of stdout is a terminal device (a tty)
        if (isatty(fileno(stdout)))
        {
            /* Get info for command prompt - path to current directory */
            if (getcwd(cwd, sizeof(cwd)) == NULL) {
                perror("getcwd() error");
                exit(EXIT_FAILURE);
            }
            /* Get info for command prompt - username */
            if (gethostname(host_name, sizeof(host_name)) == -1) {
                perror("gethostname() error");
                exit(EXIT_FAILURE);
            }
            sprintf(prompt, " %s %s \n%s@%s # "
                    , PROMPT_STR
                    , cwd
                    , getenv("LOGNAME")
                    , host_name
                   );
            fputs(prompt, stdout);
        }
        memset(str, 0, MAX_STR_LEN);
        ret_val = fgets(str, MAX_STR_LEN, stdin);

        if (NULL == ret_val) {
            // end of input, a control-D was pressed.
            // Bust out of the input loop and go home.
            break;
        }

        // STOMP on the pesky trailing newline returned from fgets().
        if (str[strlen(str) - 1] == '\n') {
            // replace the newline with a NULL
            str[strlen(str) - 1] = '\0';
        }
        if (strlen(str) == 0) {
            // An empty command line.
            // Just jump back to the promt and fgets().
            // Don't start telling me I'm going to get cooties by
            // using continue.
            continue;
        }

        if (strcmp(str, BYE_CMD) == 0) {
            break;
        }

        // I put the update of the history of command in here.
        if (strcmp(str, HISTORY_CMD) != 0) {
            // Handle time of command
            hist = (hist_t *) calloc(1, sizeof(hist_t));
            build_hist(hist, str);
            insert_hist(hist_list, hist);
        }

        // Basic commands are pipe delimited.
        // This is really for Stage 2.
        raw_cmd = strtok(str, PIPE_DELIM);

        cmd_list = (cmd_list_t *) calloc(1, sizeof(cmd_list_t));

        while (raw_cmd != NULL ) {
            cmd_t *cmd = (cmd_t *) calloc(1, sizeof(cmd_t));
            insert_cmd(cmd_list, cmd, raw_cmd, count_ptr);
            // Get the next raw command.
            raw_cmd = strtok(NULL, PIPE_DELIM);
        }

        parse_commands(cmd_list);

        exec_commands(cmd_list, hist_list);

        free_list(cmd_list);

    }
    free_hist_list(hist_list);

    return(EXIT_SUCCESS);
}

void 
simple_argv(int argc, char *argv[])
{
    int opt;

    while ((opt = getopt(argc, argv, "hv")) != -1) {
        switch (opt) {
            case 'h':
                // help
                // Show something helpful
                fprintf(stdout, "You must be out of your Vulcan mind if you think\n"
                        "I'm going to put helpful things in here.\n\n");
                exit(EXIT_SUCCESS);
                break;
            case 'v':
                // verbose option to anything
                // I have this such that I can have -v on the command line multiple
                // time to increase the verbosity of the output.
                is_verbose++;
                if (is_verbose) {
                    fprintf(stderr, "verbose: verbose option selected: %d\n"
                            , is_verbose);
                }
                break;
            case '?':
                fprintf(stderr, "*** Unknown option used, ignoring. ***\n");
                break;
            default:
                fprintf(stderr, "*** Oops, something strange happened <%c> ... ignoring ...***\n", opt);
               break;
        }
    }
}

void 
exec_commands(cmd_list_t *cmds, hist_list_t *hist_list) 
{
    cmd_t *cmd = NULL; 
    param_t *param = NULL;
    char *home = NULL;

    if (NULL == cmds)
        return;

    cmd = cmds->head;
    if (1 == cmds->count) {
        if (!cmd->cmd) {
            return;
        }
        if (0 == strcmp(cmd->cmd, CD_CMD)) {
            if (0 == cmd->param_count) {
                if (NULL == (home = getenv("HOME")))
                    perror("getenv() error");
                if (-1 == chdir(home)){
                    perror("psuSH: cd: home: ");
                }
                fprintf(stdout, "\n");
                /*if ((home = getenv("HOME")) == NULL) {
                    home = getpwuid(getuid())->pw->dir;
                }*/ 
                // Maybe use this if I run into issues with the getenv()
            }
            else {
                // try and cd to the target directory. It would be good to check
                // for errors here.
                if (0 == chdir(cmd->param_list->param)) {
                    char str[MAXPATHLEN];
                    getcwd(str, MAXPATHLEN); 
                    fprintf(stdout, "%s\n", str);
                    fprintf(stdout, "\n");
                }
                else {
                    fprintf(stderr, "psuSH: cd: %s: ", cmd->param_list->param);
                    perror("");
                    fprintf(stdout, "\n");
                }
            }
        }

        /* Current working directory */
        else if (0 == strcmp(cmd->cmd, CWD_CMD)) {
            char str[MAXPATHLEN];

            getcwd(str, MAXPATHLEN); 
            printf(" " CWD_CMD ": %s\n", str);
        }

        /* Echo command */
        else if (0 == strcmp(cmd->cmd, ECHO_CMD)) {
            if(cmd->param_count == 0)
                fprintf(stdout, "\n");
            else {
                param = cmd->param_list;
                while (NULL != param) {
                    fprintf(stdout, "%s ", param->param);
                    param = param->next;
                }
                fprintf(stdout, "\n");
                fprintf(stdout, "\n");
            }
        }

        /* History command */
        else if (0 == strcmp(cmd->cmd, HISTORY_CMD)) {
            print_hist_list(hist_list);
        }
        else {
            pid_t pid, wpid;
            int status;

            pid = wpid = -1;
            pid = fork();
            switch (pid) {
                case -1: 
                    perror("fork failed");
                    exit(EXIT_FAILURE);
                    break;
                case 0:
                    {
                        int i;
                        char **c_argv = NULL; /*child process argv*/
                        char *c_cmd = NULL;
                        param = cmd->param_list;

                        c_argv = (char **) calloc((cmd->param_count + 2),sizeof(char *));
                        c_cmd = cmd->cmd;
                        c_argv[0] = c_cmd;
                        i = 1;
                        while(NULL != param) {
                            c_argv[i] = param->param;
                            param = param->next;
                            i++;
                        }
                        execvp(c_argv[0], c_argv);
                        perror("child failed exec");
                        fprintf(stderr, "*** %d: %s failed ***\n", getpid(), c_cmd);  
                        fflush(stderr);                                             
                        _exit(EXIT_FAILURE);
                    }
                    break;

                default:
                    {
                        do {
                            wpid = waitpid(pid, &status, WUNTRACED);
                        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
                    }
            }
        }
        // A single command to create and exec
        // If you really do things correctly, you don't need a special call
        // for a single command, as distinguished from multiple commands.
    }
    else {
        // Other things???
        // More than one command on the command line. Who'da thunk it!
        // This really falls into Stage 2.
    }
}

void
free_list(cmd_list_t *cmd_list)
{
    cmd_t *temp;
    while (cmd_list->head != NULL) {
        temp = cmd_list->head;
        cmd_list->head = cmd_list->head->next;
        free_cmd(temp); 
    }
    free(cmd_list);
    cmd_list = NULL;
}

void
free_hist_list(hist_list_t *hist_list)
{
    hist_t *temp;
    while (hist_list->head != NULL) {
        temp = hist_list->head;
        hist_list->head = hist_list->head->next;
        free_hist(temp);
    }
    free(hist_list);
    hist_list = NULL;
}

void 
build_hist(hist_t *hist, char *str)
{
    time_t    t;
    struct    tm *tm;
    char      timestr[20];

    t = time(NULL);
    if ((tm = localtime(&t)) == NULL) {
        perror("localtime error");
    }
    if (strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S", 
          tm) == 0) {
        perror("strftime() error");
    }
    
    hist->hist = strdup(str);
    hist->time_str = strdup(timestr);
}

void
insert_hist(hist_list_t *hist_list, hist_t *hist)
{
    if (hist_list->head == NULL) {
        hist_list->head = hist_list->tail = hist;
    }
    else {
        hist_list->tail->next = hist;
        hist_list->tail = hist;
        if (hist_list->count == MAX_HISTORY - 1) {
            hist_t *temp = hist_list->head;
            hist_list->head = hist_list->head->next;
            free_hist(temp);
        }
        else 
            hist_list->count++;
    }
}

void
print_list(cmd_list_t *cmd_list)
{
    cmd_t *cmd = cmd_list->head;

    while (NULL != cmd) {
        print_cmd(cmd);
        cmd = cmd->next;
    }
}

void
free_cmd (cmd_t *cmd)
{
    param_t *temp;

    if (cmd != NULL) {
        if (cmd->raw_cmd != NULL) {
            free(cmd->raw_cmd);
            cmd->raw_cmd = NULL;
        }
        if (cmd->cmd != NULL) {
            free(cmd->cmd);
            cmd->cmd = NULL;
        }
        while (cmd->param_list != NULL) {
            temp = cmd->param_list;
            cmd->param_list = cmd->param_list->next;
            if (temp->param != NULL) {
                free(temp->param);
                temp->param = NULL;
            }
            free(temp);
            temp = NULL;
        }
        //if (cmd->input_file_name != NULL)
            //free(cmd->input_file_name);
        //if (cmd->output_file_name != NULL)
            //free(cmd->output_file_name);
        free(cmd);
        cmd = NULL;
    }
}

void 
free_hist (hist_t *hist)
{
    if (NULL != hist) {
        if (hist->hist != NULL) {
            free(hist->hist);
            hist->hist = NULL;
        }
        if (hist->time_str != NULL) {
            free(hist->time_str);
            hist->time_str = NULL;
        }
        free(hist);
        hist = NULL;
    }
}

void 
insert_cmd(cmd_list_t *cmd_list, cmd_t *cmd, char *raw_cmd, int *count)
{
    cmd->raw_cmd = strdup(raw_cmd);
    cmd->list_location = (*count)++;
    if (cmd_list->head == NULL) {
        // An empty list.
        cmd_list->tail = cmd_list->head = cmd;
    }
    else {
        // Make this the last in the list of cmds
        cmd_list->tail->next = cmd;
        cmd_list->tail = cmd;
    }
    cmd_list->count++;
}

// Oooooo, this is nice. Show the fully parsed command line in a nice
// easy to read and digest format.
void
print_cmd(cmd_t *cmd)
{
    param_t *param = NULL;
    int pcount = 1;

    fprintf(stderr,"raw text: +%s+\n", cmd->raw_cmd);
    fprintf(stderr,"\tbase command: +%s+\n", cmd->cmd);
    fprintf(stderr,"\tparam count: %d\n", cmd->param_count);
    param = cmd->param_list;

    while (NULL != param) {
        fprintf(stderr,"\t\tparam %d: %s\n", pcount, param->param);
        param = param->next;
        pcount++;
    }

    fprintf(stderr,"\tinput source: %s\n"
            , (cmd->input_src == REDIRECT_FILE ? "redirect file" :
               (cmd->input_src == REDIRECT_PIPE ? "redirect pipe" : "redirect none")));
    fprintf(stderr,"\toutput dest:  %s\n"
            , (cmd->output_dest == REDIRECT_FILE ? "redirect file" :
               (cmd->output_dest == REDIRECT_PIPE ? "redirect pipe" : "redirect none")));
    fprintf(stderr,"\tinput file name:  %s\n"
            , (NULL == cmd->input_file_name ? "<na>" : cmd->input_file_name));
    fprintf(stderr,"\toutput file name: %s\n"
            , (NULL == cmd->output_file_name ? "<na>" : cmd->output_file_name));
    fprintf(stderr,"\tlocation in list of commands: %d\n", cmd->list_location);
    fprintf(stderr,"\n");
}

void
print_hist_list(hist_list_t *hist_list)
{
    hist_t *temp = NULL;
    int count = 1;
    temp = hist_list->head;
    while(NULL != temp || count < hist_list->count - 1) {
        fprintf(stdout, "%d %s %s\n", count, temp->time_str, temp->hist);
        temp = temp->next;
        count++;
    }
    fprintf(stdout,"\n");
}

void
sigint_handler(__attribute__((unused)) int sig)
{
    signal(SIGINT, sigint_handler);
    fprintf(stderr, "\nchild kill\n");
    fflush(stderr);
}


// Remember how I told you that use of alloca() is
// dangerous? You can trust me. I'm a professional.
// And, if you mention this in class, I'll deny it
// ever happened. What happens in stralloca stays in
// stralloca.
#define stralloca(_R,_S) {(_R) = alloca(strlen(_S) + 1); strcpy(_R,_S);}

void
parse_commands(cmd_list_t *cmd_list)
{
    cmd_t *cmd = cmd_list->head;
    char *arg;
    char *raw;

    while (cmd) {
        // Because I'm going to be calling strtok() on the string, which does
        // alter the string, I want to make a copy of it. That's why I strdup()
        // it.
        // Given that command lines should not be tooooo long, this might
        // be a reasonable place to try out alloca(), to replace the strdup()
        // used below. It would reduce heap fragmentation.
        //raw = strdup(cmd->raw_cmd);

        // Following my comments and trying out alloca() in here. I feel the rush
        // of excitement from the pending doom of alloca(), from a macro even.
        // It's like double exciting.
        stralloca(raw, cmd->raw_cmd);

        arg = strtok(raw, SPACE_DELIM);
        if (NULL == arg) {
            // The way I've done this is like ya'know way UGLY.
            // Please, look away.
            // If the first command from the command line is empty,
            // ignore it and move to the next command.
            // No need free with alloca memory.
            //free(raw);
            cmd = cmd->next;
            // I guess I could put everything below in an else block.
            continue;
        }
        // I put something in here to strip out the single quotes if
        // they are the first/last characters in arg.
        if (arg[0] == '\'') {
            arg++;
        }
        if (arg[strlen(arg) - 1] == '\'') {
            arg[strlen(arg) - 1] = '\0';
        }
        cmd->cmd = strdup(arg);
        // Initialize these to the default values.
        cmd->input_src = REDIRECT_NONE;
        cmd->output_dest = REDIRECT_NONE;

        while ((arg = strtok(NULL, SPACE_DELIM)) != NULL) {
            if (strcmp(arg, REDIR_IN) == 0) {
                // redirect stdin

                //
                // If the input_src is something other than REDIRECT_NONE, then
                // this is an improper command.
                //

                // If this is anything other than the FIRST cmd in the list,
                // then this is an error.

                cmd->input_file_name = strdup(strtok(NULL, SPACE_DELIM));
                cmd->input_src = REDIRECT_FILE;
            }
            else if (strcmp(arg, REDIR_OUT) == 0) {
                // redirect stdout
                       
                //
                // If the output_dest is something other than REDIRECT_NONE, then
                // this is an improper command.
                //

                // If this is anything other than the LAST cmd in the list,
                // then this is an error.

                cmd->output_file_name = strdup(strtok(NULL, SPACE_DELIM));
                cmd->output_dest = REDIRECT_FILE;
            }
            else {
                // add next param
                param_t *param = (param_t *) calloc(1, sizeof(param_t));
                param_t *cparam = cmd->param_list;

                cmd->param_count++;
                // Put something in here to strip out the single quotes if
                // they are the first/last characters in arg.
                if (arg[0] == '\'') {
                    arg++;
                }
                if (arg[strlen(arg) - 1] == '\'') {
                    arg[strlen(arg) - 1] = '\0';
                }
                param->param = strdup(arg);
                if (NULL == cparam) {
                    cmd->param_list = param;
                }
                else {
                    // I should put a tail pointer on this.
                    while (cparam->next != NULL) {
                        cparam = cparam->next;
                    }
                    cparam->next = param;
                }
            }
        }
        // This could overwite some bogus file redirection.
        if (cmd->list_location > 0) {
            cmd->input_src = REDIRECT_PIPE;
        }
        if (cmd->list_location < (cmd_list->count - 1)) {
            cmd->output_dest = REDIRECT_PIPE;
        }

        // No need free with alloca memory.
        //free(raw);
        cmd = cmd->next;
    }

    if (is_verbose > 0) {
        print_list(cmd_list);
    }
}
