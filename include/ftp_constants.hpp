#ifndef FTP_CONSTANTS_HPP
#define FTP_CONSTANTS_HPP

// FTP response codes
const int FTP_RESPONSE_OK = 200;
const int FTP_RESPONSE_COMMAND_OK = 250;
const int FTP_RESPONSE_USER_LOGGED_IN = 230;
const int FTP_RESPONSE_NOT_LOGGED_IN = 530;
const int FTP_RESPONSE_SYNTAX_ERROR = 501;
const int FTP_RESPONSE_SERVICE_NOT_AVAILABLE = 421;
const int FTP_RESPONSE_DATA_CONNECTION_OPEN = 125;
const int FTP_RESPONSE_DATA_CONNECTION_CLOSED = 226;

// Buffer sizes
const int BUFFER_SIZE = 1024;
const int MAX_CLIENTS = 10;

// FTP command strings
const char* const USER_COMMAND = "USER";
const char* const PASS_COMMAND = "PASS";
const char* const LIST_COMMAND = "LIST";
const char* const RETR_COMMAND = "RETR";
const char* const STOR_COMMAND = "STOR";
const char* const QUIT_COMMAND = "QUIT";

// Other constants
const char* const ANONYMOUS_USER = "anonymous";
const char* const ANONYMOUS_PASSWORD = "";

#endif // FTP_CONSTANTS_HPP