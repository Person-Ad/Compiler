// server.cpp
#include "httplib.h"
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
std::string prepare_code_for_echo(const std::string& code) {
    std::string prepared;
    for (char c : code) {
        if (c == '\n') {
            prepared += "\\n"; // Insert literal backslash + n
        } else if (c == '"') {
            prepared += "\\\""; // Escape double quote
        } else if (c == '\\') {
            prepared += "\\\\"; // Escape backslash itself
        } else {
            prepared += c;
        }
    }
    return prepared;
}
int main()
{
    httplib::Server svr;
    // --- 1) Handle CORS preflight and attach CORS headers to every response ---
    svr.set_pre_routing_handler(
        [](const httplib::Request &req, httplib::Response &res)
        {
            // Allow only your Vite dev origin (or use "*" if you truly want open access)
            res.set_header("Access-Control-Allow-Origin", "http://localhost:5173");
            res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
            res.set_header("Access-Control-Allow-Headers", "Content-Type");
            // If this is a preflight request, mark it handled and return immediately
            if (req.method == "OPTIONS")
            {
                return httplib::Server::HandlerResponse::Handled;
            }
            return httplib::Server::HandlerResponse::Unhandled;
        });

    // Handle both GET /run?code=... and POST /run with body
    svr.Post("/run", [&](const httplib::Request &req, httplib::Response &res)
            {
        if (req.body.empty()) {
            res.status = 400;
            return res.set_content("Missing code in the request body\n", "text/plain");
        }
        std::string code = req.body;

        // Pipe code into base.exe via popen
        // Write the code to a temporary file
        std::ofstream tmpFile("tmp_code.txt");
        if (!tmpFile) {
            res.status = 500;
            return res.set_content("Failed to create temporary file\n", "text/plain");
        }
        tmpFile << code;
        tmpFile.close();

        // Execute base.exe with the temporary file as input
        std::string command = "cmd /c \"base.exe < tmp_code.txt\"";
        int ret_code = system(command.c_str());
        // if (ret_code != 0) {
        //     res.status = 500;
        //     return res.set_content("Failed to execute base.exe. Command: " + command + ", Return code: " + std::to_string(ret_code) + "\n", "text/plain");
        // }

        // Read the output files
        std::ostringstream buf;

        // Read quadruples.txt
        std::ifstream quadruplesFile("quadruples.txt");
        if (quadruplesFile) {
            buf << "=== Quadruples ===\n";
            buf << quadruplesFile.rdbuf();
            buf << "\n";
            quadruplesFile.close();
        } else {
            buf << "Could not open quadruples.txt\n";
        }

        // Read tracked_tables.txt
        std::ifstream trackedTablesFile("tracked_tables.txt");
        if (trackedTablesFile) {
            buf << "=== Tracked Tables ===\n";
            buf << trackedTablesFile.rdbuf();
            buf << "\n";
            trackedTablesFile.close();
        } else {
            buf << "Could not open tracked_tables.txt\n";
        }

        // Read errors_and_warnings.txt
        std::ifstream errorsWarningsFile("errors_and_warnings.txt");
        if (errorsWarningsFile) {
            buf << "=== Errors and Warnings ===\n";
            buf << errorsWarningsFile.rdbuf();
            buf << "\n";
            errorsWarningsFile.close();
        } else {
            buf << "Could not open errors_and_warnings.txt\n";
        }

        res.set_content(buf.str(), "text/plain");
        });

    svr.Get("/st", [&](const httplib::Request &req, httplib::Response &res)
            {
        if (!req.has_param("code")) {
            res.status = 400;
            return res.set_content("Missing `code` parameter\n", "text/plain");
        }
        std::string code = req.get_param_value("code");

        // Pipe code into base.exe via popen
        {
            FILE *proc = popen("base.exe", "w");
            if (!proc) {
                res.status = 500;
                return res.set_content("Failed to launch base.exe\n", "text/plain");
            }
            fputs(code.c_str(), proc);
            pclose(proc);
        }

        // Read the tracked_tables.txt file
        std::ifstream fin("tracked_tables.txt");
        if (!fin) {
            res.status = 500;
            return res.set_content("Could not open tracked_tables.txt\n", "text/plain");
        }
        std::ostringstream buf;
        buf << fin.rdbuf();
        fin.close();

        res.set_content(buf.str(), "text/plain"); });

    // Listen on port 8080
    std::printf("Starting server on http://0.0.0.0:8080\n");
    svr.listen("0.0.0.0", 8080);
    return 0;
}
