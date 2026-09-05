#include "httplib.h"
#include "FractalEngine.cpp"
#include <iostream>
#include <vector>
#include <string>

int main(int argc, char* argv[]) {
    FractalEngine engine;
    httplib::Server svr;

    // HTTP Interceptor & Global CORS Middleware
    svr.set_pre_routing_handler([](const httplib::Request& req, httplib::Response& res) {
        // 1. Request Logging Interceptor
        std::cout << "[Interceptor] " << req.method << " " << req.path << std::endl;

        // 2. Global CORS Header Policy
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Origin, Content-Type, Accept, Authorization");
        res.set_header("Access-Control-Allow-Credentials", "true");

        // 3. Handle browser preflight OPTIONS requests automatically
        if (req.method == "OPTIONS") {
            res.status = 204; // No Content
            return httplib::Server::HandlerResponse::Handled;
        }

        // Proceed to route handlers
        return httplib::Server::HandlerResponse::Unhandled;
    });

    // Ping / Zero Endpoint
    svr.Get("/zero", [](const httplib::Request&, httplib::Response& res) {
        res.status = 204;
    });

    // Fractal Generation Endpoint
    svr.Get("/api/fractals/generate", [&](const httplib::Request& req, httplib::Response& res) {
        try {
            if (!req.has_param("kind")) {
                res.status = 400;
                res.set_content("{\"error\":{\"type\":\"ValidationException\",\"message\":\"Missing or invalid 'kind' parameter.\"}}", "application/json");
                return;
            }

            int kindParam = std::stoi(req.get_param_value("kind"));
            FractalKind fractalKind = FractalKind::mandelbrot;
            
            switch (kindParam) {
                case 1: fractalKind = FractalKind::mandelbrot; break;
                case 2: fractalKind = FractalKind::julia; break;
                case 3: fractalKind = FractalKind::leaf; break;
                default:
                    res.status = 400;
                    res.set_content("{\"error\":{\"type\":\"ValidationException\",\"message\":\"Invalid fractal kind value.\"}}", "application/json");
                    return;
            }

            Bounds defaultBounds = (fractalKind == FractalKind::mandelbrot)
                ? Bounds{-2.0, 1.0, -1.2, 1.2}
                : Bounds{-1.5, 1.5, -1.5, 1.5};

            Bounds bounds = defaultBounds;
            if (req.has_param("xMin") && req.has_param("xMax") && req.has_param("yMin") && req.has_param("yMax")) {
                bounds = Bounds{
                    std::stod(req.get_param_value("xMin")),
                    std::stod(req.get_param_value("xMax")),
                    std::stod(req.get_param_value("yMin")),
                    std::stod(req.get_param_value("yMax"))
                };
            }

            int maxIterations = 500;
            if (req.has_param("maxIterations")) {
                maxIterations = std::stoi(req.get_param_value("maxIterations"));
            }

            // Generate fractal points using FractalEngine
            std::vector<FractalPoint> points = engine.getFractal(fractalKind, bounds, maxIterations);

            // Serialize points to JSON array
            std::string jsonResponse = "[";
            for (size_t i = 0; i < points.size(); ++i) {
                jsonResponse += points[i].toJson();
                if (i + 1 < points.size()) jsonResponse += ",";
            }
            jsonResponse += "]";

            res.set_content(jsonResponse, "application/json");
            res.status = 200;

        } catch (const std::exception& e) {
            res.status = 500;
            res.set_content("{\"error\":{\"type\":\"ServerError\",\"message\":\"An unexpected internal server error occurred.\"}}", "application/json");
        }
    });

    int port = 8080;
    if (getenv("PORT")) {
        port = std::stoi(getenv("PORT"));
    }

    std::cout << "C++ REST Server listening on port " << port << "...\n";
    svr.listen("0.0.0.0", port);

    return 0;
}