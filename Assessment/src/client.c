#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <packedobjects/packedobjects.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

// Details for the XML
#define XML_SCHEMA "basketball.xsd"
#define MAXCHARS 250
#define NUM_PLAYERS 5

// Local IP and port
#define HOST_IP "127.0.0.1"
#define HOST_PORT 6969


int basketball_team(xmlDocPtr doc)
{
  // Message for user
  printf("Welcome! Enter details for your Basketball Team");

  // Nodes to be used for the XML tree creation
  xmlNodePtr root_node = NULL , node = NULL , node2 = NULL;

  // MAXCHARS to be used for user input
  char buffer[MAXCHARS];

  // i to be used in players loop
  int i = 0;

  // Creating xml tree

  // Creating a root node (BasketballTeam) and set it for the whole doc
  root_node = xmlNewNode(NULL, BAD_CAST "BasketballTeam");
  xmlDocSetRootElement(doc, root_node);

  // Clearing buffer ready for use for input
  bzero(buffer, MAXCHARS);


  // User input for Team
  printf("Enter the name of your Team: \n");
  // Error message
  if(fgets(buffer, MAXCHARS, stdin) == NULL)
  {
    fprintf(stderr, "Failed to read your team name\n");
    return (EXIT_FAILURE);
  }
  // Save input in buffer
  strtok(buffer, "\n");
  // Making Team node, child of root_node (BasketballTeam)
  xmlNewChild(root_node, NULL, BAD_CAST "Team" , BAD_CAST buffer);

  // Clean buffer
  bzero(buffer, MAXCHARS);

  //User input for Conference
  printf("Now enter the conference (East or West): \n");
  // Error message
  if(fgets(buffer, MAXCHARS, stdin) == NULL)
  {
    fprintf(stderr, "Failed to read your conference\n");
    return (EXIT_FAILURE);
  }
  // Save input in buffer
  strtok(buffer, "\n");
  // Making Conference node, child of root_node (BasketballTeam)
  xmlNewChild(root_node, NULL, BAD_CAST "Conference" , BAD_CAST buffer);

  // Creating a new parent node (Players)
  node = xmlNewChild(root_node, NULL, BAD_CAST "Players", NULL);

  // Starting loop for Player child of Players
  printf("You will now enter data for 5 players\n");

  for (i = 1; i <= NUM_PLAYERS; i++)
  {
    // Cleaning buffer at start of loop
    bzero(buffer, MAXCHARS);

    // Creating a new subtree (Player)
    node2 = xmlNewChild(node, NULL, BAD_CAST "Player", NULL);

    // User input for Name
    printf("Enter your player's name: \n");
    // Error message
    if(fgets(buffer, MAXCHARS, stdin) == NULL)
    {
      fprintf(stderr, "Failed to read your player's name\n");
      return (EXIT_FAILURE);
    }
    // Save input in buffer
    strtok(buffer, "\n");
    xmlNewChild(node2, NULL, BAD_CAST "Name", BAD_CAST buffer);

    bzero(buffer, MAXCHARS);

    // User input for Age
    printf("Now enter that player's age between 19 and 39: \n");
    // Error message
    if(fgets(buffer, MAXCHARS, stdin) == NULL)
    {
      fprintf(stderr, "Failed to read your player's age\n");
      return (EXIT_FAILURE);
    }
    // Save input in buffer
    strtok(buffer, "\n");
    xmlNewChild(node2, NULL, BAD_CAST "Age", BAD_CAST buffer);

    bzero(buffer, MAXCHARS);

    // User input for Number
    printf("Enter the player's number between 0 and 99: \n");
    // Error message
    if(fgets(buffer, MAXCHARS, stdin) == NULL)
    {
      fprintf(stderr, "Failed to read your player's number\n");
      return (EXIT_FAILURE);
    }
    // Save input in buffer
    strtok(buffer, "\n");
    xmlNewChild(node2, NULL, BAD_CAST "Number", BAD_CAST buffer);

    bzero(buffer, MAXCHARS);

    // User input for Position
    printf("Now enter the player's position from Point Guard, Shooting Guard, Small Forward, Power Forward and Centre: \n");
    // Error message
    if(fgets(buffer, MAXCHARS, stdin) == NULL)
    {
      fprintf(stderr, "Failed to read the player's position\n");
      return (EXIT_FAILURE);
    }
    // Save input in buffer
    strtok(buffer, "\n");
    xmlNewChild(node2, NULL, BAD_CAST "Position", BAD_CAST buffer);

    bzero(buffer, MAXCHARS);

    // User input for player Skill
    printf("Enter the skill from selection Passing, Shooting, Rebounding, Free throw, Dunking and Dribbling: \n");
    // Error message
    if(fgets(buffer, MAXCHARS, stdin) == NULL)
    {
      fprintf(stderr, "Failed to read the player's skill\n");
      return (EXIT_FAILURE);
    }
    // Save input in buffer
    strtok(buffer, "\n");
    xmlNewChild(node2, NULL, BAD_CAST "Skill", BAD_CAST buffer);    
  }
}


int main (int argc, char **argv)
{
  xmlDocPtr doc = NULL;
  packedobjectsContext *pc = NULL;
  char *pdu = NULL;
  ssize_t bytes_sent;
  int       sock;                                                 
  struct    sockaddr_in servaddr;

  // setup socket
  if ( (sock = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
    fprintf(stderr, "Error creating socket.\n");
    exit(EXIT_FAILURE);
  }
  // setup addressing
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family      = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr(HOST_IP);
  servaddr.sin_port        = htons(HOST_PORT); 
  
  // initialise packedobjects
  if ((pc = init_packedobjects(XML_SCHEMA, 0, 0)) == NULL) {
    printf("failed to initialise libpackedobjects");
    exit(1);
  }
  
  // create the data
  doc = xmlNewDoc(BAD_CAST "1.0");
  basketball_team(doc);
  
  // encode the XML DOM
  pdu = packedobjects_encode(pc, doc);
  if (pc->bytes == -1) {
    printf("Failed to encode with error %d.\n", pc->encode_error);
  }

  // make network connection
  if (connect(sock, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
    fprintf(stderr, "Error calling connect()\n");
    exit(EXIT_FAILURE);
  }
  
  // send the pdu across the network
  bytes_sent = send(sock, pdu, pc->bytes, 0);

  if (bytes_sent != pc->bytes) {
    fprintf(stderr, "Error calling send()\n");
    exit(EXIT_FAILURE);
  }

  if ( close(sock) < 0 ) {
    fprintf(stderr, "Error calling close()\n");
    exit(EXIT_FAILURE);
  }  
  
  // free the DOM
  xmlFreeDoc(doc);  
  
  // free memory created by packedobjects
  free_packedobjects(pc);
  
  xmlCleanupParser();
  return(0);
}
