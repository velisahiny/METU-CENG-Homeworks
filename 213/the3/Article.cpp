#include "Article.h"

/*#############################
#               NOTE!         #
#    Please don't forget to   #
#     check PDF. Fuctions     #
#    may have more detailed   #
#     tasks which are not     #
#       mentioned here.       #
#############################*/

Article::Article( int table_size,int h1_param, int h2_param )
{
    /*#############################
    #            TO-DO            #
    # Write a default constructor #
    #   for the Article Class     #
    #############################*/
   n=0;
    this->table_size=table_size;
    this->h1_param=h1_param;
    this->h2_param=h2_param;
    table = new std::pair<std::string,int>[table_size] ;

  for(int i=0;i<table_size;i++){
     table[i].first =  EMPTY_KEY;
     table[i].second=  EMPTY_INDEX;
}
}
Article::~Article()
{
    /*#############################
    #             TO-DO           #
    #  Write a deconstructor for  #
    #     the Article Class       #
    #############################*/

    delete[] table;
}

int Article::get( std::string key, int nth, std::vector<int> &path ) const
{
    /*#############################################
    #                    TO-DO                    #
    #      Your get function should return        #
    # the original index (index in the text file) #
    #    of the nth 'key' in the hash table.      #
    #    If there is no such a key, return -1     #
    #    If there is, return the original index   #
    #     In both cases, you need to push each    #
    #          visited index while probing        #
    #           that you calculated until         #
    #      finding the key, to the path vector.   #
    #############################################*/
    int index = -1;

    for (size_t i = 0; i < table_size;i++ ) {

      index=hash_function(key,i);

      if(table[index].first == key){
        nth--;
      }
      if(i){
        path.push_back(index);
      }
      if(table[index].second==EMPTY_INDEX)
        return -1;
      if(nth==0)
        return table[index].second;
    }

    return -1;
}

int Article::insert( std::string key, int original_index )
{
    /*#########################################
    #                 TO-DO                   #
    #      Insert the given key, with the     #
    # original index value (at the text file) #
    #           to the hash table.            #
    #  Return the total number of probes you  #
    #      encountered while inserting.       #
    #########################################*/
    if(getLoadFactor()>MAX_LOAD_FACTOR){
      expand_table();
    }
    int key_int =convertStrToInt(key);
    int i=0,flag,temp;
    int index= hash_function(key,i);
    while(table[index].first != EMPTY_KEY){
      if(table[index].first != key){
        index= hash_function(key,++i);
      }
      if(table[index].first==key){
       if(table[index].second < original_index) {
        index = hash_function(key,++i);
        }
        else{
          temp = table[index].second;
          table[index].second= original_index;
          original_index=temp;
          index=hash_function(key,++i);
        }
      }
    }
    table[index].first=key;
    table[index].second=original_index;
    n++;
    return i;
}


int Article::remove( std::string key, int nth )
{
    /*#########################################
    #                  TO-DO                  #
    #      Remove the nth key at the hash     #
    #                  table.                 #
    #  Return the total number of probes you  #
    #      encountered while inserting.       #
    #   If there is no such a key, return -1  #
    #     If there, put a mark to the table   #
    #########################################*/
    int index,i=0;
    while(nth){
      if(i>=table_size){
        return -1;
      }
      index = hash_function(key,i++);
      if(table[index].first==key){
        nth--;
      }
    }
    if(i&&table[index].first==key){
      table[index].first=EMPTY_KEY;
      table[index].second=MARKED_INDEX;
      n--;
  }
    return i-1;
}

double Article::getLoadFactor() const
{
  return double(n)/table_size;
    /*#########################################
    #                TO-DO                    #
    #      Return the load factor of the      #
    #                table                    #
    #########################################*/
}

void Article::getAllWordsFromFile( std::string filepath )
{
    /*#########################################
    #                  TO-DO                  #
    #       Parse the words from the file     #
    #      word by word and insert them to    #
    #                hash table.              #
    #   For your own inputs, you can use the  #
    #  'inputify.py' script to fix them to    #
    #            the correct format.          #
    #########################################*/
    std::fstream myfile;
    std::string key;
    myfile.open(filepath.c_str());
    char c;
    int i=1;
    while( myfile.get(c)){
      if(c!=' '){
         key += c;
       }
      else {
        insert(key,i++);
        key.clear();
      }
    }
    insert(key,i++);
    key.clear();
    myfile.close();
}

void Article::expand_table()
{
    /*#########################################
    #                  TO-DO                  #
    #   Implement the expand table function   #
    #   in order to increase the table size   #
    #   to the very first prime number after  #
    #      the value of (2*table size).       #
    #         Re-hash all the data.           #
    #       Update h2_param accordingly.      #
    #########################################*/
    int prevsize =table_size;
    table_size = nextPrimeAfter(2*table_size);
    h2_param = firstPrimeBefore(table_size);

    std::pair<std::string,int>* prevtable;
    prevtable = table;
    table= new std::pair<std::string,int>[table_size];
    for(int i=0;i<table_size;i++){
       table[i].first =  EMPTY_KEY;
       table[i].second=  EMPTY_INDEX;
  }
  n=0;
    for(int i =0; i<prevsize;i++){
      if(prevtable[i].first!= EMPTY_KEY)
      insert(prevtable[i].first,prevtable[i].second);
    }
    delete[] prevtable;

}

int Article::hash_function( std::string& key, int i ) const
{
    /*#########################################
    #                TO-DO                    #
    #       Implement the main hashing        #
    #    function. Firstly, convert key to    #
    #    integer as stated in the homework    #
    #      text. Then implement the double    #
    #            hashing function.            #
    #      use convertStrToInt function to    #
    #      convert key to a integer for       #
    #         using it on h1 and h2           #
    #               reminder:                 #
    #            you should return            #
    #    ( h1(keyToInt) + i*h2(keyToınt) )    #
    #            modulo table_size            #
    #########################################*/
    int key_int=convertStrToInt(key);
    int h1_key=this->h1(key_int);
    int h2_key=h2(key_int);
    int sum= h1_key+i*h2_key;

    return sum % table_size;
}

int Article::h1( int key ) const
{
    /*###############################
    #              TO-DO            #
    #      First Hash function      #
    # Don't forget to use h1_param. #
    ###############################*/
    int pop_count=0;
    while(key!=0){
      pop_count+=key%2;
      key=key/2;
    }
    return pop_count*h1_param;
}

int Article::h2( int key ) const
{
    /*###############################
    #              TO-DO            #
    #     Second Hash function      #
    # Don't forget to use h2_param. #
    ###############################*/
    int modulo=key %h2_param;
    int result = h2_param-modulo;
    return result;
}
