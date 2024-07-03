# SQL Injection

## Union Based Attacks
 When an application is vulnerable to SQL injection, and the results of the query are returned within the application's responses, you can use the UNION keyword to retrieve data from other tables within the database. This is commonly known as a SQL injection UNION attack.

 ```sql
SELECT a, b FROM table1 UNION SELECT c, d FROM table2
```

