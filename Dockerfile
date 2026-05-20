################################# Build Stage ##################################
FROM ubuntu:22.04 AS build

# Install development tools
RUN apt-get update && apt-get install -y build-essential cmake gdb \
libboost-dev libboost-program-options-dev && rm -rf /var/lib/apt/lists/*

# Set working directory & copy files
WORKDIR /app
COPY . .

# Create build directory & change into it
RUN mkdir build
WORKDIR /app/build

# CMake commands to configure & build
RUN cmake .. && cmake --build .

################################ Release Stage #################################
FROM ubuntu:22.04 AS release

# Copy the executable from the previous stage
COPY --from=build /app/build/sudoSolve /usr/local/bin/sudoSolve

# Copy boost shared-object files from the previous stage
COPY --from=build /usr/lib/x86_64-linux-gnu/libboost* /usr/lib

# Copy the input files from the previous stage
COPY --from=build /app/input/* /usr/local/input/

# Install minimal runtime dependencies
RUN apt-get update && apt-get install -y libc6 libstdc++6 && \
rm -rf /var/lib/apt/lists/*

# Set the working directory (necessary for relative pathing within
# source code)
WORKDIR /usr/local/bin/

# Set the executable as the main command
ENTRYPOINT ["/usr/local/bin/sudoSolve"]