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

    void from_json(const json& j, material& m) {

        j.at("type").get_to(m.type);

    }

    void from_json(const json& j, wall& w) {
        j.at("x").get_to(w.x);
        j.at("y").get_to(w.y);
        j.at("x2").get_to(w.x2);
        j.at("y2").get_to(w.y2);
        j.at("material").get_to(w.m);
    }

    void from_json(const json& j, router& r) {
        j.at("x").get_to(r.x);
        j.at("y").get_to(r.y);
        j.at("freq").get_to(r.freq);
    }

    void from_json(const json& j, canvas& c) {
        std::cout << "h" << std::endl;
        j.at("height").get_to(c.height);
        j.at("width").get_to(c.width);
        j.at("cellSize").get_to(c.cellSize);
        j.at("gridDensity").get_to(c.gridDensity);
        j.at("canvasLen").get_to(c.canvasWidth);
    }

    void from_json(const json& j, payload& p) {
        j.at("canvas").get_to(p.c);
        j.at("walls").get_to(p.walls);
        j.at("router").get_to(p.r);
        j.at("solver").get_to(p.solver);
    }
}
#endif //MICROSERVICE_PAYLOAD_H
