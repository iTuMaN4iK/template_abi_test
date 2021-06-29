
#ifndef STANDALONE_EXPORTS
#include "exports.ipp"
#else
#include "core.hpp"
#include "export_types.hpp"
#endif

#include <dynalo/dynalo.hpp>

#include <filesystem>
#include <iostream>
#include <string_view>
#include <vector>

int main(int argc, char **argv)
{
    std::vector<std::string_view> cli_args(argv, std::next(argv, argc));

    if (cli_args.size() != 2)
    {
        std::cerr << "Path to plugin is not provided.\nUsage: ./app path_to_plugin\n";
        return -1;
    }

    namespace fs = std::filesystem;

    fs::path pluginPath = cli_args[1];
    if (!std::filesystem::exists(pluginPath))
    {
        std::cerr << "Plugin \"" << pluginPath << "\" not found\n";
        return -1;
    }

    // preincrement all the values
    int nonTemplate = non_template();
    int fooClassTemplate = foo_template<old>::get();
    int fooClassFunctionTemplate = foo::get<old>();
    int getTemplateFunction = get<old>();

    try
    {
        dynalo::library plugin{pluginPath.string()};

        auto pNonTemplate = plugin.get_function<int()>("plugin_non_template");
        auto pFooClassTemplate = plugin.get_function<int()>("foo_class_template");
        auto pFooClassFunctionTemplate = plugin.get_function<int()>("foo_class_function_template");
        auto pGetValue = plugin.get_function<int()>("get_value");

        int pluginNonTemplate = pNonTemplate();
        int pluginFooClassTemplate = pFooClassTemplate();
        int pluginFooClassFunctionTemplate = pFooClassFunctionTemplate();
        int pluginGetTemplateFunction = pGetValue();

        std::cout << "Values: Core - Plugin:\nClass template: " <<                    //
                fooClassTemplate + 1 << " : " << pluginFooClassTemplate <<                //
                "\nClass function template: " <<                                      //
                fooClassFunctionTemplate + 1 << " : " << pluginFooClassFunctionTemplate <<//
                "\nFunction template: " <<                                            //
                getTemplateFunction + 1 << " : " << pluginGetTemplateFunction <<
                "\nNon-template function: " << //
                nonTemplate + 1 << " : " << pluginNonTemplate << std::endl;

    } catch (const std::runtime_error &error)
    {
        std::cerr << "Error: " << error.what() << std::endl;
        return -1;
    } catch (const std::exception &exception)
    {
        std::cerr << "Exception: " << exception.what() << std::endl;
        return -1;
    }

    return 0;
}