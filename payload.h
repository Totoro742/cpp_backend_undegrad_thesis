#ifndef MICROSERVICE_PAYLOAD_H
#define MICROSERVICE_PAYLOAD_H

#include <vector>

using json = nlohmann::json;
namespace {
    struct material {
        int type;
    };

    struct wall {
        double x;
        double y;
        double x2;
        double y2;
        material m;
    };

    struct router {
        double x;
        double y;
        double freq;
    };

    struct canvas {
        double height;
        double width;
        double cellSize;
        double gridDensity;
        double canvasWidth;
    };
    struct payload {
        canvas c;
        std::vector<wall> walls;
        router r;
        std::string solver;
    };

    void from_json(const json& j, material& s) {

        j.at("type").get_to(s.type);

    }

    void from_json(const json& j, wall& s) {
        j.at("x").get_to(s.x);
        j.at("y").get_to(s.y);
        j.at("x2").get_to(s.x2);
        j.at("y2").get_to(s.y2);
        j.at("material").get_to(s.m);
    }

    void from_json(const json& j, router& s) {
        j.at("x").get_to(s.x);
        j.at("y").get_to(s.y);
        j.at("freq").get_to(s.freq);
    }

    void from_json(const json& j, canvas& s) {
        std::cout << "h" << std::endl;
        j.at("height").get_to(s.height);
        j.at("width").get_to(s.width);
        j.at("cellSize").get_to(s.cellSize);
        j.at("gridDensity").get_to(s.gridDensity);
        j.at("canvasLen").get_to(s.canvasWidth);
    }

    void from_json(const json& j, payload& s) {
        j.at("canvas").get_to(s.c);
        j.at("walls").get_to(s.walls);
        j.at("router").get_to(s.r);
        j.at("solver").get_to(s.solver);
    }
}
#endif //MICROSERVICE_PAYLOAD_H
