FROM ubuntu:latest

RUN apt update -qq \
    && apt install apache2 -qqy

ADD ./index.html /var/www/html

EXPOSE 80

CMD ["apache2ctl", "start"]
