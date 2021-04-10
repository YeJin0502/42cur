CREATE DATABASE wordpress;
CREATE USER 'yejsong'@'localhost' IDENTIFIED BY 'yejsong';
GRANT ALL ON wordpress.* TO 'yejsong'@'localhost';
FLUSH PRIVILEGES;