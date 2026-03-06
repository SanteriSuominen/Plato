#include "project_generator.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>

ProjectGenerator::ProjectGenerator()
{
}

void ProjectGenerator::generate_project(const ProjectRequest& request)
{
    std::filesystem::path path = request.root_path;
    const ProjectOptions opts = request.options;

    if(opts.add_subfolder)
    {
        std::filesystem::create_directory(path / request.project_name);
        path /= request.project_name;
    }

    std::filesystem::create_directory(path);

    std::filesystem::create_directory(path / "src");
    generate_src_file(path / "src/main.cpp");
    
    std::filesystem::create_directory(path / "build");

    if (opts.separate_src_include)
    {
        std::filesystem::create_directory(path / "include");
    }

    if (opts.create_documents)
    {
        std::filesystem::create_directory(path / "documentation");
        generate_documentation_file(path / "documentation/README.md");
    }

    if (opts.generate_makefile)
    {
        generate_makefile(path / "Makefile");
    }
}

void ProjectGenerator::generate_src_file(const std::filesystem::path& path)
{
    std::ofstream src_file(path);
    src_file << "#include <iostream>" << std::endl;
    src_file << "int main()" << std::endl;
    src_file << "{" << std::endl;
    src_file << "    std::cout << \"Hello, World!\" << std::endl;" << std::endl;
    src_file << "    return 0;" << std::endl;
    src_file << "}" << std::endl;
}

void ProjectGenerator::generate_documentation_file(const std::filesystem::path& path)
{
    std::ofstream documentation(path);
    documentation << R"README(# Project Documentation

## Build and Run

### If this project has a Makefile
First time:
```bash
make
```

After code changes:
```bash
make
```

Run:
```bash
make run
```

Clean build artifacts:
```bash
make clean
```

### If this project does not have a Makefile
Build manually:
```bash
g++ src/*.cpp -std=c++20 -Wall -Wextra -pedantic -o app
```

Run:
```bash
./app
```
)README";
}

void ProjectGenerator::generate_makefile(const std::filesystem::path& path)
{
    std::ofstream makefile(path);
    makefile << R"MAKEFILE(CXX ?= g++
CXXFLAGS ?= -std=c++20 -Wall -Wextra -pedantic
CPPFLAGS ?=
LDFLAGS ?=
LDLIBS ?=

SRC_DIR := src
INC_DIR := include
BUILD_DIR := build
TARGET := $(BUILD_DIR)/app

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

ifneq ("$(wildcard $(INC_DIR))","")
CPPFLAGS += -I$(INC_DIR)
endif

.PHONY: all run clean rebuild

all: $(TARGET)

$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

run: all
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean all

-include $(DEPS)
)MAKEFILE";
}