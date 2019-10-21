#include "SimpleServer.h"

SimpleServer::SimpleServer()
{
	int opt = true;
	int master_socket, addrlen, new_socket, client_socket[4], max_clients = 4, valread;

	char buffer[1025];
	
	struct sockaddr_in address;
	
	fd_set readfds;

	for (int i = 0; i < max_clients; i++)
		client_socket[i] = 0; // un-checks all clients 

	// Initializes the server socket 
	if ((master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Enables the socket to allow multiple connections 
	if (setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof opt) < 0)
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
	printf("Listener on port %d \n", PORT);

	// Specifies the amount of pending connections allowed at once
	if (listen(master_socket, 4) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}

	// Accept the incoming connection  
	addrlen = sizeof address;
	puts("Waiting for connections...");

	// Manages client connections without the need of multi-threading
	while(true)
	{
		// Clears the socket 
		FD_ZERO(&readfds);

		// Add server socket 
		FD_SET(master_socket, &readfds);
		int max_sd = master_socket;

		// Adds a child socket
		for (int i = 0; i < max_clients; i++)
		{
			// Descriptor  
			int sd = client_socket[i];

			// If socket descriptor is valid; add to list  
			if (sd > 0)
				FD_SET(sd, &readfds);

			// Highest file descriptor number, used to determine a function
			if (sd > max_sd)
				max_sd = sd;
		}

		// Listening for any query/activity from current client
		int activity = select(max_sd + 1, &readfds, nullptr, nullptr, nullptr);

		if (activity < 0 && errno != EINTR)
		{
			printf("select error");
		}
		
		// Incoming connection
		if (FD_ISSET(master_socket, &readfds))
		{
			if ((new_socket = accept(master_socket, (struct sockaddr*) & address, (socklen_t*)&addrlen)) < 0)
			{
				perror("accept");
				exit(EXIT_FAILURE);
			}

			// Inform user of socket number - used in send and receive commands  
			printf("New connection | Socket FD: %d | IP: %s | Port: %d\n" , new_socket , inet_ntoa(address.sin_addr) , ntohs (address.sin_port));

			// Greets the client
			char* message = "Connected!\r\n";
			if (send(new_socket, message, strlen(message), 0) != strlen(message))
			{
				perror("send");
			}

			puts("Welcome message sent successfully");

			// Assigns a socket to the client 
			for (int i = 0; i < max_clients; i++)
			{
				if (client_socket[i] == 0)
				{
					client_socket[i] = new_socket;
					break;
				}
			}
		}

		for (int i = 0; i < max_clients; i++)
		{
			int sd = client_socket[i];

			if (FD_ISSET(sd, &readfds))
			{
				// Incoming message  
				if ((valread = read(sd, buffer, 1024)) == 0)
				{
					// Client disconnected
					getpeername(sd, (struct sockaddr*) & address, \
						(socklen_t*)&addrlen);
					
					printf("Host disconnected | IP: %s | Port: %d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));

					//Close the socket and mark as 0 in list for reuse  
					close(sd);
					client_socket[i] = 0;
				}
				else //Echo back the message that came in  
				{
					//set the string terminating NULL byte on the end  
					//of the data read  
					buffer[valread] = '\0';
					send(sd, buffer, strlen(buffer), 0);
				}
			}
		}
	}
}
