#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

int main (int argc, char **argv)
{
  xmlDocPtr doc = NULL;
  xmlNodePtr root_node = NULL , node = NULL;
  doc = xmlNewDoc(BAD_CAST "1.0");
  root_node = xmlNewNode(NULL, BAD_CAST "student");
  xmlDocSetRootElement(doc, root_node);
  xmlNewChild(root_node, NULL, BAD_CAST "id", BAD_CAST "9999");
  xmlNewChild(root_node, NULL, BAD_CAST "active", BAD_CAST "true");
  node = xmlNewChild(root_node, NULL, BAD_CAST "name", NULL);
  xmlNewChild(node, NULL, BAD_CAST "fname", BAD_CAST "John");
  xmlNewChild(node, NULL, BAD_CAST "sname", BAD_CAST "Doe");
  xmlSaveFormatFileEnc("-", doc,  "UTF-8", 1);
  xmlFreeDoc(doc);
  xmlCleanupParser();
  return(0);
}
