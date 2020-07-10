#include "HistoryRecord.hpp"

std::ostream &operator<<(std::ostream &out, const HistoryRecord& t){
    out <<"<";
    if (t.operation==INSERT) out <<"INSERT:";
    if (t.operation==DELETE) out <<"DELETE:";
    if (t.operation==REVERSE) out <<"REVERSE:";
    out << t.entry <<">";
    return out;
};
/* TO-DO: method implementations below */
HistoryRecord::HistoryRecord(){
  operation = Operation();
  entry = Entry();
}
HistoryRecord::HistoryRecord(Operation oper, Entry e){
  entry = e;
  operation = oper;
}
Operation HistoryRecord::getOperation() const{
  return operation;
}
Entry HistoryRecord::getEntry() const{
  return entry;
}
