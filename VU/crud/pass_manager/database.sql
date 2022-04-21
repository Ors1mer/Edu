CREATE DATABASE passwordsDB;
USE passwordsDB;

CREATE TABLE users (
    user_id INT NOT NULL AUTO_INCREMENT,
    user VARCHAR(40) NOT NULL,
    PRIMARY KEY(user_id)
);

CREATE TABLE passwords (
    pass_id INT NOT NULL AUTO_INCREMENT,
    password VARCHAR(256) NOT NULL,
    user_id INT,
    PRIMARY KEY(pass_id),
    FOREIGN KEY(user_id) REFERENCES users(user_id)
);
