#include <grpcpp/grpcpp.h>
#include "fractal.pb.h"
#include "fractal.grpc.pb.h"
#include "FractalEngine.cpp"
#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>

class FractalServiceImpl final : public fractal::FractalService::Service {
private:
    FractalEngine engine;

public:
    grpc::Status Ping(grpc::ServerContext* context, const fractal::PingRequest* request, fractal::PingResponse* response) override {
        // Equivalent to GET /zero (returns empty status 204 equivalent)
        return grpc::Status::OK;
    }

    grpc::Status GenerateFractal(grpc::ServerContext* context, const fractal::FractalRequest* request, fractal::FractalResponse* response) override {
        try {
            int kindParam = request->kind();
            FractalKind fractalKind = FractalKind::mandelbrot;

            switch (kindParam) {
                case 1: fractalKind = FractalKind::mandelbrot; break;
                case 2: fractalKind = FractalKind::julia; break;
                case 3: fractalKind = FractalKind::leaf; break;
                default:
                    return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Invalid fractal kind value.");
            }

            Bounds defaultBounds = (fractalKind == FractalKind::mandelbrot)
                ? Bounds{-2.0, 1.0, -1.2, 1.2}
                : Bounds{-1.5, 1.5, -1.5, 1.5};

            Bounds bounds = defaultBounds;
            if (request->x_max() != 0.0 || request->x_min() != 0.0) {
                bounds = Bounds{request->x_min(), request->x_max(), request->y_min(), request->y_max()};
            }

            int maxIterations = request->max_iterations() > 0 ? request->max_iterations() : 500;

            std::vector<FractalPoint> points = engine.getFractal(fractalKind, bounds, maxIterations);

            for (const auto& pt : points) {
                auto* pointMsg = response->add_points();
                pointMsg->set_x(pt.x);
                pointMsg->set_y(pt.y);
                pointMsg->set_iteration(pt.intensity);
            }

            return grpc::Status::OK;
        } catch (const std::exception& e) {
            return grpc::Status(grpc::StatusCode::INTERNAL, "An unexpected internal server error occurred.");
        }
    }
};

void RunServer() {
    std::string port_str = "50051";
    if (const char* env_port = std::getenv("PORT")) {
        port_str = env_port;
    }
    std::string server_address("0.0.0.0:" + port_str);
    FractalServiceImpl service;

    grpc::ServerBuilder builder;
    
    // Increase maximum message sizes to 64MB to handle large point array responses
    builder.SetMaxReceiveMessageSize(64 * 1024 * 1024);
    builder.SetMaxSendMessageSize(64 * 1024 * 1024);

    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "C++ gRPC Server listening on " << server_address << "...\n";
    server->Wait();
}

int main(int argc, char* argv[]) {
    RunServer();
    return 0;
}