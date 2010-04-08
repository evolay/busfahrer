#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include "ParserDom.h"

using namespace std;
using namespace htmlcxx;

int main(int argc, char *argv[]) {
  if (argc == 1) {
    fprintf(stderr, "give HTML file to analyze, exit.\n");
    exit(EXIT_FAILURE);
  }

  FILE *f = fopen(argv[1], "rt");
  if (!f) {
    fprintf(stderr, "failed to open '%s', exit.\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  // read file
  fseek(f, 0, SEEK_END);
  int flen = ftell(f);
  char *buf = (char *)malloc(flen);
  fseek(f, 0, SEEK_SET);
  fread(buf, 1, flen, f);
  fclose(f);

  //Parse some html code
  // string html = "<html><body>hey<a href=\"http://www.fh-salzburg.ac.at\">fh</a></body></html>";
  string html(buf);
  HTML::ParserDom parser;
  tree<HTML::Node> dom = parser.parseTree(html);

  //Dump all links in the tree
  tree<HTML::Node>::iterator it = dom.begin();
  tree<HTML::Node>::iterator end = dom.end();
  for (; it != end; ++it)
  {
    if (it->tagName() == "a")
    {
        it->parseAttributes();
        pair<bool, string> link = it->attribute("href");
        if (link.first)
            cout << link.second << endl;
    }
  }

  return EXIT_SUCCESS;
}
