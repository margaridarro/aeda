#include "Gallery.h"
#include <ostream>
using namespace std;

Gallery::Gallery(vector<Paint*> c): catalog(PaintCatalogItem("", "", 0, 0.00)), collection(c) {

}

vector<Paint*> Gallery::getCollection() const {
    return collection;
}

void Gallery::setCollection(vector<Paint*> c) {
    collection = c;
}

priority_queue<ExhibitionItem> Gallery::getPaintsToShow() const {
    return paintsToShow;
}
HashTableAuthorRecord Gallery::getAuthorRecords () const {
    return  authorRecords;
}

void Gallery::addAuthorRecord(AuthorRecord ar) {
    authorRecords.insert(ar);
}

void Gallery::generateCatalog() {
    catalog.makeEmpty();
    for(int i = 0; i < collection.size(); i++) {
        catalog.insert(collection[i]);
    }
}

BST<PaintCatalogItem> Gallery::getCatalog() const {
    return catalog;
}


void Gallery::prepareExhibition() {
    while( !paintsToShow.empty())
        paintsToShow.pop();
    for(int i = 0; i < collection.size(); i++) {
        ExhibitionItem ei(collection[i]);
        paintsToShow.push(ei);
    }
}

//-------------------------------------------------------------------------------

vector<Paint*> Gallery::getPaintsBy(string a) const {
    vector<Paint*> tmp;
    BSTItrIn<PaintCatalogItem> bItr(catalog);
    for(; !bItr.isAtEnd(); bItr.advance()){
        auto elem = bItr.retrieve();
        if(elem.getAuthor() == a){
            tmp.push_back(elem.getPaint());
        }
    }
    return tmp;
}

vector<Paint*> Gallery::getPaintsBetween(int y1, int y2) const {
    vector<Paint*> tmp;
    tmp.clear();
    BSTItrIn <PaintCatalogItem> it(catalog);
    while(!it.isAtEnd())
    {
        PaintCatalogItem paint = it.retrieve();
        if(paint.getYear() >= y1 && paint.getYear() <= y2)
            tmp.push_back(paint.getPaint());
        it.advance();
    }
    return tmp;
}

bool Gallery::updateTitle(Paint* p, string tnew) {
    if(!catalog.remove(PaintCatalogItem(p))) return false;
    PaintCatalogItem newPaint(p->getAuthor(),tnew, p->getYear(), p->getPrice());
    catalog.insert(newPaint);
    return true;
}


int Gallery::recordAvailablePainters() { //carrega a tabela de dispersao com AuthorRecords
    AuthorRecord authortmp("");
    for(auto& elem: collection){
        authortmp = AuthorRecord(elem->getAuthor());
        for(auto& author: authorRecords){
            if(elem->getAuthor() == author.getAuthor()){
                authortmp = author;
                authortmp.addAvaliablePaint();
                authorRecords.erase(author.getAuthor());
                break;
            }
        }
        authorRecords.insert(authortmp);
    }
    return authorRecords.size();
}

//TODO
double Gallery::totalSells() const {
    return 0.0;
}

//TODO
double Gallery::sellPaint(string a, string t) {
    return 0.0;
}

//TODO
vector<Paint*> Gallery::nBestExibition(int n, int maxPerYear) {  //escolhe as N mais caras pinturas, dos anos mais antigos, para realizar uma exposição
    vector<Paint*> tmp;
    return tmp;
}

//TODO
int Gallery::itemExibitionOrder(string a, string t) {
    return 0;
}

