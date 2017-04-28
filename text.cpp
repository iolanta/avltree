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
    output.open("C:\\Users\\user\\Documents\\Qt\\res.txt");
    if (output.is_open())
        output<<"Top words used in "+fname<<std::endl;
       /* while(!p.empty()){
            cnt++;
            output<<p.top().second<<'\t'<<p.top().first<<"\n";
            p.pop();
        }*/
        std::for_each(v.rbegin(),v.rend(),[&](std::pair<int,std::string> i)->void{
            output << i.second << '\t' << i.first << "\n";
        });
}

