#ifndef LUACPP_H
#define LUACPP_H
#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <regex>
#include <sstream>

namespace cpp {
  class luaparsing {

    public:
      std::string luafile;

      luaparsing(){
        this->key = "key";
        this->value = "value";
        this->luafile = "";
      }

      std::string get_value_from_key(const std::string& key){
        this->action = this->key;
        this->name = key;
        return this->readluafile();
      }

      std::string get_key_from_value(const std::string& value){
        this->action = this->value;
        this->name = value;
        return this->readluafile();
      }

      std::string readluafile(){
        this->file.open( this->luafile);
        if( this->file.is_open() && this->check_ext() ){
          while( std::getline( this->file, this->line ) ){
            this->line = remove_comments();
            this->line = empty_lines(this->line);
            this->line = remove_quotes();
            if( !this->line.empty() ){
              if( this->action == "key"){
                if( show_kv( this->line, 0 ) == this->name){
                  return show_kv( this->line, 1 );
                }
              }else if( this->action == "value"){
                if( show_kv( this->line, 1 ) == this->name){
                  return show_kv( this->line, 0 );
                }
              }else{
                this->output << this->line << '\n';
              }
            }
          }
          this->file.close();
        }else{
          this->output << "Failed to open file.\n";
        }
        return this->output.str();
      }

    private:
      std::ifstream file;
      std::string line,token,key,value,action,name;
      std::stringstream output;

    protected:
      bool check_ext(){
        return this->luafile.substr(this->luafile.length() - 3, 3) == "lua";
      }

      const std::string remove_comments(){
        std::regex comment("(.*)--(.*)");
        return std::regex_replace( this->line, comment, "$1");
      }
     
      const std::string empty_lines(const std::string& line){
        std::regex blank("^( +)?(.*)( +)?$");
        return std::regex_replace( line, blank, "$2");
      }

      const std::string remove_quotes(){
        std::regex quotes("\"");
        return std::regex_replace( this->line, quotes, "");
      }

      const std::string show_kv(std::string line,const int& kv){
        std::regex keys("(.*)=(.*)");
        if( kv == 0 ){
          line.erase( std::remove( line.begin() , line.end(), ' ') , line.end() );
          this->token = std::regex_replace( line, keys, "$1");
        }else{
          this->token = std::regex_replace( line, keys, "$2");
          this->token = empty_lines( this->token);
        }
        return this->token;
      }
  };
}
#endif
