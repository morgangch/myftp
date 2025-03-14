#define BUFFER_SIZE         10240
#define MAX_COMMAND_HISTORY 10
#define MAX_CLIENTS         5000

#define LIST_RESPONSE           "150 Here comes the directory listing\r\n"
#define RETR_RESPONSE           "150 Opening data connection for file transfer\r\n"
#define STOR_RESPONSE           "150 Opening data connection for file upload\r\n"
#define PORT_RESPONSE           "200 Entering active mode\r\n"
#define NOOP_RESPONSE           "200 NOOP command successful\r\n"
#define HELP_RESPONSE           "214 Help message\r\n"
#define LOGIN_RESPONSE          "220 Welcome to FTP server\r\n"
#define LOGOUT_RESPONSE         "221 Goodbye\r\n"
#define EXIT_RESPONSE           "221 Server closing connection\r\n"
#define QUIT_RESPONSE           "221 Goodbye\r\n"
#define FILE_ACTION_OK          "226 Transfer complete\r\n"
#define PASV_RESPONSE           "227 Entering passive mode\r\n"
#define PASS_RESPONSE           "230 User logged in, proceed\r\n"
#define DELE_RESPONSE           "250 File deleted\r\n"
#define CWD_RESPONSE            "250 Directory changed to new directory\r\n"
#define CDUP_RESPONSE           "250 Directory changed to parent directory\r\n"
#define RMD_RESPONSE            "250 Directory deleted\r\n"
#define DIRECTORY_ACTION_OK     "250 Requested file action okay, completed\r\n"
#define MKD_RESPONSE            "257 Directory created\r\n"
#define DIRECTORY_DELETED       "250 Directory deleted\r\n"
#define PWD_RESPONSE            "257 Current directory is\r\n"
#define DIRECTORY_CREATED       "257 Directory created\r\n"
#define DATA_CONNECTION_CLOSED  "226 Closing data connection\r\n"
#define USER_RESPONSE           "331 User name okay, need password\r\n"
#define DATA_CONNECTION_TIMEOUT "421 Data connection timeout\r\n"
#define DATA_CONNECTION_ERROR   "425 Can't open data connection\r\n"
#define INVALID_USERNAME        "430 Invalid username or password\r\n"
#define FILE_ERROR              "451 File error\r\n"
#define INVALID_SEQUENCE        "503 Bad sequence of commands\r\n"
#define INVALID_COMMAND         "500 Invalid command\r\n"
#define INVALID_ARGUMENTS       "501 Invalid number of arguments\r\n"
#define INVALID_ARGUMENT        "501 Invalid argument\r\n"
#define COMMAND_NOT_IMPLEMENTED "502 Command not implemented\r\n"
#define NOT_LOGGED_IN           "530 Not logged in\r\n"
#define FILE_NOT_FOUND          "550 File not found\r\n"
#define INVALID_PERMISSIONS     "550 Permission denied\r\n"
#define INVALID_FILE            "550 Invalid file\r\n"
#define DIRECTORY_ERROR         "550 Directory error\r\n"
#define DIRECTORY_EXISTS        "550 Directory already exists\r\n"
#define DIRECTORY_NOT_FOUND     "550 Directory not found\r\n"
#define DIRECTORY_NOT_EMPTY     "550 Directory not empty\r\n"
#define INVALID_DIRECTORY       "550 Invalid directory\r\n"
#define INVALID_PATH            "550 Invalid path\r\n"