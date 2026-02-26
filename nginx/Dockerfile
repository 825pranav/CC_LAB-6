FROM gcc:latest

# Set the working directory
WORKDIR /app

# Copy your source code
COPY app.cpp .

# Compile the app
RUN g++ app.cpp -o app

# Best practice: document the port
EXPOSE 8080

# Run the app
CMD ["./app"]
