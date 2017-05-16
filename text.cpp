#include "text.h"

class comp{
    public:
    bool operator()(const std::pair<int,std::string>& t,const std::pair<int,std::string>& t1){
        return t.first > t1.first;
    }
};


void top_words_in_book(std::string fname){
    std::ifstream is;
    avl_tree<std::string> words;
    is.open(fname);

    if(!is.is_open())
         return;

    std::string line;
    while (std::getline(is,line)) {
        QStringList list;
        list = QString::fromStdString(line).
                split(QRegExp("(\\s|\\,|\\.|\\:|\\t|\\(|\\)|\\{|\\}|\\!|\\?|\\;)|\\”|\\“|\\-|\\*|\\’|\\‘"),QString::SkipEmptyParts);
        foreach (QString s, list)
            if (s.length() > 3)
                words.insert(s.toLower().toStdString());
    }

    fix_priority_queue<std::pair<int,std::string>,std::vector<std::pair<int,std::string>>,comp> p(40);
    auto it = words.begin();

    while (it != words.end()) {
        p.push({it.count(),*it});
        words.erase(*it);
        it = words.begin();
    }

    std::vector<std::pair<int, std::string>> v;
    p.pop();
    while(!p.empty()){
        v.push_back(p.top());
        p.pop();
    }

    std::ofstream output;
    output.open("D:\\User\\desktop\\Lesson4\\top_words.txt");
    if (output.is_open())
        std::for_each(v.rbegin(),v.rend(),[&](std::pair<int,std::string> i)->void{
            output << i.second << '\t' << i.first << "\n";
        });
}


void top_names_in_book(std::string fname){
    std::ifstream is;
    avl_tree<std::string> words;
    is.open(fname);

    if(!is.is_open())
         return;

    std::string line;
    while (std::getline(is,line)) {
        QStringList list;
        list = QString::fromStdString(line).
                split(QRegExp("(\\s|\\,|\\.|\\:|\\t|\\(|\\)|\\{|\\}|\\!|\\?|\\;)|\\”|\\“|\\-|\\*|\\’|\\|\\‘"),QString::SkipEmptyParts);
        foreach (QString s, list){
            if (s.at(0).isUpper() && s.length() > 3)
                words.insert(s.toStdString());
        }
    }

    fix_priority_queue<std::pair<int,std::string>,std::vector<std::pair<int,std::string>>,comp> p(20);
    auto it = words.begin();

    while (it != words.end()) {
        p.push({it.count(),*it});
        words.erase(*it);
        it = words.begin();
    }

    std::vector<std::pair<int, std::string>> v;
    p.pop();
    while(!p.empty()){
        v.push_back(p.top());
        p.pop();
    }

    std::ofstream output;
    output.open("D:\\User\\desktop\\Lesson4\\top_names.txt");
    if (output.is_open())
        std::for_each(v.rbegin(),v.rend(),[&](std::pair<int,std::string> i)->void{
            output << i.second << '\t' << i.first << "\n";
        });
}


void the_largest_pair_of_anagrams(std::string fname){
    std::ifstream is;
    is.open(fname);

    if(!is.is_open())
         return;

    fix_priority_queue<std::pair<int,std::pair<std::string, std::string>>,
            std::vector<std::pair<int,std::pair<std::string, std::string>>>,comp> p(1);
    std::string line;
    int ind = -1;

    while (std::getline(is,line)) {
        QStringList list;
        ++ind;
        list = QString::fromStdString(line).
                split(QRegExp("(\\s|\\,|\\.|\\:|\\t|\\(|\\)|\\{|\\}|\\!|\\?|\\;)|\\”|\\“|\\-|\\*|\\’|\\|\\‘"),QString::SkipEmptyParts);
        avl_tree<QChar> ch_word;
        //avl_tree<std::string> word;
        foreach(QChar s, list[ind])
            ch_word.insert(s.toLower());
        //word.insert(list[ind]);

        for (size_t i = ind + 1; i < list.length(); ++i){
            unsigned int cnt = 0;
            foreach(QChar s, list[i])
                if (ch_word.find(s.toLower()) == ch_word.end()){
                    ch_word.erase(s.toLower());
                    ++cnt;
                }
            if (ch_word.empty())
                p.push({cnt, {list[ind].toStdString(), list[i].toStdString()}});
            else
                ch_word.clear();

            foreach(QChar s, list[ind])
                    ch_word.insert(s.toLower());

    }
    }

    std::ofstream output;
    output.open("D:\\User\\desktop\\Lesson4\\anagrams.txt");
    if (output.is_open())
        output<< '[' << p.top().second.first << ", " << p.top().second.second << "]" << '\t' << p.top().first;

}


