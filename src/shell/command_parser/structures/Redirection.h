//
// Created by Daniel Bigos on 13.06.18.
//

#ifndef UXP1A_SHELL_REDIRECTION_H
#define UXP1A_SHELL_REDIRECTION_H

#include <string>

namespace shell::parser::structures
{
    class Redirection
    {
    public:
        explicit Redirection( const std::string &path );
        virtual ~Redirection() = default;

        std::string getPath();
    private:
        std::string path_;

    };

}
#endif //UXP1A_SHELL_REDIRECTION_H
