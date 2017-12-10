#include "opend.h"

#define NALLOC 10     /* # client structs to alloc/realloc for */

static void
client_alloc()		  /* alloc more entries in the client[] array */
{
	int i, pre_size;

	if (client == NULL) {
		client = malloc(sizeof(Client) * NALLOC);
	} else {
		client = realloc(client, sizeof(Client) * (client_size + NALLOC));
	}
	
	if (client == NULL)
		err_sys("can't alloc for client array");	

	pre_size = client_size;
	client_size += NALLOC;
	for (i = pre_size; i < client_size; i++)
		client[i].fd = -1;      /* fd of -1 means entry available */
}

/*
 * Called by loop() when connection request from a new client arrives.
 */
int
client_add(int fd, uid_t uid)
{
	int i;

	if (client == NULL)         /* first time we're called */
		client_alloc();
	
	for (i = 0; i < client_size; i++)
		if (client[i].fd == -1) {  /* find an available entry */
			break;
		}
	
	/* client array full, time to realloc for more */
	if (i == client_size)    
		client_alloc();
	
	/* fill client[i] with fd and uid */
	client[i].fd = fd;
	client[i].uid = uid;

	return (i);       /* return index in client[] array */
}

void 
client_del(int fd)
{
	int i;

	if (client == NULL)
		err_quit("client_del error: client == NULL");

	for (i = 0; i < client_size; i++) {
		if (client[i].fd == fd) {
			client[i].fd = -1;
			return;
		}
	}
	err_quit("can't find client entry for fd %d", fd);
	// shall we free client when process end 
}

