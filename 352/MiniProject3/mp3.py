from customer import Customer

import psycopg2

from config import read_config
from messages import *

POSTGRESQL_CONFIG_FILE_NAME = "database.cfg"

"""
    Connects to PostgreSQL database and returns connection object.
"""


def connect_to_db():
    db_conn_params = read_config(filename=POSTGRESQL_CONFIG_FILE_NAME, section="postgresql")
    conn = psycopg2.connect(**db_conn_params)
    conn.autocommit = False
    return conn


"""
    Splits given command string by spaces and trims each token.
    Returns token list.
"""


def tokenize_command(command):
    tokens = command.split(" ")
    return [t.strip() for t in tokens]


"""
    Prints list of available commands of the software.
"""


def help():
    # prints the choices for commands and parameters
    print("\n*** Please enter one of the following commands ***")
    print("> help")
    print("> sign_up <email> <password> <first_name> <last_name> <plan_id>")
    print("> sign_in <email> <password>")
    print("> sign_out")
    print("> show_plans")
    print("> show_subscription")
    print("> subscribe <plan_id>")
    print("> watched_movies <movie_id_1> <movie_id_2> <movie_id_3> ... <movie_id_n>")
    print("> search_for_movies <keyword_1> <keyword_2> <keyword_3> ... <keyword_n>")
    print("> suggest_movies")
    print("> quit")


"""
    Saves customer with given details.
    - Return type is a tuple, 1st element is a boolean and 2nd element is the response message from messages.py.
    - If the operation is successful, commit changes and return tuple (True, CMD_EXECUTION_SUCCESS).
    - If any exception occurs; rollback, do nothing on the database and return tuple (False, CMD_EXECUTION_FAILED).
"""


def sign_up(conn, email, password, first_name, last_name, plan_id):
    # TODO: Implement this function
    sql = "insert into Customer(email, password, first_name, last_name, session_count, plan_id) " + " values ( '" + email + "', '" + password + "' , '" + first_name + "' , '" + last_name + "' , " + " 0 " + " , " + plan_id + ");"
    cursor = conn.cursor()
    try:
        cursor.execute(sql)
        conn.commit()
        return True, CMD_EXECUTION_SUCCESS
    except (Exception, psycopg2.DatabaseError) as error :
        conn.rollback()
        return False, CMD_EXECUTION_FAILED
    finally:
        cursor.close()
    


"""
    Retrieves customer information if email and password is correct and customer's session_count < max_parallel_sessions.
    - Return type is a tuple, 1st element is a customer object and 2nd element is the response message from messages.py.
    - If email or password is wrong, return tuple (None, USER_SIGNIN_FAILED).
    - If session_count < max_parallel_sessions, commit changes (increment session_count) and return tuple (customer, CMD_EXECUTION_SUCCESS).
    - If session_count >= max_parallel_sessions, return tuple (None, USER_ALL_SESSIONS_ARE_USED).
    - If any exception occurs; rollback, do nothing on the database and return tuple (None, USER_SIGNIN_FAILED).
"""


def sign_in(conn, email, password):
    # TODO: Implement this function
    cursor= conn.cursor()
    sql = "select * from Customer where email= '{0}' and password='{1}' for update ;".format(email,password)
    signedCustomer=()
    try:
        cursor.execute(sql)
        signedCustomer = cursor.fetchone()
        if(signedCustomer!=None):
            customer_id, email, _ , first_name , last_name, session_count , plan_id = signedCustomer
            getMaxSessionCount = "select max_parallel_sessions from Plan where plan_id = {0} ;".format(plan_id)
            cursor.execute(getMaxSessionCount)
            maxSessionCount = cursor.fetchone()[0]
            if session_count < maxSessionCount:
                session_count+=1
                increment = "update Customer set session_count = {2} where email= '{0}' and password='{1}';".format(email,password,session_count)
                cursor.execute(increment)
                customer =  Customer(customer_id, email, first_name, last_name, session_count , plan_id)
                conn.commit()
                cursor.close()
                return customer,CMD_EXECUTION_SUCCESS
            else:
                conn.rollback()
                cursor.close()
                return None, USER_ALL_SESSIONS_ARE_USED 
        else :
            conn.rollback()
            cursor.close()
            return None, USER_SIGNIN_FAILED
    except(Exception):
        conn.rollback()
        cursor.close()
        return None, USER_SIGNIN_FAILED
    conn.rollback()
    cursor.close()
    return None, USER_SIGNIN_FAILED
    


"""
    Signs out from given customer's account.
    - Return type is a tuple, 1st element is a boolean and 2nd element is the response message from messages.py.
    - Decrement session_count of the customer in the database.
    - If the operation is successful, commit changes and return tuple (True, CMD_EXECUTION_SUCCESS).
    - If any exception occurs; rollback, do nothing on the database and return tuple (False, CMD_EXECUTION_FAILED).
"""


def sign_out(conn, customer):
    # TODO: Implement this function
    cursor=conn.cursor()
    sql= "select session_count from Customer where email= '{0}' for update ;".format(customer.email)
    try: 
        cursor.execute(sql)
        session_count = cursor.fetchone()[0]
        if session_count>0:
            session_count-=1
            decrement="update Customer set session_count = {0} where email= '{1}';".format(session_count,customer.email)
            cursor.execute(decrement)
            conn.commit()
            cursor.close()
            return True, CMD_EXECUTION_SUCCESS
        conn.rollback()
        cursor.close()
    except(Exception):
        conn.rollback()
        cursor.close()
        return False, CMD_EXECUTION_FAILED
    conn.rollback()
    cursor.close()
    return False, CMD_EXECUTION_FAILED
"""
    Quits from program.
    - Return type is a tuple, 1st element is a boolean and 2nd element is the response message from messages.py.
    - Remember to sign authenticated user out first.
    - If the operation is successful, commit changes and return tuple (True, CMD_EXECUTION_SUCCESS).
    - If any exception occurs; rollback, do nothing on the database and return tuple (False, CMD_EXECUTION_FAILED).
"""


def quit(conn, customer):
    # TODO: Implement this function
    if customer==None:
        return True, CMD_EXECUTION_SUCCESS
    try:
        flag,message = sign_out(conn, customer)
        if flag:
            return True, CMD_EXECUTION_SUCCESS
    except(Exception):
        return False, CMD_EXECUTION_FAILED
    return False, CMD_EXECUTION_FAILED


"""
    Retrieves all available plans and prints them.
    - Return type is a tuple, 1st element is a boolean and 2nd element is the response message from messages.py.
    - If the operation is successful; print available plans and return tuple (True, CMD_EXECUTION_SUCCESS).
    - If any exception occurs; return tuple (False, CMD_EXECUTION_FAILED).

    Output should be like:
    #|Name|Resolution|Max Sessions|Monthly Fee
    1|Basic|720P|2|30
    2|Advanced|1080P|4|50
    3|Premium|4K|10|90
"""


def show_plans(conn):
    # TODO: Implement this function
    cursor= conn.cursor()
    try:
        getPlans = "select * from plan"
        cursor.execute(getPlans)
        print("#|Name|Resolution|Max Sessions|Monthly Fee")
        for plan in cursor:
            print("{0}|{1}|{2}|{3}|{4}".format(plan[0],plan[1],plan[2],plan[3],plan[4]))
        conn.commit()
        cursor.close()
        return True, CMD_EXECUTION_SUCCESS
    except(Exception):
        conn.rollback()
        cursor.close()
        return False, CMD_EXECUTION_FAILED
    conn.rollback()
    cursor.close()
    return False, CMD_EXECUTION_FAILED


"""
    Retrieves authenticated user's plan and prints it. 
    - Return type is a tuple, 1st element is a boolean and 2nd element is the response message from messages.py.
    - If the operation is successful; print the authenticated customer's plan and return tuple (True, CMD_EXECUTION_SUCCESS).
    - If any exception occurs; return tuple (False, CMD_EXECUTION_FAILED).

    Output should be like:
    #|Name|Resolution|Max Sessions|Monthly Fee
    1|Basic|720P|2|30
"""


def show_subscription(conn, customer):
    # TODO: Implement this function
    cursor= conn.cursor()
    if(customer!=None):
        try:
            getSubscription = "select * from plan where plan_id= {0} ".format(customer.plan_id)
            cursor.execute(getSubscription)
            print("#|Name|Resolution|Max Sessions|Monthly Fee")
            plan = cursor.fetchone()
            print("{0}|{1}|{2}|{3}|{4}".format(plan[0],plan[1],plan[2],plan[3],plan[4]))
            conn.commit()
            cursor.close()
            return True, CMD_EXECUTION_SUCCESS
        except(Exception):
            conn.rollback()
            cursor.close() 
            return False, CMD_EXECUTION_FAILED
    else:
        conn.rollback()
        cursor.close() 
        return False, CMD_EXECUTION_FAILED

"""
    Insert customer-movie relationships to Watched table if not exists in Watched table.
    - Return type is a tuple, 1st element is a boolean and 2nd element is the response message from messages.py.
    - If a customer-movie relationship already exists, do nothing on the database and return (True, CMD_EXECUTION_SUCCESS).
    - If the operation is successful, commit changes and return tuple (True, CMD_EXECUTION_SUCCESS).
    - If any one of the movie ids is incorrect; rollback, do nothing on the database and return tuple (False, CMD_EXECUTION_FAILED).
    - If any exception occurs; rollback, do nothing on the database and return tuple (False, CMD_EXECUTION_FAILED).
"""


def watched_movies(conn, customer, movie_ids):
    # TODO: Implement this function
    cursor= conn.cursor()
    try:
        getWatched= "select movie_id from watched where customer_id= {0};".format(customer.customer_id)
        cursor.execute(getWatched)
        movieList=list()
        for record in cursor:
            movieList.append(record[0])
        for movie_id in movie_ids:
            movie_id= movie_id.replace("\"","")
            if not (movie_id in movieList):
                checkMovie= "select * from Movies where movie_id = '{0}';".format(movie_id)
                cursor.execute(checkMovie)
                movie=cursor.fetchone()
                if movie!=None:
                    sql ="insert into watched values ({0}, '{1}' );".format(customer.customer_id,movie_id)
                    cursor.execute(sql)
                else:
                    conn.rollback()
                    cursor.close()
                    return False, CMD_EXECUTION_FAILED
        conn.commit()
        cursor.close()
        return True, CMD_EXECUTION_SUCCESS
    except(Exception) as ex:
        conn.rollback()
        cursor.close()
        return False, CMD_EXECUTION_FAILED
    conn.rollback()
    cursor.close()
    return False, CMD_EXECUTION_FAILED


"""
    Subscribe authenticated customer to new plan.
    - Return type is a tuple, 1st element is a customer object and 2nd element is the response message from messages.py.
    - If target plan does not exist on the database, return tuple (None, SUBSCRIBE_PLAN_NOT_FOUND).
    - If the new plan's max_parallel_sessions < current plan's max_parallel_sessions, return tuple (None, SUBSCRIBE_MAX_PARALLEL_SESSIONS_UNAVAILABLE).
    - If the operation is successful, commit changes and return tuple (customer, CMD_EXECUTION_SUCCESS).
    - If any exception occurs; rollback, do nothing on the database and return tuple (None, CMD_EXECUTION_FAILED).
"""


def subscribe(conn, customer, plan_id):
    # TODO: Implement this function
    cursor= conn.cursor()
    lockCustomer = "select * from Customer where customer_id= {0} for update;".format(customer.customer_id)
    demandedPlan= "select * from plan where plan_id= {0} ;".format(plan_id)
    try:
        cursor.execute(lockCustomer)
        cursor.execute(demandedPlan)
        targetPlan = cursor.fetchone()
        if targetPlan==None:
            conn.rollback()
            cursor.close()
            return None, SUBSCRIBE_PLAN_NOT_FOUND
        else:
            getCurrentPlan =" select * from plan where plan_id ={0};".format(customer.plan_id)
            cursor.execute(getCurrentPlan)
            currentPlan = cursor.fetchone()
            currentMaxSession =  currentPlan[3]
            targetMaxSession = targetPlan[3]
            if currentMaxSession>targetMaxSession:
                conn.rollback()
                cursor.close()
                return None, SUBSCRIBE_MAX_PARALLEL_SESSIONS_UNAVAILABLE
            else:
                subscribe = "update Customer set plan_id = {0} where customer_id= {1};".format(plan_id, customer.customer_id)
                cursor.execute(subscribe)
                customer.plan_id=plan_id
                conn.commit()
                cursor.close()
                return customer, CMD_EXECUTION_SUCCESS
    except(Exception):
        return None, CMD_EXECUTION_FAILED
    return None, CMD_EXECUTION_FAILED

"""
    Searches for movies with given search_text.
    - Return type is a tuple, 1st element is a boolean and 2nd element is the response message from messages.py.
    - Print all movies whose titles contain given search_text IN CASE-INSENSITIVE MANNER.
    - If the operation is successful; print movies found and return tuple (True, CMD_EXECUTION_SUCCESS).
    - If any exception occurs; return tuple (False, CMD_EXECUTION_FAILED).

    Output should be like:
    Id|Title|Year|Rating|Votes|Watched
    "tt0147505"|"Sinbad: The Battle of the Dark Knights"|1998|2.2|149|0
    "tt0468569"|"The Dark Knight"|2008|9.0|2021237|1
    "tt1345836"|"The Dark Knight Rises"|2012|8.4|1362116|0
    "tt3153806"|"Masterpiece: Frank Millers The Dark Knight Returns"|2013|7.8|28|0
    "tt4430982"|"Batman: The Dark Knight Beyond"|0|0.0|0|0
    "tt4494606"|"The Dark Knight: Not So Serious"|2009|0.0|0|0
    "tt4498364"|"The Dark Knight: Knightfall - Part One"|2014|0.0|0|0
    "tt4504426"|"The Dark Knight: Knightfall - Part Two"|2014|0.0|0|0
    "tt4504908"|"The Dark Knight: Knightfall - Part Three"|2014|0.0|0|0
    "tt4653714"|"The Dark Knight Falls"|2015|5.4|8|0
    "tt6274696"|"The Dark Knight Returns: An Epic Fan Film"|2016|6.7|38|0
"""


def search_for_movies(conn, customer, search_text):
    # TODO: Implement this function
    cursor = conn.cursor()
    if customer==None:
        conn.rollback()
        cursor.close()
        return False, CMD_EXECUTION_FAILED
    searchSQL = "select * from movies where lower(title) like lower('%{0}%');".format(search_text)
    try:
        cursor.execute(searchSQL)
        searchedMovies=cursor.fetchall()
        print("Id|Title|Year|Rating|Votes|Watched")
        for movie in searchedMovies:
            checkWatched="select * from watched where movie_id='{0}' and customer_id={1};".format(movie[0], customer.customer_id)
            cursor.execute(checkWatched)
            getFirst = cursor.fetchone()
            watched=0
            if(getFirst!=None):
                watched=1
            print("{0}|{1}|{2}|{3:.1f}|{4}|{5}".format(movie[0],movie[1],movie[2],movie[3],movie[4],watched))
        conn.commit()
        cursor.close()
        return True, CMD_EXECUTION_SUCCESS
    except(Exception) as ex:
        print(ex)
        conn.rollback()
        cursor.close()
        return False, CMD_EXECUTION_FAILED  
    conn.rollback()
    cursor.close()          
    return False, CMD_EXECUTION_FAILED


"""
    Suggests combination of these movies:
        1- Find customer's genres. For each genre, find movies with most number of votes among the movies that the customer didn't watch.

        2- Find top 10 movies with most number of votes and highest rating, such that these movies are released 
           after 2010 ( [2010, today) ) and the customer didn't watch these movies.
           (descending order for votes, descending order for rating)

        3- Find top 10 movies with votes higher than the average number of votes of movies that the customer watched.
           Disregard the movies that the customer didn't watch.
           (descending order for votes)

    - Return type is a tuple, 1st element is a boolean and 2nd element is the response message from messages.py.    
    - Output format and return format are same with search_for_movies.
    - Order these movies by their movie id, in ascending order at the end.
    - If the operation is successful; print movies suggested and return tuple (True, CMD_EXECUTION_SUCCESS).
    - If any exception occurs; return tuple (False, CMD_EXECUTION_FAILED).
"""


def suggest_movies(conn, customer):
    # TODO: Implement this function
    cursor=conn.cursor()
    if(customer==None):
        cursor.close()
        return False, CMD_EXECUTION_FAILED
    getGenres= "select distinct genre_name from genres g, watched w where w.customer_id={0} and w.movie_id= g.movie_id;".format(customer.customer_id)
    try:
        suggestionSet=set()
        cursor.execute(getGenres)
        genreList=list()
        for genre in cursor:
            genreList.append(genre[0])
        createView= "create or replace view  myView as select * from movies m where not exists ( select * from watched w2 where w2.customer_id ={0} and w2.movie_id =m.movie_id );".format(customer.customer_id)
        cursor.execute(createView)
        getMaxVotesForGenres = "select g.genre_name ,max(votes) from myView mv,genres g where g.movie_id =mv.movie_id group by g.genre_name;"
        cursor.execute(getMaxVotesForGenres)
        suggestionGenreMaxList = list()
        for record in cursor:
            if record[0] in genreList:
                suggestionGenreMaxList.append(record)
        for record in suggestionGenreMaxList:
            getSuggestion="select mv.movie_id, title, movie_year,rating,votes from myView mv , genres g where mv.movie_id = g.movie_id and g.genre_name = '{0}' and mv.votes= {1} ;".format(record[0],record[1])
            cursor.execute(getSuggestion)
            suggestion = cursor.fetchone()
            suggestionSet.add(suggestion)
        step2SQL = "select * from myview mv where mv.movie_year> 2009 order by votes desc, rating desc limit 10;"
        cursor.execute(step2SQL)
        for record in cursor:
            suggestionSet.add(record)
        getAvgVotes="select avg(votes) from movies m ,watched w where m.movie_id =w.movie_id and w.customer_id ={0} group by w.customer_id;".format(customer.customer_id)
        cursor.execute(getAvgVotes)
        avgVotes = cursor.fetchone()[0]
        step3SQL="select * from myview  where votes>{0} order by votes desc limit 10;".format(avgVotes)
        cursor.execute(step3SQL)
        for record in cursor:
            suggestionSet.add(record)
        print("Id|Title|Year|Rating|Votes")
        for sug in sorted(suggestionSet):
            print("{0}|{1}|{2}|{3:.1f}|{4}".format(sug[0],sug[1],sug[2],sug[3],sug[4]))
        conn.commit()
        cursor.close()
        return True, CMD_EXECUTION_SUCCESS
    except(Exception) as ex:
        conn.rollback()
        cursor.close()
        return False, CMD_EXECUTION_FAILED
    cursor.close()    
    return False, CMD_EXECUTION_FAILED
