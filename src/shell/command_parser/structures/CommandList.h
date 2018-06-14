//
// Created by Daniel Bigos on 14.06.18.
//

#ifndef UXP1A_SHELL_COMMANDLIST_H
#define UXP1A_SHELL_COMMANDLIST_H

#include "Command.h"
#include <vector>

namespace shell::parser::structures
{
    class CommandList
    {
    public:
        explicit CommandList() = default;
        virtual ~CommandList() = default;

        std::vector< std::unique_ptr< Command > > &getCommands();
        void addCommand( std::unique_ptr< Command > &command );
    private:
        std::vector< std::unique_ptr< Command > > commands_;

    };
}

#endif //UXP1A_SHELL_COMMANDLIST_H
