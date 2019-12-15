#include "SimpleServer.h"

SimpleServer::SimpleServer()
{
	int master_socket;
	int client_sockets[4];

	int addrlen;
	int new_socket;
	int option = true;

	char buffer[BUFFER_SIZE];
	
	struct sockaddr_in address;
	fd_set readSet;

	// Initializes default values for the clients
	for (int& i : client_sockets)
	{
		i = 0;
	}
	
	// Initializes the server socket 
	if ((master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Enables the socket to allow multiple connections 
	if (setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char*)&option, sizeof option) < 0)
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
		
	// Configuring the socket
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// Binds the socket to the designated port 
	if (bind(master_socket, (struct sockaddr*) & address, sizeof address) < 0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	// Specifies the amount of pending connections allowed at once
	if (listen(master_socket, MAX_CLIENTS_ALLOWED) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}

	// Done initializing
	addrlen = sizeof address;
	puts("Loaded Successfully, awaiting new connections..."); // printf wouldn't work here

	// Manages client connections without the need of multi-threading
	while(true)
	{
		// Clears the socket 
		FD_ZERO(&readSet);

		// Add server socket 
		FD_SET(master_socket, &readSet);
		int max_sd = master_socket;

		// Adds a child socket
		for (int sd : client_sockets)
		{
			// Descriptor  
			// If socket descriptor is valid; add to list  
			if (sd > 0)
				FD_SET(sd, &readSet);

			// Highest file descriptor number, used to determine a function
			if (sd > max_sd)
				max_sd = sd;
		}

		// Listening for any query/activity from current client
		const int activity = select(max_sd + 1, &readSet, nullptr, nullptr, nullptr);

		if (activity < 0 && errno != EINTR)
		{
			printf("select error");
		}
		
		// Check for incoming connections on the listening socket 
		if (FD_ISSET(master_socket, &readSet))
		{
			// Attempts to accept the pending connection
			if ((new_socket = accept(master_socket, (struct sockaddr*) & address, (socklen_t*)&addrlen)) < 0)
			{
				perror("accept");
				exit(EXIT_FAILURE);
			}

			// Printed to server 
			printf("New connection | Socket FD: %d | IP: %s | Port: %d\n" , new_socket , inet_ntoa(address.sin_addr) , ntohs (address.sin_port));

			// Response sent to Client 
			char* message = "Connection Accepted!\n";
			send(new_socket, message, strlen(message), 0);

			// Assigns a socket to the client 
			for (int& i : client_sockets)
			{
				if (i == 0)
				{
					i = new_socket;
					break;
				}
			}
		}

		for (int& i : client_sockets)
		{
			// The socket assigned to this client
			int sd = i;

			// Checks for arriving messages from the client 
			if (FD_ISSET(sd, &readSet))
			{
				// Incoming data sent to the server 
				int result = read(sd, buffer, BUFFER_SIZE);
				
				// Check for disconnection 
				if (result == 0 || result == -1)
				{
					// Client disconnected, fetch client info and terminate 
					getpeername(sd, (struct sockaddr*)& address, (socklen_t*)&addrlen);

					// Print to server console
					printf("Host disconnected | IP: %s | Port: %d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));

					// Terminates the client
					close(sd);
					i = 0;
					continue;
				}

				// Mark a null character at the end of the string to differentiate data
				buffer[result] = '\0';

				// Sends back the message which got sent to the server (echo)
				send(sd, buffer, sizeof buffer, 0);
			}
		}
	}
}
