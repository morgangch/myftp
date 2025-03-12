#define BUFFER_SIZE 1024
#define MAX_COMMAND_HISTORY 10
#define MAX_CLIENTS 100

#define LOGIN_RESPONSE "220 Welcome to FTP server"
#define LOGOUT_RESPONSE "221 Goodbye"
#define USER_RESPONSE "331 User name okay, need password"
#define PASS_RESPONSE "230 User logged in, proceed"
#define LIST_RESPONSE "150 Here comes the directory listing"
#define RETR_RESPONSE "150 Opening data connection for file transfer"
#define STOR_RESPONSE "150 Opening data connection for file upload"
#define QUIT_RESPONSE "221 Goodbye"
#define NOT_LOGGED_IN "530 Not logged in"
#define INVALID_COMMAND "500 Invalid command"
#define INVALID_ARGUMENTS "501 Invalid number of arguments"
#define FILE_NOT_FOUND "550 File not found"
#define FILE_ERROR "451 File error"
#define FILE_ACTION_OK "226 Transfer complete"
#define DIRECTORY_ACTION_OK "250 Requested file action okay, completed"
#define DIRECTORY_CREATED "257 Directory created"
#define DIRECTORY_DELETED "250 Directory deleted"
#define DIRECTORY_ERROR "550 Directory error"
#define DIRECTORY_EXISTS "550 Directory already exists"
#define DIRECTORY_NOT_FOUND "550 Directory not found"
#define DIRECTORY_NOT_EMPTY "550 Directory not empty"
#define COMMAND_NOT_IMPLEMENTED "502 Command not implemented"
#define DATA_CONNECTION_CLOSED "226 Closing data connection"
#define DATA_CONNECTION_ERROR "425 Can't open data connection"
#define DATA_CONNECTION_TIMEOUT "421 Data connection timeout"
#define INVALID_USERNAME "430 Invalid username or password"
#define INVALID_PERMISSIONS "550 Permission denied"
#define INVALID_FILE "550 Invalid file"
#define INVALID_DIRECTORY "550 Invalid directory"
#define INVALID_PATH "550 Invalid path"
#define INVALID_ARGUMENT "501 Invalid argument"
#define HELP_RESPONSE "214 Help message"
#define CWD_RESPONSE "250 Directory changed to new directory"
#define CDUP_RESPONSE "250 Directory changed to parent directory"
#define PWD_RESPONSE "257 Current directory is"
#define PASV_RESPONSE "227 Entering passive mode"
#define PORT_RESPONSE "200 Entering active mode"
#define EXIT_RESPONSE "221 Server closing connection"
#define MKD_RESPONSE "257 Directory created"
#define RMD_RESPONSE "250 Directory deleted"
#define DELE_RESPONSE "250 File deleted"