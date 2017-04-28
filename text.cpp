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
                split(QRegExp("(\\s|\\,|\\.|\\:|\\t|\\(|\\)|\\{|\\}|\\!|\\?|\\;)|\\”|\\“|\\-|\\*"),QString::SkipEmptyParts);
        foreach (QString s, list)
             words.insert(s.toLower().toStdString());
    }

    priority_queue<std::pair<int,std::string>,std::vector<std::pair<int,std::string>>,comp> p;
    auto it = words.begin();

    while (it != words.end()) {
        p.push({it.count(),*it});
        words.erase(*it);
        it = words.begin();
    }

   fix_priority_queue<std::pair<int,std::string>,std::vector<std::pair<int,std::string>>,comp> p2(40);
    for (auto i = 0; i <= 40; ++i){
        auto temp = p.top();
        p.pop();
        p2.push(temp);
    }

       std::ofstream output;
       output.open("res.txt");
       if (output.is_open())
           output<<"Top words used in "+fname<<std::endl;
       int cnt = 1;
       while(!p2.empty()){
                  cnt++;
                  output<<p2.top().second<<'\t'<<p2.top().first<<"\n";
                  p2.pop();
              }

}

