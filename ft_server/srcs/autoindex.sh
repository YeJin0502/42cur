#!/bin/bash

if [ $1 -eq 1 ]; then
		sed -i 's/autoindex off/autoindex on/' $AUTOPATH/default
		sed -i 's/ index.nginx-debian.html/#index.nginx-debian.html/' $AUTOPATH/default
else
		sed -i 's/autoindex on/autoindex off/' $AUTOPATH/default
		sed -i 's/#index.nginx-debian.html/ index.nginx-debian.html/' $AUTOPATH/default
fi
service nginx restart
exit