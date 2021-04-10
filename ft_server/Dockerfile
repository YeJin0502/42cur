FROM	debian:buster

ENV		AUTOPATH /etc/nginx/sites-available

LABEL	maintainer="yejsong@student.42seoul.kr"

RUN	apt-get update && apt-get install -y \
	nginx \
	mariadb-server \
	php-mysql \
	php-mbstring \
	openssl \
	vim \
	wget \
	php7.3-fpm

COPY	./srcs ./tmp

RUN 	bash /tmp/init.sh

EXPOSE	80 443

ENTRYPOINT bash /tmp/start.sh