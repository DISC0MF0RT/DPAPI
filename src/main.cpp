#include "../lib/httplib.h"
#include "../lib/nlohmann/json.hpp"
#include "DormandPrince.h"
#include <iostream>

using json = nlohmann::json;

double GM = 398600.4418;
double J2 = 1.08263e-3;
double J4 = -1.6260e-6;
double R = 6378.137;



int main() {
    httplib::Server svr;

    svr.Get("/status", [](const httplib::Request&, httplib::Response& res) {
        json response = {
            {"status", "online"},
            {"version", "1.0"}
        };
        res.set_content(response.dump(), "application/json");
        });


    svr.Post("/solve", [](const httplib::Request& req, httplib::Response& res) {
        try {
            auto input = json::parse(req.body);

            if (!input.contains("t") || !input.contains("h") || !input.contains("t_end") || !input.contains("y")) {
                res.status = 400;
                res.set_content(R"({"error": "Missing required fields: t, h, t_end, y"})", "application/json");
                return;
            }

            double p = 1e-6;
            double t = input["t"];
            double h = input["h"];
            double t_end = input["t_end"];
            State y = {
                input["y"][0], input["y"][1], input["y"][2],
                input["y"][3], input["y"][4], input["y"][5]
            };

            DormandPrince dp(GM, J2, J4, R);

            json results = json::array();
            while (t < t_end) {
                y = dp.solve(t, y, h, p);
                t += h;

                results.push_back({
                    {"t", t},
                    {"state", {y[0], y[1], y[2], y[3], y[4], y[5]}}
                    });
            }

            res.set_content(results.dump(), "application/json");

        }
        catch (const std::exception& e) {
            json error_response = {
                {"error", e.what()}
            };
            res.status = 500;
            res.set_content(error_response.dump(), "application/json");
        }
        });

    std::cout << "Server is running on http://localhost:8080\n";
    svr.listen("0.0.0.0", 8080);

    return 0;
}
