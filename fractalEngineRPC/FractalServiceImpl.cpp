#include <grpcpp/grpcpp.h>
#include "fractal.grpc.pb.h"

class FractalServiceImpl final : public fractal::FractalService::Service {
    grpc::Status GetFractalStream(grpc::ServerContext* context,
                                  const fractal::FractalRequest* request,
                                  grpc::ServerWriter<fractal::FractalChunk>* writer) override {
        int width = request->width();
        int height = request->height();

        for (int y = 0; y < height; ++y) {
            fractal::FractalChunk chunk;
            chunk.set_y_row(y);

            std::string row_data;
            row_data.resize(width * 3); // RGB pixel values
            
            // Populate row_data with computed fractal iteration values...

            chunk.set_pixel_data(row_data);
            if (!writer->Write(chunk)) {
                break; // Client disconnected
            }
        }
        return grpc::Status::OK;
    }
};