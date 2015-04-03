#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

int main (int argc, char **argv)
{
  xmlDocPtr doc = NULL;
  xmlNodePtr root_node = NULL, node = NULL, node2 = NULL, node3 = NULL;
  doc = xmlNewDoc(BAD_CAST "1.0");

  //library is root_node
  root_node = xmlNewNode(NULL, BAD_CAST "library");
  xmlDocSetRootElement(doc, root_node);
  
  //making new node
  node = xmlNewChild(root_node, NULL, BAD_CAST "video", NULL);
  //child nodes
  xmlNewChild(node, NULL, BAD_CAST "title", BAD_CAST "Man Of Steel");
  xmlNewChild(node, NULL, BAD_CAST "genre", BAD_CAST "Action");
  xmlNewChild(node, NULL, BAD_CAST "release date", BAD_CAST "2013");
  
  //another node
  node2 = xmlNewChild(root_node, NULL, BAD_CAST "video", NULL);
  //child nodes
  xmlNewChild(node2, NULL, BAD_CAST "title", BAD_CAST "Batman");
  xmlNewChild(node2, NULL, BAD_CAST "genre", BAD_CAST "Action");
  xmlNewChild(node2, NULL, BAD_CAST "release date", BAD_CAST "1989");

  //3rd node
  node3 = xmlNewChild(root_node, NULL, BAD_CAST "video", NULL);
  //nodes
  xmlNewChild(node3, NULL, BAD_CAST "title", BAD_CAST "Taken");
  xmlNewChild(node3, NULL, BAD_CAST "genre", BAD_CAST "Action");
  xmlNewChild(node3, NULL, BAD_CAST "release date", BAD_CAST "2006");  

  xmlSaveFormatFileEnc("-", doc, "UTF-8", 1);
  xmlFreeDoc(doc);
  xmlCleanupParser();
  return(0);
}
