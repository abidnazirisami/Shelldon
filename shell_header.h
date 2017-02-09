char *reaad(); // Function for reading from the console
char **paarse(char *str); // Function for parsing
int launch(char **args); // Function for executing after managing pipe or I/O Redirection
void runProcess(char **args, int in, int out, int background); // Function to run exec
void execute_cd(char **array_of_args); // To execute cd
void execute_echo(char **array_of_args); // Tp execute Echo
void execute_help(); // To execute help
void execute_pwd(); // To execute pwd
void execute_exit(); // To exit

