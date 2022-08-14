/* Vaclav Bohac (c) 2012 - Problem No. 848 in C++ */

#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>


using namespace std;


/* Max width of the line. */
const int MAX_WIDTH = 72;

/* Whitespace (Knuth calls it the glue). */
const char GLUE = ' ';

/* Single paragraph. */
typedef vector<string> paragraph;


/* Returns formated paragraphs. */
vector<paragraph> fmt (const vector<paragraph>, const int);

/* Formats single paragraph */
static paragraph fmt_paragraph (const paragraph, const int);

/* Prints the whole file. */
static void print_file(const vector<paragraph>);

/* Trims string from right. */
static inline std::string &rtrim(std::string &s);


int main (void) {
    vector<paragraph> file;

    string line;
    bool notend;

    do {
        paragraph p; /* Load paragraph. */
        while ((notend = getline(cin, line)) && line.size()) {
            p.push_back(line);
        }

        file.push_back(p);
    } while (notend); /* Until end of file. */

    print_file(fmt(file, MAX_WIDTH));

    return EXIT_SUCCESS;
}

static void print_file (const vector<paragraph> file) {
    for (unsigned int j, i = 0; i < file.size(); i++) {
        for (j = 0; j < file[i].size(); j++) {
            cout << file[i][j] << endl;
        }

        /* If not last or empty line. */
        if (i < file.size() - 1 && file[i][j - 1][0]) {
            cout << endl;
        }
    }
}

static paragraph fmt_paragraph (const paragraph p, const int max_width) {
    paragraph q;
    stringstream line;

    /* For each line in the paragraph. */
    for (int i = 0; i < p.size(); i++) {
        if (i > 0 && p.size() && p[i][0] == GLUE) { /* Nonbreakable space */
            string s = line.str();
            q.push_back(rtrim(s));
            line.str("");
        }

        if (line.str().size()) {
            line << GLUE;
        }

        for (int k, j = 0, l = p[i].size(); j < l; j++) {
            if (p[i][j] == GLUE) { /* Char is a glue. */
                line << p[i][j];

            } else { /* Is a box. */
                /* Get word length. */
                for (k = j; k < p[i].size(); k++) {
                    if (p[i][k] == GLUE) {
                        break;
                    }
                }

                /* Fits on the line? */
                if (line.str().size() + k - j > max_width) {
                    string s = line.str();
                    q.push_back(rtrim(s));
                    line.str("");
                }

                /* Copy word. */
                while (j < k) {
                    line << p[i][j++];
                }

                j -= 1;
            }
        }
    }

    string s = line.str();
    q.push_back(rtrim(s));
    line.str("");

    return q;
}

vector<paragraph> fmt (const vector<paragraph> in, const int max_width) {
    vector<paragraph> out;
    for (unsigned int i = 0; i < in.size(); i++) {
        out.push_back(fmt_paragraph(in[i], max_width));
    }
    return out;
}

static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}