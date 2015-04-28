#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

int main (int argc, char **argv)
{
  xmlDoctPtr doc = NULL;
  xmlNodePtr root_node = NULL, node = NULL;
  doc = xmlNewDoc(BAD_CAST "1.0");
  root_node = xmlNewNode(NULL, BAD_CAST "BasketballTeam");
  xmlDocSetRootElement(doc, root_node);
  xmlNewChild(root_node, NULL, BAD_CAST "Team", BAD_CAST "Miami Heat");
  xmlNewChild(root_node, NULL, BAD_CAST "Conference", BAD_CAST "East");
  node = xmlNewChild(root_node, NULL, BAD_CAST "Player", NULL);
  xmlNewChild(node, NULL, BAD_CAST "Name", BAD_CAST "John Doe");
  xmlNewChild(node, NULL, BAD_CAST "Age", BAD_CAST "28");
  xmlNewChild(node, NULL, BAD_CAST "Number", BAD_CAST "7");
  xmlNewChild(node, NULL, BAD_CAST "Position", BAD_CAST "Point Guard");
  xmlNewChild(node, NULL, BAD_CAST "Skill", BAD_CAST "Passing");
  xmlSaveFormatFileEnc("-", doc, "UTF-8", 1);
  xmlFreeDoc(doc);
  xmlCleanupParser();
  return(0);    
}
