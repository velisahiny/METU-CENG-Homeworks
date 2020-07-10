
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ceng.ceng351.bookdb;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author sahin
 */
public class BOOKDB implements IBOOKDB {
    private static String user = "2172179"; // TODO: Your userName
    private static String password = "9ab54864"; //  TODO: Your password
    private static String host = "144.122.71.65"; // host name
    private static String database = "db2172179"; // TODO: Your database name
    private static int port = 8084; // port

    private static Connection connection = null;
    @Override
    public void initialize() {
        String url = "jdbc:mysql://" + host + ":" + port + "/" + database;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection(url, user, password);
            
        } catch (SQLException | ClassNotFoundException e) {
            ;
            e.printStackTrace();
        }
        
    }

    @Override
    public int createTables(){
        int result;
        int numberofTablesInserted = 0;


        //Player(number:integer, teamname:char(20), name:char(30), age:integer, position:char(3))
        String queryCreateAuthorTable = "create table author "
                + "(author_id int not null, author_name varchar(60), primary key(author_id))";
        String queryCreateBookTable = "create table book( "
                + "isbn char(13) not null, "
                + "book_name varchar(120), "
                + "publisher_id int, "
                + "first_publish_year char(4), "
                + "page_count int, "
                + "category varchar(25), "
                + "rating float, "
                + "primary key(isbn),"
                + "foreign key (publisher_id) references publisher(publisher_id))";
        String queryCreatePublisherTable = "create table publisher("
                + "publisher_id int not null, "
                + "publisher_name varchar(50),"
                + "primary key(publisher_id))";
        String queryCreateAuthor_ofTable = "create table author_of("
                + "isbn char(13) not null,"
                + "author_id int ,"
                + "primary key (isbn,author_id), "
                + "foreign key(author_id) references author(author_id),"
                + "foreign key(isbn) references book(isbn))";
        String queryCreatephw1Table = "create table phw1("
                + "isbn char(13) not null, "
                + "book_name varchar(120), "
                + "rating float, "
                + "primary key(isbn))";
        try {
            Statement statement = this.connection.createStatement();

            //Player Table
            result = statement.executeUpdate(queryCreateAuthorTable);
           
            numberofTablesInserted++;
            result = statement.executeUpdate(queryCreatePublisherTable);
        
            numberofTablesInserted++;
            result = statement.executeUpdate(queryCreateBookTable);
            
            numberofTablesInserted++;
            result = statement.executeUpdate(queryCreateAuthor_ofTable);
            
            numberofTablesInserted++;
            result = statement.executeUpdate(queryCreatephw1Table);
            
            numberofTablesInserted++;
            //close
            statement.close();
            
        } catch (SQLException e) {
            
            e.printStackTrace();
        }

        return numberofTablesInserted;
    }

    @Override
    public int dropTables() {
       int result;
        int numberofTablesDropped = 0;

        //Player(number:integer, teamname:char(20), name:char(30), age:integer, position:char(3))
        String queryDropAuthorTable = "drop table if exists author";
        String queryDropPublisherTable = "drop table if exists publisher";
        String queryDropAuthor_ofTable = "drop table if exists author_of";
        String queryDropBookTable = "drop table if exists book";
        String queryDropphw1Table = "drop table if exists phw1";

        try {
            Statement statement = this.connection.createStatement();

            statement.executeUpdate(queryDropphw1Table);
            numberofTablesDropped++;
            
            statement.executeUpdate(queryDropAuthor_ofTable);
            numberofTablesDropped++;
           
            
            statement.executeUpdate(queryDropBookTable);
            numberofTablesDropped++;
         
            
            statement.executeUpdate(queryDropPublisherTable);
            numberofTablesDropped++;
            
            statement.executeUpdate(queryDropAuthorTable);
            numberofTablesDropped++;
            
            //close
            statement.close();
            

        } catch (SQLException e) {
            
            e.printStackTrace();
        }
        
        return numberofTablesDropped; //To change body of generated methods, choose Tools | Templates.
    }
    public void insertAuthor(Author a) throws SQLException {
         String insertIntoAuthor="insert into author values('"+
                 a.getAuthor_id()+"','"+a.getAuthor_name().replaceAll("'","''")+ "')";
             Statement st = this.connection.createStatement();
             st.executeUpdate(insertIntoAuthor);
             st.close();
    }
    @Override
    public int insertAuthor(Author[] authors) {
        int count=0;
       
       
        for(int i=0;i<authors.length ;i++){
            try{
                insertAuthor(authors[i]);
                
                count++;
            }catch(SQLException e){
                
                e.printStackTrace();
            }
        }
        return count;
  
    }
    public void insertBook(Book b) throws SQLException {
         String insertIntoBook="insert into book values('" +
                b.getIsbn() + "','" + 
                b.getBook_name().replaceAll("'","''") + "','"+ 
                b.getPublisher_id()+"','"+
                b.getFirst_publish_year()+"','"+ 
                b.getPage_count()+"','"+
                b.getCategory().replaceAll("'","''")+"','"+
                b.getRating()+ "')";
        
             Statement st = this.connection.createStatement();
             st.executeUpdate(insertIntoBook);
             st.close();
    }
    @Override
    public int insertBook(Book[] books) {
        int count=0;
        for(int i=0;i<books.length ;i++){
            try{
                insertBook(books[i]);
                
                count++;
            }catch(SQLException e){
                
               e.printStackTrace(); 
            }
        }
        return count;
    }
     public void insertPublisher(Publisher p) throws SQLException {
         String insertIntoPublisher="insert into publisher values('" +
                p.getPublisher_id()+"','"+
                p.getPublisher_name().replaceAll("'","''") + "')";
            
             Statement st = this.connection.createStatement();
             st.executeUpdate(insertIntoPublisher);
             st.close();
    }
    @Override
    public int insertPublisher(Publisher[] publishers) {
        int count=0;
        for(int i=0;i<publishers.length ;i++){
            try{
                insertPublisher(publishers[i]);
                
                count++;
            }catch(SQLException e){
                      
                e.printStackTrace();
            }
        }
        return count;
    }
    public void insertAuthor_of(Author_of ao) throws SQLException {
         String insertIntoAuthor_of="insert into author_of values('" +
                ao.getIsbn()+"','"+
                ao.getAuthor_id() + "')";
         
             Statement st = this.connection.createStatement();
             st.executeUpdate(insertIntoAuthor_of);
             st.close();
    }
    @Override
    public int insertAuthor_of(Author_of[] author_ofs) {
        int count=0;
        for(int i=0;i<author_ofs.length ;i++){
            try{
                insertAuthor_of(author_ofs[i]);
                
                count++;
            }catch(SQLException e){
                
                e.printStackTrace();
            }
        }
        return count;
    }
    

    @Override
    public QueryResult.ResultQ1[] functionQ1() {
       
       String query = "select B.isbn, B.first_publish_year, B.page_count, P.publisher_name "
               + "from book B, publisher P "
               + "where B.publisher_id = P.publisher_id and B.page_count= "
               + "(select max(page_count) "
               + " from book) "
               + "order by B.isbn";
       
       ArrayList<QueryResult.ResultQ1> alist = new ArrayList<QueryResult.ResultQ1>() ;
        try {
            Statement st;
            st = this.connection.createStatement();
            ResultSet myset = st.executeQuery(query);
            while(myset.next()){
                String isbn = myset.getString("B.isbn");
                String first_publish_year = myset.getString("B.first_publish_year");
                int page_count = myset.getInt("B.page_count");
                String publisher_name =myset.getString("P.publisher_name");
                
                QueryResult.ResultQ1 r = new QueryResult.ResultQ1(isbn,first_publish_year,page_count,publisher_name);
                
                alist.add(r);
                
            }
            st.close();
            
            
        } catch (SQLException e) {
        
            e.printStackTrace();
        }
        QueryResult.ResultQ1[] Result=new QueryResult.ResultQ1[alist.size()];
        alist.toArray(Result);
        for(int i=0;i< Result.length;i++){
            
        }
       return Result;
    }

    @Override
    public QueryResult.ResultQ2[] functionQ2(int author_id1, int author_id2) {
        String query ="select P.publisher_id, avg(B.page_count) "
                + "from publisher P, book B "
                + "where B.publisher_id=P.publisher_id and P.publisher_id in "
                + "(select B2.publisher_id "
                + "from author_of AO1, author_of AO2, book B2 "
                + "where AO1.author_id='"+author_id1+"' and AO2.author_id='"+author_id2+"' "
                + "and AO1.isbn= AO2.isbn and AO1.isbn=B2.isbn) "
                + "group by P.publisher_id "
                + "order by P.publisher_id";
        ArrayList<QueryResult.ResultQ2> alist = new ArrayList<QueryResult.ResultQ2>();
        try{
            Statement st = this.connection.createStatement();
            ResultSet myset = st.executeQuery(query);
            while(myset.next()){
                int publisher_id = myset.getInt("P.publisher_id");
                double avg_page_count = myset.getDouble("avg(B.page_count)");
                QueryResult.ResultQ2 r =new QueryResult.ResultQ2(publisher_id,avg_page_count);
                alist.add(r);
                
            }
            st.close();
        }catch(SQLException e){
            
            e.printStackTrace();
        }
        QueryResult.ResultQ2[] Result=new QueryResult.ResultQ2[alist.size()];
        alist.toArray(Result);
        
       return Result;
    }

    @Override
    public QueryResult.ResultQ3[] functionQ3(String author_name) {
       String query ="select book_name, category, first_publish_year "
               + "from book B1 "
               + "where B1.isbn in ( select B2.isbn "
               +              "from author A, author_of AO, book B2 "
               +              "where A.author_name='" +author_name + "' and A.author_id=AO.author_id and AO.isbn=B2.isbn ) "
               + ""
               +              "AND B1.first_publish_year = (select min(B3.first_publish_year)"
               +                                            "from author A, author_of AO, book B3 "
               +                                            "where A.author_name='" +author_name + "' and A.author_id=AO.author_id and AO.isbn=B3.isbn ) "
               + "order by book_name, category, first_publish_year";
        ArrayList<QueryResult.ResultQ3> alist = new ArrayList<QueryResult.ResultQ3>();
        try{
            Statement st = this.connection.createStatement();
            ResultSet myset = st.executeQuery(query);
            while(myset.next()){
                String book_name= myset.getString("book_name");
                String category = myset.getString("category");
                String first_publish_year = myset.getString("first_publish_year");
                
                QueryResult.ResultQ3 r =new QueryResult.ResultQ3(book_name,category,first_publish_year);
                alist.add(r);
                
            }
            st.close();
        }catch(SQLException e){
            
            e.printStackTrace();
        }
        QueryResult.ResultQ3[] Result=new QueryResult.ResultQ3[alist.size()];
        alist.toArray(Result);
        
       return Result;
    }

    @Override
    public QueryResult.ResultQ4[] functionQ4() {
        String query="select distinct category, B.publisher_id "
                + "from book B, publisher P "
                + "where B.publisher_id=P.publisher_id and P.publisher_name like '% % %' "
                +   "and B.publisher_id in (select publisher_id "
                +                          "from book "
                +                           "group by publisher_id "
                +                           "having count(*)>=3 ) "
                + "and B.publisher_id in (select publisher_id "
                +                         "from book "
                +                         "group by publisher_id "
                +                         "having avg(rating)>3 ) "
                + "order by publisher_id, category " ;
        ArrayList<QueryResult.ResultQ4> alist = new ArrayList<QueryResult.ResultQ4>();
        try{
            Statement st = this.connection.createStatement();
            ResultSet myset = st.executeQuery(query);
            while(myset.next()){
                String category = myset.getString("category");
                int publisher_id = myset.getInt("B.publisher_id");
                QueryResult.ResultQ4 r =new QueryResult.ResultQ4(publisher_id, category);
                alist.add(r);
                
            }
            st.close();
        }catch(SQLException e){
            
            e.printStackTrace();
        }
        QueryResult.ResultQ4[] Result=new QueryResult.ResultQ4[alist.size()];
        alist.toArray(Result);
       return Result;
        
    }

    @Override
    public QueryResult.ResultQ5[] functionQ5(int author_id) {
        String query ="select author_id, author_name "
                + "from author A "
                + "where not exists (select distinct B1.publisher_id "
                +                  "from author_of AO1, book B1 "
                +                   "where AO1.author_id='"+author_id+"' and AO1.isbn=B1.isbn and "
                +                   " B1.publisher_id  not in "
                +                   "(select distinct B2.publisher_id "
                +                  "from author_of AO2, book B2 "
                +                   "where AO2.author_id=A.author_id and AO2.isbn=B2.isbn ) ) "
                + "order by author_id ";
        
        ArrayList<QueryResult.ResultQ5> alist = new ArrayList<QueryResult.ResultQ5>();
        try {
            Statement st = this.connection.createStatement();
            st.executeQuery(query);
            ResultSet myset = st.executeQuery(query);
            while(myset.next()){
                int id = myset.getInt("author_id");
                String author_name = myset.getString("author_name");
                QueryResult.ResultQ5 r = new QueryResult.ResultQ5(id,author_name);
                alist.add(r);        
            }
            st.close();
            
        } catch (SQLException ex) {
            ex.printStackTrace();
        }
        QueryResult.ResultQ5[] Result=new QueryResult.ResultQ5[alist.size()];
        alist.toArray(Result);
        
       
       return Result;
   
    }

    @Override
    public QueryResult.ResultQ6[] functionQ6() {
        String query=" select A.author_id, AO.isbn "
                + "from author A, author_of AO "
                + "where A.author_id=AO.author_id "
                + "         and not exists (select B.isbn "
                +                          "from author_of AO2, book B "
                +                          "where AO2.isbn=B.isbn and A.author_id=AO2.author_id "
                +                          "and B.publisher_id in "
                +                          "(select B2.publisher_id "
                +                          "from book B2, author_of AO3 "
                +                          "where B2.isbn=AO3.isbn and AO3.author_id<>A.author_id ) ) "
                + "order by A.author_id, AO.isbn ";
        
       
        ArrayList<QueryResult.ResultQ6> alist = new ArrayList<QueryResult.ResultQ6>();
        try {
            Statement st = this.connection.createStatement();
            st.executeQuery(query);
            ResultSet myset = st.executeQuery(query);
            while(myset.next()){
                int author_id = myset.getInt("A.author_id");
                String isbn = myset.getString("AO.isbn");
                QueryResult.ResultQ6 r = new QueryResult.ResultQ6(author_id,isbn);
                alist.add(r);        
            }
            st.close();
            
        } catch (SQLException ex) {
            ex.printStackTrace();
        }
        QueryResult.ResultQ6[] Result=new QueryResult.ResultQ6[alist.size()];
        alist.toArray(Result);
       
       return Result;
    }

    @Override
    public QueryResult.ResultQ7[] functionQ7(double rating) {
        String query =" select B.publisher_id, P.publisher_name "
                + "from book B, publisher P "
                + "where P.publisher_id =B.publisher_id and  B.publisher_id in (select B1.publisher_id "
                +                           "from book B1, book B2 "
                +                           "where B1.publisher_id=B2.publisher_id and B1.isbn<>B2.isbn and B1.category='Roman' and B2.category='Roman')"
                + "group by B.publisher_id "
                + "having avg(rating)>'"+rating+"' "
                + "order by B.publisher_id ";
        
       
        ArrayList<QueryResult.ResultQ7> alist = new ArrayList<QueryResult.ResultQ7>();
        try {
            Statement st = this.connection.createStatement();
            st.executeQuery(query);
            ResultSet myset = st.executeQuery(query);
            while(myset.next()){
                int publisher_id= myset.getInt("B.publisher_id");
                String publisher_name = myset.getString("P.publisher_name");
                QueryResult.ResultQ7 r= new QueryResult.ResultQ7(publisher_id, publisher_name);
                alist.add(r);        
            }
            st.close();
            
        } catch (SQLException ex) {
            ex.printStackTrace();
        }
        QueryResult.ResultQ7[] Result=new QueryResult.ResultQ7[alist.size()];
        alist.toArray(Result);
       
       return Result;
    }

    @Override
    public QueryResult.ResultQ8[] functionQ8() {
        String query="insert into phw1 "
                + "select B.isbn, B.book_name, B.rating "
                + "from book B, (select B1.book_name as b_name, min(B1.rating) as min_rating "
                +               "from book B1, book B2 "
                +               "where B1.isbn<>B2.isbn and B1.book_name=B2.book_name "
                +               "group by B1.book_name ) as Temp "
                + "where B.book_name=Temp.b_name and B.rating = Temp.min_rating ";
        String listquery = "select isbn, book_name, rating "
                +           "from phw1 "
                +           "order by isbn ";
        ArrayList<QueryResult.ResultQ8> alist = new ArrayList<QueryResult.ResultQ8>();
        try {
            Statement st = this.connection.createStatement();
            st.executeUpdate(query);
            ResultSet myset = st.executeQuery(listquery);
            while(myset.next()){
                String isbn =myset.getString("isbn");
                String book_name = myset.getString("book_name");
                double rating = myset.getDouble("rating");
                QueryResult.ResultQ8 r = new QueryResult.ResultQ8(isbn,book_name,rating);
                alist.add(r);        
            }
            st.close();
            
        } catch (SQLException ex) {
            ex.printStackTrace();
        }
        QueryResult.ResultQ8[] Result=new QueryResult.ResultQ8[alist.size()];
        alist.toArray(Result);
        
       return Result;
       
        
    }

    @Override
    public double functionQ9(String keyword) {
        String query=  "update book "
                + "set rating=rating+1 "
                + "where book_name like '%"+keyword+"%' and rating<=4 "; 
        
        String sumquery ="select sum(rating) "
                + "from book";
        double sum=0;
        try {
            Statement st = this.connection.createStatement();
            st.executeUpdate(query);
            ResultSet myset = st.executeQuery(sumquery);
            while(myset.next()){
                sum = myset.getDouble("sum(rating)");
                
            }
            st.close();
            
        } catch (SQLException ex) {
            ex.printStackTrace();
        }
        
        return sum;
        
    }

    @Override
    public int function10() {
         String query =" delete "
                 + "from publisher "
                 + "where publisher_id not in (select publisher_id "
                 +                            "from book )";
        String countquery=" select count(*) "
                +           "from publisher ";
        int sum=0;
        try {
            Statement st = this.connection.createStatement();
            st.executeUpdate(query);
            ResultSet myset = st.executeQuery(countquery);
            while(myset.next()){
                sum = myset.getInt("count(*)");
               
            }
            st.close();
            
        } catch (SQLException ex) {
            ex.printStackTrace();
        }
        
        return sum;
    }
    
}
