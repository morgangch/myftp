# FTP Server

This project implements a simple FTP server in C++ that adheres to the specifications outlined in RFC 959. The server supports multiple clients simultaneously and handles FTP commands using a blocking TCP socket approach. 

## Project Structure

The project is organized into the following directories:

- **include/**: Contains header files for various classes used in the FTP server.
  - `auth.hpp`: User authentication management.
  - `client.hpp`: Client connection and state management.
  - `command_handler.hpp`: Parsing and executing FTP commands.
  - `ftp_constants.hpp`: Constants used throughout the server.
  - `ftp_server.hpp`: Main server setup and loop.
  - `session.hpp`: Management of individual client sessions.
  - `transfer.hpp`: Data transfer operations in active and passive modes.

- **src/**: Contains the implementation files for the server.
  - `auth.cpp`: Implementation of authentication methods.
  - `client.cpp`: Implementation of client management.
  - `command_handler.cpp`: Implementation of command handling.
  - `ftp_server.cpp`: Main server loop and client management.
  - `main.cpp`: Entry point of the application.
  - `session.cpp`: Implementation of session management.
  - `transfer.cpp`: Implementation of data transfer methods.

- **Makefile**: Build instructions for compiling the project using g++.

## Features

- **TCP Sockets**: The server uses TCP sockets for network communication.
- **Blocking Mode**: All socket operations are performed in blocking mode.
- **Multiple Clients**: Supports multiple clients using `poll` for I/O management.
- **Authentication**: Supports an Anonymous account with an empty password.
- **FTP Commands**: Implements mandatory FTP commands including USER, PASS, LIST, RETR, STOR, and QUIT.
- **Data Transfer Modes**: Supports both active and passive data transfer modes as per RFC 959.

## Build Instructions

To compile the project, navigate to the project directory and run:

```bash
make
```

This will generate the executable for the FTP server.

## Usage

After building the project, you can start the FTP server by running the executable. The server will listen for incoming client connections and handle FTP commands as specified.

## Contributing

Contributions are welcome! Please feel free to submit issues or pull requests for improvements or bug fixes.

## License

This project is licensed under the MIT License. See the LICENSE file for more details.