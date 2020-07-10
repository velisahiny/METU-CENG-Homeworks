package ceng.ceng351.labdb;

import static java.lang.Math.pow;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map.Entry;
import java.util.Set;



public class LabDB {
HashMap<Integer,Bucket> directory;
int bucketSize;
int globalDepth;


    public LabDB(int bucketSize) {
        this.bucketSize=bucketSize;
        globalDepth=1;
        Bucket b0= new Bucket(bucketSize,globalDepth);
       Bucket b1= new Bucket(bucketSize,globalDepth);
       directory=new HashMap<Integer,Bucket>();
        directory.put(0, b0);
        directory.put(1,b1);
    }

    public void enter(String studentID) {
        if(studentID.charAt(0)!='e'){
            return;
        } 
        String str = studentID.substring(1);
        int id = Integer.parseInt(str);
        int index = hash(id,globalDepth);
        Bucket b = directory.get(index);
        if(b.enterID(studentID)){
           return; 
        }
        else{//bucket is full
            ArrayList<String> list = new ArrayList<String>();
            list.addAll(b.getList());
            list.add(studentID);
            int localDepth=b.getlocalDepth();
            int newlocalDepth = localDepth+1;
            b.clear();
            //split required but not doubling
            if(localDepth<globalDepth){
                 
                b.setlocalDepth(newlocalDepth);
                Bucket newBucket= new Bucket(bucketSize,newlocalDepth);
                int splitIndex= index + (int) pow(2,localDepth);
                int splitBits = splitIndex % (int) pow(2,(newlocalDepth));
                int lastlocalDepthBits = index % (int) pow(2,(newlocalDepth));
                int tableSize = (int) pow(2,globalDepth);
               
                for(int i=0; i<tableSize; i++){
                    int hashValue = i % (int )  pow(2,newlocalDepth ); 
                    if(hashValue==lastlocalDepthBits){
                        directory.put(i, b);
                    }
                    else if(hashValue==splitBits){
                        directory.put(i,newBucket);
                    }
                }
                for(String s: list){
                    this.enter(s);
                }
            }
            else{//split with doubling
                
                int tableSize = (int) pow(2,globalDepth);
                for(int i=0;i<tableSize;i++){
                     Bucket temp = directory.get(i);
                     directory.put(i+tableSize,temp );
                }
                Bucket newBucket= new Bucket(bucketSize,newlocalDepth);
                b.setlocalDepth(newlocalDepth);
                int splitIndex;
                if(index<tableSize){
                     splitIndex=index+tableSize;
                 }
                else{
                     splitIndex=index-tableSize;
                 }
                directory.put(index, b);
                directory.put(splitIndex, newBucket);
                globalDepth++;
               
                for(String s: list){
                    this.enter(s);
                }
            }
            
        }
            
        
    }

    public void leave(String studentID) {
     String str = studentID.substring(1);
        int id = Integer.parseInt(str);
        int index = hash(id,globalDepth);
        Bucket b = directory.get(index);
        ArrayList<String> list=b.getList();
            if(b.leaveID(studentID)){//empty
                int temp= (int) pow(2,b.getlocalDepth()-1);
                Bucket buddy ;
                if(index-temp>=0){
                    buddy=directory.get(index-temp);
                }
                else{
                    buddy=directory.get(index+temp);
                }
                if(buddy.getlocalDepth()==b.getlocalDepth()){
                    buddy.setlocalDepth(buddy.getlocalDepth()-1);
                    int localDepth =b.getlocalDepth();
                    int var = globalDepth-localDepth;
                    int len = (int) pow(2,var);
                    int addition = (int) pow(2,localDepth);
                    for(int i=0;i<len;i++){
                        directory.put(index,buddy);
                        index+=addition;
                    }
                }
                 int tableSize = (int) pow(2,globalDepth);
                for(int i=0;i<tableSize;i++){
                    if(directory.get(i).getlocalDepth()==globalDepth){
                        return;
                    }
                }
                //if not returned before (means there is no localDepth==globalDepth) then halve directory
                globalDepth--;
                for(int i=tableSize/2; i<tableSize;i++){
                    directory.remove(i);
                }
                
                
            }
       
    }

    public String search(String studentID) {
        String str = studentID.substring(1);
        int id = Integer.parseInt(str);
        int index = hash(id,globalDepth);
        Bucket b = directory.get(index);
        ArrayList<String> list=b.getList();
            if(list.contains(studentID)){
                return String.format("%"+globalDepth+"s", Integer.toBinaryString(index)).replace(' ', '0');
            }
        return "-1"; 
    }

    public void printLab() {
        System.out.println("Global depth : "+globalDepth);
        Set<Entry<Integer,Bucket>> myset=  directory.entrySet();
        int i=0;
        for(HashMap.Entry<Integer,Bucket> e: myset){
                    Bucket bucket = e.getValue();
                    i = e.getKey();
                    System.out.print(String.format("%"+globalDepth+"s", Integer.toBinaryString(i)).replace(' ', '0') +" : [Local depth:"+bucket.getlocalDepth()+"]");
                    ArrayList<String> list = bucket.getList();
                    for(String str:list){
                        System.out.print("<"+str+">");
                    }
                    System.out.println();
               }
    }
    public int hash(int id,int depth){
        int temp = (int) pow(2,depth);
        int index= id % temp;
        return index;
    }

}
