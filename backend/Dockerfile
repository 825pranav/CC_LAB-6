FROM gcc:latest
RUN apt-get update && apt-get install -y netcat-openbsd
COPY . /usr/src/myapp
WORKDIR /usr/src/myapp
RUN g++ -o myapp app.cpp
# This keeps the app listening for browser requests
CMD ["sh", "-c", "while true; do { echo -e 'HTTP/1.1 200 OK\r\n'; ./myapp; } | nc -lp 8080; done"]
