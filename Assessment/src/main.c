#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

int main (int argc, char **argv)
{
  // XML details
  xmlDocPtr doc = NULL;
  xmlNodePtr root_node = NULL , node = NULL , node2 = NULL;
  doc = xmlNewDoc(BAD_CAST "1.0");

  // Creating xml tree

  // Creating a root node (BasketballTeam) and set it for the whole doc
  root_node = xmlNewNode(NULL, BAD_CAST "BasketballTeam");
  xmlDocSetRootElement(doc, root_node);

  // Creating children for the root node

  // Making Team node, child of root_node (BasketballTeam)
  xmlNewChild(root_node, NULL, BAD_CAST "Team" , BAD_CAST "Heat");

  // Making Conference node, child of root_node (BasketballTeam)
  xmlNewChild(root_node, NULL, BAD_CAST "Conference" , BAD_CAST "East");

  // Creating a new parent node (Players)
  node = xmlNewChild(root_node, NULL, BAD_CAST "Players", NULL);

  // Creating a new subtree (Player)
  node2 = xmlNewChild(node, NULL, BAD_CAST "Player", NULL);

  // Making children for node2 (Player)

  // Node Name
  xmlNewChild(node2, NULL, BAD_CAST "Name", BAD_CAST "John Doe");

  // Node Age
  xmlNewChild(node2, NULL, BAD_CAST "Age", BAD_CAST "28");

  // Node Number
  xmlNewChild(node2, NULL, BAD_CAST "Number", BAD_CAST "7");

  // Node Position
  xmlNewChild(node2, NULL, BAD_CAST "Position", BAD_CAST "Point Guard");

  // Node Skill
  xmlNewChild(node2, NULL, BAD_CAST "Skill", BAD_CAST "Passing");

  // More XML details
  xmlSaveFormatFileEnc("-", doc, "UTF-8", 1);
  xmlFreeDoc(doc);
  xmlCleanupParser();
  return(0);
}
