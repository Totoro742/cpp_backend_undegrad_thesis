#include <iostream>
#include <MES.h>
#include "crow.h"
#include "crow/middlewares/cors.h"
#include <Magick++.h>
#include "nlohmann/json.hpp"
#include "payload.h"
#include <cstdio>

using json = nlohmann::json;

std::string generateHeatmap(payload p) {


    const double width = p.c.canvasWidth;
    const double height = width * (double(p.c.height) / double(p.c.width));

    double dx = (p.c.cellSize / p.c.width * width) / (p.c.gridDensity - 1);
    std::cout << dx << std::endl;
    mes::baseFuncType baseFunc;

    if (p.solver == "lin") {
        baseFunc = mes::baseFuncType::LIN;
    } else if (p.solver == "quad") {
        baseFunc = mes::baseFuncType::QUAD;
    }

    mes::solver::Solver solver(baseFunc, p.r.freq);

    solver.setMeshSize(width, height, dx).setImageSize((int) p.c.width, (int) p.c.height);

    auto xIRL = [&p, &width](auto point) { return (point / p.c.width - .5) * width; };
    auto yIRL = [&p, &height](auto point) { return (.5 - point / p.c.height) * height; };

    for (auto &wall: p.walls) {
        double leftDownX = wall.x < wall.x2 ? wall.x : wall.x2;
        double rightUpX = wall.x > wall.x2 ? wall.x : wall.x2;
        double leftDownY = wall.y > wall.y2 ? wall.y : wall.y2;
        double rightUpY = wall.y < wall.y2 ? wall.y : wall.y2;

        solver.addWall(mes::Wall::createFromCorners(xIRL(leftDownX),
                                                    yIRL(leftDownY),
                                                    xIRL(rightUpX),
                                                    yIRL(rightUpY),
                                                    mes::elementType(wall.m.type)));
    }
    std::cout << "initDampWalls" << std::endl;

    solver.buildStructure(true).computeSolver(true).solve(xIRL(p.r.x), yIRL(p.r.y));
    std::cout << "abs result range: [" << 0 << ", " << solver.getMaxValue() << "]\n";
    std::cout << "draw" << std::endl;
    std::string filename = solver.draw();
    std::string path = "./temp/" + filename;

    Magick::Image image;
    image.negate(true);
    Magick::Blob blob;
    image.read(path);

    image.write(&blob);

    std::remove(path.c_str());

    return blob.base64();
}

int main() {
    Magick::InitializeMagick(nullptr);


    crow::App<crow::CORSHandler> app;

    CROW_ROUTE(app, "/").methods(crow::HTTPMethod::POST)([](const crow::request &request) {
        crow::response res;
        // res.add_header("Content-Type", "image/jpeg");
        std::string body = request.body;
        json body_json = json::parse(body);
        std::cout << body_json.dump(4);
        auto bodyPayload = body_json.template get<payload>();

        auto heatmap = generateHeatmap(bodyPayload);
        res.body = heatmap;
        return res;
    });

    app.bindaddr("::1").port(3002).multithreaded().run();

}
