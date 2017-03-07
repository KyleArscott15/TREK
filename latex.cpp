#include "latex.h"
#include <fcntl.h>
#include <unistd.h>

Latex::Latex() {}

Latex::~Latex() {}

int Latex::savePackingList(map<string,
                               Frame>list,
                           map<string, All_type>optional,
                           vector<string>notes) {
  string latexAll = string("");

  string latexBegin = string(
    "\\documentclass[12pt]{article} \n \
	\n \
	\\usepackage{float} \n \
	\\usepackage{geometry} \n \
	\\usepackage{fancyhdr} \n \
	\\usepackage{longtable} \n \
	\\usepackage{placeins} \n \
	\\usepackage{enumitem} \n \
	\n \
	% times new roman font \n \
	\\usepackage[T1]{fontenc} \n \
	\\usepackage[utf8]{inputenc} \n \
	\\usepackage{mathptmx} \n \
	\n \
	\\pagestyle{fancy} \n \
	\\geometry{margin=0.5in} \n \
	\\setlength{\\parindent}{30pt} \n \
	\n \
	\\title{TREK \\\\ Packing List} \n \
	\n \
	\\begin{document} \n \
	\n \
	\\maketitle \n \
	\n \
	\\iffalse \n \
	\\fi \n \
	\n \
	\\noindent \n \
	\\section{Packing List Items} \n \
	\\FloatBarrier \n \
	\\begin{longtable}{|p{1.5in}|p{0.75in}|p{4.75in}|} \\hline \n \
		\\textbf{Item} & \\textbf{Quantity} & \\textbf{Notes about Item} \\ \\hline  \n");

  string latexMiddle = string(
    " \
	\\end{longtable} \n \
	\\FloatBarrier \n \
	 \n \
	\\section{General Notes} \n \
	\\begin{enumerate}[itemsep=-1ex] \n \
		\\item Affirmer offers the Work as-is and makes no representations or \n \
		warranties of any kind concerning the Work, express, implied, \n \
		statutory or otherwise, including without limitation warranties of \n \
		title, merchantability, fitness for a particular purpose, non \n \
		infringement, or the absence of latent or other defects, accuracy, or \n \
		the present or absence of errors, whether or not discoverable, all to \n \
		the greatest extent permissible under applicable law. \n ");

  string latexEnd = string(
    " \
	\\end{enumerate} \n \
	\n \n\
	\\end{document} \n ");

  // construct the latex document
  latexAll += latexBegin;

  for (map<string, Frame>::iterator it = list.begin();
       it != list.end();
       ++it) {
    string line = string("");
    line += it->second.getName();
    line += string(" & ");
    line += to_string(it->second.getQuantity());
    line += string(" & ");
    line += it->second.getUserNote();
    line += string(" \\ \\hline \n");

    latexAll += line;
  }
  latexAll += latexMiddle;

  for (vector<string>::iterator it = notes.begin();
       it != notes.end();
       ++it) {
    latexAll += string("\\item ");
    latexAll += *it;
    latexAll += string(" \\ \\hline \n");
  }
  latexAll += latexEnd;


#define LATEX_PACKING_LIST_OUTPUT_FILE "./latex/packingList.tex"
#define LATEX_PACKING_LIST_OUTPUT_FILE_BASE "./latex/packingList"
  int fd = open(
    LATEX_PACKING_LIST_OUTPUT_FILE,
    O_WRONLY | O_CREAT | O_TRUNC,
    S_IWGRP  | S_IRGRP | S_IRUSR | S_IWUSR);

#define EXTRA_PADDING (10)
  char buffer[latexAll.length() + EXTRA_PADDING];

  bzero(buffer, latexAll.length() + EXTRA_PADDING);
  memcpy(buffer, latexAll.c_str(), latexAll.length());
  write(fd, buffer, strlen(buffer));
  close(fd);

  // turn the latex into a pdf
  string command = string(
    "pdflatex -synctex=1 -interaction=nonstopmode -output-directory=./latex/ \"");
  command += string(LATEX_PACKING_LIST_OUTPUT_FILE_BASE);
  command += string("\".tex > /dev/null");
  D(LAT, "Command[%s] \n ", command.c_str());
  system(command.c_str());

  return -1;
}
