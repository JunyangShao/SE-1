//
// Created by jxq96 on 2019/3/21.
//

void  mostWords2(map<char, vector<pair<string, bool>>>*words){
    char c = 'a';
    for(;c<='z';c++){
        if(words->count(c)) {
            tmpresult->push_back((*words)[c][0].first);
            (*words)[c][0].second = true;
            used[c-GAP] ++ ;
            search(words,c,0);
            tmpresult->pop_back();
            (*words)[c][0].second = false;
            used[c-GAP] -- ;
        }
    }
}

void search(map<char, vector<pair<string, bool>>>*words,char start,int index){

    char next = (*words)[start][index].first.at((*words)[start][index].first.size()-1);
    if(!words->count(next) || used[next-GAP] == (*words)[next].size()){
        if(result->empty()){
            result->push_back(*tmpresult);
        }
        else{
            if((*result)[0].size() < tmpresult->size()){
                result->clear();
                result->push_back(*tmpresult);
            }
            else if((*result)[0].size() == tmpresult->size()){
                result->push_back(*tmpresult);
            }
        }
        return;
    }
    else{
        for(int i = 0;i<(*words)[next].size();i++){
            if(!(*words)[next][i].second){
                tmpresult->push_back((*words)[next][i].first);
                (*words)[next][i].second = true;
                used[next-GAP]++;
                search(words,(*words)[next][i].first.at(0),i);
                tmpresult->pop_back();
                (*words)[next][i].second = false;
                used[next-GAP] -- ;
            }
            else{
                continue;
            }
        }
    }
}