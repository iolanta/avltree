#ifndef TEXT_H
#define TEXT_H

#include <iostream>
#include <utility>
#include <string>
#include <fstream>
#include <QString>
#include <QRegExp>
#include <vector>
#include <QStringList>
#include <algorithm>

#include "avl_tree.h"
#include "pr_queue.h"

void top_words_in_book(std::string fname);

void top_names_in_book(std::string fname);

void the_largest_pair_of_anagrams(std::string fname);

#endif // TEXT_H
