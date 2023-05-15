/* Tyler Taormina - taormina@pdx.edu */
/* CS333 PSUsh program - Lab 2*/
/* Credits: rchaney@pdx.edu*/


#pragma once

#ifndef _CMD_PARSE_H
# define _CMD_PARSE_H

# define MAX_STR_LEN 2000

# define CD_CMD  "cd"
# define CWD_CMD "cwd"
# define ECHO_CMD "echo"
# define BYE_CMD "bye"
# define HISTORY_CMD "history"

# define PIPE_DELIM  "|"
# define SPACE_DELIM " "
# define REDIR_IN    "<"
# define REDIR_OUT   ">"
//# define BACKGROUND_CHAR   "&"

# define PROMPT_STR "PSUsh"

// This enumeration is used when determining if the re direction
// characters (the < and >) were used on a command.
typedef enum {
      REDIRECT_NONE
    , REDIRECT_FILE
    , REDIRECT_PIPE
    , BACKGROUND_PROC
} redir_t;

// A list of param_t elements.
typedef struct param_s {
    char           *param;
    struct param_s *next;
} param_t;

typedef struct hist_s {
    char          *hist;
    char          *time_str;
    time_t        time;
    struct hist_s *next;
} hist_t;

typedef struct hist_list_s {
    hist_t *head;
    hist_t *tail;
    int    count;
} hist_list_t;

// A linked list that has a linked list as a member.
typedef struct cmd_s {
    char    *raw_cmd;
    char    *cmd;
    int     param_count;
    param_t *param_list;
    redir_t input_src;
    redir_t output_dest;
    char    *input_file_name;
    char    *output_file_name;
    int     list_location; // zero based
    struct cmd_s *next;
} cmd_t;

typedef struct cmd_list_s {
    cmd_t *head;
    cmd_t *tail;
    int   count;
} cmd_list_t;

void parse_commands(cmd_list_t *cmd_list);
void free_list(struct cmd_list_s *);
void print_list(struct cmd_list_s *);
void free_cmd(struct cmd_s *);
void insert_cmd(struct cmd_list_s *, struct cmd_s *, char *, int *);
void print_cmd(struct cmd_s *);
void insert_hist(struct hist_list_s *, struct hist_s *);
void free_hist_list(struct hist_list_s *);
void free_hist(struct hist_s *);
void print_hist_list(struct hist_list_s *);
void build_hist(struct hist_s *, char *);
void exec_commands(cmd_list_t *cmds, hist_list_t *hist_list);
int  process_user_input_simple(void);
void simple_argv(int argc, char *argv[]);

#endif // _CMD_PARSE_H
