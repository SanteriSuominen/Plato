#pragma once
#include <filesystem>
#include <string>

class ProjectGenerator {
public:
    ProjectGenerator();

    struct ProjectOptions {
        bool separate_src_include{};
        bool generate_makefile{};
        bool create_documents{};
        bool setup_git{};
        bool setup_gitignore{};
        bool add_subfolder{};
    };

    struct ProjectRequest {
        std::filesystem::path root_path;
        std::string project_name;
        ProjectOptions options;
    };

    void generate_project(const ProjectRequest& request);

private:
    void generate_src_file(const std::filesystem::path& path);
    void generate_documentation_file(const std::filesystem::path& path);
    void generate_makefile(const std::filesystem::path& path);
};