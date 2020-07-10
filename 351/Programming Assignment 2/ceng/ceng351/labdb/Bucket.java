/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ceng.ceng351.labdb;

import java.util.ArrayList;

/**
 *
 * @author sahin
 */
public class Bucket {
    private int localDepth;
    private int size;
    private ArrayList<String> list;
    public Bucket(int size,int localDepth){
        this.size=size;
        this.localDepth=localDepth;
        list=new ArrayList<String>(size);
    }
    public boolean enterID(String ID){
        if(list.contains(ID)){
            return true;
        }
        if(list.size()<size){
             list.add(ID);
             return true;
        }
        else{
            return false;
        }
    }
    public boolean leaveID(String ID){
            list.remove(ID);
            return list.isEmpty();
    }
    public ArrayList<String> getList(){
        return list;
    }
    public void setList(ArrayList<String> list){
        this.list=list;
    }
    public ArrayList<String> setList(){
        return this.list;
    }
    public void clear(){
        this.list.clear();
    }
    public void setlocalDepth(int localDepth){
        this.localDepth=localDepth;
    }
    public int getlocalDepth(){
        return this.localDepth;
    }

}

