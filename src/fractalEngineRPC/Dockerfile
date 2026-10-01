# Stage 1: Build environment
FROM debian:bookworm-slim AS builder

RUN apt-get update && apt-get install -y \
    g++ \
    make \
    cmake \
    pkg-config \
    libgrpc++-dev \
    protobuf-compiler-grpc \
    libprotobuf-dev \
    libabsl-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Copy source and protocol files
COPY fractal.proto FractalEngine.cpp FractalDemoRPC.cpp ./

# Generate gRPC stubs
RUN protoc --cpp_out=. --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` fractal.proto

# Compile the gRPC server using pkg-config to automatically pull in Linux gRPC/Abseil flags
RUN g++ -std=c++17 -O3 FractalDemoRPC.cpp fractal.pb.cc fractal.grpc.pb.cc \
    $(pkg-config --cflags --libs grpc++ protobuf) \
    -lpthread \
    -o fractal_grpc_server

# Stage 2: Runtime image
FROM debian:bookworm-slim

WORKDIR /app

RUN apt-get update && apt-get install -y \
    libgrpc++1.51 \
    libprotobuf32 \
    && rm -rf /var/lib/apt/lists/*

COPY --from=builder /app/fractal_grpc_server /app/fractal_grpc_server

EXPOSE 50051

CMD ["./fractal_grpc_server"]