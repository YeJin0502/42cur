#!/bin/bash

if [ $1 -eq 1 ]; then
		sed -i 's/autoindex off/autoindex on/' $AUTOPATH/default
		mv /var/www/html/index.html /var/www/html/index.nginx-debian.html
else
		sed -i 's/autoindex on/autoindex off/' $AUTOPATH/default
		mv /var/www/html/index.nginx-debian.html /var/www/html/index.html
fi
service nginx restart
exit