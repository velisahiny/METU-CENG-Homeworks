#ifndef _title_h__
#define _title_h__

#include "book.hpp"
#include <cstring>

class TitleComparator
{
  public:
    bool operator( ) (const Book::SecondaryKey & key1,
                      const Book::SecondaryKey & key2) const
    {
      //if key1 is less than key2 wrt specifications
    int i;
      for (i=0;key1.getTitle()[i]&&key2.getTitle()[i];i++){
        int k1=key1.getTitle()[i];
        int k2 = key2.getTitle()[i];
        if(k1>96)
          k1-= 32;
        if(k2>96)
          k2-=32;
        if(k1<k2)
        return true;
      //return true
      else if(k1>k2)
        return false;
    }

      if(!key1.getTitle()[i]){
        if(key2.getTitle()[i])
          return true;
      }
      else if(!key2.getTitle()[i]){
        return false;
      }
      if(!key1.getTitle()[i]&& !key2.getTitle()[i]){
        for (i=0;key1.getAuthor()[i]&&key2.getAuthor()[i];i++){
          int k1=key1.getAuthor()[i];
          int k2 = key2.getAuthor()[i];
          if(k1>96)
            k1-= 32;
          if(k2>96)
            k2-=32;
          if(k1<k2)
            return true;
          else if(k1>k2)
            return false;
      }
      if( !key1.getAuthor()[i] ){
        if(key2.getAuthor()[i])
          return true;
        }
      else if(!key2.getAuthor()[i]){
        return false;
      }
      if(!key1.getAuthor()[i]&&!key2.getAuthor()[i])
        return false;
      //otherwise
      //return false
    }
    return false;
    }

};
#endif
