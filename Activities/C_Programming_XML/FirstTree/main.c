#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

int main(int argc, char **argv)
{
  xmlDocPtr doc = NULL;
  xmlNodePtr root_node = NULL, node = NULL;
  doc = xmlNewDoc(BAD_CAST "1.0");
  root_node = xmlNewNode(NULL, BAD_CAST "root");
  xmlDocSetRootElement(doc, root_node);
  xmlNewChild(root_node, NULL, BAD_CAST "node1", BAD_CAST "content of node 1");
  xmlNewChild(root_node, NULL, BAD_CAST "node2", NULL);
  node = xmlNewChild(root_node, NULL, BAD_CAST "node3", 
		     BAD_CAST "this node has attributes");
  xmlNewProp(node, BAD_CAST "attribute", BAD_CAST "yes");
  xmlNewProp(node, BAD_CAST "foo", BAD_CAST "bar");
  xmlSaveFormatFileEnc("-", doc, "UTF-8", 1);
  xmlFreeDoc(doc);
  xmlCleanupParser();
  return(0);
}
