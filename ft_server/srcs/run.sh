#!/bin/bash

docker build -t ft_server ../
docker run -it -p 80:80 -p 443:443 ft_server