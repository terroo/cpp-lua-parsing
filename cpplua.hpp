#ifndef LUACPP_H
#define LUACPP_H

#include <map>
#include <regex>
#include <fstream>

namespace cpp {
  class luaparsing {
    public:
      luaparsing() = delete;
      luaparsing(const std::string& filepath) : luafile(filepath) {}

      void parse() {
        std::ifstream file;
        file.open(luafile);

        if (!file.is_open()) {
          file.close();
          return;
        }

        if (!this->check_ext()) {
          return;
        }

        auto trim = [](std::string& str) {
          str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
              return !std::isspace(ch);
          }));

          str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
              return !std::isspace(ch);
          }).base(), str.end());
        };

        while(std::getline(file, this->currentLine)){
          this->currentLine = remove_comments();
          this->currentLine = empty_lines(this->currentLine);
          this->currentLine = remove_quotes();

          if(!this->currentLine.empty()){
            std::regex pair("(.*)=(.*)");

            std::string key = std::regex_replace(currentLine, pair, "$1");
            std::string value = std::regex_replace(currentLine, pair, "$2");
            
            trim(key);
            trim(value);

            luaVars[key] = value;
          }
        }

        file.close();
      }

      std::string get_value_from_key(const std::string& key) const {
        auto it = luaVars.find(key);

        if (it == luaVars.end()) {
          return "null";
        }

        return luaVars.at(key);
      }

      std::string get_key_from_value(const std::string& value) const {
        for (auto it = luaVars.begin(); it != luaVars.end(); ++it) {
          if (it->second == value) {
            return it->first;
          }
        }

        return "null";
      }

    protected:
      bool check_ext(){
        return this->luafile.substr(this->luafile.length() - 3, 3) == "lua";
      }

      const std::string remove_comments(){
        std::regex comment("(.*)--(.*)");
        return std::regex_replace( this->currentLine, comment, "$1");
      }

      const std::string empty_lines(const std::string& line){
        std::regex blank("^( +)?(.*)( +)?$");
        return std::regex_replace( line, blank, "$2");
      }

      const std::string remove_quotes(){
        std::regex quotes("\"");
        return std::regex_replace( this->currentLine, quotes, "");
      }

      std::string luafile;
      std::string currentLine;
      std::map<std::string, std::string> luaVars;
  };
}

#endif
