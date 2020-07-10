#include "bookstore.hpp"

BookStore::BookStore( ) //implemented, do not change
{
}

void
BookStore::insert(const Book & book)
{
    primaryIndex.insert(book.getISBN(),book);
    BSTP::Iterator it = primaryIndex.find(book.getISBN());
    SKey skey(*it);
        secondaryIndex.insert(skey,&(*it));

    ternaryIndex.insert(skey,&(*it));

}

void
BookStore::remove(const std::string & isbn)
{
  BSTP::Iterator it = primaryIndex.find(isbn);
  if(it==primaryIndex.end())
    return ;
  SKey skey(*it);
  ternaryIndex.remove(skey);
  secondaryIndex.remove(skey);
  primaryIndex.remove(isbn);



}
void
BookStore::remove(const std::string & title , const std::string & author){
 SKey skey(title, author);
  BSTT::Iterator it= ternaryIndex.find(skey);
  if(it==ternaryIndex.end()) return;
  std::string isbn = (*it)->getISBN();
  ternaryIndex.remove(skey);
  secondaryIndex.remove(skey);
  primaryIndex.remove(isbn);
}
void
BookStore::removeAllBooksWithTitle(const std::string & title){

  BSTT::Iterator itend = ternaryIndex.end();
  std::list<std::string> isb;

  for(BSTT::Iterator it=ternaryIndex.begin();it!=itend;++it){
    std::string str1( (*it)->getTitle());
    for(size_t i = 0; i<str1.size(); i++)if(str1[i] > 64 && str1[i] < 91)str1[i]+=32;
    if (str1 == title){
        while(it != itend && str1==title){
            isb.push_back((*it)->getISBN());
            ++it;
            if(it != itend) str1=(*it)->getTitle();
            for(size_t i = 0; i<str1.size(); i++)if(str1[i] > 64 && str1[i] < 91)str1[i]+=32;

        }
        for(std::list<std::string>::iterator i = isb.begin(); i!= isb.end(); i++)
                    this->remove(*i);
                return;

    }
  }
  for(std::list<std::string>::iterator i = isb.begin(); i!= isb.end(); i++)
                    this->remove(*i);
}
void
BookStore::makeAvailable(const std::string & isbn)
{
  BSTP::Iterator it = primaryIndex.find(isbn);
  if(it==primaryIndex.end()) return;
  (*it).setAvailable();
}

void
BookStore::makeUnavailable(const std::string & title,
                           const std::string & author)
{
  SKey skey(title,author);
  BSTT::Iterator it= ternaryIndex.find(skey);
  if (it==ternaryIndex.end()) return;
  (*it)->setUnavailable();
}

void
BookStore::updatePublisher(const std::string & author,
                           const std::string & publisher)
{
    BSTP::Iterator it;
    for(it=primaryIndex.begin();it!=primaryIndex.end();++it){
      if ((*it).getAuthor()==author){
        (*it).setPublisher(publisher);
      }
    }
}

void
BookStore::printBooksWithISBN(const std::string & isbn1,
                              const std::string & isbn2,
                              unsigned short since) const
{
  std::list< BSTP::Iterator> it_list;
  it_list = primaryIndex.find(isbn1,isbn2);
  while(!it_list.empty()) {
      if((*(it_list.front())).getYear() >= since )
        std::cout<<*(it_list.front())<<std::endl;
      it_list.pop_front();
  }
}

void
BookStore::printBooksOfAuthor(const std::string & author,
                              const std::string & first,
                              const std::string & last) const
{
  SKey skey_first(first,author),skey_last(last,author);
  std::list<BSTS::Iterator> it_list;
  it_list=secondaryIndex.find(skey_first,skey_last);
 while(!it_list.empty()) {
        std::cout<<**(it_list.front())<<std::endl;
      it_list.pop_front();

}

}

void //implemented, do not change
BookStore::printPrimarySorted( ) const
{
  BSTP::Iterator it;

  for (it=primaryIndex.begin(); it != primaryIndex.end(); ++it)
  {
    std::cout << *it << std::endl;
  }
}

void //implemented, do not change
BookStore::printSecondarySorted( ) const
{
  BSTS::Iterator it;

  for (it = secondaryIndex.begin(); it != secondaryIndex.end(); ++it)
  {
    std::cout << *(*it) << std::endl;
  }
}

void //implemented, do not change
BookStore::printTernarySorted( ) const
{
  BSTT::Iterator it;

  for (it = ternaryIndex.begin(); it != ternaryIndex.end(); ++it)
  {
    std::cout << *(*it) << std::endl;
  }
}
