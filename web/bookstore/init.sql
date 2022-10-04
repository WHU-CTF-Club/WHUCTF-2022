CREATE DATABASE IF NOT EXISTS bookstore;
USE bookstore;

CREATE TABLE IF NOT EXISTS users (
    id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(255) NOT NULL UNIQUE,
    password VARCHAR(255) NOT NULL
);

CREATE TABLE IF NOT EXISTS books (
    id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    title VARCHAR(255) NOT NULL UNIQUE,
    author VARCHAR(255) NOT NULL,
    price INT NOT NULL,
    texts VARCHAR(2048) NOT NULL
);

CREATE TABLE IF NOT EXISTS requests (
    id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    email VARCHAR(255) NOT NULL,
    book_id INT NOT NULL
);

INSERT INTO books(title, author, price, texts) VALUES('Pig Science', 'Palmer J.Holden', 0, 'Pig!!!');
INSERT INTO books(title, author, price, texts) VALUES('How to Improve the Reproductive Benefit of Sows', 'Li', 0, 'Sows!!!');
INSERT INTO books(title, author, price, texts) VALUES('How to raise pigs safely and efficiently', 'hongmei', 0, 'money!!!');
INSERT INTO books(title, author, price, texts) VALUES('Prevention and treatment of swine disease and safe drug use', 'Luo', 0, 'swine fever!!!');
INSERT INTO books(title, author, price, texts) VALUES('How to save WhuCTF', 'NO ONE', 0, 'FLAGE');

CREATE USER 'player'@'%' IDENTIFIED WITH mysql_native_password BY 'Player123!';
GRANT INSERT ON requests TO 'player'@'%';
GRANT SELECT ON *.* TO 'player'@'%';
FLUSH PRIVILEGES;